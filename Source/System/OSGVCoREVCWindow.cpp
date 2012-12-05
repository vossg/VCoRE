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

#include "OSGVCoREVCWindow.h"
#include "OSGNameAttachment.h"

#include "OSGOSGSceneFileType.h"

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

VCWindowDesc::VCWindowDesc(void) : 
    _szTitle      (    ""),
    _bVisible     ( false),
    _bFullscreen  ( false),
    _vSize        ( 0,  0),
    _vPosition    (-1, -1),
    _bDrawCursor  (  true),
    _iSampleCount (     1),
    _bStereoBuffer( false)
{
}

// Documentation for this class is emited in the
// OSGVCoREVCWindowBase.cpp file.
// To modify it, please change the .fcd file (OSGPythonScript.fcd) and
// regenerate the base file.

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void VCWindow::changed(ConstFieldMaskArg whichField,
                       UInt32            origin,
                       BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void VCWindow::sendEvent(VCWindowEvent *pEvent)
{
    _oWindowEventSource.sendEvent(pEvent);
}


/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void VCWindow::dump(      UInt32    uiIndent,
                    const BitVector bvFlags) const
{
    Inherited::dump(uiIndent, bvFlags);
}

void VCWindow::tick(void)
{
//    fprintf(stderr, "window tick\n");

    if(_pAction == NULL)
    {
        _pAction = RenderAction::create();
    }

#if 0
    if(_pOSGWin != NULL && _pAction != NULL)
    {
        _pOSGWin->render(_pAction);
    }
#endif

    if(_pMgr == NULL)
    {
        _pMgr = SimpleSceneManager::create();
    }

    if(_pOSGWin != NULL && _pMgr->getWindow() != _pOSGWin)
    {
        Viewport *pPort = _pOSGWin->getPort(0);

        _pMgr->setWindow            (_pOSGWin);
        _pMgr->setUseTraversalAction( true   );

        if(pPort != NULL)
        {
            _pMgr->setRoot(pPort->getRoot());
        }

        _pMgr->showAll();

//        _pMgr->setHeadlight         ( true   );

        Node *pRoot = _pMgr->getRoot();

        while(pRoot->getParent() != NULL)
        {
            pRoot = pRoot->getParent();
        }

        pPort->setCamera(_pMgr->getCamera());
        pPort->setRoot  ( pRoot            );

        fprintf(stderr, "port : %ld %p %p\n",
                _pOSGWin->getMFPort()->size(),
                pPort,
                pPort->getRoot());
    }

//    _pMgr->update();

    VCWindowEventSink::EventList tmpEventList;

    _oWindowEventSink.swapEventList(tmpEventList);

#if 0
    fprintf(stderr, "Got %ld events\n",
            tmpEventList.size());
#endif

    VCWindowEventSink::EventList::const_iterator eIt = tmpEventList.begin();

    for(; eIt != tmpEventList.end(); ++eIt)
    {
        VCDisplayWindowEvent *dwe = 
            dynamic_cast<VCDisplayWindowEvent *>(eIt->get());
        
        if(dwe != NULL)
        {
//            std::cout << "DISPLAY" << std::endl;
            _pMgr->redraw();
//            _renderer->update();
        }

        VCMouseWindowEvent *mwe = 
            dynamic_cast<VCMouseWindowEvent *>(eIt->get());

        if(mwe != NULL)
        {
//            std::cout << "MOUSE" << std::endl;
            if(mwe->_iButton >= 0)
            {
                if(mwe->_iButtonState)
                {
                    _pMgr->mouseButtonRelease(mwe->_iButton, 
                                              mwe->_x, 
                                              mwe->_y);
                }
                else
                {
                    _pMgr->mouseButtonPress(mwe->_iButton, 
                                            mwe->_x, 
                                            mwe->_y);
                }
            }
            else
            {
                _pMgr->mouseMove(mwe->_x, mwe->_y);
            }
        }

        VCResizeWindowEvent *rwe = 
            dynamic_cast<VCResizeWindowEvent *>(eIt->get());

        if(rwe != NULL)
        {
            std::cout << "RESIZE : " 
                      << rwe->_iWidth  << " " 
                      << rwe->_iHeight << std::endl;

            _pMgr   ->resize(rwe->_iWidth, rwe->_iHeight);
            _pOSGWin->resize(rwe->_iWidth, rwe->_iHeight);
        }

        VCKeyboardWindowEvent *kwe =
            dynamic_cast<VCKeyboardWindowEvent *>(eIt->get());

        if(kwe != NULL)
        {
            switch(kwe->_iKey)
            {
                case 27:

                    fprintf(stderr, "Terminate\n");
                    break;

                default:
                    break;
            }
        }
    }
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VCWindow::VCWindow(void) :
     Inherited         (    ),
    _pOSGWin           (NULL),
    _pAction           (NULL),
    _pMgr              (NULL),
    _oWindowEventSource(    ),
    _oWindowEventSink  (    )
{
    _oWindowEventSource.addSink(_oWindowEventSink);
}

VCWindow::VCWindow(const VCWindow &source) :
     Inherited         (source),
    _pOSGWin           (NULL  ),
    _pAction           (NULL  ),
    _pMgr              (NULL  ),
    _oWindowEventSource(      ),
    _oWindowEventSink  (      )
{
    _oWindowEventSource.addSink(_oWindowEventSink);
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VCWindow::~VCWindow(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Intersect                                   */

void VCWindow::resolveLinks(void)
{
    _pOSGWin = NULL;

    _pAction = NULL;

    _pMgr    = NULL;
}

/*-------------------------------------------------------------------------*/
/*                                Init                                     */

void VCWindow::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

bool VCWindow::init(UInt32 uiInitPhase, App *pApp)
{
    fprintf(stderr, "VCWindow::init %s (%d)\n", getName(this), uiInitPhase);

    MFViewsType::const_iterator vIt  = _mfViews.begin();
    MFViewsType::const_iterator vEnd = _mfViews.end  ();

    for(; vIt != vEnd; ++vIt)
    {
        (*vIt)->init(uiInitPhase, pApp);
    }

    if(0x0000 != (uiInitPhase & ::OSG::InitPhase::ResolveReferences))
    {
        fprintf(stderr, "Got osg win : %p\n", _pOSGWin.get());

        if(_pOSGWin != NULL)
        {
            vIt  = getMFViews()->begin();
            vEnd = getMFViews()->end  ();

            for(; vIt != vEnd; ++vIt)
            {
                VCViewarea::ViewportStoreConstIt pIt  = 
                    (*vIt)->beginViewports();

                VCViewarea::ViewportStoreConstIt pEnd = 
                    (*vIt)->endViewports  ();

                for(; pIt != pEnd; ++pIt)
                {
                    _pOSGWin->addPort((*pIt));
                }
            }

            OSGSceneFileType::the().writeContainer(_pOSGWin, 
                                                   "/tmp/vc.osg");
        }
    }

    return true;
}

VCORE_END_NAMESPACE
