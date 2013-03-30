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

#include "OSGStagedViewport.h"
#include "OSGTextureBuffer.h"
#include "OSGTextureObjChunk.h"
#include "OSGStage.h"
#include "OSGFrameBufferObject.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGStagedViewportBase.cpp file.
// To modify it, please change the .fcd file (OSGStagedViewport.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void StagedViewport::initMethod(InitPhase ePhase)
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

StagedViewport::StagedViewport(void) :
    Inherited()
{
    _visitSubtreeNode = OSG::VisitSubTreeNodeRefPtr::create();
    _visitSubtreeNode->setSubTreeRoot(NULL);

    _stageNode = Node::create();
    _stageNode->addChild(_visitSubtreeNode);
}

StagedViewport::StagedViewport(const StagedViewport &source) :
    Inherited(source)
{
//    assert(false);
    _visitSubtreeNode = OSG::VisitSubTreeNodeRefPtr::create();
    _visitSubtreeNode->setSubTreeRoot(source._visitSubtreeNode->getSubTreeRoot());

    _stageNode = Node::create();
    _stageNode->setCore(source._stageNode->getCore());
    _stageNode->addChild(_visitSubtreeNode);
}

StagedViewport::~StagedViewport(void)
{
}

/*----------------------------- class specific ----------------------------*/

void StagedViewport::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    if(whichField & StageFieldMask)
    {
//        FNOTICE(("Stage changed.\n"));
        _stageNode->setCore(getStage());
    }
    if(whichField & RootFieldMask)
    {
//        FNOTICE(("root changed.\n"));
        _visitSubtreeNode->setSubTreeRoot(getRoot());
    }

    Inherited::changed(whichField, origin, details);
}

void StagedViewport::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump StagedViewport NI" << std::endl;
}


Int32 StagedViewport::getPixelLeft(void) const
{
    if(!getFrameBufferObject())
    {   // => behave like normal viewport
        return Viewport::calcPixelLeft();
    }
    else
    {   // => behave like FBOViewport
        if(getLeft() > 1)
            return Int32(getLeft());

        return Int32(getFrameBufferObject()->getWidth() * getLeft());
    }
}

Int32 StagedViewport::getPixelRight(void) const
{
    if(!getFrameBufferObject())
    {   // => behave like normal viewport
        return Viewport::calcPixelRight();
    }
    else
    {   // => behave like FBOViewport
        if(getRight() > 1)
            return Int32(getRight());

        // <=1: partial screen, use 1 less to not overlap other windows
        return Int32(getFrameBufferObject()->getWidth() * getRight() - 1);
    }
}

Int32 StagedViewport::getPixelBottom(void) const
{
    if(!getFrameBufferObject())
    {   // => behave like normal viewport
        return Viewport::calcPixelBottom();
    }
    else
    {   // => behave like FBOViewport
        if(getBottom() > 1)
            return Int32(getBottom());

        return Int32(getFrameBufferObject()->getHeight() * getBottom());
    }
}

Int32 StagedViewport::getPixelTop(void) const
{
    if(!getFrameBufferObject())
    {   // => behave like normal viewport
        return Viewport::calcPixelTop();
    }
    else
    {   // => behave like FBOViewport
        if(getTop() > 1)
            return Int32(getTop());

        // <=1: partial screen, use 1 less to not overlap other windows
        return Int32(getFrameBufferObject()->getHeight() * getTop() - 1);
    }
}

bool StagedViewport::isFullWindow(void) const
{
    if(getFrameBufferObject() == NULL)
        return Viewport::calcIsFullWindow();
    else
        return  
            getPixelBottom() == 0 &&
            getPixelLeft()   == 0 &&
            getPixelTop()    == getFrameBufferObject()->getHeight() - 1 &&
            getPixelRight()  == getFrameBufferObject()->getWidth () - 1;
}


void StagedViewport::render(RenderActionBase *action)
{
//#ifndef OSG_OGL_ES2
//        if(getLeftBuffer())
//        {
//            if(getRightBuffer())
//            {
//                glDrawBuffer(GL_BACK);
//                glReadBuffer(GL_BACK);
//            }
//            else
//            {
//                glDrawBuffer(GL_BACK_LEFT);
//                glReadBuffer(GL_BACK_LEFT);
//            }
//        }
//        else
//        {
//            if(getRightBuffer())
//            {
//                glDrawBuffer(GL_BACK_RIGHT);
//                glReadBuffer(GL_BACK_RIGHT);
//            }
//            else
//            {
//                glDrawBuffer(GL_NONE);
//                glReadBuffer(GL_NONE);
//            }
//        }
//#endif

    if(!getStage())
    {
//        FNOTICE((">>> NO stage\n"));
        Inherited::render(action);
    }
    else
    {
//        FNOTICE((">>> With stage\n"));
        renderWithStage(action);
    }

//#ifndef OSG_OGL_ES2
//        glDrawBuffer(GL_BACK);
//        glReadBuffer(GL_BACK);
//#endif
}


void StagedViewport::renderWithStage(RenderActionBase *action)
{
    _pTravValidator->incEventCounter();

    if(this->getTravMask() == 0x0000)
        return;

    if(getCamera() == NULL)
    {
        SWARNING << "Viewport::render: no Camera, can not render!" << std::endl;
        return;
    }
    if(getBackground() == NULL)
    {
        SWARNING << "Viewport::render: no Background, can not render!" << std::endl;
        return;
    }
    if(getRoot() == NULL)
    {
        SWARNING << "Viewport::render: no root, can not render!" << std::endl;
        return;
    }

#if 0 // Have to check GV
    activate();
#endif

    action->setCamera    (getCamera    ());
    action->setBackground(getBackground());
    action->setViewarea  (this           );
    action->setTravMask  (getTravMask()  );

    action->apply(_stageNode);

    // Blit the result
    // myTarget && stageTarget => assume stage renders into stageTarget, blit this into myTarget (TODO)
    // !myTarget && stageTarget => assume stage renders into stageTarget, blit this into back buffer
    // !myTarget && !stageTarget => assume stage renders into back buffer, no blitting
    // myTarget && !stageTarget => assume stage renders into myTarget, no blitting
    StageUnrecPtr stage = getStage();
    FrameBufferObjectUnrecPtr myTarget = this->getTarget();
    FrameBufferObjectUnrecPtr stageTarget = stage->getRenderTarget();
    FrameBufferObjectUnrecPtr theTarget = stageTarget ? stageTarget : myTarget;
    if( !myTarget && stageTarget )
        stretchTargetToFrameBuffer(action, theTarget);


    //Window  *pWin = action->getWindow();

    //if((pWin->getDrawMode() & Window::PartitionDrawMask) ==
    //    Window::SequentialPartitionDraw)
    //{
    //    DrawEnv  oEnv;

    //    oEnv.setWindow(action->getWindow());

    //    oEnv.setTileFullSize(getCamera()->tileGetFullSize());
    //    oEnv.setTileRegion  (getCamera()->tileGetRegion  ());

    //    oEnv.setDrawerId  (action->getDrawerId  ());
    //    oEnv.setDrawableId(action->getDrawableId());

    //    for(UInt16 i=0; i < getMFForegrounds()->size(); i++)
    //    {
    //        Foreground        *pForeground = getForegrounds(i);
    //        FrameBufferObject *pTarget     = this->getTarget();

    //        if(pTarget != NULL)
    //        {
    //            pTarget->activate(&oEnv);
    //        }

    //        pForeground->draw(&oEnv, this);

    //        if(pTarget != NULL)
    //        {
    //            pTarget->deactivate(&oEnv);
    //        }
    //    }
    //}
    //else
    //{
    //    if(_pForegroundTask == NULL)
    //    {
    //        _pForegroundTask = 
    //            new ViewportDrawTask(this, ViewportDrawTask::Foregrounds);
    //    }

    //    pWin->queueTaskFromDrawer(_pForegroundTask);
    //}

#if 0 // Have to check GV
    deactivate();
#endif
}


void StagedViewport::stretchTargetToFrameBuffer(RenderActionBase *action, FrameBufferObject *target)
{

    Window  *pWin = action->getWindow();

    if((pWin->getDrawMode() & Window::PartitionDrawMask) ==
        Window::SequentialPartitionDraw)
    {
        DrawEnv  oEnv;

        oEnv.setWindow(action->getWindow());

        //oEnv.setTileFullSize(getCamera()->tileGetFullSize());
        //oEnv.setTileRegion  (getCamera()->tileGetRegion  ());

        // THINKABOUTME KS:
        //oEnv.setDrawerId  (action->getDrawerId  ());
        //oEnv.setDrawableId(action->getDrawableId());

        glClearColor(0.0, 1.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);

        FrameBufferAttachment* fba = target->getColorAttachments(0);
        TextureObjChunk* texObj = dynamic_cast<TextureBuffer*>(fba)->getTexture();
        if( texObj )
        {
            texObj->activate(&oEnv,0);
            glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadIdentity();
            glOrtho(0, 1, 0, 1, -1, 1 );
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();

            float u = 0.0f;
            float v = 0.0f;

            //            glColor3f(1,1,1);
            glBegin(GL_QUADS);
#if 0
            RTsize w,h;
            buffer->getSize(w,h);
            float view[4];
            view[0] = _optixViewport._viewport.x/(float)w;
            view[1] = _optixViewport._viewport.y/(float)h;
            view[2] = view[0] + _optixViewport._viewport.z/(float)w;
            view[3] = view[1] + _optixViewport._viewport.w/(float)h;

            glTexCoord2f(view[0], view[1]);
            glVertex2f(0.0f, 0.0f);

            glTexCoord2f(view[2], view[1]);
            glVertex2f(1.0f, 0.0f);

            glTexCoord2f(view[2], view[3]);
            glVertex2f(1.0f, 1.0f);

            glTexCoord2f(view[0], view[3]);
            glVertex2f(0.0f, 1.0f);
#else
            glTexCoord2f(u, v);
            glVertex2f(0.1f, 0.1f);
            glTexCoord2f(1.0f, v);
            glVertex2f(.9f, 0.1f);
            glTexCoord2f(1.0f - u, 1.0f - v);
            glVertex2f(.9f, .9f);
            glTexCoord2f(u, 1.0f - v);
            glVertex2f(0.1f, .9f);
#endif
            glEnd();

            glMatrixMode(GL_PROJECTION);
            glPopMatrix();
            glMatrixMode(GL_MODELVIEW);
            glPopMatrix();

            texObj->deactivate(&oEnv,0);
        }
    }
    else
    {
        // TODO: ???
        OSG_ASSERT(false);
    }

}

OSG_END_NAMESPACE
