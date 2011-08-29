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


#ifndef _OSGVCOREDYNFIELDCONTAINERFIELDS_H_
#define _OSGVCOREDYNFIELDCONTAINERFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGVCoreBaseDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE

class VCoreDynFieldContainer;

OSG_GEN_CONTAINERPTR(VCoreDynFieldContainer);

/*! \ingroup GrpVCoreBaseFieldTraits
    \ingroup GrpLibOSGVCoreBase
 */
template <>
struct FieldTraits<VCoreDynFieldContainer *> :
    public FieldTraitsFCPtrBase<VCoreDynFieldContainer *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<VCoreDynFieldContainer *>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_VCOREBASE_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFVCoreDynFieldContainerPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFVCoreDynFieldContainerPtr"; }
};

template<> inline
const Char8 *FieldTraits<VCoreDynFieldContainer *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecVCoreDynFieldContainerPtr"; 
}

template<> inline
const Char8 *FieldTraits<VCoreDynFieldContainer *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecVCoreDynFieldContainerPtr"; 
}

template<> inline
const Char8 *FieldTraits<VCoreDynFieldContainer *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakVCoreDynFieldContainerPtr"; 
}

template<> inline
const Char8 *FieldTraits<VCoreDynFieldContainer *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdVCoreDynFieldContainerPtr"; 
}

template<> inline
const Char8 *FieldTraits<VCoreDynFieldContainer *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecVCoreDynFieldContainerPtr"; 
}

template<> inline
const Char8 *FieldTraits<VCoreDynFieldContainer *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecVCoreDynFieldContainerPtr"; 
}

template<> inline
const Char8 *FieldTraits<VCoreDynFieldContainer *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakVCoreDynFieldContainerPtr"; 
}

template<> inline
const Char8 *FieldTraits<VCoreDynFieldContainer *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdVCoreDynFieldContainerPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpVCoreBaseFieldSFields */
typedef PointerSField<VCoreDynFieldContainer *,
                      RecordedRefCountPolicy  > SFRecVCoreDynFieldContainerPtr;
/*! \ingroup GrpVCoreBaseFieldSFields */
typedef PointerSField<VCoreDynFieldContainer *,
                      UnrecordedRefCountPolicy> SFUnrecVCoreDynFieldContainerPtr;
/*! \ingroup GrpVCoreBaseFieldSFields */
typedef PointerSField<VCoreDynFieldContainer *,
                      WeakRefCountPolicy      > SFWeakVCoreDynFieldContainerPtr;
/*! \ingroup GrpVCoreBaseFieldSFields */
typedef PointerSField<VCoreDynFieldContainer *,
                      NoRefCountPolicy        > SFUncountedVCoreDynFieldContainerPtr;


/*! \ingroup GrpVCoreBaseFieldMFields */
typedef PointerMField<VCoreDynFieldContainer *,
                      RecordedRefCountPolicy  > MFRecVCoreDynFieldContainerPtr;
/*! \ingroup GrpVCoreBaseFieldMFields */
typedef PointerMField<VCoreDynFieldContainer *,
                      UnrecordedRefCountPolicy> MFUnrecVCoreDynFieldContainerPtr;
/*! \ingroup GrpVCoreBaseFieldMFields */
typedef PointerMField<VCoreDynFieldContainer *,
                      WeakRefCountPolicy      > MFWeakVCoreDynFieldContainerPtr;
/*! \ingroup GrpVCoreBaseFieldMFields */
typedef PointerMField<VCoreDynFieldContainer *,
                      NoRefCountPolicy        > MFUncountedVCoreDynFieldContainerPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpVCoreBaseFieldSFields \ingroup GrpLibOSGVCoreBase */
struct SFRecVCoreDynFieldContainerPtr : 
    public PointerSField<VCoreDynFieldContainer *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpVCoreBaseFieldSFields \ingroup GrpLibOSGVCoreBase */
struct SFUnrecVCoreDynFieldContainerPtr : 
    public PointerSField<VCoreDynFieldContainer *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpVCoreBaseFieldSFields \ingroup GrpLibOSGVCoreBase */
struct SFWeakVCoreDynFieldContainerPtr :
    public PointerSField<VCoreDynFieldContainer *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpVCoreBaseFieldSFields \ingroup GrpLibOSGVCoreBase */
struct SFUncountedVCoreDynFieldContainerPtr :
    public PointerSField<VCoreDynFieldContainer *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpVCoreBaseFieldMFields \ingroup GrpLibOSGVCoreBase */
struct MFRecVCoreDynFieldContainerPtr :
    public PointerMField<VCoreDynFieldContainer *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpVCoreBaseFieldMFields \ingroup GrpLibOSGVCoreBase */
struct MFUnrecVCoreDynFieldContainerPtr :
    public PointerMField<VCoreDynFieldContainer *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpVCoreBaseFieldMFields \ingroup GrpLibOSGVCoreBase */
struct MFWeakVCoreDynFieldContainerPtr :
    public PointerMField<VCoreDynFieldContainer *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpVCoreBaseFieldMFields \ingroup GrpLibOSGVCoreBase */
struct MFUncountedVCoreDynFieldContainerPtr :
    public PointerMField<VCoreDynFieldContainer *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGVCOREDYNFIELDCONTAINERFIELDS_H_ */
