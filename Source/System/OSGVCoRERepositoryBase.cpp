/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: dirk@opensg.org, gerrit.voss@vossg.org, carsten_neumann@gmx.net  *
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
 **     class Repository!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"




#include "OSGVCoRERepositoryBase.h"
#include "OSGVCoRERepository.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

VCORE_IMPORT_NAMESPACE;

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::Repository
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
PointerType FieldTraits<Repository *, nsVCoRE>::_type(
    "RepositoryPtr", 
    "AttachmentContainerPtr", 
    Repository::getClassType(),
    nsVCoRE);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(Repository *, nsVCoRE)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           Repository *,
                           nsVCoRE);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           Repository *,
                           nsVCoRE);

OSG_END_NAMESPACE

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

void RepositoryBase::classDescInserter(TypeObject &oType)
{
}


RepositoryBase::TypeObject RepositoryBase::_type(
    RepositoryBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsVCoRE, //Namespace
    reinterpret_cast<PrototypeCreateF>(&RepositoryBase::createEmptyLocal),
    Repository::initMethod,
    Repository::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&Repository::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\" ?>\n"
    "\n"
    "<FieldContainer\n"
    "    name=\"Repository\"\n"
    "    parent=\"AttachmentContainer\"\n"
    "    parentnamespace=\"OSG\"\n"
    "    library=\"VCoRESystem\"\n"
    "    structure=\"concrete\"\n"
    "    pointerfieldtypes=\"both\"\n"
    "    systemcomponent=\"true\"\n"
    "    parentsystemcomponent=\"true\"\n"
    "    isNodeCore=\"false\"\n"
    "    isBundle=\"true\"\n"
    "    docGroupBase=\"GrpVCoreSystem\"\n"
    "    libnamespace=\"VCoRE\"\n"
    "   >\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &RepositoryBase::getType(void)
{
    return _type;
}

const FieldContainerType &RepositoryBase::getType(void) const
{
    return _type;
}

UInt32 RepositoryBase::getContainerSize(void) const
{
    return sizeof(Repository);
}

/*------------------------- decorator get ------------------------------*/






/*------------------------------ access -----------------------------------*/

SizeT RepositoryBase::getBinSize(ConstFieldMaskArg whichField)
{
    SizeT returnValue = Inherited::getBinSize(whichField);


    return returnValue;
}

void RepositoryBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

}

void RepositoryBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

}

//! create a new instance of the class
RepositoryTransitPtr RepositoryBase::createLocal(BitVector bFlags)
{
    RepositoryTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<Repository>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
RepositoryTransitPtr RepositoryBase::createDependent(BitVector bFlags)
{
    RepositoryTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<Repository>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
RepositoryTransitPtr RepositoryBase::create(void)
{
    return createLocal();
}

Repository *RepositoryBase::createEmptyLocal(BitVector bFlags)
{
    Repository *returnValue;

    newPtr<Repository>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
Repository *RepositoryBase::createEmpty(void)
{
    return createEmptyLocal();
}


FieldContainerTransitPtr RepositoryBase::shallowCopyLocal(
    BitVector bFlags) const
{
    Repository *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const Repository *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr RepositoryBase::shallowCopyDependent(
    BitVector bFlags) const
{
    Repository *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const Repository *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr RepositoryBase::shallowCopy(void) const
{
    return shallowCopyLocal();
}




/*------------------------- constructors ----------------------------------*/

RepositoryBase::RepositoryBase(void) :
    Inherited()
{
}

RepositoryBase::RepositoryBase(const RepositoryBase &source) :
    Inherited(source)
{
}


/*-------------------------- destructors ----------------------------------*/

RepositoryBase::~RepositoryBase(void)
{
}



#ifdef OSG_MT_CPTR_ASPECT
void RepositoryBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Repository *pThis = static_cast<Repository *>(this);

    pThis->execSync(static_cast<Repository *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *RepositoryBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    Repository *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const Repository *>(pRefAspect),
                  dynamic_cast<const Repository *>(this));

    return returnValue;
}
#endif

void RepositoryBase::resolveLinks(void)
{
    Inherited::resolveLinks();


}


VCORE_END_NAMESPACE
