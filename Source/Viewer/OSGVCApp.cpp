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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGConfig.h"

#include "OSGComponentTransform.h"
#include "OSGSimpleGeometry.h"
#include "OSGSolidBackground.h"

#include "OSGVCApp.h"
#include "OSGVCSystem.h"


VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

VCApp::AppBag VCApp::_apps;

void VCApp::setCreateNativeWindowFunc(const CreateNativeWindowFunc& func)
{
    _createNativeWindowFunc = func;
}

void VCApp::setEventLoopFunc(const EventLoopFunc& func)
{
    _eventLoopFunc = func;
}

VCNativeWindowTransitPtr VCApp::createNativeWindow(const VCNativeWindowDesc& desc)
{
    if(_createNativeWindowFunc)
        return _createNativeWindowFunc(desc);
    else
        return VCNativeWindowTransitPtr(NULL);
}

VCAppTransitPtr VCApp::createFromFile(const std::string& filename)
{
    // just create a dummy until the loading works
    VCAppTransitPtr dummyApp( new VCDummyApp );
    return dummyApp;
}



VCApp::VCApp()
{
    _apps.insert(this);
}
VCApp::~VCApp()
{
    _apps.erase(this);
}

int VCApp::run()
{
    init();
    int retval = _eventLoopFunc ? _eventLoopFunc() : 0;
    shutdown();

    return retval;
}



VCDummyApp::VCDummyApp()
    : VCApp()
{

}
VCDummyApp::~VCDummyApp()
{

}
void VCDummyApp::tickHackImpl()
{
    // just process accumulated window messages
    // VCWindow would do this normally.
    VCWindowEventSink::EventList eventList;
    _windowEventSink.swapEventList(eventList);
    handleWindowEvents(eventList);
}
void VCDummyApp::init()
{
    // >>> test scene
    OSG::GroupNodeRefPtr beacon = OSG::GroupNodeRefPtr::create();

    OSG::ComponentTransformNodeRefPtr beaconTrans = OSG::ComponentTransformNodeRefPtr::create();
    beaconTrans->setTranslation(OSG::Vec3f(0.f,0.f,10.f));
    beaconTrans.node()->addChild(beacon);

    OSG::NodeUnrecPtr torus = OSG::makeTorus(.5, 2, 16, 16);

    OSG::TransformNodeRefPtr sceneTrans = OSG::TransformNodeRefPtr::create();
    sceneTrans.node()->addChild(torus);

    OSG::DirectionalLightNodeRefPtr dlight = 
        OSG::DirectionalLightNodeRefPtr::create();
    dlight->setAmbient  (.3f, .3f, .3f, 1);
    dlight->setDiffuse  ( 1,  1,  1, 1);
    dlight->setDirection( 0,  0,  1   );
    dlight->setBeacon   (beacon       );
    dlight.node()->addChild(sceneTrans);

    _root = OSG::GroupNodeRefPtr::create();
    _root.node()->addChild(beaconTrans);
    _root.node()->addChild(dlight);
    // <<< test scene

    // >>> app stuff

    // create the native window
    // normally VCWindow would do this, but the VCWindow class is not there yet
    // so we pretend the app is the window
    VCNativeWindowDesc winDesc;
    winDesc._title = "DummyApp";
    winDesc._size = Vec2i(512, 512);
    winDesc._visible = true;
    _nativeWindow = this->createNativeWindow(winDesc);
    // subscribe to window events from our native window
    // again, normally VCWindow would do this
    _nativeWindow->_windowEventSource.addSink(_windowEventSink);

    _viewport = Viewport::create();
    _viewport->setSize(0,0, 1,1);
    SolidBackgroundUnrecPtr bg = SolidBackground::create();
    bg->setColor(Color3f(0.2f, 0.8f, 0.2f));
    _viewport->setBackground(bg);

    _osgWindow = _nativeWindow->getOSGWindow();
    _osgWindow->init();
    _osgWindow->addPort(_viewport);

    _renderer = VCRenderer::create();
    _renderer->init();
    _renderer->addWindow(_osgWindow);

    _sceneMgr = SimpleSceneManager::create();
    _sceneMgr->setWindow(_osgWindow);
    _sceneMgr->setUseTraversalAction(true);
    _sceneMgr->setRoot(_root);
    _sceneMgr->showAll();

    _viewport->setCamera(_sceneMgr->getCamera());
    _viewport->setRoot(_sceneMgr->getRoot());
    // <<< app stuff

    OSG::commitChanges();
}


void VCDummyApp::shutdown()
{
    _sceneMgr = NULL;
}


void VCDummyApp::handleWindowEvents(const VCWindowEventSink::EventList& list)
{
    for( VCWindowEventSink::EventList::const_iterator iter = list.begin();
        iter != list.end(); ++iter)
    {
        VCDisplayWindowEvent* dwe = dynamic_cast<VCDisplayWindowEvent*>(iter->get());
        if(dwe)
        {
            //std::cout << "DISPLAY" << std::endl;
            _sceneMgr->update();
            _renderer->update();
        }

        VCMouseWindowEvent* mwe = dynamic_cast<VCMouseWindowEvent*>(iter->get());
        if(mwe)
        {
            //std::cout << "MOUSE" << std::endl;
            if(mwe->_button >= 0)
            {
                if (mwe->_buttonState)
                    _sceneMgr->mouseButtonRelease(mwe->_button, mwe->_x, mwe->_y);
                else
                    _sceneMgr->mouseButtonPress(mwe->_button, mwe->_x, mwe->_y);
            }
            else
            {
                _sceneMgr->mouseMove(mwe->_x, mwe->_y);
            }

        }

        VCResizeWindowEvent* rwe = dynamic_cast<VCResizeWindowEvent*>(iter->get());
        if(rwe)
        {
            //std::cout << "RESIZE" << std::endl;
            _sceneMgr->resize(rwe->_width, rwe->_height);
            _osgWindow->resize(rwe->_width, rwe->_height);
        }
    }
}


VCORE_END_NAMESPACE
