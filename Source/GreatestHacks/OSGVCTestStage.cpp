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

#include "OSGVCTestStage.h"
#include "OSGRenderAction.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGVCTestStageBase.cpp file.
// To modify it, please change the .fcd file (OSGVCTestStage.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void VCTestStage::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            VCTestStage::getClassType(), 
            reinterpret_cast<Action::Callback>(&VCTestStage::renderEnter));

        RenderAction::registerLeaveDefault( 
            VCTestStage::getClassType(), 
            reinterpret_cast<Action::Callback>(&VCTestStage::renderLeave));
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

VCTestStage::VCTestStage(void) :
    Inherited()
{
}

VCTestStage::VCTestStage(const VCTestStage &source) :
    Inherited(source)
{
}

VCTestStage::~VCTestStage(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void VCTestStage::changed(ConstFieldMaskArg whichField, 
                          UInt32            origin,
                          BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void VCTestStage::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                       const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump VisitSubTree NI" << std::endl;
}

ActionBase::ResultE VCTestStage::renderEnter(Action *action)
{
    RenderAction *a = dynamic_cast<RenderAction *>(action);

    if(a == NULL)
        return ActionBase::Continue;

    RenderPartition   *pParentPart = a   ->getActivePartition();
    Window            *pWin        = a   ->getWindow         ();
    FrameBufferObject *pTarget     = this->getRenderTarget   ();
    Camera            *pCam        = this->getCamera         ();
    Background        *pBack       = this->getBackground     ();
    Viewport          *pView       = a   ->getViewport       ();


    if(pTarget == NULL && this->getInheritedTarget() == true)
    {
        pTarget = pParentPart->getRenderTarget();
    }
    if(!pCam)
    {
        pCam = a->getCamera();
    }
    if(!pBack)
    {
        pBack = a->getBackground();
    }

    this->pushPartition(a);

    RenderPartition   *pPart   = a->getActivePartition();

    setupPartition(pPart, pWin, pTarget, pCam, pBack, pView);

    //Inherited::addCallbacks(pPart);

    return ActionBase::Continue;
}

ActionBase::ResultE VCTestStage::renderLeave(Action *action)
{
    RenderAction *a = dynamic_cast<RenderAction *>(action);

    if(a == NULL)
        return ActionBase::Continue;

    this->popPartition(a);

    return ActionBase::Continue;
}

//void VCTestStage::initMethod(InitPhase ePhase)
//{
//    Inherited::initMethod(ePhase);
//
//    if(ePhase == TypeObject::SystemPost)
//    {
//        //RenderAction::registerEnterDefault(
//        //    VCTestStage::getClassType(), 
//        //    reinterpret_cast<Action::Callback>(&VCTestStage::renderEnter));
//
//        //RenderAction::registerLeaveDefault( 
//        //    VCTestStage::getClassType(), 
//        //    reinterpret_cast<Action::Callback>(&VCTestStage::renderLeave));
//    }
//}

void VCTestStage::setupPartition(
     RenderPartition *pPart, Window     *pWin, FrameBufferObject *pTarget,
     Camera          *pCam,  Background *pBack, Viewport *pViewport )
{
    pPart->setRenderTarget(pTarget);
    pPart->setWindow      (pWin   );

    Real32 left = pViewport->getLeft();
    Real32 right = pViewport->getRight();
    Real32 bottom = pViewport->getBottom();
    Real32 top = pViewport->getTop();

    if(pTarget != NULL)
    {
        pPart->calcViewportDimension(
            left, bottom, right, top,
            pTarget->getWidth    (),
            pTarget->getHeight   ());
    }
    else if(pWin != NULL)
    {
        pPart->calcViewportDimension(
            left, bottom, right, top,
            pWin->getWidth   (),
            pWin->getHeight  ());
    }
    else
    {
        SWARNING << "SimpleStage::setupPartition: No target or window."
            << std::endl;
    }

    if(pCam != NULL)
    {
        Matrix m, t;

        // set the projection
        pCam->getProjection          (m,
            pPart->getViewportWidth (),
            pPart->getViewportHeight());

        pCam->getProjectionTranslation(t,
            pPart->getViewportWidth (),
            pPart->getViewportHeight());

        pPart->getDrawEnv().setTileFullSize(pCam->tileGetFullSize());
        pPart->getDrawEnv().setTileRegion  (pCam->tileGetRegion  ());

        pPart->setupProjection(m, t);

        pCam->getViewing(m,
            pPart->getViewportWidth (),
            pPart->getViewportHeight());

        pPart->setupViewing(m              );

        pPart->setNear     (pCam->getNear());
        pPart->setFar      (pCam->getFar ());

        pPart->calcFrustum (               );
    }

    pPart->setBackground(pBack);
}


OSG_END_NAMESPACE
