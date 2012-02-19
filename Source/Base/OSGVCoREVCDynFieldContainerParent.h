/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#ifndef _OSGVCOREVCDYNFIELDCONTAINERPARENT_H_
#define _OSGVCOREVCDYNFIELDCONTAINERPARENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAttachmentContainer.h"
#include "OSGDynamicContainerMixin.h"

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

/*! \ingroup GrpDynamicsBaseObj
    \nohierarchy
*/

struct AttContainerVCoreDesc
{
    typedef AttachmentContainer         ParentT;
    typedef AttachmentContainer        *ParentPtrT;
    typedef FieldContainer::TypeObject  TypeObject;

    static const Char8 *getTypeName      (void) 
    {
        return "VCDynFieldContainerParent"; 
    }

    static const Char8 *getParentTypeName(void) 
    {
        return "AttachmentContainer"; 
    }
    static const Char8 *getGroupName     (void) 
    { 
        return "VCDynFieldContainerParent"; 
    }
};

/*! \ingroup GrpDynamicsBaseObj
 */

typedef DynFieldContainer< 
            ContainerMixinHead< 
                AttContainerVCoreDesc > > VCDynFieldContainerParent;

VCORE_END_NAMESPACE

#endif /* _OSGVCOREVCDYNFIELDCONTAINERPARENT_H_ */
