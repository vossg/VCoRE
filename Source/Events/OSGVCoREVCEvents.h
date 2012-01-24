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

#ifndef _OSGVCOREVCEVENTS_H_
#define _OSGVCOREVCEVENTS_H_

#include "OSGVCoREEventsDef.h"

#include <vector>
#include "boost/bind.hpp"

//#include "boost/thread.hpp"

#include "OSGMPBase.h"

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

// mother of all events

class OSG_VCOREEVENTS_DLLMAPPING VCEvent : public MemoryObject
{
  public:

    OSG_GEN_INTERNAL_MEMOBJPTR(VCEvent);

  protected:
    
    VCEvent(void);
    ~VCEvent(void);

  private:

    // prohibit default functions (move to 'public' if you need one)
    VCEvent(const VCEvent &source);
    void operator =(const VCEvent &source);
};

OSG_GEN_MEMOBJPTR(VCEvent);

// receives events and buffers them until they are removed via swapEventList

template<class EventT>
class VCEventSink
{
    
  public:

    typedef std::vector<typename EventT::ObjRefPtr> EventList;

    VCEventSink(void);
    ~VCEventSink(void);

    void receiveEvent (typename EventT::ObjRefPtr  event );
    void swapEventList(         EventList         &events);

  protected:


//    boost::mutex _mutex;
    EventList _events;
  
  private:

    // prohibit default functions (move to 'public' if you need one)
    VCEventSink(const VCEventSink &source);
    void operator =(const VCEventSink &source);
};

// sends events to all subscribed EventSinks

template<class EventT>
class VCEventSource
{
  public:
  
    typedef std::vector< VCEventSink<EventT>* > SinkList;

  public:

    VCEventSource(void);
    ~VCEventSource(void);

    void addSink   (         VCEventSink<EventT> &sink );
    void removeSink(         VCEventSink<EventT> &sink );

    void sendEvent (typename EventT::ObjRefPtr    event);

  protected:

//    boost::mutex _mutex;
    SinkList _sinks;

  private:

    // prohibit default functions (move to 'public' if you need one)
    VCEventSource(const VCEventSource &source);
    void operator =(const VCEventSource &source);
};

VCORE_END_NAMESPACE

#include "OSGVCoREVCEvents.inl"

#endif /* _OSGVCOREVCEVENTS_H_ */
