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
 **     class VCGLUTViewer!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &VCGLUTViewerBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 VCGLUTViewerBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 VCGLUTViewerBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the VCGLUTViewer::_sfPostDFMixinTestField field.

inline
Int32 &VCGLUTViewerBase::editPostDFMixinTestField(void)
{
    editSField(PostDFMixinTestFieldFieldMask);

    return _sfPostDFMixinTestField.getValue();
}

//! Get the value of the VCGLUTViewer::_sfPostDFMixinTestField field.
inline
      Int32  VCGLUTViewerBase::getPostDFMixinTestField(void) const
{
    return _sfPostDFMixinTestField.getValue();
}

//! Set the value of the VCGLUTViewer::_sfPostDFMixinTestField field.
inline
void VCGLUTViewerBase::setPostDFMixinTestField(const Int32 value)
{
    editSField(PostDFMixinTestFieldFieldMask);

    _sfPostDFMixinTestField.setValue(value);
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void VCGLUTViewerBase::execSync (      VCGLUTViewerBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (PostDFMixinTestFieldFieldMask & whichField))
        _sfPostDFMixinTestField.syncWith(pFrom->_sfPostDFMixinTestField);
}
#endif


inline
const Char8 *VCGLUTViewerBase::getClassname(void)
{
    return "VCGLUTViewer";
}
OSG_GEN_CONTAINERPTR(VCGLUTViewer);

OSG_END_NAMESPACE
