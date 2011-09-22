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

#ifndef _OSGVCGLUTNATIVEWINDOW_H_
#define _OSGVCGLUTNATIVEWINDOW_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGVCoreViewerDef.h"

#include <map>
#include <memory>

#include "OSGWindow.h"

#include "OSGVCNativeWindow.h"

OSG_BEGIN_NAMESPACE

class VCApp;

class OSG_VCOREVIEWER_DLLMAPPING VCGLUTNativeWindow: public VCNativeWindow
{
// types
private:
    typedef std::map< int, VCGLUTNativeWindow* > WindowBag;

// static interface
public:
    static void setupGLUTApp(VCApp& app);
    static VCNativeWindowTransitPtr createNativeWindow(const VCNativeWindowDesc& desc);
    static int enterEventLoop();
private:
    static WindowBag _windowBag;
    static bool _glutInitialized;

    static VCGLUTNativeWindow *findWindow(int id);
    static VCGLUTNativeWindow *getWindowByIndex(int index);
    static int windowCount();

    // glut callbacks
    static void reshape(int u, int v);
    static void visibility(int);
    static void display();
    static void idle();
    static void keyDown(unsigned char key, int x, int y);
    static void keyUp(unsigned char key, int x, int y);
    static void mouse(int button, int state, int x, int y);
    static void motion(int x, int y);
    static void specialKeyDown(int ch, int, int);
    static void specialKeyUp(int ch, int, int);
    static void triggerMenuControl(int id);
    static void menuState(int state);
//#if defined(GLUT_MACOSX_IMPLEMENTATION) && (GLUT_MACOSX_IMPLEMENTATION >= 2)
//    static void wmClose();
//#endif
    static void runTimerFrame(int regTimer);


// instance interface
public:
    virtual ~VCGLUTNativeWindow();

private:
    VCGLUTNativeWindow(const VCNativeWindowDesc& desc);
    VCGLUTNativeWindow(const VCGLUTNativeWindow&);
    const VCGLUTNativeWindow& operator = (const VCGLUTNativeWindow&);


    int _winID;
};

OSG_END_NAMESPACE

#include "OSGVCGLUTNativeWindow.inl"

#endif /* _OSGVCGLUTNATIVEWINDOW_H_ */
