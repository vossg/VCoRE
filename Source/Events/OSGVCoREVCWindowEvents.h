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

#ifndef _OSGVCOREVCWINDOWEVENTS_H_
#define _OSGVCOREVCWINDOWEVENTS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGVCoREVCEvents.h"

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

// special window events, primarily for communication between VCWindow and
// NativeWindow 

class OSG_VCOREEVENTS_DLLMAPPING VCWindowEvent: public VCEvent
{
  public:
    
    typedef VCEvent Inherited;

    OSG_GEN_INTERNAL_MEMOBJPTR(VCEvent);

    VCWindowEvent(void);

  protected:

    ~VCWindowEvent(void);

  private:

    // prohibit default functions (move to 'public' if you need one)
    VCWindowEvent(const VCWindowEvent &source);
    void operator =(const VCWindowEvent &source);
};

OSG_GEN_MEMOBJPTR(VCWindowEvent);


typedef VCEventSource<VCWindowEvent> VCWindowEventSource;
typedef VCEventSink  <VCWindowEvent> VCWindowEventSink;


class OSG_VCOREEVENTS_DLLMAPPING VCDisplayWindowEvent: public VCWindowEvent
{
  public:

    typedef VCWindowEvent Inherited;

    OSG_GEN_INTERNAL_MEMOBJPTR(VCDisplayWindowEvent);

    VCDisplayWindowEvent(void);

  protected:

    ~VCDisplayWindowEvent(void);

  private:

    // prohibit default functions (move to 'public' if you need one)
    VCDisplayWindowEvent(const VCDisplayWindowEvent &source);
    void operator =(const VCDisplayWindowEvent &source);
};

OSG_GEN_MEMOBJPTR(VCDisplayWindowEvent);


class OSG_VCOREEVENTS_DLLMAPPING VCResizeWindowEvent: public VCWindowEvent
{
  public:

    typedef VCWindowEvent Inherited;

    OSG_GEN_INTERNAL_MEMOBJPTR(VCResizeWindowEvent);

    VCResizeWindowEvent(Int32 iWidth, Int32 iHeight);

    Int32 _iWidth;
    Int32 _iHeight;

  protected:

    ~VCResizeWindowEvent(void);

  private:

    // prohibit default functions (move to 'public' if you need one)
    VCResizeWindowEvent(const VCResizeWindowEvent &source);
    void operator =(const VCResizeWindowEvent &source);
};

OSG_GEN_MEMOBJPTR(VCResizeWindowEvent);


class OSG_VCOREEVENTS_DLLMAPPING VCMouseWindowEvent: public VCWindowEvent
{
  public:

    typedef VCWindowEvent Inherited;

    OSG_GEN_INTERNAL_MEMOBJPTR(VCMouseWindowEvent);

    VCMouseWindowEvent(Int32 x, Int32 y, Int32 iButton, Int32 iButtonState);

    Int32 _x;
    Int32 _y;
    Int32 _iButton;
    Int32 _iButtonState;

  protected:

    ~VCMouseWindowEvent(void);

  private:

    // prohibit default functions (move to 'public' if you need one)
    VCMouseWindowEvent(const VCMouseWindowEvent &source);
    void operator =(const VCMouseWindowEvent &source);
};

OSG_GEN_MEMOBJPTR(VCMouseWindowEvent);


class OSG_VCOREEVENTS_DLLMAPPING VCKeyboardWindowEvent: public VCWindowEvent
{
  public:

    typedef VCWindowEvent Inherited;

    OSG_GEN_INTERNAL_MEMOBJPTR(VCKeyboardWindowEvent);

    enum EventType
    {
        EventType_Up    = 0x0001,
        EventType_Down  = 0x0002,
        EventType_NumOf = 0x0003
    };


    VCKeyboardWindowEvent(Int32     x, 
                          Int32     y, 
                          Int32     iKey, 
                          EventType eEventType);

    Int32     _x;
    Int32     _y;
    Int32     _iKey;
    EventType _eEventType;

  protected:

    ~VCKeyboardWindowEvent(void);

  private:

    // prohibit default functions (move to 'public' if you need one)
    VCKeyboardWindowEvent(const VCKeyboardWindowEvent &source);
    void operator =(const VCKeyboardWindowEvent &source);
};

OSG_GEN_MEMOBJPTR(VCKeyboardWindowEvent);

VCORE_END_NAMESPACE

#include "OSGVCoREVCWindowEvents.inl"

#endif /* _OSGVCOREVCWINDOWEVENTS_H_ */
