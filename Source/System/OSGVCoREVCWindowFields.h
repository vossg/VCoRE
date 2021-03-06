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


#ifndef _OSGVCWINDOWFIELDS_H_
#define _OSGVCWINDOWFIELDS_H_
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

class VCWindow;

OSG_GEN_CONTAINERPTR(VCWindow);

VCORE_END_NAMESPACE

OSG_BEGIN_NAMESPACE

VCORE_IMPORT_NAMESPACE;
/*! \ingroup GrpVCoreSystemFieldTraits
    \ingroup GrpLibOSGVCoRESystem
 */
template <>
struct FieldTraits<VCWindow *, nsVCoRE> :
    public FieldTraitsFCPtrBase<VCWindow *, nsVCoRE>
{
  private:

    static PointerType             _type;

  public:

    typedef FieldTraits<VCWindow *, nsVCoRE>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_VCORESYSTEM_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<VCWindow *, nsVCoRE>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecVCWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<VCWindow *, nsVCoRE>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecVCWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<VCWindow *, nsVCoRE>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakVCWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<VCWindow *, nsVCoRE>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdVCWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<VCWindow *, nsVCoRE>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecVCWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<VCWindow *, nsVCoRE>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecVCWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<VCWindow *, nsVCoRE>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakVCWindowPtr"; 
}

template<> inline
const Char8 *FieldTraits<VCWindow *, nsVCoRE>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdVCWindowPtr"; 
}


OSG_END_NAMESPACE

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpVCoreSystemFieldSFields */
typedef PointerSField<VCWindow *,
                      RecordedRefCountPolicy, nsVCoRE  > SFRecVCWindowPtr;
/*! \ingroup GrpVCoreSystemFieldSFields */
typedef PointerSField<VCWindow *,
                      UnrecordedRefCountPolicy, nsVCoRE> SFUnrecVCWindowPtr;
/*! \ingroup GrpVCoreSystemFieldSFields */
typedef PointerSField<VCWindow *,
                      WeakRefCountPolicy, nsVCoRE      > SFWeakVCWindowPtr;
/*! \ingroup GrpVCoreSystemFieldSFields */
typedef PointerSField<VCWindow *,
                      NoRefCountPolicy, nsVCoRE        > SFUncountedVCWindowPtr;


/*! \ingroup GrpVCoreSystemFieldMFields */
typedef PointerMField<VCWindow *,
                      RecordedRefCountPolicy, nsVCoRE  > MFRecVCWindowPtr;
/*! \ingroup GrpVCoreSystemFieldMFields */
typedef PointerMField<VCWindow *,
                      UnrecordedRefCountPolicy, nsVCoRE> MFUnrecVCWindowPtr;
/*! \ingroup GrpVCoreSystemFieldMFields */
typedef PointerMField<VCWindow *,
                      WeakRefCountPolicy, nsVCoRE      > MFWeakVCWindowPtr;
/*! \ingroup GrpVCoreSystemFieldMFields */
typedef PointerMField<VCWindow *,
                      NoRefCountPolicy, nsVCoRE        > MFUncountedVCWindowPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpVCoreSystemFieldSFields \ingroup GrpLibOSGVCoRESystem */
struct SFRecVCWindowPtr : 
    public PointerSField<VCWindow *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpVCoreSystemFieldSFields \ingroup GrpLibOSGVCoRESystem */
struct SFUnrecVCWindowPtr : 
    public PointerSField<VCWindow *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpVCoreSystemFieldSFields \ingroup GrpLibOSGVCoRESystem */
struct SFWeakVCWindowPtr :
    public PointerSField<VCWindow *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpVCoreSystemFieldSFields \ingroup GrpLibOSGVCoRESystem */
struct SFUncountedVCWindowPtr :
    public PointerSField<VCWindow *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpVCoreSystemFieldMFields \ingroup GrpLibOSGVCoRESystem */
struct MFRecVCWindowPtr :
    public PointerMField<VCWindow *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpVCoreSystemFieldMFields \ingroup GrpLibOSGVCoRESystem */
struct MFUnrecVCWindowPtr :
    public PointerMField<VCWindow *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpVCoreSystemFieldMFields \ingroup GrpLibOSGVCoRESystem */
struct MFWeakVCWindowPtr :
    public PointerMField<VCWindow *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpVCoreSystemFieldMFields \ingroup GrpLibOSGVCoRESystem */
struct MFUncountedVCWindowPtr :
    public PointerMField<VCWindow *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

VCORE_END_NAMESPACE

#endif /* _OSGVCWINDOWFIELDS_H_ */
