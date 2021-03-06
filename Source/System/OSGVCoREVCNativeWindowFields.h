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
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGVCNATIVEWINDOWFIELDS_H_
#define _OSGVCNATIVEWINDOWFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGVCoRESystemDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

class VCNativeWindow;

OSG_GEN_CONTAINERPTR(VCNativeWindow);

VCORE_END_NAMESPACE

OSG_BEGIN_NAMESPACE

VCORE_IMPORT_NAMESPACE;
/*! \ingroup GrpVCoreSystemFieldTraits
    \ingroup GrpLibOSGVCoRESystem
 */
template <>
struct FieldTraits<VCNativeWindow *, nsVCoRE> :
    public FieldTraitsFCPtrBase<VCNativeWindow *, nsVCoRE>
{
  private:

    static PointerType             _type;

  public:

    typedef FieldTraits<VCNativeWindow *, nsVCoRE>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_VCORESYSTEM_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<VCNativeWindow *, nsVCoRE>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecVCNativeWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<VCNativeWindow *, nsVCoRE>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecVCNativeWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<VCNativeWindow *, nsVCoRE>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakVCNativeWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<VCNativeWindow *, nsVCoRE>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdVCNativeWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<VCNativeWindow *, nsVCoRE>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecVCNativeWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<VCNativeWindow *, nsVCoRE>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecVCNativeWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<VCNativeWindow *, nsVCoRE>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakVCNativeWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<VCNativeWindow *, nsVCoRE>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdVCNativeWindowPtr"; 
}


OSG_END_NAMESPACE

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpVCoreSystemFieldSFields */
typedef PointerSField<VCNativeWindow *,
                      RecordedRefCountPolicy, nsVCoRE  > SFRecVCNativeWindowPtr;
/*! \ingroup GrpVCoreSystemFieldSFields */
typedef PointerSField<VCNativeWindow *,
                      UnrecordedRefCountPolicy, nsVCoRE> SFUnrecVCNativeWindowPtr;
/*! \ingroup GrpVCoreSystemFieldSFields */
typedef PointerSField<VCNativeWindow *,
                      WeakRefCountPolicy, nsVCoRE      > SFWeakVCNativeWindowPtr;
/*! \ingroup GrpVCoreSystemFieldSFields */
typedef PointerSField<VCNativeWindow *,
                      NoRefCountPolicy, nsVCoRE        > SFUncountedVCNativeWindowPtr;


/*! \ingroup GrpVCoreSystemFieldMFields */
typedef PointerMField<VCNativeWindow *,
                      RecordedRefCountPolicy, nsVCoRE  > MFRecVCNativeWindowPtr;
/*! \ingroup GrpVCoreSystemFieldMFields */
typedef PointerMField<VCNativeWindow *,
                      UnrecordedRefCountPolicy, nsVCoRE> MFUnrecVCNativeWindowPtr;
/*! \ingroup GrpVCoreSystemFieldMFields */
typedef PointerMField<VCNativeWindow *,
                      WeakRefCountPolicy, nsVCoRE      > MFWeakVCNativeWindowPtr;
/*! \ingroup GrpVCoreSystemFieldMFields */
typedef PointerMField<VCNativeWindow *,
                      NoRefCountPolicy, nsVCoRE        > MFUncountedVCNativeWindowPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpVCoreSystemFieldSFields \ingroup GrpLibOSGVCoRESystem */
struct SFRecVCNativeWindowPtr : 
    public PointerSField<VCNativeWindow *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpVCoreSystemFieldSFields \ingroup GrpLibOSGVCoRESystem */
struct SFUnrecVCNativeWindowPtr : 
    public PointerSField<VCNativeWindow *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpVCoreSystemFieldSFields \ingroup GrpLibOSGVCoRESystem */
struct SFWeakVCNativeWindowPtr :
    public PointerSField<VCNativeWindow *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpVCoreSystemFieldSFields \ingroup GrpLibOSGVCoRESystem */
struct SFUncountedVCNativeWindowPtr :
    public PointerSField<VCNativeWindow *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpVCoreSystemFieldMFields \ingroup GrpLibOSGVCoRESystem */
struct MFRecVCNativeWindowPtr :
    public PointerMField<VCNativeWindow *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpVCoreSystemFieldMFields \ingroup GrpLibOSGVCoRESystem */
struct MFUnrecVCNativeWindowPtr :
    public PointerMField<VCNativeWindow *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpVCoreSystemFieldMFields \ingroup GrpLibOSGVCoRESystem */
struct MFWeakVCNativeWindowPtr :
    public PointerMField<VCNativeWindow *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpVCoreSystemFieldMFields \ingroup GrpLibOSGVCoRESystem */
struct MFUncountedVCNativeWindowPtr :
    public PointerMField<VCNativeWindow *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

VCORE_END_NAMESPACE

#endif /* _OSGVCNATIVEWINDOWFIELDS_H_ */
