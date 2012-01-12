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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGVCoREVCNativeGLUTWindowHandler.h"
#include "OSGVCoREVCNativeWindow.h"

#include "OSGVCoREApp.h"

#include "OSGGLUT.h"
#include "OSGGLUTWindow.h"

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

// Documentation for this class is emited in the
// OSGVCoREVCNativeGLUTWindowBase.cpp file.
// To modify it, please change the .fcd file (OSGPythonScript.fcd) and
// regenerate the base file.

bool VCNativeGLUTWindowHandler::_bGlutInitialized = false;

VCNativeGLUTWindowHandler::WindowHandlerBag VCNativeGLUTWindowHandler::
    _mWindowHandlerBag;

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

Int32 VCNativeGLUTWindowHandler::enterEventLoop(void)
{
    if(_bGlutInitialized == true)
    {
        glutMainLoop();
    }

    return 0;
}

VCNativeGLUTWindowHandler::NWinHandlerTransitPtr 
    VCNativeGLUTWindowHandler::createNativeWindow(
        const VCWindowDesc &oDesc)
{
    NWinHandlerTransitPtr returnValue(new VCNativeGLUTWindowHandler(oDesc));

    return returnValue;
}

void VCNativeGLUTWindowHandler::setupApp(App &oApp)
{
    if(_bGlutInitialized == false)
    {
        int  argc = 1;
        char *argv[] = { const_cast<char *>("[dummy]") };

        glutInit(&argc, argv);
        
        _bGlutInitialized = true;
    }

    oApp.setCreateNativeWindowFunc(Self::createNativeWindow);
    oApp.setEventLoopFunc         (Self::enterEventLoop    );
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VCNativeGLUTWindowHandler::VCNativeGLUTWindowHandler(
    const VCWindowDesc &oDesc) :

     Inherited(  ),
    _iWinID   (-1)
{
    assert(_bGlutInitialized);

    UInt32 uiDispMode = (GLUT_RGBA    | 
                         GLUT_DEPTH   | 
                         GLUT_STENCIL | 
                         GLUT_ALPHA   | 
                         GLUT_DOUBLE  );
    
    if(oDesc._iSampleCount > 1)
        uiDispMode |= GLUT_MULTISAMPLE;

    if (oDesc._bStereoBuffer)
        uiDispMode |= GLUT_STEREO;

    glutInitDisplayMode(uiDispMode);

    _iWinID = glutCreateWindow(oDesc._szTitle.c_str());

    // create window
    if(oDesc._bFullscreen)
    {
        glutFullScreen();
    }

    if(oDesc._bVisible == false)
        glutHideWindow();

//#if defined(GLUT_MACOSX_IMPLEMENTATION) && (GLUT_MACOSX_IMPLEMENTATION >= 2)
//    glutWMCloseFunc(wmClose);
//#endif

    OSG::GLUTWindowUnrecPtr pGlutWin = OSG::GLUTWindow::create();

    pGlutWin->setGlutId(_iWinID);


    //glutTimerFunc (0, runTimerFrame, 0);  
    //glutVisibilityFunc(visibility);  
    glutDisplayFunc   (display);
    glutIdleFunc      (idle   );
    glutReshapeFunc   (reshape);
    glutKeyboardFunc  (keyDown);
    glutKeyboardUpFunc(keyUp  );
    glutMotionFunc    (motion );
    //glutPassiveMotionFunc(motion);
    glutMouseFunc     (mouse  );
    //glutSpecialFunc(specialKeyDown);
    //glutSpecialUpFunc(specialKeyUp);
    //glutMenuStateFunc(menuState);
    
    // switch off key repetition on keypress (i.e. constant keyup/keydown
    //toggle for pressed keys) 
    //glutIgnoreKeyRepeat (1);


    if(oDesc._bDrawCursor == false)
        glutSetCursor(GLUT_CURSOR_NONE);

    if(oDesc._bFullscreen == false)
    {
        Int32 iWidth  = oDesc._vSize.x();
        Int32 iHeight = oDesc._vSize.y();

        if((iWidth >= 0) && (iHeight >= 0))
            glutReshapeWindow(iWidth, iHeight);
    }

    Int32 x = oDesc._vPosition.x();
    Int32 y = oDesc._vPosition.y();

    if((x >= 0) && (y >= 0))
        glutPositionWindow(x, y);

    FDEBUG (("Create window (ID: %d)\n", _iWinID));

    _pOSGWin = pGlutWin;

    // init is will be called by VCWindow
    // _osgWindow->init();

    _mWindowHandlerBag[_iWinID] = this;
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VCNativeGLUTWindowHandler::~VCNativeGLUTWindowHandler(void)
{
    if(_iWinID != -1)
        glutDestroyWindow(_iWinID);
}


VCNativeGLUTWindowHandler *
    VCNativeGLUTWindowHandler::findWindowHandler(Int32 iId)
{
    WindowHandlerBag::iterator mIt = _mWindowHandlerBag.find(iId);

    if(mIt != _mWindowHandlerBag.end())
    {
        return mIt->second;
    }
    else
    {
        return NULL;
    }
}

VCNativeGLUTWindowHandler *
    VCNativeGLUTWindowHandler::getWindowHandlerByIndex(Int32 iIndex)
{
    VCNativeGLUTWindowHandler  *returnValue = NULL;
    WindowHandlerBag::iterator  mIt         = _mWindowHandlerBag.begin();

    Int32 i = 0;

    for(; mIt != _mWindowHandlerBag.end(); ++mIt) 
    {
        if(i++ == iIndex) 
        {
            returnValue = mIt->second;

            break;
        }
    }

    return returnValue;
}

/*-------------------------------------------------------------------------*/
/*                             Intersect                                   */


void VCNativeGLUTWindowHandler::reshape(Int32 u, Int32 v)
{
    Int32 iId = glutGetWindow();

    VCNativeWindowHandler *pWinHandler = findWindowHandler(iId);

    if(pWinHandler != NULL)
    {
        pWinHandler->sendResizeWindowEvent(u, v);

        glutPostRedisplay();
    }
    else
    {
        FWARNING(("VCNativeGLUTWindowHandler::reshape: no window handler!\n"));
    }

}

void VCNativeGLUTWindowHandler::display(void)
{
    Int32 iId = glutGetWindow();

    VCNativeGLUTWindowHandler *pWinHandler = findWindowHandler(iId);

    if(pWinHandler != NULL)
    {
        // Let the System (all apps) do a single update tick in THIS thread.
        // Normally Items (VCWindow in this case) would continuously run in
        // their VCWorkers (or whatever), and process their events there.
        // But since this whole Threading business in not in place yet, I did
        // it this way.
        App::tick();
        //glutSwapBuffers();

        pWinHandler->sendDisplayWindowEvent();
    }
    else
    {
        FWARNING(("VCNativeGLUTWindowHandler::display: no window handler!\n"));
    }

#if 0 // Leave that to the individual threads
    Thread::getCurrentChangeList()->commitChangesAndClear();
#endif
}

void VCNativeGLUTWindowHandler::idle(void)
{
    display();
}

void VCNativeGLUTWindowHandler::mouse(Int32 button, 
                                      Int32 state, 
                                      Int32 x, 
                                      Int32 y     )
{
    Int32 iId = glutGetWindow();

    VCNativeGLUTWindowHandler *pWinHandler = findWindowHandler(iId);

    if(pWinHandler != NULL)
    {
        pWinHandler->sendMouseWindowEvent(x, y, button, state);

        glutPostRedisplay();
    }
    else
    {
        FWARNING(("VCNativeGLUTWindowHandler::mouse: no window handler!\n"));
    }
}

void VCNativeGLUTWindowHandler::motion(Int32 x, Int32 y)
{
    Int32 iId = glutGetWindow();

    VCNativeGLUTWindowHandler *pWinHandler = findWindowHandler(iId);

    if(pWinHandler != NULL)
    {
        pWinHandler->sendMouseWindowEvent(x, y, -1, 0);

        glutPostRedisplay();
    }
}

void VCNativeGLUTWindowHandler::keyDown(UChar8 cKey, Int32 x, Int32 y)
{
    Int32 iId = glutGetWindow();

    VCNativeGLUTWindowHandler *pWinHandler = findWindowHandler(iId);

    if(pWinHandler != NULL)
    {
        pWinHandler->sendKeyboardWindowEvent(
            x, 
            y, 
            cKey, 
            VCKeyboardWindowEvent::EventType_Down);

        glutPostRedisplay();
    }
    else
    {
        FWARNING(("VCGLUTNativeWindow::keyUp: no window!\n"));
    }
}

void VCNativeGLUTWindowHandler::keyUp(UChar8 cKey, Int32 x, Int32 y)
{
    Int32 iId = glutGetWindow();

    VCNativeGLUTWindowHandler *pWinHandler = findWindowHandler(iId);

    if(pWinHandler != NULL)
    {
        pWinHandler->sendKeyboardWindowEvent(
            x, 
            y, 
            cKey, 
            VCKeyboardWindowEvent::EventType_Up);

        glutPostRedisplay();
    }
    else
    {
        FWARNING(("VCGLUTNativeWindow::keyUp: no window!\n"));
    }
}

/*-------------------------------------------------------------------------*/
/*                                Init                                     */

VCORE_END_NAMESPACE
