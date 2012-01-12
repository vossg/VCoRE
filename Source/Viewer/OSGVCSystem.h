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

#ifndef _OSGVCSYSTEM_H_
#define _OSGVCSYSTEM_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGVCoREViewerDef.h"

#include <memory>
#include <vector>

#include "boost/function.hpp"

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

class OSG_VCOREVIEWER_DLLMAPPING VCSystem
{
// static interface
public:
    static void init(int argc, char **argv);
    static void shutdown();
    static VCSystem* the();
private:
    static VCSystem* _the;

// instance interface
public:

private:
    VCSystem();
    VCSystem(const VCSystem&);
    ~VCSystem();
    const VCSystem& operator = (const VCSystem&);
};

VCORE_END_NAMESPACE

#include "OSGVCSystem.inl"

#endif /* _OSGVCSYSTEM_H_ */
