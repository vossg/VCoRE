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


#ifndef _OSGVCRENDERTASKFIELDS_H_
#define _OSGVCRENDERTASKFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGVCoRERendererDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

class VCRenderTask;

OSG_GEN_CONTAINERPTR(VCRenderTask);

VCORE_END_NAMESPACE

OSG_BEGIN_NAMESPACE

VCORE_IMPORT_NAMESPACE;
/*! \ingroup GrpVCoreRendererFieldTraits
    \ingroup GrpLibOSGVCoRERenderer
 */
template <>
struct FieldTraits<VCRenderTask *, nsVCoRE> :
    public FieldTraitsFCPtrBase<VCRenderTask *, nsVCoRE>
{
  private:

    static PointerType             _type;

  public:

    typedef FieldTraits<VCRenderTask *, nsVCoRE>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_VCORERENDERER_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

};

template<> inline
const Char8 *FieldTraits<VCRenderTask *, nsVCoRE>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecVCRenderTaskPtr"; 
}

template<> inline
const Char8 *FieldTraits<VCRenderTask *, nsVCoRE>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecVCRenderTaskPtr"; 
}

template<> inline
const Char8 *FieldTraits<VCRenderTask *, nsVCoRE>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakVCRenderTaskPtr"; 
}

template<> inline
const Char8 *FieldTraits<VCRenderTask *, nsVCoRE>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdVCRenderTaskPtr"; 
}

template<> inline
const Char8 *FieldTraits<VCRenderTask *, nsVCoRE>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecVCRenderTaskPtr"; 
}

template<> inline
const Char8 *FieldTraits<VCRenderTask *, nsVCoRE>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecVCRenderTaskPtr"; 
}

template<> inline
const Char8 *FieldTraits<VCRenderTask *, nsVCoRE>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakVCRenderTaskPtr"; 
}

template<> inline
const Char8 *FieldTraits<VCRenderTask *, nsVCoRE>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdVCRenderTaskPtr"; 
}


OSG_END_NAMESPACE

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpVCoreRendererFieldSFields */
typedef PointerSField<VCRenderTask *,
                      RecordedRefCountPolicy, nsVCoRE  > SFRecVCRenderTaskPtr;
/*! \ingroup GrpVCoreRendererFieldSFields */
typedef PointerSField<VCRenderTask *,
                      UnrecordedRefCountPolicy, nsVCoRE> SFUnrecVCRenderTaskPtr;
/*! \ingroup GrpVCoreRendererFieldSFields */
typedef PointerSField<VCRenderTask *,
                      WeakRefCountPolicy, nsVCoRE      > SFWeakVCRenderTaskPtr;
/*! \ingroup GrpVCoreRendererFieldSFields */
typedef PointerSField<VCRenderTask *,
                      NoRefCountPolicy, nsVCoRE        > SFUncountedVCRenderTaskPtr;


/*! \ingroup GrpVCoreRendererFieldMFields */
typedef PointerMField<VCRenderTask *,
                      RecordedRefCountPolicy, nsVCoRE  > MFRecVCRenderTaskPtr;
/*! \ingroup GrpVCoreRendererFieldMFields */
typedef PointerMField<VCRenderTask *,
                      UnrecordedRefCountPolicy, nsVCoRE> MFUnrecVCRenderTaskPtr;
/*! \ingroup GrpVCoreRendererFieldMFields */
typedef PointerMField<VCRenderTask *,
                      WeakRefCountPolicy, nsVCoRE      > MFWeakVCRenderTaskPtr;
/*! \ingroup GrpVCoreRendererFieldMFields */
typedef PointerMField<VCRenderTask *,
                      NoRefCountPolicy, nsVCoRE        > MFUncountedVCRenderTaskPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpVCoreRendererFieldSFields \ingroup GrpLibOSGVCoRERenderer */
struct SFRecVCRenderTaskPtr : 
    public PointerSField<VCRenderTask *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpVCoreRendererFieldSFields \ingroup GrpLibOSGVCoRERenderer */
struct SFUnrecVCRenderTaskPtr : 
    public PointerSField<VCRenderTask *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpVCoreRendererFieldSFields \ingroup GrpLibOSGVCoRERenderer */
struct SFWeakVCRenderTaskPtr :
    public PointerSField<VCRenderTask *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpVCoreRendererFieldSFields \ingroup GrpLibOSGVCoRERenderer */
struct SFUncountedVCRenderTaskPtr :
    public PointerSField<VCRenderTask *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpVCoreRendererFieldMFields \ingroup GrpLibOSGVCoRERenderer */
struct MFRecVCRenderTaskPtr :
    public PointerMField<VCRenderTask *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpVCoreRendererFieldMFields \ingroup GrpLibOSGVCoRERenderer */
struct MFUnrecVCRenderTaskPtr :
    public PointerMField<VCRenderTask *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpVCoreRendererFieldMFields \ingroup GrpLibOSGVCoRERenderer */
struct MFWeakVCRenderTaskPtr :
    public PointerMField<VCRenderTask *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpVCoreRendererFieldMFields \ingroup GrpLibOSGVCoRERenderer */
struct MFUncountedVCRenderTaskPtr :
    public PointerMField<VCRenderTask *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

VCORE_END_NAMESPACE

#endif /* _OSGVCRENDERTASKFIELDS_H_ */
