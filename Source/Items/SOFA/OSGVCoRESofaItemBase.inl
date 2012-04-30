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
 **     class SofaItem!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;


//! access the type of the class
inline
OSG::FieldContainerType &SofaItemBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 SofaItemBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 SofaItemBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the SofaItem::_sfRotationSpeed field.

inline
Real32 &SofaItemBase::editRotationSpeed(void)
{
    editSField(RotationSpeedFieldMask);

    return _sfRotationSpeed.getValue();
}

//! Get the value of the SofaItem::_sfRotationSpeed field.
inline
      Real32  SofaItemBase::getRotationSpeed(void) const
{
    return _sfRotationSpeed.getValue();
}

//! Set the value of the SofaItem::_sfRotationSpeed field.
inline
void SofaItemBase::setRotationSpeed(const Real32 value)
{
    editSField(RotationSpeedFieldMask);

    _sfRotationSpeed.setValue(value);
}
//! Get the value of the SofaItem::_sfSofaDataPath field.

inline
std::string &SofaItemBase::editSofaDataPath(void)
{
    editSField(SofaDataPathFieldMask);

    return _sfSofaDataPath.getValue();
}

//! Get the value of the SofaItem::_sfSofaDataPath field.
inline
const std::string &SofaItemBase::getSofaDataPath(void) const
{
    return _sfSofaDataPath.getValue();
}

//! Set the value of the SofaItem::_sfSofaDataPath field.
inline
void SofaItemBase::setSofaDataPath(const std::string &value)
{
    editSField(SofaDataPathFieldMask);

    _sfSofaDataPath.setValue(value);
}
//! Get the value of the SofaItem::_sfSofaSceneFile field.

inline
std::string &SofaItemBase::editSofaSceneFile(void)
{
    editSField(SofaSceneFileFieldMask);

    return _sfSofaSceneFile.getValue();
}

//! Get the value of the SofaItem::_sfSofaSceneFile field.
inline
const std::string &SofaItemBase::getSofaSceneFile(void) const
{
    return _sfSofaSceneFile.getValue();
}

//! Set the value of the SofaItem::_sfSofaSceneFile field.
inline
void SofaItemBase::setSofaSceneFile(const std::string &value)
{
    editSField(SofaSceneFileFieldMask);

    _sfSofaSceneFile.setValue(value);
}
//! Get the value of the SofaItem::_sfIgnoreSofaLights field.

inline
bool &SofaItemBase::editIgnoreSofaLights(void)
{
    editSField(IgnoreSofaLightsFieldMask);

    return _sfIgnoreSofaLights.getValue();
}

//! Get the value of the SofaItem::_sfIgnoreSofaLights field.
inline
      bool  SofaItemBase::getIgnoreSofaLights(void) const
{
    return _sfIgnoreSofaLights.getValue();
}

//! Set the value of the SofaItem::_sfIgnoreSofaLights field.
inline
void SofaItemBase::setIgnoreSofaLights(const bool value)
{
    editSField(IgnoreSofaLightsFieldMask);

    _sfIgnoreSofaLights.setValue(value);
}
//! Get the value of the SofaItem::_sfAnimate field.

inline
bool &SofaItemBase::editAnimate(void)
{
    editSField(AnimateFieldMask);

    return _sfAnimate.getValue();
}

//! Get the value of the SofaItem::_sfAnimate field.
inline
      bool  SofaItemBase::getAnimate(void) const
{
    return _sfAnimate.getValue();
}

//! Set the value of the SofaItem::_sfAnimate field.
inline
void SofaItemBase::setAnimate(const bool value)
{
    editSField(AnimateFieldMask);

    _sfAnimate.setValue(value);
}
//! Get the value of the SofaItem::_sfReset field.

inline
bool &SofaItemBase::editReset(void)
{
    editSField(ResetFieldMask);

    return _sfReset.getValue();
}

//! Get the value of the SofaItem::_sfReset field.
inline
      bool  SofaItemBase::getReset(void) const
{
    return _sfReset.getValue();
}

//! Set the value of the SofaItem::_sfReset field.
inline
void SofaItemBase::setReset(const bool value)
{
    editSField(ResetFieldMask);

    _sfReset.setValue(value);
}
//! Get the value of the SofaItem::_sfMouseData field.

inline
MouseData &SofaItemBase::editMouseData(void)
{
    editSField(MouseDataFieldMask);

    return _sfMouseData.getValue();
}

//! Get the value of the SofaItem::_sfMouseData field.
inline
const MouseData &SofaItemBase::getMouseData(void) const
{
    return _sfMouseData.getValue();
}

//! Set the value of the SofaItem::_sfMouseData field.
inline
void SofaItemBase::setMouseData(const MouseData &value)
{
    editSField(MouseDataFieldMask);

    _sfMouseData.setValue(value);
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void SofaItemBase::execSync (      SofaItemBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (RotationSpeedFieldMask & whichField))
        _sfRotationSpeed.syncWith(pFrom->_sfRotationSpeed);

    if(FieldBits::NoField != (SofaDataPathFieldMask & whichField))
        _sfSofaDataPath.syncWith(pFrom->_sfSofaDataPath);

    if(FieldBits::NoField != (SofaSceneFileFieldMask & whichField))
        _sfSofaSceneFile.syncWith(pFrom->_sfSofaSceneFile);

    if(FieldBits::NoField != (IgnoreSofaLightsFieldMask & whichField))
        _sfIgnoreSofaLights.syncWith(pFrom->_sfIgnoreSofaLights);

    if(FieldBits::NoField != (AnimateFieldMask & whichField))
        _sfAnimate.syncWith(pFrom->_sfAnimate);

    if(FieldBits::NoField != (ResetFieldMask & whichField))
        _sfReset.syncWith(pFrom->_sfReset);

    if(FieldBits::NoField != (MouseDataFieldMask & whichField))
        _sfMouseData.syncWith(pFrom->_sfMouseData);
}
#endif


inline
const Char8 *SofaItemBase::getClassname(void)
{
    return "SofaItem";
}
OSG_GEN_CONTAINERPTR(SofaItem);

VCORE_END_NAMESPACE
