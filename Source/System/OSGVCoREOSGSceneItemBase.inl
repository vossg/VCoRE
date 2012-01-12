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
 **     class OSGSceneItem!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;


//! access the type of the class
inline
OSG::FieldContainerType &OSGSceneItemBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 OSGSceneItemBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 OSGSceneItemBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the OSGSceneItem::_sfMatchedUrl field.

inline
std::string &OSGSceneItemBase::editMatchedUrl(void)
{
    editSField(MatchedUrlFieldMask);

    return _sfMatchedUrl.getValue();
}

//! Get the value of the OSGSceneItem::_sfMatchedUrl field.
inline
const std::string &OSGSceneItemBase::getMatchedUrl(void) const
{
    return _sfMatchedUrl.getValue();
}

//! Set the value of the OSGSceneItem::_sfMatchedUrl field.
inline
void OSGSceneItemBase::setMatchedUrl(const std::string &value)
{
    editSField(MatchedUrlFieldMask);

    _sfMatchedUrl.setValue(value);
}

//! Get the value of the OSGSceneItem::_sfRoot field.
inline
Node * OSGSceneItemBase::getRoot(void) const
{
    return _sfRoot.getValue();
}

//! Set the value of the OSGSceneItem::_sfRoot field.
inline
void OSGSceneItemBase::setRoot(Node * const value)
{
    editSField(RootFieldMask);

    _sfRoot.setValue(value);
}
//! Get the value of the OSGSceneItem::_sfMatchedGlobalUrl field.

inline
std::string &OSGSceneItemBase::editMatchedGlobalUrl(void)
{
    editSField(MatchedGlobalUrlFieldMask);

    return _sfMatchedGlobalUrl.getValue();
}

//! Get the value of the OSGSceneItem::_sfMatchedGlobalUrl field.
inline
const std::string &OSGSceneItemBase::getMatchedGlobalUrl(void) const
{
    return _sfMatchedGlobalUrl.getValue();
}

//! Set the value of the OSGSceneItem::_sfMatchedGlobalUrl field.
inline
void OSGSceneItemBase::setMatchedGlobalUrl(const std::string &value)
{
    editSField(MatchedGlobalUrlFieldMask);

    _sfMatchedGlobalUrl.setValue(value);
}

//! Get the value of the OSGSceneItem::_sfCamera field.
inline
Camera * OSGSceneItemBase::getCamera(void) const
{
    return _sfCamera.getValue();
}

//! Set the value of the OSGSceneItem::_sfCamera field.
inline
void OSGSceneItemBase::setCamera(Camera * const value)
{
    editSField(CameraFieldMask);

    _sfCamera.setValue(value);
}
//! Get the value of the OSGSceneItem::_sfActiveCamera field.

inline
std::string &OSGSceneItemBase::editActiveCamera(void)
{
    editSField(ActiveCameraFieldMask);

    return _sfActiveCamera.getValue();
}

//! Get the value of the OSGSceneItem::_sfActiveCamera field.
inline
const std::string &OSGSceneItemBase::getActiveCamera(void) const
{
    return _sfActiveCamera.getValue();
}

//! Set the value of the OSGSceneItem::_sfActiveCamera field.
inline
void OSGSceneItemBase::setActiveCamera(const std::string &value)
{
    editSField(ActiveCameraFieldMask);

    _sfActiveCamera.setValue(value);
}

//! Get the value of the \a index element the OSGSceneItem::_mfUrl field.
inline
const std::string &OSGSceneItemBase::getUrl(const UInt32 index) const
{
    return _mfUrl[index];
}

inline
std::string &OSGSceneItemBase::editUrl(const UInt32 index)
{
    editMField(UrlFieldMask, _mfUrl);

    return _mfUrl[index];
}


//! Get the value of the \a index element the OSGSceneItem::_mfGlobals field.
inline
FieldContainer * OSGSceneItemBase::getGlobals(const UInt32 index) const
{
    return _mfGlobals[index];
}

//! Get the value of the \a index element the OSGSceneItem::_mfGlobalUrl field.
inline
const std::string &OSGSceneItemBase::getGlobalUrl(const UInt32 index) const
{
    return _mfGlobalUrl[index];
}

inline
std::string &OSGSceneItemBase::editGlobalUrl(const UInt32 index)
{
    editMField(GlobalUrlFieldMask, _mfGlobalUrl);

    return _mfGlobalUrl[index];
}



#ifdef OSG_MT_CPTR_ASPECT
inline
void OSGSceneItemBase::execSync (      OSGSceneItemBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (UrlFieldMask & whichField))
        _mfUrl.syncWith(pFrom->_mfUrl,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (MatchedUrlFieldMask & whichField))
        _sfMatchedUrl.syncWith(pFrom->_sfMatchedUrl);

    if(FieldBits::NoField != (RootFieldMask & whichField))
        _sfRoot.syncWith(pFrom->_sfRoot);

    if(FieldBits::NoField != (GlobalsFieldMask & whichField))
        _mfGlobals.syncWith(pFrom->_mfGlobals,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (GlobalUrlFieldMask & whichField))
        _mfGlobalUrl.syncWith(pFrom->_mfGlobalUrl,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (MatchedGlobalUrlFieldMask & whichField))
        _sfMatchedGlobalUrl.syncWith(pFrom->_sfMatchedGlobalUrl);

    if(FieldBits::NoField != (CameraFieldMask & whichField))
        _sfCamera.syncWith(pFrom->_sfCamera);

    if(FieldBits::NoField != (ActiveCameraFieldMask & whichField))
        _sfActiveCamera.syncWith(pFrom->_sfActiveCamera);
}
#endif


inline
const Char8 *OSGSceneItemBase::getClassname(void)
{
    return "OSGSceneItem";
}
OSG_GEN_CONTAINERPTR(OSGSceneItem);

VCORE_END_NAMESPACE

