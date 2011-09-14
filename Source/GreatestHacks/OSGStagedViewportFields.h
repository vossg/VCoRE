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
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGSTAGEDVIEWPORTFIELDS_H_
#define _OSGSTAGEDVIEWPORTFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGVCoreGreatestHacksDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE

class StagedViewport;

OSG_GEN_CONTAINERPTR(StagedViewport);

/*! \ingroup GrpVCoreGreatestHacksFieldTraits
    \ingroup GrpLibOSGVCoreGreatestHacks
 */
template <>
struct FieldTraits<StagedViewport *> :
    public FieldTraitsFCPtrBase<StagedViewport *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<StagedViewport *>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_VCOREGREATESTHACKS_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFStagedViewportPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFStagedViewportPtr"; }
};

template<> inline
const Char8 *FieldTraits<StagedViewport *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecStagedViewportPtr"; 
}

template<> inline
const Char8 *FieldTraits<StagedViewport *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecStagedViewportPtr"; 
}

template<> inline
const Char8 *FieldTraits<StagedViewport *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakStagedViewportPtr"; 
}

template<> inline
const Char8 *FieldTraits<StagedViewport *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdStagedViewportPtr"; 
}

template<> inline
const Char8 *FieldTraits<StagedViewport *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecStagedViewportPtr"; 
}

template<> inline
const Char8 *FieldTraits<StagedViewport *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecStagedViewportPtr"; 
}

template<> inline
const Char8 *FieldTraits<StagedViewport *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakStagedViewportPtr"; 
}

template<> inline
const Char8 *FieldTraits<StagedViewport *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdStagedViewportPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpVCoreGreatestHacksFieldSFields */
typedef PointerSField<StagedViewport *,
                      RecordedRefCountPolicy  > SFRecStagedViewportPtr;
/*! \ingroup GrpVCoreGreatestHacksFieldSFields */
typedef PointerSField<StagedViewport *,
                      UnrecordedRefCountPolicy> SFUnrecStagedViewportPtr;
/*! \ingroup GrpVCoreGreatestHacksFieldSFields */
typedef PointerSField<StagedViewport *,
                      WeakRefCountPolicy      > SFWeakStagedViewportPtr;
/*! \ingroup GrpVCoreGreatestHacksFieldSFields */
typedef PointerSField<StagedViewport *,
                      NoRefCountPolicy        > SFUncountedStagedViewportPtr;


/*! \ingroup GrpVCoreGreatestHacksFieldMFields */
typedef PointerMField<StagedViewport *,
                      RecordedRefCountPolicy  > MFRecStagedViewportPtr;
/*! \ingroup GrpVCoreGreatestHacksFieldMFields */
typedef PointerMField<StagedViewport *,
                      UnrecordedRefCountPolicy> MFUnrecStagedViewportPtr;
/*! \ingroup GrpVCoreGreatestHacksFieldMFields */
typedef PointerMField<StagedViewport *,
                      WeakRefCountPolicy      > MFWeakStagedViewportPtr;
/*! \ingroup GrpVCoreGreatestHacksFieldMFields */
typedef PointerMField<StagedViewport *,
                      NoRefCountPolicy        > MFUncountedStagedViewportPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpVCoreGreatestHacksFieldSFields \ingroup GrpLibOSGVCoreGreatestHacks */
struct SFRecStagedViewportPtr : 
    public PointerSField<StagedViewport *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpVCoreGreatestHacksFieldSFields \ingroup GrpLibOSGVCoreGreatestHacks */
struct SFUnrecStagedViewportPtr : 
    public PointerSField<StagedViewport *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpVCoreGreatestHacksFieldSFields \ingroup GrpLibOSGVCoreGreatestHacks */
struct SFWeakStagedViewportPtr :
    public PointerSField<StagedViewport *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpVCoreGreatestHacksFieldSFields \ingroup GrpLibOSGVCoreGreatestHacks */
struct SFUncountedStagedViewportPtr :
    public PointerSField<StagedViewport *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpVCoreGreatestHacksFieldMFields \ingroup GrpLibOSGVCoreGreatestHacks */
struct MFRecStagedViewportPtr :
    public PointerMField<StagedViewport *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpVCoreGreatestHacksFieldMFields \ingroup GrpLibOSGVCoreGreatestHacks */
struct MFUnrecStagedViewportPtr :
    public PointerMField<StagedViewport *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpVCoreGreatestHacksFieldMFields \ingroup GrpLibOSGVCoreGreatestHacks */
struct MFWeakStagedViewportPtr :
    public PointerMField<StagedViewport *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpVCoreGreatestHacksFieldMFields \ingroup GrpLibOSGVCoreGreatestHacks */
struct MFUncountedStagedViewportPtr :
    public PointerMField<StagedViewport *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGSTAGEDVIEWPORTFIELDS_H_ */
