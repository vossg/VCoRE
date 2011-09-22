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


#include "OSGConfig.h"

#include "OSGGLUT.h"
#include "OSGGLUTWindow.h"

#include "OSGVCGLUTNativeWindow.h"
#include "OSGVCApp.h"   // just to get tickHack()


OSG_BEGIN_NAMESPACE

VCGLUTNativeWindow::WindowBag VCGLUTNativeWindow::_windowBag;
bool VCGLUTNativeWindow::_glutInitialized = false;

VCGLUTNativeWindow *VCGLUTNativeWindow::findWindow(int id)
{
    WindowBag::iterator vI = _windowBag.find(id);

    if(vI != _windowBag.end())
        return vI->second;
    else
        return NULL;
}

VCGLUTNativeWindow *VCGLUTNativeWindow::getWindowByIndex(int index)
{
    VCGLUTNativeWindow *window = 0;
    WindowBag::iterator vI;
    int i = 0;

    for (vI = _windowBag.begin(); vI != _windowBag.end(); ++vI) {
        if (i++ == index) {
            window = vI->second;
            break;
        }
    }

    return window;
}

int VCGLUTNativeWindow::windowCount()
{
    return _windowBag.size();
}



//
//void VCGLUTNativeWindow::runTimerFrame(int t)
//{
//    unsigned int delay = unsigned(1000.0 * _frameDelay);
//
//    glutTimerFunc (delay ? delay : 1, runTimerFrame, 0);  
//
//    glutPostRedisplay();
//}

void VCGLUTNativeWindow::reshape  (int u, int v)
{
    int id = glutGetWindow();
    VCGLUTNativeWindow *window = findWindow(id);

    if (window)
    {
        window->sendResizeWindowEvent(u,v);
        glutPostRedisplay();
    }
    else
    {
        FWARNING(("VCGLUTNativeWindow::reshape: no window!\n"));
    }

}

void VCGLUTNativeWindow::visibility  (int state)
{
#if 0
    int id = glutGetWindow();
    VCGLUTNativeWindow *window = findWindow(id);
    bool visible = (state == GLUT_VISIBLE) ? true : false;

    if (window && (window->_desc._visible != visible))
    {
        window->_desc._visible = visible;
//        _visibleCount += visible ? 1 : -1;
        glutPostRedisplay();
    }
#endif
}

void VCGLUTNativeWindow::display(void)
{
    int id = glutGetWindow();
    VCGLUTNativeWindow *window = findWindow(id);
    if(window)
    {
        window->sendDisplayWindowEvent();
        
        // Let the System (all apps) do a single update tick in THIS thread.
        // Normally Items (VCWindow in this case) would continuously run in
        // their VCWorkers (or whatever), and process their events there.
        // But since this whole Threading business in not in place yet, I did
        // it this way.
        VCApp::tickHack();
        //glutSwapBuffers();
    }
    else
    {
        FWARNING(("VCGLUTNativeWindow::display: no window!\n"));
    }

    Thread::getCurrentChangeList()->commitChangesAndClear();
}

void VCGLUTNativeWindow::idle(void)
{
    display();
}


//unsigned int VCGLUTNativeWindow::extKey ( unsigned char key )
//{
//#if 0
//    int mod(glutGetModifiers());
//    unsigned int extKey = 0;
//
//    if (mod) {
//        if (mod & GLUT_ACTIVE_CTRL) 
//            extKey = CONTROL_MK;
//        else 
//            if (mod & GLUT_ACTIVE_SHIFT)
//                extKey = SHIFT_MK;
//            else
//                if (mod & GLUT_ACTIVE_ALT)
//                    extKey = ALT_MK;
//                else {
//                    FFATAL (("Unknown modifier: %d\n", int (mod) ));
//                }
//    }
//
//    //std::cerr << "-------------------------------" << std::endl;
//    //std::cerr << "key:     " << int(key) << std::endl;
//    //std::cerr << "mod:     " << mod << std::endl;
//    //std::cerr << "extKey1: " << extKey << std::endl;
//
//    extKey |= key;
//
//    //std::cerr << "extKey2: " << extKey << std::endl;
//
//    return extKey;
//#endif
//}

void VCGLUTNativeWindow::keyDown (unsigned char key, int x, int y)
{
    int id = glutGetWindow();
    VCGLUTNativeWindow *window = findWindow(id);
    if(window)
    {
        window->sendKeyboardWindowEvent(x, y, key, VCKeyboardWindowEvent::EventType_Down);
        glutPostRedisplay();
    }
    else
    {
        FWARNING(("VCGLUTNativeWindow::keyUp: no window!\n"));
    }

}

void VCGLUTNativeWindow::keyUp (unsigned char key, int x, int y)
{
    int id = glutGetWindow();
    VCGLUTNativeWindow *window = findWindow(id);
    if(window)
    {
        window->sendKeyboardWindowEvent(x, y, key, VCKeyboardWindowEvent::EventType_Up);
        glutPostRedisplay();
    }
    else
    {
        FWARNING(("VCGLUTNativeWindow::keyUp: no window!\n"));
    }
}

void VCGLUTNativeWindow::mouse(int button, int state, int x, int y)
{
    int id = glutGetWindow();
    VCGLUTNativeWindow *window = findWindow(id);
    if(window)
    {
        window->sendMouseWindowEvent(x, y, button, state);
        glutPostRedisplay();
    }
    else
    {
        FWARNING(("VCGLUTNativeWindow::mouse: no window!\n"));
    }
}

void VCGLUTNativeWindow::motion(int x, int y)
{
    int id = glutGetWindow();
    VCGLUTNativeWindow *window = findWindow(id);
    if(window)
    {
        window->sendMouseWindowEvent(x, y, -1, 0);
        glutPostRedisplay();
    }
}

void VCGLUTNativeWindow::specialKeyDown(int key, int , int )
{

}
void VCGLUTNativeWindow::specialKeyUp(int key, int , int )
{

}
void VCGLUTNativeWindow::menuState (int state)
{

}

//#if defined(GLUT_MACOSX_IMPLEMENTATION) && (GLUT_MACOSX_IMPLEMENTATION >= 2)
//void VCGLUTNativeWindow::wmClose()
//{
//    exit(EXIT_SUCCESS);
//}
//#endif



void VCGLUTNativeWindow::triggerMenuControl (int id)
{

}
void VCGLUTNativeWindow::runTimerFrame(int t)
{

}


VCNativeWindowTransitPtr
VCGLUTNativeWindow::createNativeWindow(const VCNativeWindowDesc& desc)
{
    return VCNativeWindowTransitPtr( new VCGLUTNativeWindow(desc) );
}

int VCGLUTNativeWindow::enterEventLoop()
{
    glutMainLoop();
    return 0;
}

void VCGLUTNativeWindow::setupGLUTApp(VCApp& app)
{
    if( !_glutInitialized )
    {
        int  argc = 1;
        char *argv[] = { "[dummy]" };
        glutInit(&argc, argv);
        _glutInitialized = true;
    }

    app.setCreateNativeWindowFunc(VCGLUTNativeWindow::createNativeWindow);
    app.setEventLoopFunc(VCGLUTNativeWindow::enterEventLoop);

}


VCGLUTNativeWindow::VCGLUTNativeWindow(const VCNativeWindowDesc& desc)
    : VCNativeWindow(desc)
    , _winID(-1)
{
    assert(_glutInitialized);

    unsigned dispMode = GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL | GLUT_ALPHA | GLUT_DOUBLE;
    
    if (_desc._sampleCount > 1)
        dispMode |= GLUT_MULTISAMPLE;

    if (_desc._stereoBuffer)
        dispMode |= GLUT_STEREO;

    glutInitDisplayMode (dispMode);

    // create window
    if (_desc._fullscreen)
    {
        //if (pipeStr.empty() == false) {
        //    glutGameModeString(pipeStr.c_str());
        //    if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)) {
        //        FNOTICE (("Enter glut game mode\n"));
        //        _winID = glutEnterGameMode();
        //    }
        //    else {
        //        FFATAL (("pipe >%s< mode not supported, start default fullscreen\n",
        //            pipeStr.c_str() ));
        //        _winID = glutCreateWindow(title.c_str());
        //        glutFullScreen();
        //    }
        //}
        //else {
            _winID = glutCreateWindow(_desc._title.c_str());
            glutFullScreen();
        //}
    }
    else
    {
        _winID = glutCreateWindow(_desc._title.c_str());
    }

    if(!_desc._visible)
        glutHideWindow();

//#if defined(GLUT_MACOSX_IMPLEMENTATION) && (GLUT_MACOSX_IMPLEMENTATION >= 2)
//    glutWMCloseFunc(wmClose);
//#endif

    OSG::GLUTWindowUnrecPtr glutWinPtr = OSG::GLUTWindow::create();
    glutWinPtr->setGlutId(_winID);


        //glutTimerFunc (0, runTimerFrame, 0);  
        //glutVisibilityFunc(visibility);  
        glutDisplayFunc(display);
        glutIdleFunc(idle);
        glutReshapeFunc(reshape);
        //glutKeyboardFunc(keyDown);
        //glutKeyboardUpFunc(keyUp);
        glutMotionFunc(motion);
        //glutPassiveMotionFunc(motion);
        glutMouseFunc(mouse);
        //glutSpecialFunc(specialKeyDown);
        //glutSpecialUpFunc(specialKeyUp);
        //glutMenuStateFunc(menuState);

        // switch off key repetition on keypress (i.e. constant keyup/keydown toggle for pressed keys)
        //glutIgnoreKeyRepeat (1);


    if (_desc._drawCursor == false)
        glutSetCursor(GLUT_CURSOR_NONE);

    if (_desc._fullscreen == false)
    {
        int width = _desc._size.x();
        int height = _desc._size.y();
        if ((width >= 0) && (height >= 0))
            glutReshapeWindow(width, height);
    }
    int x = _desc._position.x();
    int y = _desc._position.y();
    if ((x >= 0) && (y >= 0))
        glutPositionWindow(x, y);

    FDEBUG (("Create window (ID: %d)\n", _winID));

    _osgWindow = glutWinPtr;

    // init is will be called by VCWindow
    // _osgWindow->init();

    _windowBag[_winID] = this;
}
VCGLUTNativeWindow::~VCGLUTNativeWindow()
{
    if (_winID)
    {
        _windowBag.erase(_winID);
        glutDestroyWindow(_winID);
    }
    else
    {
        // init failed??
    }
    _winID = 0;

    _osgWindow = NULL;
}




OSG_END_NAMESPACE
