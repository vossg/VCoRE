/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

inline
VCWindowEvent::VCWindowEvent(void) :
    Inherited()
{
}

inline
VCWindowEvent::~VCWindowEvent(void)
{
}


inline
VCDisplayWindowEvent::VCDisplayWindowEvent(void) :
    Inherited()
{
}

inline
VCDisplayWindowEvent::~VCDisplayWindowEvent(void)
{
}


inline
VCResizeWindowEvent::VCResizeWindowEvent(Int32 iWidth, Int32 iHeight) :
     Inherited(       ),
    _iWidth   (iWidth ), 
    _iHeight  (iHeight)
{
}

inline
VCResizeWindowEvent::~VCResizeWindowEvent(void)
{
}


inline
VCMouseWindowEvent::VCMouseWindowEvent(Int32 x, 
                                       Int32 y, 
                                       Int32 iButton, 
                                       Int32 iButtonState) :
     Inherited   (            ),
    _x           (x           ), 
    _y           (y           ), 
    _iButton     (iButton     ), 
    _iButtonState(iButtonState)
{
}

inline
VCMouseWindowEvent::~VCMouseWindowEvent(void)
{
}


inline
VCKeyboardWindowEvent::VCKeyboardWindowEvent(Int32     x, 
                                             Int32     y, 
                                             Int32     iKey, 
                                             EventType eEventType) :
     Inherited (          ),
    _x         (x         ), 
    _y         (y         ), 
    _iKey      (iKey      ), 
    _eEventType(eEventType)
{
}

inline
VCKeyboardWindowEvent::~VCKeyboardWindowEvent(void)
{
}

VCORE_END_NAMESPACE
