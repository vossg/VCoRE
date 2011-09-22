#include "OSGConfig.h"

#include <iostream>

#include "OSGGLUT.h"

#include "OSGVector.h"
#include "OSGQuaternion.h"
#include "OSGMatrix.h"
#include "OSGMatrixUtility.h"
#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGThread.h"
#include "OSGComponentTransform.h"
#include "OSGAction.h"
#include "OSGRenderAction.h"
#include "OSGSimpleGeometry.h"
#include "OSGSceneFileHandler.h"

#include "OSGDirectionalLight.h"

#include "OSGStagedViewport.h"
#include "OSGFrameBufferObject.h"
#include "OSGRenderBuffer.h"
#include "OSGTextureBuffer.h"

#include "OSGWindow.h"
#include "OSGPerspectiveCamera.h"
#include "OSGSolidBackground.h"
#include "OSGChangeList.h"
#include "OSGTextureObjChunk.h"
#include "OSGTextureEnvChunk.h"
#include "OSGSimpleMaterial.h"
#include "OSGSimpleStage.h"
#include "OSGDeferredShadingStage.h"
#include "OSGHDRStage.h"
#include "OSGVCTestStage.h"
#include "OSGVisitSubTree.h"

#include "OSGSimpleSceneManager.h"
#include "OSGPassiveWindow.h"

#include "OSGVCGLUTViewer.h"
#include "OSGVCRenderTask.h"

//#define USE_DEPTH_TEXTURE 1

OSG::SimpleSceneManager      *mgr(NULL);

OSG::GroupNodeRefPtr          planeRoot;
OSG::GroupNodeRefPtr          animRoot;

OSG::VCTestStageNodeRefPtr          stage;
OSG::PerspectiveCameraUnrecPtr stage_cam;
OSG::SolidBackgroundUnrecPtr bkgnd;

OSG::Vec3f                     sceneTrans;
OSG::ComponentTransformNodeRefPtr       cam_transScene;  // Transofrmation of cam/light/stage
OSG::TransformNodeRefPtr       sceneXform;      // Rotation of model we are viewing

//OSG::TextureObjChunkUnrecPtr   tx1o;       // Texture object to shared
//OSG::TextureEnvChunkUnrecPtr   tx1e;       // Texture environment to share
//
//#ifdef USE_DEPTH_TEXTURE
//OSG::TextureObjChunkUnrecPtr   txDepth;    // Depth texture
//#endif
//
//OSG::FrameBufferObjectUnrecPtr pFBO;
//OSG::TextureBufferUnrecPtr     pTexBuffer;

OSG::VisitSubTreeNodeRefPtr  pVisit;

bool                      bReadBack = false;
bool                      bBoxActive = true;

OSG::VCRenderTaskRefPtr renderTask;

// ----- Scene structure --- //
/*
planeRoot:Group[gr1]
/           |          \  |
dlight:dl b1   animRoot       t1n:Xform[cam_transPlane]
|                              |
sceneTrN:Xform[scene_trans]   b1n:Group[b1]  cam/light beacon
|
plane_node


animRoot:Group
/              \    |
dlight:DirLight:beacon      cam_transScene:Transform
|                                |
sceneXform:Transform                beacon:Group
|
fileNode:Node

animRoot
|
pStage:SimpleStage --> pFBO, cam:b1n
|
pVisit:VisitSubTree
|
dlight

FrameBufferObject: pFBO    --> pTexBuffer, pDepthBuffer
TextureBuffer: pTexBuffer  --> tx1o
RenderBuffer: pDepthBuffer
*/


namespace OSG {
    class FBOComplex
    {
    public:
        OSG::FrameBufferObjectUnrecPtr _fbo;
        OSG::RenderBufferUnrecPtr     _texBuffer;
        OSG::ImageUnrecPtr _texImg;
        OSG::TextureObjChunkUnrecPtr   _texObj;
        OSG::TextureEnvChunkUnrecPtr   _texEnv;
        //    OSG::TextureObjChunkUnrecPtr   _depthTexObj;
        OSG::RenderBufferUnrecPtr      _depthBuffer;

        FBOComplex(Int32 w, Int32 h)
        {
            bool readBack = true;

            _texObj = OSG::TextureObjChunk::create();
            _texEnv = OSG::TextureEnvChunk::create();

            _texImg = OSG::Image::create();
            _texImg->set(OSG::Image::OSG_RGBA_PF, w, h, 1,
                1, 1, 0.f, NULL, OSG::Image::OSG_UINT8_IMAGEDATA, readBack);

//            _texObj->setImage    (_texImg      );
            _texObj->setMinFilter(GL_LINEAR );
            _texObj->setMagFilter(GL_LINEAR );
            _texObj->setWrapS    (GL_REPEAT );
            _texObj->setWrapT    (GL_REPEAT );

            _texEnv->setEnvMode (GL_REPLACE);

            //OSG::ImageUnrecPtr dImg = OSG::Image::create();
            //dImg->set(Image::OSG_L_PF, 512, 512);

            //txDepth->setImage (dImg);
            //txDepth->setMinFilter(GL_NEAREST );
            //txDepth->setMagFilter(GL_LINEAR );
            //txDepth->setWrapS    (GL_CLAMP_TO_EDGE );
            //txDepth->setWrapT    (GL_CLAMP_TO_EDGE );
            //txDepth->setExternalFormat(GL_DEPTH_COMPONENT);
            //txDepth->setInternalFormat(GL_DEPTH_COMPONENT32);

            _fbo         = OSG::FrameBufferObject::create();
            _texBuffer   = OSG::RenderBuffer::create();

            //OSG::TextureBufferUnrecPtr     pDepthBuffer = OSG::TextureBuffer::create();
            //pDepthBuffer->setTexture(txDepth);
            _depthBuffer = OSG::RenderBuffer ::create();
            _depthBuffer->setInternalFormat(GL_DEPTH_COMPONENT24   );

//            _texBuffer->setTexture (_texObj);
            _texBuffer->setInternalFormat(GL_RGBA);
            _texBuffer->setImage(_texImg);
            _texBuffer->setReadBack(readBack);

            _fbo->setSize(w, h);
            _fbo->setColorAttachment(_texBuffer, 0);
            _fbo->setDepthAttachment(_depthBuffer );

            _fbo->editMFDrawBuffers()->clear();
            _fbo->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0_EXT);

            _fbo->setPostProcessOnDeactivate(readBack);
//            commitChanges();
        }

        void resize(Int32 w, Int32 h)
        {
            _texImg->set(OSG::Image::OSG_RGB_PF, w, h, 1,
                1, 1, 0, NULL, OSG::Image::OSG_UINT8_IMAGEDATA, false);
            _fbo->setSize(w, h);
//            commitChanges();
        }
    };
}

OSG::FBOComplex* fboComplex = NULL;

void testPreRenderCB(OSG::DrawEnv *)
{
    //    fprintf(stderr, "PreRender\n");
}

void testPostRenderCB(OSG::DrawEnv *)
{
    //    fprintf(stderr, "PostRender\n");
}

void testRenderTask()
{
    if(!renderTask)
    {
        FNOTICE(("CREATE\n"));
        renderTask = OSG::VCRenderTask::create();

        stage->setInheritedTarget(true);

        OSG::StagedViewportUnrecPtr vp = OSG::StagedViewport::create();
        vp->setStage(stage);
        //OSG::FBOViewportUnrecPtr vp = OSG::FBOViewport::create();
        vp->setFrameBufferObject(fboComplex->_fbo);
        vp->setCamera      (/*stage_cam*/ OSG::VCGLUTViewer::the()->_sceneMgr->getCamera()  );
        vp->setBackground  (bkgnd);
        vp->setRoot(animRoot);

        renderTask->setViewport(vp);
        renderTask->setDone(false);
        OSG::commitChanges();
    }

    if(renderTask->getDone())
    {
        FNOTICE(("RESULT\n"));
        OSG::VCGLUTViewer::the()->getRenderer()->subRenderTask(0);
//        fboComplex->_texImg->write("c:/work/tmp/fuck.png");
        fboComplex->_texBuffer->getImage()->write("c:/work/tmp/fuck.png");
        renderTask->setDone(false);
        OSG::commitChanges();
    }
    else
    {
        OSG::Matrix bla;
        stage_cam->getViewing(bla, 128, 128);
        std::cout << "beacon: " << bla << std::endl;
        stage_cam->getBeacon()->getParent()->getCore()->dump();
        OSG::VCGLUTViewer::the()->getRenderer()->addRenderTask(renderTask);
        FNOTICE(("QUEUED\n"));
    }


}

//void display(void)
//{
//    OSG::Matrix m1;
//
//    // Anim
//    OSG::Real32 t = glutGet(GLUT_ELAPSED_TIME);
//    m1.setTransform(-sceneTrans, OSG::Quaternion(OSG::Vec3f(0,1,0), 
//        t / 1000.f));
//    sceneXform->setMatrix(m1);
//
//    OSG::commitChanges();
//
//    mgr->redraw();
//
//    // all done, swap
//    glutSwapBuffers();
//
//    if(bReadBack == true)
//    {
//        OSG::Image *pImg = tx1o->getImage();
//
//        pImg->write("/tmp/foo.png");
//    }
//}
//
//void reshape(int w, int h)
//{
//    std::cerr << "Reshape: " << w << "," << h << std::endl;
//    mgr->resize(w,h);
//    glutPostRedisplay();
//}


void animate(void)
{
    glutPostRedisplay();
}

// tballall stuff


void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);

    glutPostRedisplay();
}

void key(unsigned char key, int x, int y)
{
    switch(key)
    {
//    case 27:
//
//        planeRoot      = static_cast<OSG::Node *>(NULL);
//        animRoot       = static_cast<OSG::Node *>(NULL);
//
//        cam_transScene = static_cast<OSG::Node *>(NULL);
//        sceneXform     = static_cast<OSG::Node *>(NULL);
//
//        tx1o           = NULL;
//        tx1e           = NULL;
//
//#ifdef USE_DEPTH_TEXTURE
//        txDepth        = NULL;
//#endif
//
//        pFBO           = NULL;
//        pTexBuffer     = NULL;
//
//        pVisit         = static_cast<OSG::Node *>(NULL);
//
//        delete mgr;
//
//        OSG::osgExit();
//        exit(0);

    case 'a':
        glDisable( GL_LIGHTING );
        std::cerr << "Lighting disabled." << std::endl;
        break;
    case 's':
        glEnable( GL_LIGHTING );
        std::cerr << "Lighting enabled." << std::endl;
        break;
    case 'z':
        glPolygonMode( GL_FRONT_AND_BACK, GL_POINT);
        std::cerr << "PolygonMode: Point." << std::endl;
        break;
    case 'x':
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
        std::cerr << "PolygonMode: Line." << std::endl;
        break;
    case 'c':
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
        std::cerr << "PolygonMode: Fill." << std::endl;
        break;
    case 'd':
        std::cerr << "Wrote out scene file." << std::endl;
        OSG::SceneFileHandler::the()->write(planeRoot, 
            "simple_stage_dump.osb");
        break;
    case 'b':
        bBoxActive = !bBoxActive;

        if(bBoxActive == true)
        {
            pVisit->setSubTreeTravMask(0xFFFFFFFF);
        }
        else
        {
            pVisit->setSubTreeTravMask(0xFFFFFFFE);
        }
        break;

    //case 'B':
    //    {
    //        OSG::ImageRefPtr pImg = tx1o->getImage();

    //        pImg->set(OSG::Image::OSG_RGB_PF, 512, 512);

    //        //            tx1o->imageContentChanged();

    //        //            Window::reinitializeGLObject(tx1o->getGLId());

    //        pFBO->setSize(512, 512);
    //    }
    //    break;

    //case 'S':
    //    {
    //        OSG::ImageRefPtr pImg = tx1o->getImage();

    //        pImg->set(OSG::Image::OSG_RGB_PF, 256, 256);

    //        //            tx1o->imageContentChanged();

    //        //            Window::reinitializeGLObject(tx1o->getGLId());

    //        pFBO->setSize(256, 256);
    //    }
    //    break;

    //case 'r':
    //    {
    //        fprintf(stderr, "enable readback\n");

    //        bReadBack = true;

    //        pFBO->setPostProcessOnDeactivate(true);
    //    }
    //    break;

    //case 'R':
    //    {
    //        fprintf(stderr, "disable readback\n");

    //        bReadBack = false;

    //        pFBO->setPostProcessOnDeactivate(false);
    //    }

    case '1':
        {
            OSG::VCGLUTViewer::the()->setStage(stage.core());
            FNOTICE(("setting stage.\n"));
            OSG::commitChanges();
        }
        break;

    case '2':
        {
            OSG::VCGLUTViewer::the()->setStage(NULL);
            FNOTICE(("UNsetting stage.\n"));
            OSG::commitChanges();
        }
        break;
    case '3':
        {
            fboComplex->resize(512,512);
            OSG::commitChanges();
        }
        break;
    case '4':
        {
            fboComplex->resize(128,128);
            OSG::commitChanges();
        }
        break;
    case '5':
        {
            testRenderTask();
        }
        break;

    }
}



// Setup the part of the scene rooted at animRoot
// This includes a file to animate, a beacon for a light,
// and a staged core to render this subtree from the position
// of the light.
void initAnimSetup(int argc, char **argv)
{
    // beacon for light and stage camera
    OSG::GroupNodeRefPtr beacon = OSG::GroupNodeRefPtr::create();

    // transformation for beacon
    cam_transScene   = OSG::ComponentTransformNodeRefPtr::create();
    cam_transScene->setTranslation(OSG::Vec3f(0.f,0.f,10.f));
    cam_transScene.node()->addChild(beacon);

    // light
    OSG::DirectionalLightNodeRefPtr dlight = 
        OSG::DirectionalLightNodeRefPtr::create();

    dlight->setAmbient  (.3f, .3f, .3f, 1);
    dlight->setDiffuse  ( 1,  1,  1, 1);
    dlight->setDirection( 0,  0,  1   );
    dlight->setBeacon   (beacon       );

    // animRoot
    animRoot = OSG::GroupNodeRefPtr::create();
    animRoot.node()->addChild(cam_transScene   );

    // Load the file and put it in the graph
    // under the sceneXform node.
    OSG::NodeUnrecPtr file = NULL;

    if(argc > 1)
    { file = OSG::SceneFileHandler::the()->read(argv[1]); }

    if(file == NULL)
    {
        std::cerr << "Couldn't load file, ignoring" << std::endl;
        file = OSG::makeTorus(.5, 2, 16, 16);
    }

    OSG::Vec3f min,max;
    OSG::commitChanges();
    file->updateVolume();
    file->dump();
    file->getVolume().getBounds(min, max);

    std::cout << "Volume: from " << min << " to " << max << std::endl;
    sceneTrans.setValues(min[0] + ((max[0] - min[0]) * 0.5),
        min[1] + ((max[1] - min[1]) * 0.5),
        max[2] + ( max[2] - min[2]) * 4.5 );


    sceneXform = OSG::TransformNodeRefPtr::create();
    sceneXform.node()->addChild(file);

//    OSG::NodeUnrecPtr pBoxNode = OSG::makeBox(1, 1, 1, 5, 5, 5);
//    pBoxNode->setTravMask(pBoxNode->getTravMask() & 0x0001);
//    sceneXform.node()->addChild(pBoxNode);

    dlight.node()->addChild(sceneXform);


    // ---- STAGE RENDERING SETUP --- //
    // Camera: setup camera to point from beacon (light pos)
    //   with a 90deg FOV to render the scene
    stage_cam = OSG::PerspectiveCamera::create();

    stage_cam->setBeacon(beacon);
    stage_cam->setFov   (OSG::osgDegree2Rad(90));
    stage_cam->setNear  (0.1f);
    stage_cam->setFar   (100000);


    // Background
    bkgnd = OSG::SolidBackground::create();
    bkgnd->setColor(OSG::Color3f(1,0,1));

//    // FBO setup
//    tx1o = OSG::TextureObjChunk::create();
//    tx1e = OSG::TextureEnvChunk::create();
//
//    // Setup the shared texture and texture environment
//    // - Create an empty image so texture can allocate size and memory
//    OSG::ImageUnrecPtr pImg = OSG::Image::create();
//    pImg->set(OSG::Image::OSG_RGB_PF, 512, 512, 1,
//        1, 1, 0, NULL, OSG::Image::OSG_UINT8_IMAGEDATA, false);
//
//    tx1o->setImage    (pImg      );
//    tx1o->setMinFilter(GL_LINEAR );
//    tx1o->setMagFilter(GL_LINEAR );
//    tx1o->setWrapS    (GL_REPEAT );
//    tx1o->setWrapT    (GL_REPEAT );
//
//    tx1e->setEnvMode (GL_REPLACE);
//
//#ifdef USE_DEPTH_TEXTURE
//    OSG::ImageUnrecPtr dImg = OSG::Image::create();
//    dImg->set(Image::OSG_L_PF, 512, 512);
//
//    txDepth->setImage (dImg);
//    txDepth->setMinFilter(GL_NEAREST );
//    txDepth->setMagFilter(GL_LINEAR );
//    txDepth->setWrapS    (GL_CLAMP_TO_EDGE );
//    txDepth->setWrapT    (GL_CLAMP_TO_EDGE );
//    txDepth->setExternalFormat(GL_DEPTH_COMPONENT);
//    txDepth->setInternalFormat(GL_DEPTH_COMPONENT32);
//#endif
//
//    pFBO         = OSG::FrameBufferObject::create();
//    pTexBuffer   = OSG::TextureBuffer::create();
//
//#ifdef USE_DEPTH_TEXTURE
//    OSG::TextureBufferUnrecPtr     pDepthBuffer = OSG::TextureBuffer::create();
//    pDepthBuffer->setTexture(txDepth);
//#else
//    OSG::RenderBufferUnrecPtr      pDepthBuffer = OSG::RenderBuffer ::create();
//    pDepthBuffer->setInternalFormat(GL_DEPTH_COMPONENT24   );
//#endif
//
//    pTexBuffer->setTexture (tx1o);
//    pTexBuffer->setReadBack(false);
//
//    pFBO->setSize(512, 512);
//    pFBO->setColorAttachment(pTexBuffer, 0);
//    pFBO->setDepthAttachment(pDepthBuffer );
//
//    pFBO->editMFDrawBuffers()->clear();
//    pFBO->editMFDrawBuffers()->push_back(GL_COLOR_ATTACHMENT0_EXT);

    // Stage core setup
    fboComplex = new OSG::FBOComplex(128,128);
    stage = OSG::VCTestStageNodeRefPtr::create();
    //stage->setRenderTarget(fboComplex->_fbo);
    //stage->setCamera      (stage_cam  );
    //stage->setBackground  (bkgnd);
//
//    pStage->addPreRenderFunctor (&testPreRenderCB, "" );
//    pStage->addPostRenderFunctor(&testPostRenderCB, "");
//
//    // Setup sub-tree visitor
//    // - This will setup a graph that will render a subtree during traversal
//    pVisit = OSG::VisitSubTreeNodeRefPtr::create();
//    pVisit->setSubTreeRoot(dlight);
//
//    pStage.node()->addChild(pVisit);
//    animRoot.node()->addChild(pStage);
    animRoot.node()->addChild(dlight);
}


void initPlaneSetup(void)
{
//    // beacon for camera and light
//    OSG::GroupNodeRefPtr  beacon = OSG::GroupNodeRefPtr::create();
//
//    // transformation
//    OSG::TransformNodeRefPtr cam_transPlane = 
//        OSG::TransformNodeRefPtr::create();
//    cam_transPlane.node()->addChild(beacon);
//
//    // light
//    OSG::DirectionalLightNodeRefPtr dl = 
//        OSG::DirectionalLightNodeRefPtr::create();
//
//    dl->setAmbient  (.3f, .3f, .3f, 1);
//    dl->setDiffuse  ( 1,  1,  1, 1);
//    dl->setDirection( 0,  0,  1   );
//    dl->setBeacon   (beacon          );
//
//    // planeRoot
//    planeRoot = OSG::GroupNodeRefPtr::create();
//
//    planeRoot.node()->addChild(cam_transPlane);
//    planeRoot.node()->addChild(animRoot);
//    planeRoot.node()->addChild(dl);
//
//    // Create plane to project the staged render
//    OSG::NodeUnrecPtr plane_node = OSG::makePlane(10, 10, 5, 5);
//
//    // Setup the shared texture and texture environment
//    // - Create an empty image so texture can allocate size and memory
//    OSG::ImageUnrecPtr pImg = OSG::Image::create();
//    pImg->set(OSG::Image::OSG_RGB_PF, 512, 512);
//
//    tx1o->setImage    (pImg      );
//    tx1o->setMinFilter(GL_LINEAR );
//    tx1o->setMagFilter(GL_LINEAR );
//    tx1o->setWrapS    (GL_REPEAT );
//    tx1o->setWrapT    (GL_REPEAT );
//
//    tx1e->setEnvMode (GL_REPLACE);
//
//#ifdef USE_DEPTH_TEXTURE
//    OSG::ImageUnrecPtr dImg = OSG::Image::create();
//    dImg->set(Image::OSG_L_PF, 512, 512);
//
//    txDepth->setImage (dImg);
//    txDepth->setMinFilter(GL_NEAREST );
//    txDepth->setMagFilter(GL_LINEAR );
//    txDepth->setWrapS    (GL_CLAMP_TO_EDGE );
//    txDepth->setWrapT    (GL_CLAMP_TO_EDGE );
//    txDepth->setExternalFormat(GL_DEPTH_COMPONENT);
//    txDepth->setInternalFormat(GL_DEPTH_COMPONENT32);
//#endif
//
//
//    // Material for plane
//    // - Create a material that will reference the texture and render
//    //     it on the plane
//    OSG::SimpleMaterialUnrecPtr mat = OSG::SimpleMaterial::create();
//
//    mat->setDiffuse(OSG::Color3f(1,1,1));
//    mat->setLit    (false              );
//#ifdef USE_DEPTH_TEXTURE
//    mat->addChunk  (txDepth            );
//#else
//    mat->addChunk  (tx1o               );
//#endif
//    mat->addChunk  (tx1e               );
//
//    OSG::GeometryUnrecPtr pGeo = 
//        dynamic_cast<OSG::Geometry *>(plane_node->getCore());
//    pGeo->setMaterial(mat);
//
//    // Finish connecting graph
//    OSG::TransformNodeRefPtr scene_trans = OSG::TransformNodeRefPtr::create();
//    scene_trans.node()->addChild(plane_node );
//
//    dl.node()->addChild(scene_trans);

}

int doMain (int argc, char **argv)
{
#ifdef WIN32
    OSG::preloadSharedObject("OSGImageFileIO");
#endif
    OSG::osgInit(argc,argv);
    OSG::osgLog().setLogLevel(OSG::LOG_NOTICE);


    // GLUT init

    //glutInit(&argc, argv);
    //glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
    //glutInitWindowSize(500,500);
    ///*int winid =*/ glutCreateWindow("testSimpleStage");
    //glutKeyboardFunc(key);
    ////glutVisibilityFunc(vis);
    //glutReshapeFunc(reshape);
    //glutDisplayFunc(display);
    //glutIdleFunc(display);
    //glutMouseFunc(mouse);
    //glutMotionFunc(motion);

    // OSG
    OSG::SceneFileHandler::the()->print();

    initAnimSetup(argc, argv);
    initPlaneSetup();

//    stage = OSG::SimpleStageNodeRefPtr::create();

    OSG::VCGLUTViewer::the()->setRoot(animRoot);
    OSG::VCGLUTViewer::the()->setKeyCallback(key);

    OSG::commitChanges();

    //OSG::PassiveWindowUnrecPtr pwin(OSG::PassiveWindow::create());
    //pwin->init();

    //// create the SimpleSceneManager helper
    //mgr = new OSG::SimpleSceneManager;

    //// create the window and initial camera/viewport
    //mgr->setWindow(pwin );
    //// tell the manager what to manage
    //mgr->setRoot  (planeRoot);

    //OSG::commitChanges();

    //// show the whole scene
    //mgr->showAll();

    //mgr->setUseTraversalAction(true);

    return 0;
}
int main (int argc, char **argv)
{
    doMain(argc, argv);

    glutMainLoop();

    return 0;
}
