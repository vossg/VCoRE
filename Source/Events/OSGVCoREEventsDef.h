/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2003 by the OpenSG Forum                    *
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

#ifndef _OSGVCOREEVENTSDEF_H_
#define _OSGVCOREEVENTSDEF_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGVCoRENamespace.h"

//---------------------------------------------------------------------------
//  Defines
//---------------------------------------------------------------------------

#if defined(WIN32)
#   ifdef OSG_COMPILEVCOREEVENTSLIB
#       define OSG_VCOREEVENTS_DLLMAPPING     __declspec(dllexport)
#       define OSG_VCOREEVENTS_DLLTMPLMAPPING __declspec(dllexport)
#   else
#       define OSG_VCOREEVENTS_DLLMAPPING     __declspec(dllimport)
#       define OSG_VCOREEVENTS_DLLTMPLMAPPING __declspec(dllimport)
#   endif
#else
#define OSG_VCOREEVENTS_DLLMAPPING
#define OSG_VCOREEVENTS_DLLTMPLMAPPING
#endif

#endif /* _OSGVCOREEVENTSDEF_H_ */
