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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGVCGLUTViewer.h"
#include "OSGGLUT.h"
#include "OSGGLUTWindow.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGVCGLUTViewerBase.cpp file.
// To modify it, please change the .fcd file (OSGVCGLUTViewer.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/
bool           VCGLUTViewer::_bGLUTInitialized = false;
//CSMGLUTWindow *VCGLUTViewer::_pGLUTWindow      = NULL;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void VCGLUTViewer::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

VCGLUTViewer::VCGLUTViewer(void) :
    Inherited(),
    _iGlutWinId(-1),
    _pWindow(NULL)
{
}

VCGLUTViewer::VCGLUTViewer(const VCGLUTViewer &source) :
    Inherited(source),
    _iGlutWinId(-1),
    _pWindow(NULL)
{
}

VCGLUTViewer::~VCGLUTViewer(void)
{
}

/*----------------------------- class specific ----------------------------*/

bool VCGLUTViewer::init(void)
{
    if(_bGLUTInitialized == false)
    {
        Int32  argc   = 1;
        const Char8 *argv[] = { "testCSM" };

        glutInit(&argc, const_cast<Char8 **>(argv));
    }

    UInt32 uiDisplayMode = (GLUT_RGBA       | 
        GLUT_DEPTH      | 
        GLUT_DOUBLE     | 
        GLUT_STENCIL    |
        GLUT_MULTISAMPLE);

#if 0
    if(_pVSCWindow->stereo() == true)
    {
        uiDisplayMode |= GLUT_STEREO;
    }
#endif

    OSG::GLUTWindowUnrecPtr pGLUTWindow = OSG::GLUTWindow::create();

    if(pGLUTWindow == NULL)
        return false;

    glutInitDisplayMode(uiDisplayMode);

    //if(this->getXPos() > 0.f && this->getYPos() > 0.f)
    //{
    //    glutInitWindowPosition(Int32(this->getXPos()), 
    //        Int32(this->getYPos()));
    //}

    //if(this->getXSize() > 0.f && this->getYSize() > 0.f)
    //{
    //    glutInitWindowSize(Int32(this->getXSize()), 
    //        Int32(this->getYSize()));
    //}

    _iGlutWinId = glutCreateWindow("OpenSG - CSM");

    pGLUTWindow->setGlutId(_iGlutWinId);

    //if(this->getXSize() > 0.f && this->getYSize() > 0.f)
    //{
    //    pGLUTWindow->resize(Int32(this->getXSize()), 
    //        Int32(this->getYSize()));
    //}

    //if(ComplexSceneManager::the() != NULL)
    //    ComplexSceneManager::the()->setMainloop(glutMainLoop);
    //    vscSetMainLoop(static_cast<MainLoopFuncF>(glutMainLoop));

#if 0
    if(_pVSCWindow->getXSize       () <  0.f && 
        _pVSCWindow->getYSize       () <  0.f &&
        _pVSCWindow->getDecorEnabled() == false)
    {
        glutFullScreen();
    }
#endif    
    //    _bSceneWireframe = _pVSCWindow->getSFSceneWireframeR()->getValue();

    //    setFCPtr(pGLUTWindow);

    _pWindow     = pGLUTWindow;
//    _pGLUTWindow = this;

    if(_bGLUTInitialized == false)
    {
        _bGLUTInitialized = true;

        //        _pFirstWindow = this;

        glutKeyboardFunc  (glutKeyHandler        );
        //        glutVisibilityFunc(vscGlutVisHandler        );
        glutReshapeFunc   (glutReshapeHandler    );
        glutDisplayFunc   (glutFrameHandler      );       
        glutMouseFunc     (glutMouseHandler      );   
        glutMotionFunc    (glutMouseMotionHandler); 
        glutIdleFunc      (glutFrameHandler      );  
    }

    pGLUTWindow->init();


//    Inherited::init();

    //    pGLUTWindow->deactivate();

    return true;
}

void VCGLUTViewer::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void VCGLUTViewer::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump VCGLUTViewer NI" << std::endl;
}


void VCGLUTViewer::glutKeyHandler(UChar8 key, 
                                      Int32  x, 
                                      Int32  y  )
{
    switch(key)
    {
    case 27:    

        glutKeyboardFunc  (NULL);
        glutReshapeFunc   (NULL);
        //            glutDisplayFunc   (NULL);       
        glutMouseFunc     (NULL);   
        glutMotionFunc    (NULL); 
        glutIdleFunc      (NULL);  

//        ComplexSceneManager::the()->terminate();

        osgExit(); 

        exit(0);

        break;

    default:
        //ComplexSceneManager::the()->key(x, 
        //    y, 
        //    CSMKeyData::ButtonDown, 
        //    key);
        break;
    }
}

void VCGLUTViewer::glutReshapeHandler(Int32 w, 
                                          Int32 h)
{
//    _pGLUTWindow->reshape(w, h);

    glutPostRedisplay();
}

void VCGLUTViewer::glutFrameHandler(void)
{
//    ComplexSceneManager::the()->frame();

    Thread::getCurrentChangeList()->commitChangesAndClear();
}

void VCGLUTViewer::glutMouseHandler(Int32 iButton, 
                                        Int32 iState,
                                        Int32 x,       
                                        Int32 y      )
{
    //_pGLUTWindow->mouse(iButton, 
    //    iState, 
    //    glutGetModifiers(), 
    //    x, 
    //    y);
}

void VCGLUTViewer::glutMouseMotionHandler(Int32 x, 
                                              Int32 y)
{
//    _pGLUTWindow->motion(x, y);
}


OSG_END_NAMESPACE
