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

#ifndef _OSGVCAPP_H_
#define _OSGVCAPP_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGVCoreViewerDef.h"

#include <set>

//#include "OSGBaseTypes.h"
#include "OSGMPBase.h"
#include "OSGGroup.h"
#include "OSGWindow.h"
#include "OSGSimpleSceneManager.h"

#include "OSGVCNativeWindow.h"
#include "OSGVCRenderer.h"

OSG_BEGIN_NAMESPACE

class OSG_VCOREVIEWER_DLLMAPPING VCApp: public MemoryObject
{
// types
public:
    OSG_GEN_INTERNAL_MEMOBJPTR(VCApp);
    typedef boost::function< VCNativeWindowTransitPtr (const VCNativeWindowDesc&) > CreateNativeWindowFunc;
    typedef boost::function< int (void) > EventLoopFunc;

// static interface
public:
    static ObjTransitPtr createFromFile(const std::string& filename);
    static void tickHack()
    {
        for_each(_apps.begin(), _apps.end(), boost::bind(&VCApp::tickHackImpl,_1));
    }

private:
    typedef std::set<VCApp*> AppBag;
    static AppBag _apps;

// instance interface
public:
    virtual ~VCApp() = 0;

    virtual void tickHackImpl() = 0;
    virtual void init() = 0;
    virtual void shutdown() = 0;

    int run();

    void setCreateNativeWindowFunc(const CreateNativeWindowFunc& func);
    void setEventLoopFunc(const EventLoopFunc& func);

    VCNativeWindowTransitPtr createNativeWindow(const VCNativeWindowDesc& desc);

protected:
    VCApp();

private:
    CreateNativeWindowFunc _createNativeWindowFunc;
    EventLoopFunc _eventLoopFunc;

};
OSG_GEN_MEMOBJPTR(VCApp);


// Simple dummy app till loading works
class OSG_VCOREVIEWER_DLLMAPPING VCDummyApp: public VCApp
{
public:
    virtual void tickHackImpl();
    virtual void init();
    virtual void shutdown();

    VCDummyApp();   // public so VCApp can access it in createFromFile
    ~VCDummyApp();

private:
    GroupNodeRefPtr _root;
    VCNativeWindowRefPtr _nativeWindow;
    WindowRecPtr _osgWindow;
    ViewportUnrecPtr _viewport;
    VCRendererUnrecPtr _renderer;
    SimpleSceneManager* _sceneMgr;
    VCWindowEventSource _windowEventSource; // to send stuff to NativeWindow (not used atm)
    VCWindowEventSink _windowEventSink; // to receive stuff from NativeWindow

    void handleWindowEvents(const VCWindowEventSink::EventList& list);
};
OSG_GEN_MEMOBJPTR(VCDummyApp);


OSG_END_NAMESPACE

#include "OSGVCApp.inl"

#endif /* _OSGVCAPP_H_ */
