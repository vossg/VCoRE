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
 **     class VCoreApp!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"



#include "OSGVCoreRepository.h"         // Repositories Class
#include "OSGVCoreArena.h"              // Arenas Class

#include "OSGVCoreAppBase.h"
#include "OSGVCoreApp.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::VCoreApp
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var VCoreRepository * VCoreAppBase::_mfRepositories
    
*/

/*! \var VCoreArena *    VCoreAppBase::_mfArenas
    
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<VCoreApp *>::_type("VCoreAppPtr", "AttachmentContainerPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(VCoreApp *)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           VCoreApp *,
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           VCoreApp *,
                           0);

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void VCoreAppBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new MFUnrecVCoreRepositoryPtr::Description(
        MFUnrecVCoreRepositoryPtr::getClassType(),
        "repositories",
        "",
        RepositoriesFieldId, RepositoriesFieldMask,
        false,
        (Field::MFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&VCoreApp::editHandleRepositories),
        static_cast<FieldGetMethodSig >(&VCoreApp::getHandleRepositories));

    oType.addInitialDesc(pDesc);

    pDesc = new MFUnrecVCoreArenaPtr::Description(
        MFUnrecVCoreArenaPtr::getClassType(),
        "arenas",
        "",
        ArenasFieldId, ArenasFieldMask,
        false,
        (Field::MFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&VCoreApp::editHandleArenas),
        static_cast<FieldGetMethodSig >(&VCoreApp::getHandleArenas));

    oType.addInitialDesc(pDesc);
}


VCoreAppBase::TypeObject VCoreAppBase::_type(
    VCoreAppBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    reinterpret_cast<PrototypeCreateF>(&VCoreAppBase::createEmptyLocal),
    VCoreApp::initMethod,
    VCoreApp::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&VCoreApp::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\" ?>\n"
    "\n"
    "<FieldContainer\n"
    "    name=\"VCoreApp\"\n"
    "    parent=\"AttachmentContainer\"\n"
    "    library=\"VCoreSystem\"\n"
    "    structure=\"concrete\"\n"
    "    pointerfieldtypes=\"both\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "    isNodeCore=\"false\"\n"
    "    isBundle=\"true\"\n"
    "    docGroupBase=\"GrpVCoreSystem\"\n"
    "   >\n"
    "  <Field\n"
    "      name=\"repositories\"\n"
    "      type=\"VCoreRepository\"\n"
    "      cardinality=\"multi\"\n"
    "      visibility=\"external\"\n"
    "      access=\"public\"\n"
    "      category=\"pointer\"\n"
    "      >\n"
    "  </Field> \n"
    "  <Field\n"
    "      name=\"arenas\"\n"
    "      type=\"VCoreArena\"\n"
    "      cardinality=\"multi\"\n"
    "      visibility=\"external\"\n"
    "      access=\"public\"\n"
    "      category=\"pointer\"\n"
    "      >\n"
    "  </Field>\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &VCoreAppBase::getType(void)
{
    return _type;
}

const FieldContainerType &VCoreAppBase::getType(void) const
{
    return _type;
}

UInt32 VCoreAppBase::getContainerSize(void) const
{
    return sizeof(VCoreApp);
}

/*------------------------- decorator get ------------------------------*/


//! Get the VCoreApp::_mfRepositories field.
const MFUnrecVCoreRepositoryPtr *VCoreAppBase::getMFRepositories(void) const
{
    return &_mfRepositories;
}

MFUnrecVCoreRepositoryPtr *VCoreAppBase::editMFRepositories   (void)
{
    editMField(RepositoriesFieldMask, _mfRepositories);

    return &_mfRepositories;
}

//! Get the VCoreApp::_mfArenas field.
const MFUnrecVCoreArenaPtr *VCoreAppBase::getMFArenas(void) const
{
    return &_mfArenas;
}

MFUnrecVCoreArenaPtr *VCoreAppBase::editMFArenas         (void)
{
    editMField(ArenasFieldMask, _mfArenas);

    return &_mfArenas;
}



void VCoreAppBase::pushToRepositories(VCoreRepository * const value)
{
    editMField(RepositoriesFieldMask, _mfRepositories);

    _mfRepositories.push_back(value);
}

void VCoreAppBase::assignRepositories(const MFUnrecVCoreRepositoryPtr &value)
{
    MFUnrecVCoreRepositoryPtr::const_iterator elemIt  =
        value.begin();
    MFUnrecVCoreRepositoryPtr::const_iterator elemEnd =
        value.end  ();

    static_cast<VCoreApp *>(this)->clearRepositories();

    while(elemIt != elemEnd)
    {
        this->pushToRepositories(*elemIt);

        ++elemIt;
    }
}

void VCoreAppBase::removeFromRepositories(UInt32 uiIndex)
{
    if(uiIndex < _mfRepositories.size())
    {
        editMField(RepositoriesFieldMask, _mfRepositories);

        _mfRepositories.erase(uiIndex);
    }
}

void VCoreAppBase::removeObjFromRepositories(VCoreRepository * const value)
{
    Int32 iElemIdx = _mfRepositories.findIndex(value);

    if(iElemIdx != -1)
    {
        editMField(RepositoriesFieldMask, _mfRepositories);

        _mfRepositories.erase(iElemIdx);
    }
}
void VCoreAppBase::clearRepositories(void)
{
    editMField(RepositoriesFieldMask, _mfRepositories);


    _mfRepositories.clear();
}

void VCoreAppBase::pushToArenas(VCoreArena * const value)
{
    editMField(ArenasFieldMask, _mfArenas);

    _mfArenas.push_back(value);
}

void VCoreAppBase::assignArenas   (const MFUnrecVCoreArenaPtr &value)
{
    MFUnrecVCoreArenaPtr::const_iterator elemIt  =
        value.begin();
    MFUnrecVCoreArenaPtr::const_iterator elemEnd =
        value.end  ();

    static_cast<VCoreApp *>(this)->clearArenas();

    while(elemIt != elemEnd)
    {
        this->pushToArenas(*elemIt);

        ++elemIt;
    }
}

void VCoreAppBase::removeFromArenas(UInt32 uiIndex)
{
    if(uiIndex < _mfArenas.size())
    {
        editMField(ArenasFieldMask, _mfArenas);

        _mfArenas.erase(uiIndex);
    }
}

void VCoreAppBase::removeObjFromArenas(VCoreArena * const value)
{
    Int32 iElemIdx = _mfArenas.findIndex(value);

    if(iElemIdx != -1)
    {
        editMField(ArenasFieldMask, _mfArenas);

        _mfArenas.erase(iElemIdx);
    }
}
void VCoreAppBase::clearArenas(void)
{
    editMField(ArenasFieldMask, _mfArenas);


    _mfArenas.clear();
}



/*------------------------------ access -----------------------------------*/

UInt32 VCoreAppBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (RepositoriesFieldMask & whichField))
    {
        returnValue += _mfRepositories.getBinSize();
    }
    if(FieldBits::NoField != (ArenasFieldMask & whichField))
    {
        returnValue += _mfArenas.getBinSize();
    }

    return returnValue;
}

void VCoreAppBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (RepositoriesFieldMask & whichField))
    {
        _mfRepositories.copyToBin(pMem);
    }
    if(FieldBits::NoField != (ArenasFieldMask & whichField))
    {
        _mfArenas.copyToBin(pMem);
    }
}

void VCoreAppBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (RepositoriesFieldMask & whichField))
    {
        editMField(RepositoriesFieldMask, _mfRepositories);
        _mfRepositories.copyFromBin(pMem);
    }
    if(FieldBits::NoField != (ArenasFieldMask & whichField))
    {
        editMField(ArenasFieldMask, _mfArenas);
        _mfArenas.copyFromBin(pMem);
    }
}

//! create a new instance of the class
VCoreAppTransitPtr VCoreAppBase::createLocal(BitVector bFlags)
{
    VCoreAppTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<VCoreApp>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
VCoreAppTransitPtr VCoreAppBase::createDependent(BitVector bFlags)
{
    VCoreAppTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<VCoreApp>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
VCoreAppTransitPtr VCoreAppBase::create(void)
{
    return createLocal();
}

VCoreApp *VCoreAppBase::createEmptyLocal(BitVector bFlags)
{
    VCoreApp *returnValue;

    newPtr<VCoreApp>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
VCoreApp *VCoreAppBase::createEmpty(void)
{
    return createEmptyLocal();
}


FieldContainerTransitPtr VCoreAppBase::shallowCopyLocal(
    BitVector bFlags) const
{
    VCoreApp *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const VCoreApp *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr VCoreAppBase::shallowCopyDependent(
    BitVector bFlags) const
{
    VCoreApp *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const VCoreApp *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr VCoreAppBase::shallowCopy(void) const
{
    return shallowCopyLocal();
}




/*------------------------- constructors ----------------------------------*/

VCoreAppBase::VCoreAppBase(void) :
    Inherited(),
    _mfRepositories           (),
    _mfArenas                 ()
{
}

VCoreAppBase::VCoreAppBase(const VCoreAppBase &source) :
    Inherited(source),
    _mfRepositories           (),
    _mfArenas                 ()
{
}


/*-------------------------- destructors ----------------------------------*/

VCoreAppBase::~VCoreAppBase(void)
{
}

void VCoreAppBase::onCreate(const VCoreApp *source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        VCoreApp *pThis = static_cast<VCoreApp *>(this);

        MFUnrecVCoreRepositoryPtr::const_iterator RepositoriesIt  =
            source->_mfRepositories.begin();
        MFUnrecVCoreRepositoryPtr::const_iterator RepositoriesEnd =
            source->_mfRepositories.end  ();

        while(RepositoriesIt != RepositoriesEnd)
        {
            pThis->pushToRepositories(*RepositoriesIt);

            ++RepositoriesIt;
        }

        MFUnrecVCoreArenaPtr::const_iterator ArenasIt  =
            source->_mfArenas.begin();
        MFUnrecVCoreArenaPtr::const_iterator ArenasEnd =
            source->_mfArenas.end  ();

        while(ArenasIt != ArenasEnd)
        {
            pThis->pushToArenas(*ArenasIt);

            ++ArenasIt;
        }
    }
}

GetFieldHandlePtr VCoreAppBase::getHandleRepositories    (void) const
{
    MFUnrecVCoreRepositoryPtr::GetHandlePtr returnValue(
        new  MFUnrecVCoreRepositoryPtr::GetHandle(
             &_mfRepositories,
             this->getType().getFieldDesc(RepositoriesFieldId),
             const_cast<VCoreAppBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr VCoreAppBase::editHandleRepositories   (void)
{
    MFUnrecVCoreRepositoryPtr::EditHandlePtr returnValue(
        new  MFUnrecVCoreRepositoryPtr::EditHandle(
             &_mfRepositories,
             this->getType().getFieldDesc(RepositoriesFieldId),
             this));

    returnValue->setAddMethod(
        boost::bind(&VCoreApp::pushToRepositories,
                    static_cast<VCoreApp *>(this), _1));
    returnValue->setRemoveMethod(
        boost::bind(&VCoreApp::removeFromRepositories,
                    static_cast<VCoreApp *>(this), _1));
    returnValue->setRemoveObjMethod(
        boost::bind(&VCoreApp::removeObjFromRepositories,
                    static_cast<VCoreApp *>(this), _1));
    returnValue->setClearMethod(
        boost::bind(&VCoreApp::clearRepositories,
                    static_cast<VCoreApp *>(this)));

    editMField(RepositoriesFieldMask, _mfRepositories);

    return returnValue;
}

GetFieldHandlePtr VCoreAppBase::getHandleArenas          (void) const
{
    MFUnrecVCoreArenaPtr::GetHandlePtr returnValue(
        new  MFUnrecVCoreArenaPtr::GetHandle(
             &_mfArenas,
             this->getType().getFieldDesc(ArenasFieldId),
             const_cast<VCoreAppBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr VCoreAppBase::editHandleArenas         (void)
{
    MFUnrecVCoreArenaPtr::EditHandlePtr returnValue(
        new  MFUnrecVCoreArenaPtr::EditHandle(
             &_mfArenas,
             this->getType().getFieldDesc(ArenasFieldId),
             this));

    returnValue->setAddMethod(
        boost::bind(&VCoreApp::pushToArenas,
                    static_cast<VCoreApp *>(this), _1));
    returnValue->setRemoveMethod(
        boost::bind(&VCoreApp::removeFromArenas,
                    static_cast<VCoreApp *>(this), _1));
    returnValue->setRemoveObjMethod(
        boost::bind(&VCoreApp::removeObjFromArenas,
                    static_cast<VCoreApp *>(this), _1));
    returnValue->setClearMethod(
        boost::bind(&VCoreApp::clearArenas,
                    static_cast<VCoreApp *>(this)));

    editMField(ArenasFieldMask, _mfArenas);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void VCoreAppBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    VCoreApp *pThis = static_cast<VCoreApp *>(this);

    pThis->execSync(static_cast<VCoreApp *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *VCoreAppBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    VCoreApp *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const VCoreApp *>(pRefAspect),
                  dynamic_cast<const VCoreApp *>(this));

    return returnValue;
}
#endif

void VCoreAppBase::resolveLinks(void)
{
    Inherited::resolveLinks();

    static_cast<VCoreApp *>(this)->clearRepositories();

    static_cast<VCoreApp *>(this)->clearArenas();


}


OSG_END_NAMESPACE
