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

#ifndef _OSGVCNATIVEWINDOW_H_
#define _OSGVCNATIVEWINDOW_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGVCoREViewerDef.h"

#include <string>

#include "OSGVector.h"
#include "OSGMPBase.h"
#include "OSGWindow.h"

#include "OSGVCWindowEvent.h"

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

class OSG_VCOREVIEWER_DLLMAPPING VCNativeWindowDesc
{
public:
    std::string _title;
    bool _visible;
    bool _fullscreen;
    Vec2i _size;
    Vec2i _position;
    bool _drawCursor;
    int _sampleCount;
    bool _stereoBuffer;

    VCNativeWindowDesc()
        : _title("")
        , _visible(false)
        , _fullscreen(false)
        , _size(0,0)
        , _position(-1,-1)
        , _drawCursor(true)
        , _sampleCount(1)
        , _stereoBuffer(false)
    {}
};

class OSG_VCOREVIEWER_DLLMAPPING VCNativeWindow: public MemoryObject
{
// instance interface
public:
    virtual ~VCNativeWindow();

    WindowUnrecPtr getOSGWindow() const;

    VCWindowEventSource _windowEventSource; // sends events to VCWindow (or whoever listens)
    VCWindowEventSink _windowEventSink;     // receives events from VCWindow (or whoever is sending)

protected:
    VCNativeWindow(const VCNativeWindowDesc& desc);

    VCNativeWindowDesc _desc;       // saves _current_ state (may differ from creation params)
    WindowUnrecPtr _osgWindow;

    // send event utility functions
    void sendDisplayWindowEvent();
    void sendResizeWindowEvent(int width, int height);
    void sendMouseWindowEvent(int x, int y, int button, int buttonState);
    void sendKeyboardWindowEvent(int x, int y, int key,
        VCKeyboardWindowEvent::EventType eventType);

private:
    VCNativeWindow(const VCNativeWindow&);
    const VCNativeWindow& operator = (const VCNativeWindow&);

};
OSG_GEN_MEMOBJPTR(VCNativeWindow);

VCORE_END_NAMESPACE

#include "OSGVCNativeWindow.inl"

#endif /* _OSGVCNATIVEWINDOW_H_ */
