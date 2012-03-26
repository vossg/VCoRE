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

#include "OSGNode.h"
#include "OSGSimpleGeometry.h"

//SOFA
#include "OSGSofaVisualModelPolicy.h"
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
        fprintf(stderr, "new animation %i\n",
                _sfAnimate.getValue());

        if(_pGRoot != NULL)
        {
            _pGRoot->setAnimate(!_sfAnimate.getValue());
        }
    }

    if(0x0000 != (whichField & ResetFieldMask))
    {
        fprintf(stderr, "reset animation %i\n",
                _sfReset.getValue());

        if(_pGRoot != NULL)
        {
            sofa::simulation::getSimulation()->reset(_pGRoot.get());
        }
    }

    if(0x0000 != (whichField & ShadowModeFieldMask))
    {
        if(_pShadowStage) 
        {
            _pShadowStage->setShadowMode(
                OSG::ShadowStage::NO_SHADOW + _sfShadowMode.getValue());
        }

//        if(_pShadowStage != NULL) 
//            _pShadowStage->setShadowMode(OSG::ShadowStage::STD_SHADOW_MAP);

        if(_pShadowStage != NULL)
            fprintf(stderr, "new ShadowMode %d\n", _sfShadowMode.getValue());
    }
    if(0x0000 != (whichField & MouseDataFieldMask))
    {
//        printMouse();
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
     Inherited          (    ),
    _pTransform         (NULL),
    _fAngle             (0.f ),
    _pGRoot             (NULL),
    _oPick              (    ),
    _pShadowStage       (NULL),
    _pChunkOverrideGroup(NULL),
    _pScene             (NULL)
{
    initDefaults();
}

SofaItem::SofaItem(const SofaItem &source) :
     Inherited          (source),
    _pTransform         (NULL  ),
    _fAngle             (0.f   ),
    _pGRoot             (NULL  ),
    _oPick              (      ),
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
// NOT CALLED
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

    sofa::gui::qt::viewer::OSGModelPolicy policy; 
    policy.load();

    sofa::core::ExecParams::defaultInstance()->setAspectID(0);

    sofa::simulation::setSimulation(
        new sofa::simulation::tree::TreeSimulation());

    sofa::component::init();

    sofa::simulation::xml::initXml();

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


    if(_sfAnimate.getValue()) 
        _pGRoot->setAnimate(true );
    else 
        _pGRoot->setAnimate(false);


    //pScene->updateVolume();
    NodeUnrecPtr   pLocalRoot = Node ::create();
    GroupUnrecPtr  pTr        = Group::create();

    pLocalRoot->setCore(pTr);

    pLocalRoot->addChild(pScene);

    pItemRoot->addChild(pLocalRoot);

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
//fprintf(stderr, " SofaItem::TICK animate\n");

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

void SofaItem::printMouse(void) const
{
    UInt32  button   = _sfMouseData.getValue().getButton();
    UInt32  state    = _sfMouseData.getValue().getState();
    UInt32  modifier = _sfMouseData.getValue().getModifier();
    Real32  x        = _sfMouseData.getValue().getX();
    Real32  y        = _sfMouseData.getValue().getY();
//    Window *window   = _sfMouseData.getValue().getWindow();
    UInt32  mode     = _sfMouseData.getValue().getMode();

    std::string whichbutton;

    if(button == MouseData::LeftButton) 
        whichbutton += "LeftButton ";
    else if(button == MouseData::MiddleButton) 
        whichbutton += "MiddleButton ";
    else if(button == MouseData::RightButton) 
        whichbutton += "RightButton ";

    whichbutton += "\n";
    
    std::string whichmodifier;

    if(modifier == MouseData::NoModifier) 
        whichmodifier += "NoModifier ";
    else if(modifier == MouseData::ShiftActive) 
        whichmodifier += "Shift ";
    else if(modifier == MouseData::CtrlActive) 
        whichmodifier += "Ctrl ";
    else if(modifier == MouseData::AltActive) 
        whichmodifier += "Alt ";

    whichmodifier += "\n";

    std::string whichmode;

    if(mode == MouseData::AbsValues) 
        whichmode += "AbsValues ";
    else 
        whichmode += "RelValues ";

    whichmode += "\n";

    std::string whichstate;

    if(state == MouseData::ButtonDown) 
        whichstate += "Button DOWN";
    else
        whichstate += "Button UP";

    whichstate += "\n";

    std::cerr << "======= Mouse =============" << "\n";
    std::cerr << "X : "        << x << " Y : " << y << "\n";
    std::cerr << "Buttons "    << whichbutton << "\n";
    std::cerr << "State "      << whichstate << "\n";
    std::cerr << "Modifiers "  << whichmodifier << "\n";
    std::cerr << "Mode "       << whichmode << "\n";
    std::cerr << "====================" << "\n";
}

VCORE_END_NAMESPACE
