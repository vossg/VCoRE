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

#ifndef _OSGVCWINDOWEVENT_H_
#define _OSGVCWINDOWEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGVCoreViewerDef.h"

#include <vector>

//#include "boost/thread.hpp"

#include "OSGMPBase.h"

OSG_BEGIN_NAMESPACE

class OSG_VCOREVIEWER_DLLMAPPING VCEvent: public MemoryObject
{
public:
    OSG_GEN_INTERNAL_MEMOBJPTR(VCEvent);

};
OSG_GEN_MEMOBJPTR(VCEvent);

template<class EventT>
class OSG_VCOREVIEWER_DLLMAPPING VCEventSink
{
public:
    typedef std::vector< typename EventT::ObjRefPtr > EventList;
public:
    void receiveEvent(typename EventT::ObjRefPtr event)
    {
//        boost::mutex::scoped_lock lock(_mutex);
        _events.push_back(event);
    }
    void swapEventList(EventList& events)
    {
//        boost::mutex::scoped_lock lock(_mutex);
        events.swap(_events);
    }
private:
//    boost::mutex _mutex;
    EventList _events;
};

template<class EventT>
class OSG_VCOREVIEWER_DLLMAPPING VCEventSource
{
public:
    typedef std::vector< VCEventSink<EventT>* > SinkList;
public:
    void addSink(VCEventSink<EventT>& sink)
    {
//        boost::mutex::scoped_lock lock(_mutex);
        _sinks.push_back(&sink);
    }
    void removeSink(VCEventSink<EventT>& sink)
    {
//        boost::mutex::scoped_lock lock(_mutex);
        _sinks.erase(std::remove(_sinks.begin(), _sinks.end(), &sink), _sinks.end());
    }
    void sendEvent(typename EventT::ObjRefPtr event)
    {
//        boost::mutex::scoped_lock lock(_mutex);
        // send the event to all sinks
        for_each(_sinks.begin(), _sinks.end(),
            boost::bind(&VCEventSink<EventT>::receiveEvent,_1,event)
            );
    }
private:
//    boost::mutex _mutex;
    SinkList _sinks;
};



class OSG_VCOREVIEWER_DLLMAPPING VCWindowEvent: public VCEvent
{
public:
    OSG_GEN_INTERNAL_MEMOBJPTR(VCEvent);
};
OSG_GEN_MEMOBJPTR(VCWindowEvent);
typedef VCEventSource<VCWindowEvent> VCWindowEventSource;
typedef VCEventSink<VCWindowEvent> VCWindowEventSink;


class OSG_VCOREVIEWER_DLLMAPPING VCDisplayWindowEvent: public VCWindowEvent
{
public:
    OSG_GEN_INTERNAL_MEMOBJPTR(VCDisplayWindowEvent);
public:

};
OSG_GEN_MEMOBJPTR(VCDisplayWindowEvent);

class OSG_VCOREVIEWER_DLLMAPPING VCResizeWindowEvent: public VCWindowEvent
{
public:
    OSG_GEN_INTERNAL_MEMOBJPTR(VCResizeWindowEvent);
public:
    VCResizeWindowEvent(int width, int height)
        : _width(width), _height(height)
    {}

    int _width;
    int _height;
};
OSG_GEN_MEMOBJPTR(VCResizeWindowEvent);

class OSG_VCOREVIEWER_DLLMAPPING VCMouseWindowEvent: public VCWindowEvent
{
public:
    OSG_GEN_INTERNAL_MEMOBJPTR(VCMouseWindowEvent);
public:
    VCMouseWindowEvent(int x, int y, int button, int buttonState)
        : _x(x), _y(y), _button(button), _buttonState(buttonState)
    {}

    int _x;
    int _y;
    int _button;
    int _buttonState;
};
OSG_GEN_MEMOBJPTR(VCMouseWindowEvent);

class OSG_VCOREVIEWER_DLLMAPPING VCKeyboardWindowEvent: public VCWindowEvent
{
public:
    OSG_GEN_INTERNAL_MEMOBJPTR(VCKeyboardWindowEvent);
    enum EventType
    {
        EventType_Up,
        EventType_Down,
        EventType_NumOf,
    };
public:
    VCKeyboardWindowEvent(int x, int y, int key, EventType eventType)
        : _x(x), _y(y), _key(key), _eventType(eventType)
    {}

    int _x;
    int _y;
    int _key;
    EventType _eventType;
};
OSG_GEN_MEMOBJPTR(VCKeyboardWindowEvent);

OSG_END_NAMESPACE

#include "OSGVCWindowEvent.inl"

#endif /* _OSGVCWINDOWEVENT_H_ */
