/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 **     Do not change this file, changes should be done in the derived      **
 **     class VCRenderer!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"



#include "OSGRenderTask.h"              // Tasks Class

#include "OSGVCRendererBase.h"
#include "OSGVCRenderer.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::VCRenderer
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var RenderTask *    VCRendererBase::_mfTasks
    
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<VCRenderer *>::_type("VCRendererPtr", "VCoreItemPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(VCRenderer *)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           VCRenderer *,
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           VCRenderer *,
                           0);

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void VCRendererBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new MFUnrecRenderTaskPtr::Description(
        MFUnrecRenderTaskPtr::getClassType(),
        "tasks",
        "",
        TasksFieldId, TasksFieldMask,
        false,
        (Field::MFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&VCRenderer::editHandleTasks),
        static_cast<FieldGetMethodSig >(&VCRenderer::getHandleTasks));

    oType.addInitialDesc(pDesc);
}


VCRendererBase::TypeObject VCRendererBase::_type(
    VCRendererBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    reinterpret_cast<PrototypeCreateF>(&VCRendererBase::createEmptyLocal),
    VCRenderer::initMethod,
    VCRenderer::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&VCRenderer::classDescInserter),
    true,
    0,
    "<?xml version=\"1.0\" ?>\n"
    "\n"
    "<FieldContainer\n"
    "   name=\"VCRenderer\"\n"
    "   parent=\"VCoreItem\"\n"
    "   library=\"VCoreRenderer\"\n"
    "   structure=\"concrete\"\n"
    "   pointerfieldtypes=\"both\"\n"
    "   systemcomponent=\"true\"\n"
    "   parentsystemcomponent=\"true\"\n"
    "   isNodeCore=\"true\"\n"
    "   docGroupBase=\"GrpVCoreRenderer\"\n"
    "   typeDescAddable=\"true\"\n"
    "   dynFCDerived=\"true\"\n"
    "   >\n"
    "   <Field\n"
    "     name=\"tasks\"\n"
    "     type=\"RenderTaskPtr\"\n"
    "     cardinality=\"multi\"\n"
    "     visibility=\"external\"\n"
    "     access=\"public\"\n"
    "     defaultValue=\"\"\n"
    "     >\n"
    "  </Field>\n"
    "\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &VCRendererBase::getType(void)
{
    return _localType;
}

const FieldContainerType &VCRendererBase::getType(void) const
{
    return _localType;
}

UInt32 VCRendererBase::getContainerSize(void) const
{
    return sizeof(VCRenderer);
}

VCRendererBase::TypeObject &VCRendererBase::getFinalType(void)
{
    return _type;
}

const VCRendererBase::TypeObject &VCRendererBase::getFinalType(void) const
{
    return _type;
}

/*------------------------- decorator get ------------------------------*/


//! Get the VCRenderer::_mfTasks field.
const MFUnrecRenderTaskPtr *VCRendererBase::getMFTasks(void) const
{
    return &_mfTasks;
}

MFUnrecRenderTaskPtr *VCRendererBase::editMFTasks          (void)
{
    editMField(TasksFieldMask, _mfTasks);

    return &_mfTasks;
}



void VCRendererBase::pushToTasks(RenderTask * const value)
{
    editMField(TasksFieldMask, _mfTasks);

    _mfTasks.push_back(value);
}

void VCRendererBase::assignTasks    (const MFUnrecRenderTaskPtr &value)
{
    MFUnrecRenderTaskPtr::const_iterator elemIt  =
        value.begin();
    MFUnrecRenderTaskPtr::const_iterator elemEnd =
        value.end  ();

    static_cast<VCRenderer *>(this)->clearTasks();

    while(elemIt != elemEnd)
    {
        this->pushToTasks(*elemIt);

        ++elemIt;
    }
}

void VCRendererBase::removeFromTasks(UInt32 uiIndex)
{
    if(uiIndex < _mfTasks.size())
    {
        editMField(TasksFieldMask, _mfTasks);

        _mfTasks.erase(uiIndex);
    }
}

void VCRendererBase::removeObjFromTasks(RenderTask * const value)
{
    Int32 iElemIdx = _mfTasks.findIndex(value);

    if(iElemIdx != -1)
    {
        editMField(TasksFieldMask, _mfTasks);

        _mfTasks.erase(iElemIdx);
    }
}
void VCRendererBase::clearTasks(void)
{
    editMField(TasksFieldMask, _mfTasks);


    _mfTasks.clear();
}



/*------------------------------ access -----------------------------------*/

UInt32 VCRendererBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (TasksFieldMask & whichField))
    {
        returnValue += _mfTasks.getBinSize();
    }

    return returnValue;
}

void VCRendererBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (TasksFieldMask & whichField))
    {
        _mfTasks.copyToBin(pMem);
    }
}

void VCRendererBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (TasksFieldMask & whichField))
    {
        editMField(TasksFieldMask, _mfTasks);
        _mfTasks.copyFromBin(pMem);
    }
}

//! create a new instance of the class
VCRendererTransitPtr VCRendererBase::createLocal(BitVector bFlags)
{
    VCRendererTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<VCRenderer>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
VCRendererTransitPtr VCRendererBase::createDependent(BitVector bFlags)
{
    VCRendererTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<VCRenderer>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
VCRendererTransitPtr VCRendererBase::create(void)
{
    VCRendererTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<VCRenderer>(tmpPtr);
    }

    return fc;
}

VCRenderer *VCRendererBase::createEmptyLocal(BitVector bFlags)
{
    VCRenderer *returnValue;

    newPtr<VCRenderer>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
VCRenderer *VCRendererBase::createEmpty(void)
{
    VCRenderer *returnValue;

    newPtr<VCRenderer>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr VCRendererBase::shallowCopyLocal(
    BitVector bFlags) const
{
    VCRenderer *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const VCRenderer *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr VCRendererBase::shallowCopyDependent(
    BitVector bFlags) const
{
    VCRenderer *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const VCRenderer *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr VCRendererBase::shallowCopy(void) const
{
    VCRenderer *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const VCRenderer *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

VCRendererBase::VCRendererBase(void) :
    Inherited(),
    _mfTasks                  ()
{
}

VCRendererBase::VCRendererBase(const VCRendererBase &source) :
    Inherited(source),
    _mfTasks                  ()
{
}


/*-------------------------- destructors ----------------------------------*/

VCRendererBase::~VCRendererBase(void)
{
}

void VCRendererBase::onCreate(const VCRenderer *source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        VCRenderer *pThis = static_cast<VCRenderer *>(this);

        MFUnrecRenderTaskPtr::const_iterator TasksIt  =
            source->_mfTasks.begin();
        MFUnrecRenderTaskPtr::const_iterator TasksEnd =
            source->_mfTasks.end  ();

        while(TasksIt != TasksEnd)
        {
            pThis->pushToTasks(*TasksIt);

            ++TasksIt;
        }
    }
}

GetFieldHandlePtr VCRendererBase::getHandleTasks           (void) const
{
    MFUnrecRenderTaskPtr::GetHandlePtr returnValue(
        new  MFUnrecRenderTaskPtr::GetHandle(
             &_mfTasks,
             this->getType().getFieldDesc(TasksFieldId),
             const_cast<VCRendererBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr VCRendererBase::editHandleTasks          (void)
{
    MFUnrecRenderTaskPtr::EditHandlePtr returnValue(
        new  MFUnrecRenderTaskPtr::EditHandle(
             &_mfTasks,
             this->getType().getFieldDesc(TasksFieldId),
             this));

    returnValue->setAddMethod(
        boost::bind(&VCRenderer::pushToTasks,
                    static_cast<VCRenderer *>(this), _1));
    returnValue->setRemoveMethod(
        boost::bind(&VCRenderer::removeFromTasks,
                    static_cast<VCRenderer *>(this), _1));
    returnValue->setRemoveObjMethod(
        boost::bind(&VCRenderer::removeObjFromTasks,
                    static_cast<VCRenderer *>(this), _1));
    returnValue->setClearMethod(
        boost::bind(&VCRenderer::clearTasks,
                    static_cast<VCRenderer *>(this)));

    editMField(TasksFieldMask, _mfTasks);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void VCRendererBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    VCRenderer *pThis = static_cast<VCRenderer *>(this);

    pThis->execSync(static_cast<VCRenderer *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *VCRendererBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    VCRenderer *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const VCRenderer *>(pRefAspect),
                  dynamic_cast<const VCRenderer *>(this));

    return returnValue;
}
#endif

void VCRendererBase::resolveLinks(void)
{
    Inherited::resolveLinks();

    static_cast<VCRenderer *>(this)->clearTasks();


}


OSG_END_NAMESPACE
