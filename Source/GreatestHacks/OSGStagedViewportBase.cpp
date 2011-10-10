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
 **     class StagedViewport!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"



#include "OSGStage.h"                   // Stage Class

#include "OSGStagedViewportBase.h"
#include "OSGStagedViewport.h"

#include <boost/bind.hpp>

#ifdef WIN32 // turn off 'this' : used in base member initializer list warning
#pragma warning(disable:4355)
#endif

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::StagedViewport
    
 */

/***************************************************************************\
 *                        Field Documentation                              *
\***************************************************************************/

/*! \var Stage *         StagedViewportBase::_sfStage
    
*/


/***************************************************************************\
 *                      FieldType/FieldTrait Instantiation                 *
\***************************************************************************/

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldTraits<StagedViewport *, nsOSG>::_type("StagedViewportPtr", "FBOViewportPtr", nsOSG);
#endif

OSG_FIELDTRAITS_GETTYPE_NS(StagedViewport *, nsOSG)

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField,
                           StagedViewport *,
                           nsOSG);

OSG_EXPORT_PTR_MFIELD_FULL(PointerMField,
                           StagedViewport *,
                           nsOSG);

/***************************************************************************\
 *                         Field Description                               *
\***************************************************************************/

void StagedViewportBase::classDescInserter(TypeObject &oType)
{
    FieldDescriptionBase *pDesc = NULL;


    pDesc = new SFUnrecStagePtr::Description(
        SFUnrecStagePtr::getClassType(),
        "stage",
        "",
        StageFieldId, StageFieldMask,
        false,
        (Field::SFDefaultFlags | Field::FStdAccess),
        static_cast<FieldEditMethodSig>(&StagedViewport::editHandleStage),
        static_cast<FieldGetMethodSig >(&StagedViewport::getHandleStage));

    oType.addInitialDesc(pDesc);
}


StagedViewportBase::TypeObject StagedViewportBase::_type(
    StagedViewportBase::getClassname(),
    Inherited::getClassname(),
    "NULL",
    nsOSG, //Namespace
    reinterpret_cast<PrototypeCreateF>(&StagedViewportBase::createEmptyLocal),
    StagedViewport::initMethod,
    StagedViewport::exitMethod,
    reinterpret_cast<InitalInsertDescFunc>(&StagedViewport::classDescInserter),
    false,
    0,
    "<?xml version=\"1.0\" ?>\n"
    "\n"
    "<FieldContainer\n"
    "   name=\"StagedViewport\"\n"
    "   parent=\"FBOViewport\"\n"
    "   library=\"VCoreGreatestHacks\"\n"
    "   structure=\"concrete\"\n"
    "   pointerfieldtypes=\"both\"\n"
    "   systemcomponent=\"true\"\n"
    "   parentsystemcomponent=\"true\"\n"
    "   isNodeCore=\"true\"\n"
    "   docGroupBase=\"GrpVCoreGreatestHacks\"\n"
    "   typeDescAddable=\"false\"\n"
    "   dynFCDerived=\"false\"\n"
    "   >\n"
    "  <Field\n"
    "     name=\"stage\"\n"
    "     type=\"StagePtr\"\n"
    "     cardinality=\"single\"\n"
    "     visibility=\"external\"\n"
    "     access=\"public\"\n"
    "     defaultValue=\"NULL\"\n"
    "     >\n"
    "  </Field>\n"
    "</FieldContainer>\n",
    ""
    );

/*------------------------------ get -----------------------------------*/

FieldContainerType &StagedViewportBase::getType(void)
{
    return _type;
}

const FieldContainerType &StagedViewportBase::getType(void) const
{
    return _type;
}

UInt32 StagedViewportBase::getContainerSize(void) const
{
    return sizeof(StagedViewport);
}

/*------------------------- decorator get ------------------------------*/


//! Get the StagedViewport::_sfStage field.
const SFUnrecStagePtr *StagedViewportBase::getSFStage(void) const
{
    return &_sfStage;
}

SFUnrecStagePtr     *StagedViewportBase::editSFStage          (void)
{
    editSField(StageFieldMask);

    return &_sfStage;
}





/*------------------------------ access -----------------------------------*/

UInt32 StagedViewportBase::getBinSize(ConstFieldMaskArg whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (StageFieldMask & whichField))
    {
        returnValue += _sfStage.getBinSize();
    }

    return returnValue;
}

void StagedViewportBase::copyToBin(BinaryDataHandler &pMem,
                                  ConstFieldMaskArg  whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (StageFieldMask & whichField))
    {
        _sfStage.copyToBin(pMem);
    }
}

void StagedViewportBase::copyFromBin(BinaryDataHandler &pMem,
                                    ConstFieldMaskArg  whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (StageFieldMask & whichField))
    {
        editSField(StageFieldMask);
        _sfStage.copyFromBin(pMem);
    }
}

//! create a new instance of the class
StagedViewportTransitPtr StagedViewportBase::createLocal(BitVector bFlags)
{
    StagedViewportTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyLocal(bFlags);

        fc = dynamic_pointer_cast<StagedViewport>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class, copy the container flags
StagedViewportTransitPtr StagedViewportBase::createDependent(BitVector bFlags)
{
    StagedViewportTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopyDependent(bFlags);

        fc = dynamic_pointer_cast<StagedViewport>(tmpPtr);
    }

    return fc;
}

//! create a new instance of the class
StagedViewportTransitPtr StagedViewportBase::create(void)
{
    StagedViewportTransitPtr fc;

    if(getClassType().getPrototype() != NULL)
    {
        FieldContainerTransitPtr tmpPtr =
            getClassType().getPrototype()-> shallowCopy();

        fc = dynamic_pointer_cast<StagedViewport>(tmpPtr);
    }

    return fc;
}

StagedViewport *StagedViewportBase::createEmptyLocal(BitVector bFlags)
{
    StagedViewport *returnValue;

    newPtr<StagedViewport>(returnValue, bFlags);

    returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

//! create an empty new instance of the class, do not copy the prototype
StagedViewport *StagedViewportBase::createEmpty(void)
{
    StagedViewport *returnValue;

    newPtr<StagedViewport>(returnValue, Thread::getCurrentLocalFlags());

    returnValue->_pFieldFlags->_bNamespaceMask &=
        ~Thread::getCurrentLocalFlags();

    return returnValue;
}


FieldContainerTransitPtr StagedViewportBase::shallowCopyLocal(
    BitVector bFlags) const
{
    StagedViewport *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const StagedViewport *>(this), bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

    return returnValue;
}

FieldContainerTransitPtr StagedViewportBase::shallowCopyDependent(
    BitVector bFlags) const
{
    StagedViewport *tmpPtr;

    newPtr(tmpPtr, dynamic_cast<const StagedViewport *>(this), ~bFlags);

    FieldContainerTransitPtr returnValue(tmpPtr);

    tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

    return returnValue;
}

FieldContainerTransitPtr StagedViewportBase::shallowCopy(void) const
{
    StagedViewport *tmpPtr;

    newPtr(tmpPtr,
           dynamic_cast<const StagedViewport *>(this),
           Thread::getCurrentLocalFlags());

    tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

    FieldContainerTransitPtr returnValue(tmpPtr);

    return returnValue;
}




/*------------------------- constructors ----------------------------------*/

StagedViewportBase::StagedViewportBase(void) :
    Inherited(),
    _sfStage                  (NULL)
{
}

StagedViewportBase::StagedViewportBase(const StagedViewportBase &source) :
    Inherited(source),
    _sfStage                  (NULL)
{
}


/*-------------------------- destructors ----------------------------------*/

StagedViewportBase::~StagedViewportBase(void)
{
}

void StagedViewportBase::onCreate(const StagedViewport *source)
{
    Inherited::onCreate(source);

    if(source != NULL)
    {
        StagedViewport *pThis = static_cast<StagedViewport *>(this);

        pThis->setStage(source->getStage());
    }
}

GetFieldHandlePtr StagedViewportBase::getHandleStage           (void) const
{
    SFUnrecStagePtr::GetHandlePtr returnValue(
        new  SFUnrecStagePtr::GetHandle(
             &_sfStage,
             this->getType().getFieldDesc(StageFieldId),
             const_cast<StagedViewportBase *>(this)));

    return returnValue;
}

EditFieldHandlePtr StagedViewportBase::editHandleStage          (void)
{
    SFUnrecStagePtr::EditHandlePtr returnValue(
        new  SFUnrecStagePtr::EditHandle(
             &_sfStage,
             this->getType().getFieldDesc(StageFieldId),
             this));

    returnValue->setSetMethod(
        boost::bind(&StagedViewport::setStage,
                    static_cast<StagedViewport *>(this), _1));

    editSField(StageFieldMask);

    return returnValue;
}


#ifdef OSG_MT_CPTR_ASPECT
void StagedViewportBase::execSyncV(      FieldContainer    &oFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    StagedViewport *pThis = static_cast<StagedViewport *>(this);

    pThis->execSync(static_cast<StagedViewport *>(&oFrom),
                    whichField,
                    oOffsets,
                    syncMode,
                    uiSyncInfo);
}
#endif


#ifdef OSG_MT_CPTR_ASPECT
FieldContainer *StagedViewportBase::createAspectCopy(
    const FieldContainer *pRefAspect) const
{
    StagedViewport *returnValue;

    newAspectCopy(returnValue,
                  dynamic_cast<const StagedViewport *>(pRefAspect),
                  dynamic_cast<const StagedViewport *>(this));

    return returnValue;
}
#endif

void StagedViewportBase::resolveLinks(void)
{
    Inherited::resolveLinks();

    static_cast<StagedViewport *>(this)->setStage(NULL);


}


OSG_END_NAMESPACE
