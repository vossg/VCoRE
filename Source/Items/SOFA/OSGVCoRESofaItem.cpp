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

#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
//#pragma GCC diagnostic warning "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#endif

#include <cstdlib>
#include <cstdio>

//#include "OSGConfig.h"


// SOFA :: must be here
//#include <sofa/helper/system/config.h>
//#include <sofa/helper/system/gl.h>

#include <sofa/helper/ArgumentParser.h>
#include <sofa/simulation/common/xml/initXml.h>
#include <sofa/simulation/common/Node.h>

#include <sofa/simulation/tree/TreeSimulation.h>
#include <sofa/component/init.h>
#include <sofa/component/misc/ReadState.h>
#include <sofa/component/misc/CompareState.h>
#include <sofa/helper/Factory.h>
#include <sofa/helper/BackTrace.h>
#include <sofa/helper/system/FileRepository.h>
#include <sofa/helper/system/SetDirectory.h>
#include <sofa/helper/system/atomic.h>
#include <sofa/gui/OperationFactory.h>

#include "OSGVCoRESofaItem.h"
#include "OSGNameAttachment.h"
#include "OSGOSGSceneFileType.h"
#include "OSGSceneFileHandler.h"
#include "OSGImageFileHandler.h"
#include "OSGContainerCollection.h"
#include "OSGVCoRESystemDef.h"

#include "OSGCSMWindow.h"
#include "OSGLine.h"
#include "OSGNode.h"
#include "OSGSimpleGeometry.h"

//SOFA

#include "OSGSofaVisualVisitor.h"

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

// Documentation for this class is emited in the
// OSGVCoRESofaItemBase.cpp file.
// To modify it, please change the .fcd file (OSGPythonScript.fcd) and
// regenerate the base file.

PathHandler SofaItem::_oPathHandler;

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

// Do not change anything that affects the SOFA part here

void SofaItem::changed(ConstFieldMaskArg whichField,
                       UInt32            origin,
                       BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(0x0000 != (whichField & RotationSpeedFieldMask))
    {
        fprintf(stderr, "new rotation speed %f\n",
                _sfRotationSpeed.getValue());
    }

    if(0x0000 != (whichField & AnimateFieldMask))
    {
        fprintf(stderr, "Animation %i\n",
                _sfAnimate.getValue());

    }

    if(0x0000 != (whichField & ResetFieldMask))
    {
        fprintf(stderr, "Reset animation \n");

        _bResetAnimation = true;
    }

    if(0x0000 != (whichField & MouseDataFieldMask))
    {
        _bPicking = true;
        //printMouse();
    }

    if(0x0000 != (whichField & RootFieldMask))
    {
        fprintf(stderr, "new root %p\n", this->getRoot());
    }
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void SofaItem::dump(      UInt32    uiIndent,
                    const BitVector bvFlags) const
{
    Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

SofaItem::SofaItem(void) :
     Inherited          (     ),
    _pTransform         (NULL ),
    _fAngle             (0.f  ),
    _pGRoot             (NULL ),
    _oPick              (     ),
    _bPicking           (false),
    _bResetAnimation    (false),
    _pShadowStage       (NULL ),
    _pChunkOverrideGroup(NULL ),
    _pScene             (NULL )
{
    initDefaults();
}

SofaItem::SofaItem(const SofaItem &source) :
     Inherited          (source),
    _pTransform         (NULL  ),
    _fAngle             (0.f   ),
    _pGRoot             (NULL  ),
    _oPick              (      ),
    _bPicking           (false),
    _bResetAnimation    (false),
    _pShadowStage       (NULL  ),
    _pChunkOverrideGroup(NULL  ),
    _pScene             (NULL  )
{
    initDefaults();
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

SofaItem::~SofaItem(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Intersect                                   */

/*-------------------------------------------------------------------------*/
/*                                Init                                     */
void SofaItem::initDefaults()
{
    // Picking
    _oPick.setPickingMethod(sofa::gui::PickHandler::RAY_CASTING);

    sofa::gui::RegisterOperation("Attach").add< sofa::gui::AttachOperation  >();
    sofa::gui::RegisterOperation("Fix"   ).add< sofa::gui::FixOperation     >();
    sofa::gui::RegisterOperation("Incise").add< sofa::gui::InciseOperation  >();
    sofa::gui::RegisterOperation("Remove").add< sofa::gui::TopologyOperation>();

    //Add to each button of the mouse an operation
    _oPick.changeOperation(sofa::gui::LEFT,   "Attach");
    _oPick.changeOperation(sofa::gui::MIDDLE, "Incise");
    _oPick.changeOperation(sofa::gui::RIGHT,  "Remove");
    
    sofa::gui::RegisterOperation("Attach").add< sofa::gui::AttachOperation >();
}



void SofaItem::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
#ifdef WIN32
        fprintf(stderr, "SofaItem::initMETHOD\n");

        typedef OSGSceneFileType::PostLoadingDispatcher<
            SofaItem> PLDSofaItem;

        OSGSceneFileType::the().registerEndNodeCallback(
            SofaItem::getClassType(),
            boost::bind(&PLDSofaItem::dispatch,
                        PLDSofaItem(), _1)); 
#else
        OSGSceneFileType::the().registerEndNodeCallback(
            SofaItem::getClassType(),
            reinterpret_cast<OSGSceneFileType::Callback>(
                &SofaItem::postOSGLoading));
#endif
    }
}

void SofaItem::postOSGLoading(void)
{
    fprintf(stderr, "SofaItem::postOSGLoading\n");

#if 0
    UInt32 i = 0;

    for(; i < _mfUrl.size(); ++i)
    {
        std::string szFilenameResolved = 
            SceneFileHandler::the()->getPathHandler()->findFile(
                _mfUrl[i].c_str());

        fprintf(stderr, "got %s -> %s\n",
                _mfUrl[i].c_str(),
                szFilenameResolved.c_str());

        if(szFilenameResolved.empty() == false)
        {
            setMatchedUrl(szFilenameResolved);

            break;
        }
    }


    for(; i < _mfGlobalUrl.size(); ++i)
    {
        std::string szFilenameResolved = 
            SceneFileHandler::the()->getPathHandler()->findFile(
                _mfGlobalUrl[i].c_str());

        fprintf(stderr, "got %s -> %s\n",
                _mfGlobalUrl[i].c_str(),
                szFilenameResolved.c_str());

        if(szFilenameResolved.empty() == false)
        {
            setMatchedGlobalUrl(szFilenameResolved);

            break;
        }
    }
#endif
}

bool SofaItem::init(UInt32 uiInitPhase, App *pApp)
{
    fprintf(stderr, "SofaItem::init %s (%x)\n",
            getName(this),
            uiInitPhase);

#if 0
    if(0x0000 != (uiInitPhase & InitPhase::LoadReferences))
    {
        if(_sfMatchedUrl.getValue().empty() == false)
        {
            fprintf(stderr, "Loading %s\n",
                    _sfMatchedUrl.getValue().c_str());
            
            NodeUnrecPtr pRoot = SceneFileHandler::the()->read(
                _sfMatchedUrl.getValue().c_str(),
                NULL,
                NULL,
                false);
            
            fprintf(stderr, "got %p\n", pRoot.get());
            
            if(pRoot != NULL)
            {
                setRoot(pRoot);
            }
            else
            {
                fprintf(stderr, "  failed\n");
            }
        }


        if(_sfMatchedGlobalUrl.getValue().empty() == false)
        {
            fprintf(stderr, "Loading global %s\n",
                    _sfMatchedGlobalUrl.getValue().c_str());
            
            FieldContainerUnrecPtr pRes(NULL);

            _oPathHandler.pushState();

            _oPathHandler.setBaseFile(_sfMatchedGlobalUrl.getValue().c_str());

            ImageFileHandler::the()->setPathHandler(&_oPathHandler);

            fprintf(stderr, "loading osg file %s ...\n",
                    _sfMatchedGlobalUrl.getValue().c_str());

            pRes = OSG::OSGSceneFileType::the().readContainer(
                _sfMatchedGlobalUrl.getValue().c_str(),
                NULL);

            ImageFileHandler::the()->setPathHandler(NULL);

            _oPathHandler.popState();
            
            fprintf(stderr, "got global %p\n", pRes.get());
            
            if(pRes != NULL)
            {
                ContainerCollectionUnrecPtr pColl = 
                    dynamic_pointer_cast<ContainerCollection>(pRes);

                if(pColl != NULL)
                {
                    MFUnrecFieldContainerPtr::const_iterator fIt  = 
                        pColl->getMFContainers()->begin();

                    MFUnrecFieldContainerPtr::const_iterator fEnd = 
                        pColl->getMFContainers()->end();

                    while(fIt != fEnd)
                    {
                        this->pushToGlobals(*fIt);
                        ++fIt;
                    }   
                }
            }
            else
            {
                fprintf(stderr, "  failed\n");
            }

            fprintf(stderr, "got %ld globals\n",
                    _mfGlobals.size());

            if(_sfActiveCamera.getValue().empty() == false)
            {
                FieldContainer *pCnt = findNamedComponent(
                    _sfActiveCamera.getValue().c_str());

                Camera *pCam = dynamic_cast<Camera *>(pCnt);

                fprintf(stderr, "found camera %p\n",
                        pCam);

                setCamera(pCam);
            }
        }
    }
#endif

    return true;
}


NodeTransitPtr SofaItem::buildSceneGraph(sofa::simulation::Node::SPtr pRoot)
{
    _pScene              = NULL;
    _pChunkOverrideGroup = NULL;

    sofa::core::visual::VisualParams *pVParams = 
        sofa::core::visual::VisualParams::defaultInstance();

    OSG::NodeUnrecPtr pShadowStageNode;
    
    if(_pScene == NULL)
    {
        std::cerr << "OSG Scene is NULL" << std::endl;

        //_scene = OSG::Node::create();
        _pChunkOverrideGroup = OSG::ChunkOverrideGroup::create();

        //_scene = OSG::makeNodeFor(OSG::Group::create());
        _pScene = OSG::makeNodeFor(_pChunkOverrideGroup);


        if(_pScene == NULL) 
            std::cerr << "OSG Scene not created" << std::endl;


        sofa::simulation::OSGVisualUpdateVisitor vmVisitor(pVParams);

        vmVisitor.setChunkOverrideGroupNode(_pScene);

        // get lights
        if(!_sfIgnoreSofaLights.getValue())
        {
            if(_pShadowStage == NULL) 
                _pShadowStage = OSG::ShadowStage::create();

            _pShadowStage->setMapSize(1024);
            _pShadowStage->setShadowSmoothness(0.5f);
            _pShadowStage->setShadowMode(OSG::ShadowStage::NO_SHADOW);
            //_shadowStage->setShadowMode(OSG::ShadowStage::STD_SHADOW_MAP);
            _pShadowStage->setAutoSearchForLights(true);

            pShadowStageNode = OSG::makeNodeFor(_pShadowStage);

            sofa::simulation::OSGLightVisitor lightVisitor(pVParams);

            lightVisitor.setOSG2Parent     (_pScene      );
            lightVisitor.setOSG2ShadowStage(_pShadowStage);
            lightVisitor.setAttachNode     (_pScene      );

            pRoot->execute(&lightVisitor);

            if(lightVisitor.getAttachNode() != NULL)
            {
                vmVisitor.setOSG2Parent(lightVisitor.getAttachNode());

                pRoot->execute(&vmVisitor);
            }
        }
        else
        {
            vmVisitor.setOSG2Parent(_pScene);

            pRoot->execute(&vmVisitor);
        }

        _oPick.init(_pGRoot.get());

        if(pShadowStageNode != NULL && !_sfIgnoreSofaLights.getValue()) 
        {
            pShadowStageNode->addChild(_pScene);

            return NodeTransitPtr(pShadowStageNode);
        }

        return NodeTransitPtr(_pScene);
    }

    return NodeTransitPtr(NULL);
}

bool SofaItem::initialize(void)
{
    Node *pItemRoot  = this->getRoot();

    fprintf(stderr, "SofaItem build scene : %p\n", pItemRoot);

    if(pItemRoot == NULL)
        return false;

    sofa::helper::BackTrace::autodump();

    _loadPolicy.load();

    sofa::core::ExecParams::defaultInstance()->setAspectID(0);

    sofa::simulation::setSimulation(
        new sofa::simulation::tree::TreeSimulation());

    sofa::component::init();

    sofa::simulation::xml::initXml();


    if (_sfSofaDataPath.getValue().empty() == false)
    {
        sofa::helper::system::DataRepository.addFirstPath(_sfSofaDataPath.getValue());
        sofa::helper::system::DataRepository.addFirstPath(_sfSofaDataPath.getValue() + "/examples");
        sofa::helper::system::DataRepository.addFirstPath(_sfSofaDataPath.getValue() + "/share");

    }

    std::string fileName = 
        sofa::helper::system::DataRepository.getFile(
            _sfSofaSceneFile.getValue());

    destroySofaSCN   ();
    destroySceneGraph();

    _pGRoot = 
        sofa::core::objectmodel::SPtr_dynamic_cast<sofa::simulation::Node>(
            sofa::simulation::getSimulation()->load(fileName.c_str()));

    if(_pGRoot == NULL)
    {
        NodeUnrecPtr                pLocalRoot = Node::create();
        ComponentTransformUnrecPtr  pTr        = ComponentTransform::create();

        pLocalRoot->setCore(pTr);

        _pTransform = pTr;

        NodeUnrecPtr pScene = makeTorus(.5, 2, 16, 16);

        pLocalRoot->addChild(pScene);

        pItemRoot->addChild(pLocalRoot);

        return true;
    }

    //if (!verif.empty())
    //{
    //  loadVerificationData(verif, fileName, sofa_root.get());
    //}

    sofa::simulation::getSimulation()->init(_pGRoot.get());
   

    // we shouldn't call this
    //sofa::simulation::getSimulation()->initTextures(groot.get());
    // do this instead to avoid possible opengl calls

    sofa::core::visual::VisualParams *pVParams = 
        sofa::core::visual::VisualParams::defaultInstance();

    sofa::simulation::OSGVisualInitVisitor initVisitor(pVParams);

    _pGRoot->execute(&initVisitor); 
    
    sofa::simulation::getSimulation()->reset(_pGRoot.get());

    std::cerr << "Init - Animate = " << _pGRoot->getAnimate() << std::endl;

    //NodeUnrecPtr pScene = buildSceneGraph(_groot);
    
    NodeUnrecPtr pScene = _pShadowGraph.build(_pGRoot, 
                                              _sfIgnoreSofaLights.getValue());


    _pGRoot->setAnimate(_sfAnimate.getValue() );
    _oPick.init(_pGRoot.get());


    //pScene->updateVolume();
    NodeUnrecPtr   pLocalRoot = Node ::create();
    GroupUnrecPtr  pTr        = Group::create();

    pLocalRoot->setCore(pTr);

    pLocalRoot->addChild(pScene);

    pItemRoot->addChild(pLocalRoot);

    printHelp();

    return true;
}

void SofaItem::tick(void)
{
    if(_pGRoot == NULL) 
    {
        if(_pTransform != NULL)
        {
            Quaternion qRot;

            qRot.setValueAsAxisRad(0.f, 1.f, 0.f, _fAngle);

            _pTransform->setRotation(qRot);

            _fAngle += 0.01 * _sfRotationSpeed.getValue();
        }

        return;
    }

    //if (_shadowStage)
    //{
    //OSG::UInt32 mode = OSG::ShadowStage::NO_SHADOW + _sfShadowMode.getValue();
    //if (_shadowStage->getShadowMode() != mode)
    //    _shadowStage->setShadowMode(mode);
    //}

    SReal dt = _pGRoot->getDt();

    _pGRoot->setAnimate(_sfAnimate.getValue());

    if (_bResetAnimation == true && _sfAnimate.getValue() == true)
    {
        fprintf(stderr, " SofaItem::reset animate\n");
        sofa::simulation::getSimulation()->reset(_pGRoot.get());
    }
    _bResetAnimation = false;

    if (_bPicking)
    {
        //handleMouse(_sfMouseData.getValue());
        //_bPicking = false;
    }

    if(_sfAnimate.getValue() == true)
    {
        sofa::simulation::getSimulation()->animate     (_pGRoot.get(), dt);
        sofa::simulation::getSimulation()->updateVisual(_pGRoot.get()    );
    }
}

void SofaItem::destroySofaSCN(void)
{
    if(_pGRoot != NULL)
    {
        std::cerr << "Unloading GROOT" << std::endl;

        sofa::simulation::getSimulation()->unload(_pGRoot);

        _pGRoot = NULL;

        _loadPolicy.unload();
    }
}

void SofaItem::destroySceneGraph(void)
{
    _pShadowStage        = NULL;
    _pChunkOverrideGroup = NULL;
    _pScene              = NULL;
}


void SofaItem::resolveLinks(void)
{
    std::cerr << "SofaItem::resolveLinks" << std::endl;

    destroySofaSCN   ();
    destroySceneGraph();

    Inherited::resolveLinks();
}

// WIP
void SofaItem::handleMouse(const MouseData& mousedata) 
{
    
    if (!_pGRoot) return;

   


    _bPicking - true;

    Window* window = mousedata.getWindow();
    if (!window) return;
    // currently assume viewport 0
    Viewport* viewport = window->getPort(0);
    if (!viewport) return;
    Camera* camera = viewport->getCamera();
    if (!camera) return;

    Int32 modifier = mousedata.getModifier();
    bool bInteractive = false;
    if (modifier != MouseData::ShiftActive) return;

    //std::cerr << "Handle Picking" << "\n";    

    //printMouse();
    //return;

    bInteractive = true;


    sofa::gui::MousePosition mousepos;
    Int32 state    = mousedata.getState();
    Int32 button   = mousedata.getButton();
    Real32 x       = mousedata.getX();
    Real32 y       = mousedata.getY();

    mousepos.screenWidth = viewport->calcPixelWidth();
    mousepos.screenHeight = viewport->calcPixelHeight();

    mousepos.x = mousedata.getX();
    mousepos.y = mousedata.getY();

    Line l;
    bool hit = camera->calcViewRay(l, mousedata.getX(),
                                      mousedata.getY(),
                                      *viewport       );
    if (!hit) return;

    Pnt3f p = l.getPosition();
    Vec3f d = l.getDirection();

    // OpenSG has Vec3d as well ... be careful
    ::sofa::defaulttype::Vec3d pos, dir;
    pos[0] = p[0]; 
    pos[1] = p[1]; 
    pos[2] = p[2]; 
    dir[0] = d[0]; 
    dir[1] = d[1]; 
    dir[2] = d[2];


    _oPick.activateRay(mousepos.screenWidth,mousepos.screenHeight, _pGRoot.get());

    _oPick.updateRay(pos, dir);
    _oPick.updateMouse2D(mousepos);




    switch (state)
    {
        case MouseData::ButtonDown:
                if (button == MouseData::LeftButton)
                {
                    _oPick.handleMouseEvent(sofa::gui::PRESSED, sofa::gui::LEFT);
                }
                // Shift+Rightclick to remove triangles
                else if (button == MouseData::RightButton) 
                {
                    _oPick.handleMouseEvent(sofa::gui::PRESSED, sofa::gui::RIGHT);
                } 
                // Shift+Midclick (by 2 steps defining 2 input points) 
                // to cut from one point to another
                else if (button == MouseData::MiddleButton)
                {
                    _oPick.handleMouseEvent(sofa::gui::PRESSED, sofa::gui::MIDDLE);
                }
                break;
            case MouseData::ButtonUp:

                if (button == MouseData::LeftButton)
                {
                    _oPick.handleMouseEvent(sofa::gui::RELEASED, sofa::gui::LEFT);
                }
                else if (button == MouseData::RightButton)
                {
                    _oPick.handleMouseEvent(sofa::gui::RELEASED, sofa::gui::RIGHT);
                }
                else if (button == MouseData::MiddleButton)
                {
                    _oPick.handleMouseEvent(sofa::gui::RELEASED, sofa::gui::MIDDLE);
                }
                break;
        
                default:
                break;
     }


    hit = camera->calcViewRay(l, mousedata.getX(),
                                      mousedata.getY(),
                                      *viewport       );
    if (!hit) return;

    p = l.getPosition();
    d = l.getDirection();

    pos[0] = p[0]; 
    pos[1] = p[1]; 
    pos[2] = p[2]; 
    dir[0] = d[0]; 
    dir[1] = d[1]; 
    dir[2] = d[2];

    _oPick.updateRay(pos, dir);
    
}

void SofaItem::printMouse(void) const
{
    const MouseData& mdata = _sfMouseData.getValue();
    Int32 button   = mdata.getButton();
    Int32 state    = mdata.getState();
    Int32 modifier = mdata.getModifier();
    Real32 x       = mdata.getX();
    Real32 y       = mdata.getY();
    UInt32 mode    = mdata.getMode();
    Window* window = mdata.getWindow();
    Viewport* viewport = NULL;
    if (window) viewport = window->getPort(0);
    Camera* camera = NULL;
    if (viewport) camera = viewport->getCamera();


    

    std::string whichbutton;
    if (button == MouseData::LeftButton) whichbutton += "LeftButton ";
    else if (button == MouseData::MiddleButton) whichbutton += "MiddleButton ";
    else if (button == MouseData::RightButton) whichbutton += "RightButton ";
    whichbutton += "\n";
    
    std::string whichmodifier;
    if (modifier == MouseData::NoModifier) whichmodifier += "NoModifier ";
    else if (modifier == MouseData::ShiftActive) whichmodifier += "Shift ";
    else if (modifier == MouseData::CtrlActive) whichmodifier += "Ctrl ";
    else if (modifier == MouseData::AltActive) whichmodifier += "Alt ";
    whichmodifier += "\n";

    std::string whichmode;
    if (mode == MouseData::AbsValues) whichmode += "AbsValues ";
    else whichmode += "RelValues ";
    whichmode += "\n";

    std::string whichstate;
    if (state == MouseData::ButtonDown) whichstate += "Button DOWN";
    else  whichstate += "Button UP";
    whichstate += "\n";

    std::cerr << "======= Mouse =============" << "\n";
    std::cerr << "X : " << x << " Y : " << y << "\n";
    std::cerr << "Buttons "  << whichbutton << "\n";
    std::cerr << "State "  << whichstate << "\n";
    std::cerr << "Modifiers "  << whichmodifier << "\n";
    std::cerr << "Mode "  << whichmode << "\n";
    std::cerr << "Window : " << window << "\n";
    std::cerr << "Viewport : " << viewport << "\n";
    std::cerr << "Camera : " << camera << "\n";
    std::cerr << "====================" << "\n";
}

void SofaItem::printHelp(void) const
{
    std::cerr << "===== Help  ===== " << "\n";
    std::cerr << "a  - Toggle Animation" << "\n";
    std::cerr << "r  - Reset Animation" << "\n";
    std::cerr << "q  - Fit Scene to Screen" << "\n";
    std::cerr << "===== End ===== " << "\n";

}


VCORE_END_NAMESPACE
