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


#ifndef _OSGVCOREREPOSITORYFIELDS_H_
#define _OSGVCOREREPOSITORYFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGVCoreSystemDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE

class VCoreRepository;

OSG_GEN_CONTAINERPTR(VCoreRepository);

/*! \ingroup GrpVCoreSystemFieldTraits
    \ingroup GrpLibOSGVCoreSystem
 */
template <>
struct FieldTraits<VCoreRepository *> :
    public FieldTraitsFCPtrBase<VCoreRepository *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<VCoreRepository *>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_VCORESYSTEM_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFVCoreRepositoryPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFVCoreRepositoryPtr"; }
};

template<> inline
const Char8 *FieldTraits<VCoreRepository *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecVCoreRepositoryPtr"; 
}

template<> inline
const Char8 *FieldTraits<VCoreRepository *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecVCoreRepositoryPtr"; 
}

template<> inline
const Char8 *FieldTraits<VCoreRepository *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakVCoreRepositoryPtr"; 
}

template<> inline
const Char8 *FieldTraits<VCoreRepository *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdVCoreRepositoryPtr"; 
}

template<> inline
const Char8 *FieldTraits<VCoreRepository *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecVCoreRepositoryPtr"; 
}

template<> inline
const Char8 *FieldTraits<VCoreRepository *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecVCoreRepositoryPtr"; 
}

template<> inline
const Char8 *FieldTraits<VCoreRepository *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakVCoreRepositoryPtr"; 
}

template<> inline
const Char8 *FieldTraits<VCoreRepository *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdVCoreRepositoryPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpVCoreSystemFieldSFields */
typedef PointerSField<VCoreRepository *,
                      RecordedRefCountPolicy  > SFRecVCoreRepositoryPtr;
/*! \ingroup GrpVCoreSystemFieldSFields */
typedef PointerSField<VCoreRepository *,
                      UnrecordedRefCountPolicy> SFUnrecVCoreRepositoryPtr;
/*! \ingroup GrpVCoreSystemFieldSFields */
typedef PointerSField<VCoreRepository *,
                      WeakRefCountPolicy      > SFWeakVCoreRepositoryPtr;
/*! \ingroup GrpVCoreSystemFieldSFields */
typedef PointerSField<VCoreRepository *,
                      NoRefCountPolicy        > SFUncountedVCoreRepositoryPtr;


/*! \ingroup GrpVCoreSystemFieldMFields */
typedef PointerMField<VCoreRepository *,
                      RecordedRefCountPolicy  > MFRecVCoreRepositoryPtr;
/*! \ingroup GrpVCoreSystemFieldMFields */
typedef PointerMField<VCoreRepository *,
                      UnrecordedRefCountPolicy> MFUnrecVCoreRepositoryPtr;
/*! \ingroup GrpVCoreSystemFieldMFields */
typedef PointerMField<VCoreRepository *,
                      WeakRefCountPolicy      > MFWeakVCoreRepositoryPtr;
/*! \ingroup GrpVCoreSystemFieldMFields */
typedef PointerMField<VCoreRepository *,
                      NoRefCountPolicy        > MFUncountedVCoreRepositoryPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpVCoreSystemFieldSFields \ingroup GrpLibOSGVCoreSystem */
struct SFRecVCoreRepositoryPtr : 
    public PointerSField<VCoreRepository *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpVCoreSystemFieldSFields \ingroup GrpLibOSGVCoreSystem */
struct SFUnrecVCoreRepositoryPtr : 
    public PointerSField<VCoreRepository *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpVCoreSystemFieldSFields \ingroup GrpLibOSGVCoreSystem */
struct SFWeakVCoreRepositoryPtr :
    public PointerSField<VCoreRepository *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpVCoreSystemFieldSFields \ingroup GrpLibOSGVCoreSystem */
struct SFUncountedVCoreRepositoryPtr :
    public PointerSField<VCoreRepository *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpVCoreSystemFieldMFields \ingroup GrpLibOSGVCoreSystem */
struct MFRecVCoreRepositoryPtr :
    public PointerMField<VCoreRepository *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpVCoreSystemFieldMFields \ingroup GrpLibOSGVCoreSystem */
struct MFUnrecVCoreRepositoryPtr :
    public PointerMField<VCoreRepository *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpVCoreSystemFieldMFields \ingroup GrpLibOSGVCoreSystem */
struct MFWeakVCoreRepositoryPtr :
    public PointerMField<VCoreRepository *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpVCoreSystemFieldMFields \ingroup GrpLibOSGVCoreSystem */
struct MFUncountedVCoreRepositoryPtr :
    public PointerMField<VCoreRepository *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGVCOREREPOSITORYFIELDS_H_ */