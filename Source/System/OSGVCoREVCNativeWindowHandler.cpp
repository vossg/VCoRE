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


/***************************************************************************\
*                             Includes                                    *
\***************************************************************************/

#include <cstring>
#include <boost/bind.hpp>

#include "OSGVCoREVCNativeWindowHandler.h"
#include "OSGVCoREVCNativeWindow.h"

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::GraphOp
    \ingroup GrpSystemNodeCoresDrawablesGeometry
    
 */

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

Window *VCNativeWindowHandler::getOSGWindow(void)
{
    return _pOSGWin;
}


/*------------- constructors & destructors --------------------------------*/

VCNativeWindowHandler::VCNativeWindowHandler(void) : 
     Inherited(    ),
    _pOSGWin  (NULL),
    _pWin     (NULL)
{
}

VCNativeWindowHandler::~VCNativeWindowHandler(void)
{
    _pOSGWin = NULL;
    _pWin    = NULL;
}

/*--------------------------- Exclude List --------------------------------*/


void VCNativeWindowHandler::sendDisplayWindowEvent(void)
{
    if(_pWin != NULL)
    {
        VCDisplayWindowEventRefPtr event(new VCDisplayWindowEvent);

        _pWin->sendEvent(event);
    }
}

void VCNativeWindowHandler::sendResizeWindowEvent(Int32 width, 
                                                  Int32 height)
{
    if(_pWin != NULL)
    {
        VCResizeWindowEventRefPtr event( 
            new VCResizeWindowEvent(width, height));

        _pWin->sendEvent(event);
    }
}

void VCNativeWindowHandler::sendMouseWindowEvent(Int32 x, 
                                                 Int32 y, 
                                                 Int32 iButton, 
                                                 Int32 iButtonState)
{
    if(_pWin != NULL)
    {
        VCMouseWindowEventRefPtr event(
            new VCMouseWindowEvent(x, y, iButton, iButtonState));

        _pWin->sendEvent(event);
    }
}

void VCNativeWindowHandler::sendKeyboardWindowEvent(
    Int32                            x, 
    Int32                            y, 
    Int32                            iKey,
    VCKeyboardWindowEvent::EventType eEventType  )
{
    if(_pWin != NULL)
    {
        VCKeyboardWindowEventRefPtr event(
            new VCKeyboardWindowEvent(x, y, iKey, eEventType));

        _pWin->sendEvent(event);
    }
}

void VCNativeWindowHandler::setWindow(VCNativeWindow *pWin)
{
    _pWin = pWin;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

VCORE_END_NAMESPACE

