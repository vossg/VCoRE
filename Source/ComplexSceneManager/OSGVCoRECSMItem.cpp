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

#include "OSGVCoRECSMItem.h"
#include "OSGVCoREItemController.h"

#include "OSGNameAttachment.h"

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

// Documentation for this class is emited in the
// OSGVCoRECSMItemBase.cpp file.
// To modify it, please change the .fcd file (OSGPythonScript.fcd) and
// regenerate the base file.

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void CSMItem::changed(ConstFieldMaskArg whichField,
                      UInt32            origin,
                      BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}


/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void CSMItem::dump(      UInt32    uiIndent,
                   const BitVector bvFlags) const
{
    Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

CSMItem::CSMItem(void) :
     Inherited      (    ),
    _pItemController(NULL)
{
}

CSMItem::CSMItem(const CSMItem &source) :
     Inherited      (source),
    _pItemController(NULL  )
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

CSMItem::~CSMItem(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Intersect                                   */

void CSMItem::onCreate(const CSMItem *source)
{
    Inherited::onCreate(source);

    // Don't add the prototype instances to the list
    if(GlobalSystemState != Running)
        return;

    _pItemController = ItemController::create();
    _pItemController->setCSMItem(this);
}

void CSMItem::onCreateAspect(const CSMItem *createAspect,
                             const CSMItem *source      )
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

void CSMItem::onDestroy(UInt32 uiContainerId)
{
    Inherited::onDestroy(uiContainerId);
}

void CSMItem::onDestroyAspect(UInt32 uiContainerId,
                              UInt32 uiAspect     )
{
    Inherited::onDestroyAspect(uiContainerId, uiAspect);

    _pItemController = NULL;
}

/*-------------------------------------------------------------------------*/
/*                                Init                                     */

void CSMItem::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

void CSMItem::setSyncBarrier(Barrier *pBarrier)
{
    _pItemController->setGlobalSyncBarrier(pBarrier);
}

void CSMItem::syncProducer(void)
{
    _pItemController->syncProducer();
}

FieldContainer *CSMItem::findNamedComponent(
    const Char8 *szName) const
{
#if 0
    MFWorkerType::const_iterator wIt  = _mfWorker.begin();
    MFWorkerType::const_iterator wEnd = _mfWorker.end  ();

    for(; wIt != wEnd; ++wIt)
    {
        const Char8 *szTmpName = OSG::getName(*wIt);

        if(szTmpName != NULL && osgStringCmp(szTmpName, szName) == 0)
        {
            return *wIt;
        }

        FieldContainer *tmpVal = (*wIt)->findNamedComponent(szName);

         if(tmpVal != NULL)
             return tmpVal;
    }


    MFItemsType::const_iterator iIt  = _mfItems.begin();
    MFItemsType::const_iterator iEnd = _mfItems.end  ();


    for(; iIt != iEnd; ++iIt)
    {
        const Char8 *szTmpName = OSG::getName(*iIt);

        if(szTmpName != NULL && osgStringCmp(szTmpName, szName) == 0)
        {
            return *iIt;
        }

        FieldContainer *tmpVal = (*iIt)->findNamedComponent(szName);

         if(tmpVal != NULL)
             return tmpVal;
    }
#endif

    return NULL;
}

#if 0
void CSMItem::tick(void)
{
    MFWorkerType::const_iterator wIt  = _mfWorker.begin();
    MFWorkerType::const_iterator wEnd = _mfWorker.end  ();

    for(; wIt != wEnd; ++wIt)
    {
        (*wIt)->tick();
    }

    MFItemsType::const_iterator iIt  = _mfItems.begin();
    MFItemsType::const_iterator iEnd = _mfItems.end  ();

    for(; iIt != iEnd; ++iIt)
    {
        (*iIt)->tick();
    }
}

bool CSMItem::init(UInt32 uiInitPhase, App *pApp)
{
    fprintf(stderr, "CSMItem::init %s (%x)\n",
            getName(this),
            uiInitPhase);

    MFWorkerType::const_iterator wIt  = _mfWorker.begin();
    MFWorkerType::const_iterator wEnd = _mfWorker.end  ();

    for(; wIt != wEnd; ++wIt)
    {
        (*wIt)->init(uiInitPhase, pApp);
    }

    MFItemsType::const_iterator iIt  = _mfItems.begin();
    MFItemsType::const_iterator iEnd = _mfItems.end  ();

    for(; iIt != iEnd; ++iIt)
    {
        (*iIt)->init(uiInitPhase, pApp);
    }

    return true;
}
#endif

bool CSMItem::init(void)
{
    fprintf(stderr, "CSMItem::init\n");

    if(_pItemController != NULL)
    {
        _pItemController->init(_sfAspect.getValue());
    }

    return true;
}

void CSMItem::frame(Time oTime, UInt32 uiFrame)
{
    if(uiFrame < 10)
    {
        fprintf(stderr, "CSMItem::frame\n");
    }
}

void CSMItem::shutdown(void)
{
    fprintf(stderr, "CSMItem::shutdown\n");

    if(_pItemController != NULL)
    {
        _pItemController->shutdown();
    }
}

VCORE_END_NAMESPACE
