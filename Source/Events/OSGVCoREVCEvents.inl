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
VCEvent::VCEvent(void)
{
}

inline
VCEvent::~VCEvent(void)
{
}


template<class EventT> inline
VCEventSink<EventT>::VCEventSink(void) : 
    _events()
{
}


template<class EventT> inline
VCEventSink<EventT>::~VCEventSink(void)
{
}


template<class EventT> inline
void VCEventSink<EventT>::receiveEvent(typename EventT::ObjRefPtr event)
{
//        boost::mutex::scoped_lock lock(_mutex);
    _events.push_back(event);
}


template<class EventT> inline
void VCEventSink<EventT>::swapEventList(EventList &events)
{
//        boost::mutex::scoped_lock lock(_mutex);
    events.swap(_events);
}



template<class EventT> inline
VCEventSource<EventT>::VCEventSource(void) : 
    _sinks()
{
}


template<class EventT> inline
VCEventSource<EventT>::~VCEventSource(void)
{
}


template<class EventT> inline
void VCEventSource<EventT>::addSink(VCEventSink<EventT>& sink)
{
//        boost::mutex::scoped_lock lock(_mutex);
    _sinks.push_back(&sink);
}



template<class EventT> inline
void VCEventSource<EventT>::removeSink(VCEventSink<EventT>& sink)
{
//        boost::mutex::scoped_lock lock(_mutex);
    
    _sinks.erase(std::remove( _sinks.begin(), 
                              _sinks.end  (), 
                             & sink         ), 
                 _sinks.end());
}


template<class EventT> inline
void VCEventSource<EventT>::sendEvent(typename EventT::ObjRefPtr event)
{
//        boost::mutex::scoped_lock lock(_mutex);

    // send the event to all sinks

    for_each(_sinks.begin(), 
             _sinks.end(),
              boost::bind(&VCEventSink<EventT>::receiveEvent,_1,event));
}

VCORE_END_NAMESPACE
