
#include "OSGBaseInitFunctions.h"
#include "OSGNode.h"
#include "OSGNodeFields.h"
#include "OSGNodeCore.h"
#include "OSGVCoREItem.h"
#include "OSGVecSFields.h"

#define DO_DUMP_ASPECTS 1

const OSG::UInt32 uiNumAspects = 4;

OSG::ChangeList *vAspectChangeList[3];

void dumpAspect(VCoRE::Item *pFC, OSG::UInt32 uiAspect)
{
    OSG::UInt32 uiCurrAspect= OSG::Thread::getCurrentAspect();

    OSG::Thread::setAspectTo(uiAspect);

#ifdef OSG_MT_CPTR_ASPECT
    VCoRE::Item *pAFC = OSG::convertToCurrentAspect(pFC);
#else
    VCoRE::Item *pAFC = getCPtr(pFC);
#endif

    if(pAFC != NULL)
    {
        pAFC->dump();
    }
    else
    {
        fprintf(stderr, "No Aspect Ptr\n");
    }

    OSG::Thread::setAspectTo(uiCurrAspect);
}

void dumpAspects(VCoRE::Item *pFC)
{
#ifdef DO_DUMP_ASPECTS
    for(OSG::UInt32 i = 0; i < uiNumAspects; ++i)
    {
        fprintf(stderr, "Aspect %d\n", i);

        dumpAspect(pFC, i);
    }
#endif
}

void applyToAspect(OSG::UInt32 uiAspect, bool bClear = false)
{
    OSG::commitChanges();

    OSG::Thread::setAspectTo    (uiAspect);
    OSG::Thread::setChangelistTo(vAspectChangeList[uiAspect]);

    vAspectChangeList[0]->applyNoClear();

    OSG::commitChangesAndClear();

    OSG::Thread::setAspectTo    (0);
    OSG::Thread::setChangelistTo(vAspectChangeList[0]);

    if(bClear == true)
        OSG::Thread::getCurrentChangeList()->clear();
}

template<class FieldT>
void setValueSField(typename FieldT::StoredType  val,
                             VCoRE::Item        *pFC,
                             OSG::UInt32         uiFieldId)
{
    typedef typename FieldT::EditHandle    TypedEditHandle;
    typedef typename FieldT::EditHandlePtr TypedEditHandlePtr;

    OSG::EditFieldHandlePtr pFH = pFC->editDynamicField(uiFieldId);

    TypedEditHandlePtr pTypedHandle = 
        boost::dynamic_pointer_cast<TypedEditHandle>(pFH);

    if(pTypedHandle != NULL && pTypedHandle->isValid() == true)
    {
        (*pTypedHandle)->setValue(val);
    }
}

template<class FieldT>
void setPtrSField(typename FieldT::StoredType  val,
                           VCoRE::Item        *pFC,
                           OSG::UInt32         uiFieldId)
{
    typedef typename FieldT::EditHandle    TypedEditHandle;
    typedef typename FieldT::EditHandlePtr TypedEditHandlePtr;

    OSG::EditFieldHandlePtr pFH = pFC->editDynamicField(uiFieldId);

    TypedEditHandlePtr pTypedHandle = 
        boost::dynamic_pointer_cast<TypedEditHandle>(pFH);

    if(pTypedHandle != NULL && pTypedHandle->isValid() == true)
    {
        pTypedHandle->set(val);
    }
}


template<class FieldT>
void setValueMField(typename FieldT::StoredType *aVals,
                             OSG::UInt32         uiNumVals,
                             VCoRE::Item        *pFC,
                             OSG::UInt32         uiFieldId)
{
    typedef typename FieldT::EditHandle    TypedEditHandle;
    typedef typename FieldT::EditHandlePtr TypedEditHandlePtr;

    OSG::EditFieldHandlePtr pFH = pFC->editDynamicField(uiFieldId);

    TypedEditHandlePtr pTypedHandle = 
        boost::dynamic_pointer_cast<TypedEditHandle>(pFH);

    if(pTypedHandle != NULL && pTypedHandle->isValid() == true)
    {
        (*pTypedHandle)->clear();

        for(OSG::UInt32 i = 0; i < uiNumVals; ++i)
            (*pTypedHandle)->push_back(aVals[i]);
    }
}

template<class FieldT, class ValueT>
void setPtrMField(ValueT         *aVals,
                  OSG::UInt32     uiNumVals,
                  VCoRE::Item    *pFC,
                  OSG::UInt32     uiFieldId)
{
    typedef typename FieldT::EditHandle    TypedEditHandle;
    typedef typename FieldT::EditHandlePtr TypedEditHandlePtr;

    OSG::EditFieldHandlePtr pFH = pFC->editDynamicField(uiFieldId);

    TypedEditHandlePtr pTypedHandle = 
        boost::dynamic_pointer_cast<TypedEditHandle>(pFH);

    if(pTypedHandle != NULL && pTypedHandle->isValid() == true)
    {
        pTypedHandle->clear();

        for(OSG::UInt32 i = 0; i < uiNumVals; ++i)
            pTypedHandle->add(aVals[i]);
    }
}

void testValField(void)
{
    fprintf(stderr, "sharing\n===============================\n\n");
    fprintf(stderr, "%"PRIUSize"\n", sizeof(VCoRE::Item));

    VCoRE::ItemRecPtr pTestFC = VCoRE::Item::create();

    fprintf(stderr, "sharing | created\n===============================\n\n");

    dumpAspects(pTestFC);

#ifdef DO_DUMP_CHANGELIST
    OSG::Thread::getCurrentChangeList()->dump();
#endif

    OSG::UInt32 fSIdx = pTestFC->addField(
        OSG::SFUInt32::getClassType().getId(),
        "testSField");

    fprintf(stderr, "added sfield %d\n===============================\n\n", 
            fSIdx);

#ifdef DO_DUMP_CHANGELIST
    OSG::Thread::getCurrentChangeList()->dump();
#endif

    dumpAspects(pTestFC);


    setValueSField<OSG::SFUInt32>(42, pTestFC, fSIdx);


#ifdef DO_DUMP_CHANGELIST
    OSG::Thread::getCurrentChangeList()->dump();
#endif
    OSG::Thread::getCurrentChangeList()->commitChanges();
#ifdef DO_DUMP_CHANGELIST
    OSG::Thread::getCurrentChangeList()->dump();
#endif

    fprintf(stderr, "sharing | filled\n===============================\n\n");

    dumpAspects(pTestFC);

    fprintf(stderr, "sharing | apply\n===============================\n\n");

    applyToAspect(1);
    applyToAspect(2, true);

    dumpAspects(pTestFC);

    applyToAspect(1);
    applyToAspect(2, true);

    dumpAspects(pTestFC);






    OSG::UInt32 fMIdx = pTestFC->addField(
        OSG::MFUInt32::getClassType().getId(),
        "testMField");

    fprintf(stderr, "added mfield %d\n===============================\n\n", 
            fMIdx);

    OSG::Thread::getCurrentChangeList()->commitChanges();

    dumpAspects(pTestFC);

    applyToAspect(1);
    applyToAspect(2, true);

    fprintf(stderr, "synced mfield\n===============================\n\n");

    dumpAspects(pTestFC);

    {
        OSG::UInt32 uiVals[3] = { 10, 11, 12 };

        setValueMField<OSG::MFUInt32>(uiVals, 3, pTestFC, fMIdx);
    }

    fprintf(stderr, "changed mfield\n===============================\n\n");

    dumpAspects(pTestFC);


    applyToAspect(1);
    applyToAspect(2, true);

    fprintf(stderr, "synced mfield\n===============================\n\n");

    dumpAspects(pTestFC);


    setValueSField<OSG::SFUInt32>(21, pTestFC, fSIdx);
    {
        OSG::UInt32 uiVals[3] = { 5, 6, 7 };

        setValueMField<OSG::MFUInt32>(uiVals, 3, pTestFC, fMIdx);
    }

    fprintf(stderr, "changed mfield\n===============================\n\n");

    dumpAspects(pTestFC);


    applyToAspect(1);
    applyToAspect(2, true);

    fprintf(stderr, "synced mfield\n===============================\n\n");

    dumpAspects(pTestFC);


    pTestFC = NULL;

    applyToAspect(1);
    applyToAspect(2, true);
}



void testPtrField(void)
{
    fprintf(stderr, "sharing\n===============================\n\n");
    fprintf(stderr, "%"PRIUSize"\n", sizeof(VCoRE::Item));

    VCoRE::ItemRecPtr pTestFC = VCoRE::Item::create();

    fprintf(stderr, "sharing | created\n===============================\n\n");

    dumpAspects(pTestFC);

#ifdef DO_DUMP_CHANGELIST
    OSG::Thread::getCurrentChangeList()->dump();
#endif

    OSG::UInt32 fSIdx = pTestFC->addField(
        OSG::SFUnrecNodePtr::getClassType().getId(),
        "testSField");

    fprintf(stderr, "added sfield %d\n===============================\n\n", 
            fSIdx);

#ifdef DO_DUMP_CHANGELIST
    OSG::Thread::getCurrentChangeList()->dump();
#endif

    dumpAspects(pTestFC);

    OSG::NodeUnrecPtr pNode = OSG::Node::create();

    setPtrSField<OSG::SFUnrecNodePtr>(pNode, pTestFC, fSIdx);

    pNode = NULL;

#ifdef DO_DUMP_CHANGELIST
    OSG::Thread::getCurrentChangeList()->dump();
#endif
    OSG::Thread::getCurrentChangeList()->commitChanges();
#ifdef DO_DUMP_CHANGELIST
    OSG::Thread::getCurrentChangeList()->dump();
#endif

    fprintf(stderr, "sharing | filled\n===============================\n\n");

    dumpAspects(pTestFC);

    fprintf(stderr, "sharing | apply\n===============================\n\n");

    applyToAspect(1);
    applyToAspect(2, true);

    dumpAspects(pTestFC);

    applyToAspect(1);
    applyToAspect(2, true);

    dumpAspects(pTestFC);






    OSG::UInt32 fMIdx = pTestFC->addField(
        OSG::MFUnrecNodePtr::getClassType().getId(),
        "testMField");

    fprintf(stderr, "added mfield %d\n===============================\n\n", 
            fMIdx);

    OSG::Thread::getCurrentChangeList()->commitChanges();

    dumpAspects(pTestFC);

    applyToAspect(1);
    applyToAspect(2, true);

    fprintf(stderr, "synced mfield\n===============================\n\n");

    dumpAspects(pTestFC);

    {
        OSG::NodeUnrecPtr pVals[3] = { OSG::Node::create(), 
                                       OSG::Node::create(),
                                       OSG::Node::create() };

        setPtrMField<OSG::MFUnrecNodePtr, OSG::NodeUnrecPtr>(pVals, 
                                                             3, 
                                                             pTestFC, 
                                                             fMIdx);
    }

    fprintf(stderr, "changed mfield\n===============================\n\n");

    dumpAspects(pTestFC);


    applyToAspect(1);
    applyToAspect(2, true);

    fprintf(stderr, "synced mfield\n===============================\n\n");

    dumpAspects(pTestFC);

    pNode = OSG::Node::create();

    setPtrSField<OSG::SFUnrecNodePtr>(pNode, pTestFC, fSIdx);

    pNode = NULL;

    {
        OSG::NodeUnrecPtr pVals[3] = { OSG::Node::create(),
                                       OSG::Node::create(),
                                       OSG::Node::create() };

        setPtrMField<OSG::MFUnrecNodePtr, OSG::NodeUnrecPtr>(pVals, 
                                                             3, 
                                                             pTestFC, 
                                                             fMIdx);
    }

    fprintf(stderr, "changed mfield\n===============================\n\n");

    dumpAspects(pTestFC);


    applyToAspect(1);
    applyToAspect(2, true);

    fprintf(stderr, "synced mfield\n===============================\n\n");

    dumpAspects(pTestFC);


    pTestFC = NULL;

    applyToAspect(1);
    applyToAspect(2, true);
}


void testCreate(void)
{
    fprintf(stderr, "create\n");
    fprintf(stderr, "%"PRIUSize"\n", sizeof(VCoRE::Item));

    VCoRE::ItemRecPtr pTestFC = VCoRE::Item::create();

    fprintf(stderr, "sharing | created\n");

    dumpAspects(pTestFC);


#ifdef DO_DUMP_CHANGELIST
    OSG::Thread::getCurrentChangeList()->dump();
#endif

    {
        OSG::UInt32 fIdx = pTestFC->addField(
            OSG::SFVec3f::getClassType().getId(),
            "testField");

        fprintf(stderr, "added field %d\n", fIdx);
    }

#ifdef DO_DUMP_CHANGELIST
    OSG::Thread::getCurrentChangeList()->dump();
#endif
    OSG::Thread::getCurrentChangeList()->commitChanges();
#ifdef DO_DUMP_CHANGELIST
    OSG::Thread::getCurrentChangeList()->dump();
#endif

    fprintf(stderr, "sharing | created\n");

    dumpAspects(pTestFC);

    fprintf(stderr, "sharing | apply\n");

    applyToAspect(1);
    applyToAspect(2, true);

    dumpAspects(pTestFC);

    fprintf(stderr, "sharing | destroy\n");

    pTestFC = NULL;

    applyToAspect(1);
    applyToAspect(2, true);
}

int main (int argc, char **argv)
{
//    OSG::ThreadManager::setNumAspects(3);
    OSG::ChangeList::setReadWriteDefault(true);
    OSG::osgInit(argc, argv);

    vAspectChangeList[0] = OSG::Thread::getCurrentChangeList();
    vAspectChangeList[1] = OSG::ChangeList::create();
    vAspectChangeList[2] = OSG::ChangeList::create();

    vAspectChangeList[1]->setAspectTo(1);
    vAspectChangeList[2]->setAspectTo(2);

    fprintf(stderr, "ChangeLists:\n [0] : %p\n [1] : %p\n [2] : %p\n",
            vAspectChangeList[0],
            vAspectChangeList[1],
            vAspectChangeList[2]);
    
    OSG::Thread::getCurrentChangeList()->dump ();
    OSG::Thread::getCurrentChangeList()->clear();

    OSG  ::Node               ::getClassType ().dump();
    OSG  ::NodeCore           ::getClassType ().dump();    
    VCoRE::Item               ::getClassType().dump();
    VCoRE::VCDynFieldContainer::getClassType().dump();

//    testCreate();
//    testValField();
    testPtrField();

    fprintf(stderr, "exit\n");

    OSG::subRef(vAspectChangeList[1]);
    OSG::subRef(vAspectChangeList[2]);


    OSG::osgExit();

    return 0;
}
