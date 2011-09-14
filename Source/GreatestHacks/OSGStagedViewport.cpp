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

    _stageNode = OSG::StageNodeRefPtr(NodeRefPtr(Node::create()));//::create();
    _stageNode.node()->addChild(_visitSubtreeNode);
}

StagedViewport::StagedViewport(const StagedViewport &source) :
    Inherited(source)
{
//    assert(false);
    _visitSubtreeNode = OSG::VisitSubTreeNodeRefPtr::create();
    _visitSubtreeNode->setSubTreeRoot(source._visitSubtreeNode->getSubTreeRoot());

    _stageNode = OSG::StageNodeRefPtr(source._stageNode.core());//::create();
//    _stageNode.setCore(source._stageNode.core());
    _stageNode.node()->addChild(_visitSubtreeNode);
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
        FNOTICE(("Stage changed.\n"));
        _stageNode.node()->setCore(getStage());
    }
    if(whichField & RootFieldMask)
    {
        FNOTICE(("root changed.\n"));
        _visitSubtreeNode->setSubTreeRoot(getRoot());
    }


    Inherited::changed(whichField, origin, details);
}

void StagedViewport::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump StagedViewport NI" << std::endl;
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
        FNOTICE((">>> NO stage\n"));
        Inherited::render(action);
    }
    else
    {
        FNOTICE((">>> With stage\n"));
    }

//#ifndef OSG_OGL_ES2
//        glDrawBuffer(GL_BACK);
//        glReadBuffer(GL_BACK);
//#endif
}

OSG_END_NAMESPACE
