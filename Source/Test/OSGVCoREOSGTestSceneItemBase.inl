/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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
 **     class OSGTestSceneItem!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;


//! access the type of the class
inline
OSG::FieldContainerType &OSGTestSceneItemBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 OSGTestSceneItemBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 OSGTestSceneItemBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the OSGTestSceneItem::_sfRotationSpeed field.

inline
Real32 &OSGTestSceneItemBase::editRotationSpeed(void)
{
    editSField(RotationSpeedFieldMask);

    return _sfRotationSpeed.getValue();
}

//! Get the value of the OSGTestSceneItem::_sfRotationSpeed field.
inline
      Real32  OSGTestSceneItemBase::getRotationSpeed(void) const
{
    return _sfRotationSpeed.getValue();
}

//! Set the value of the OSGTestSceneItem::_sfRotationSpeed field.
inline
void OSGTestSceneItemBase::setRotationSpeed(const Real32 value)
{
    editSField(RotationSpeedFieldMask);

    _sfRotationSpeed.setValue(value);
}
//! Get the value of the OSGTestSceneItem::_sfAnimate field.

inline
bool &OSGTestSceneItemBase::editAnimate(void)
{
    editSField(AnimateFieldMask);

    return _sfAnimate.getValue();
}

//! Get the value of the OSGTestSceneItem::_sfAnimate field.
inline
      bool  OSGTestSceneItemBase::getAnimate(void) const
{
    return _sfAnimate.getValue();
}

//! Set the value of the OSGTestSceneItem::_sfAnimate field.
inline
void OSGTestSceneItemBase::setAnimate(const bool value)
{
    editSField(AnimateFieldMask);

    _sfAnimate.setValue(value);
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void OSGTestSceneItemBase::execSync (      OSGTestSceneItemBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (RotationSpeedFieldMask & whichField))
        _sfRotationSpeed.syncWith(pFrom->_sfRotationSpeed);

    if(FieldBits::NoField != (AnimateFieldMask & whichField))
        _sfAnimate.syncWith(pFrom->_sfAnimate);
}
#endif


inline
const Char8 *OSGTestSceneItemBase::getClassname(void)
{
    return "OSGTestSceneItem";
}
OSG_GEN_CONTAINERPTR(OSGTestSceneItem);

VCORE_END_NAMESPACE

