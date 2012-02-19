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

#include "OSGVCoRECSMItemHandler.h"
#include "OSGVCoREItemController.h"

#include "OSGNameAttachment.h"

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

// Documentation for this class is emited in the
// OSGVCoRECSMItemHandlerBase.cpp file.
// To modify it, please change the .fcd file (OSGPythonScript.fcd) and
// regenerate the base file.

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void CSMItemHandler::changed(ConstFieldMaskArg whichField,
                             UInt32            origin,
                             BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}


/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void CSMItemHandler::dump(      UInt32    uiIndent,
                          const BitVector bvFlags) const
{
    Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

CSMItemHandler::CSMItemHandler(void) :
     Inherited      (    ),
    _pItemController(NULL)
{
}

CSMItemHandler::CSMItemHandler(const CSMItemHandler &source) :
     Inherited      (source),
    _pItemController(NULL  )
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

CSMItemHandler::~CSMItemHandler(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Intersect                                   */

void CSMItemHandler::onCreate(const CSMItemHandler *source)
{
    Inherited::onCreate(source);

    // Don't add the prototype instances to the list
    if(GlobalSystemState != Running)
        return;

    _pItemController = ItemController::create();
    _pItemController->setCSMItemHandler(this);
}

void CSMItemHandler::onCreateAspect(const CSMItemHandler *createAspect,
                                    const CSMItemHandler *source      )
{
    Inherited::onCreateAspect(createAspect, source);

    // Don't add the prototype instances to the list
    if(GlobalSystemState != Running)
        return;

    if(createAspect != NULL)
    {
        _pItemController = createAspect->_pItemController;
    }
}

void CSMItemHandler::onDestroy(UInt32 uiContainerId)
{
    Inherited::onDestroy(uiContainerId);
}

void CSMItemHandler::onDestroyAspect(UInt32 uiContainerId,
                                     UInt32 uiAspect     )
{
    Inherited::onDestroyAspect(uiContainerId, uiAspect);

    _pItemController = NULL;
}

/*-------------------------------------------------------------------------*/
/*                                Init                                     */

void CSMItemHandler::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

void CSMItemHandler::setSyncBarrier(Barrier *pBarrier)
{
    _pItemController->setGlobalSyncBarrier(pBarrier);
}

void CSMItemHandler::syncProducer(UInt32 uiFrame)
{
    if(uiFrame != 1)
        _pItemController->syncProducer(uiFrame);
}

bool CSMItemHandler::init(void)
{
    fprintf(stderr, "CSMItemHandler::init\n");

    if(_pItemController != NULL)
    {
        _pItemController->init(_sfAspect.getValue());
    }

    return true;
}

void CSMItemHandler::frame(Time oTime, UInt32 uiFrame)
{
    if(uiFrame < 10)
    {
        fprintf(stderr, "CSMItemHandler::frame\n");
    }
}

void CSMItemHandler::shutdown(void)
{
    fprintf(stderr, "CSMItemHandler::shutdown\n");

    if(_pItemController != NULL)
    {
        _pItemController->shutdown();
    }
}

VCORE_END_NAMESPACE
