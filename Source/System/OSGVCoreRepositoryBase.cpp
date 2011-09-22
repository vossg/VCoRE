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
 **     class VCoreRepository!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"




#include "OSGVCoreRepositoryBase.h"
#include "OSGVCoreRepository.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::VCoreRepository
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<VCoreRepository *>::_type("VCoreRepositoryPtr", "AttachmentContainerPtr");
#endif

OSG_FIELDTRAITS_GETTYPE(VCoreRepository *)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           VCoreRepository *,
                           0);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           VCoreRepository *,
                           0);

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void VCoreRepositoryBase::classDescInserter(TypeObject &oType)
{
}


VCoreRepositoryBase::TypeObject VCoreRepositoryBase::_type(
    VCoreRepositoryBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    0,
    reinterpret_cast<PrototypeCreateF>(&VCoreRepositoryBase::createEmptyLocal),
    VCoreRepository::initMethod,
    VCoreRepository::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&VCoreRepository::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\" ?>\n"
    "\n"
    "<FieldContainer\n"
    "    name=\"VCoreRepository\"\n"
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
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &VCoreRepositoryBase::getType(void)
{
    return _type;
}

const FieldContainerType &VCoreRepositoryBase::getType(void) const
{
    return _type;
}

UInt32 VCoreRepositoryBase::getContainerSize(void) const
{
    return sizeof(VCoreRepository);
}

/*------------------------- decorator get ------------------------------*/






/*------------------------------ access -----------------------------------*/

UInt32 VCoreRepositoryBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);


    return returnValue;
}

void VCoreRepositoryBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

}

void VCoreRepositoryBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

}

//! create a new instance of the class
VCoreRepositoryTransitPtr VCoreRepositoryBase::createLocal(BitVector bFlags)
{
    VCoreRepositoryTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<VCoreRepository>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
VCoreRepositoryTransitPtr VCoreRepositoryBase::createDependent(BitVector bFlags)
{
    VCoreRepositoryTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<VCoreRepository>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
VCoreRepositoryTransitPtr VCoreRepositoryBase::create(void)
{
    return createLocal();
}

VCoreRepository *VCoreRepositoryBase::createEmptyLocal(BitVector bFlags)
{
    VCoreRepository *returnValue;

    newPtr<VCoreRepository>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
VCoreRepository *VCoreRepositoryBase::createEmpty(void)
{
    return createEmptyLocal();
}


FieldContainerTransitPtr VCoreRepositoryBase::shallowCopyLocal(
    BitVector bFlags) const
{
    VCoreRepository *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const VCoreRepository *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr VCoreRepositoryBase::shallowCopyDependent(
    BitVector bFlags) const
{
    VCoreRepository *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const VCoreRepository *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr VCoreRepositoryBase::shallowCopy(void) const
{
    return shallowCopyLocal();
}




/*------------------------- constructors ----------------------------------*/

VCoreRepositoryBase::VCoreRepositoryBase(void) :
    Inherited()
{
}

VCoreRepositoryBase::VCoreRepositoryBase(const VCoreRepositoryBase &source) :
    Inherited(source)
{
}


/*-------------------------- destructors ----------------------------------*/

VCoreRepositoryBase::~VCoreRepositoryBase(void)
{
}



#ifdef OSG_MT_CPTR_ASPECT
void VCoreRepositoryBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    VCoreRepository *pThis = static_cast<VCoreRepository *>(this);

    pThis->execSync(static_cast<VCoreRepository *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *VCoreRepositoryBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    VCoreRepository *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const VCoreRepository *>(pRefAspect),
                  dynamic_cast<const VCoreRepository *>(this));

    return returnValue;
}
#endif

void VCoreRepositoryBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


OSG_END_NAMESPACE