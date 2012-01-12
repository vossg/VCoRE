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

#include "OSGVCoREVCRenderer.h"

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

// Documentation for this class is emitted in the
// OSGVCRendererBase.cpp file.
// To modify it, please change the .fcd file (OSGVCRenderer.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void VCRenderer::initMethod(InitPhase ePhase)
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

VCRenderer::VCRenderer(void) :
    Inherited(),
    _renderAction(NULL)
{
}

VCRenderer::VCRenderer(const VCRenderer &source) :
    Inherited(source),
    _renderAction(source._renderAction)
{
}

VCRenderer::~VCRenderer(void)
{
    _renderAction = NULL;
}

/*----------------------------- class specific ----------------------------*/

void VCRenderer::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void VCRenderer::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump VCRenderer NI" << std::endl;
}


void VCRenderer::init()
{
    _renderAction = RenderAction::create();
}

void VCRenderer::update()
{
    if(_mfWindows.empty())
        return;

    Window* win = getWindows(0);

    //std::cout << "RENDER START" << std::endl;
    if(_mfRenderTasks.empty() == false)
    {
        MFUnrecVCRenderTaskPtr::const_iterator tIt  = _mfRenderTasks.begin();
        MFUnrecVCRenderTaskPtr::const_iterator tEnd = _mfRenderTasks.end  ();

        for(; tIt != tEnd; ++tIt)
        {
            if((*tIt)->getDone() == false)
                win->addPort((*tIt)->getViewport());
        }
    }

    win->render(_renderAction);

    if(_mfRenderTasks.empty() == false)
    {
        MFUnrecVCRenderTaskPtr::const_iterator tIt  = _mfRenderTasks.begin();
        MFUnrecVCRenderTaskPtr::const_iterator tEnd = _mfRenderTasks.end  ();

        for(; tIt != tEnd; ++tIt)
        {
            if((*tIt)->getDone() == false)
            {
                win->subPortByObj((*tIt)->getViewport());
                (*tIt)->setDone(true);
            }
        }
    }
    //std::cout << "RENDER STOP" << std::endl;
}


VCORE_END_NAMESPACE
