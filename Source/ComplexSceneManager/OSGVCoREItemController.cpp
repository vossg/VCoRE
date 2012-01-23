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

#include "OSGVCoREItemController.h"
#include "OSGThreadManager.h"
#include "OSGVCoRECSMItem.h"

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

// Documentation for this class is emitted in the
// OSGCSMDrawerBase.cpp file.
// To modify it, please change the .fcd file (OSGCSMDrawer.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ItemController::ItemController(void) :
     Inherited         (     ),
    _pCSMItem          (NULL ),
    _pItemThread       (NULL ),
    _pSyncFromThread   (NULL ),
    _pLocalSyncBarrier (NULL ),
    _pGlobalSyncBarrier(NULL ),

    _uiLocalSyncCount  (2    ),
    _uiSwapCount       (0    ),
    _bParallel         (false),
    _bRun              (false)
{
    fprintf(stderr, "Construct item controller\n");
}

ItemController::ItemController(const ItemController &source) :
     Inherited         (source),
    _pCSMItem          (NULL  ),
    _pItemThread       (NULL  ),
    _pSyncFromThread   (NULL ),
    _pLocalSyncBarrier (NULL  ),
    _pGlobalSyncBarrier(NULL  ),

    _uiLocalSyncCount  (2     ),
    _uiSwapCount       (0     ),
    _bParallel         (false ),
    _bRun              (false)
{
    fprintf(stderr, "CopyConstruct item controller\n");
}

ItemController::~ItemController(void)
{
    fprintf(stderr, "Destruct item controller\n");
//    _pAction = NULL;
}

ItemController::ObjTransitPtr ItemController::create(void)
{
    return ObjTransitPtr(new ItemController());
}


void ItemController::postSync(void)
{
#if 0
    MFUnrecChildCSMWindowPtr::const_iterator wIt  = getMFWindows()->begin();
    MFUnrecChildCSMWindowPtr::const_iterator wEnd = getMFWindows()->end  ();

    for(; wIt != wEnd; ++wIt)
    {
        (*wIt)->postSync();
    }
#endif
}

/*----------------------------- class specific ----------------------------*/

void ItemController::dump(      UInt32    ,
                          const BitVector ) const
{
    SLOG << "Dump CSMDrawer NI" << std::endl;
}

void ItemController::setCSMItem(CSMItem *pCSMItem)
{
    _pCSMItem = pCSMItem;
}

void ItemController::setGlobalSyncBarrier(Barrier *pBarrier)
{
    _pGlobalSyncBarrier = pBarrier;
}

bool ItemController::init(UInt32 uiAspect)
{
    bool returnValue = true;

    _pItemThread       = ItemThread::get(NULL, false);
    _pLocalSyncBarrier = Barrier   ::get(NULL, false);

    _pSyncFromThread   = dynamic_cast<Thread *>(Thread::getCurrent());
    _uiLocalSyncCount  = 2;

    _pItemThread->setController(this);

    _pItemThread->run(uiAspect);

    _pLocalSyncBarrier->enter(_uiLocalSyncCount);

//    Thread::getCurrentChangeList()->dump();

    _pItemThread->getChangeList()->applyNoClear();

//    Thread::getCurrentChangeList()->dump();

    commitChanges();

    _pLocalSyncBarrier->enter(_uiLocalSyncCount);

    fprintf(stderr, "sync back %p %p\n",
            _pCSMItem->getItem(),
            _pCSMItem->getItem()->getRoot());

    if(_pCSMItem->getItem() != NULL && _pCSMItem->getItem()->getRoot() != NULL)
    {
        _pCSMItem->addChild(_pCSMItem->getItem()->getRoot());
    }

    return returnValue;
}

void ItemController::shutdown(void)
{
    if(_pItemThread != NULL)
    {
        _pItemThread->setRunning(false);       

        _pLocalSyncBarrier ->enter(_uiLocalSyncCount);

        Thread::join(_pItemThread);

        _pItemThread        = NULL;
        _pLocalSyncBarrier  = NULL;
        _pGlobalSyncBarrier = NULL;
        _pSyncFromThread    = NULL;
    }
}

void ItemController::syncProducer(void)
{
    _pLocalSyncBarrier->enter(_uiLocalSyncCount);

//    fprintf(stderr, "sync item\n");

    _pItemThread->getChangeList()->applyNoClear();
    commitChanges();

    _pGlobalSyncBarrier->enter();
}

void ItemController::frame(Time oTime, UInt32 uiFrame)
{
#if 0
    MFUnrecChildCSMWindowPtr::const_iterator winIt  = getMFWindows()->begin();
    MFUnrecChildCSMWindowPtr::const_iterator winEnd = getMFWindows()->end  ();

    while(winIt != winEnd)
    {
        (*winIt)->render(_pAction);
        
        ++winIt;
    }
#endif
}

void ItemController::runParallel(void)
{
    fprintf(stderr, "Item run par\n");

    _bRun = true;

    fprintf(stderr, "basic init \n");

//    _pSyncFromThread->getChangeList()->applyNoClear();
//    commitChanges();

    
    CSMItemUnrecPtr pThreadLocalItem = 
        Aspect::initializeFrom<CSMItem *>(_pCSMItem);

    commitChanges();
    Thread::getCurrentChangeList()->clear();

    fprintf(stderr, "Got local item %p\n", pThreadLocalItem.get());

    if(pThreadLocalItem != NULL)
    {
        Item *pItem = pThreadLocalItem->getItem();

        fprintf(stderr, "Has VCoreItem : %p\n",
                pItem);
        
        if(pItem != NULL)
        {
            pItem->initialize();
        }

        commitChanges();
    }

    _pLocalSyncBarrier->enter(_uiLocalSyncCount);
    _pLocalSyncBarrier->enter(_uiLocalSyncCount);

    Thread::getCurrentChangeList()->clear();

    while(_bRun == true)
    {
        pThreadLocalItem->getItem()->tick();

        commitChanges();

        _pLocalSyncBarrier ->enter(_uiLocalSyncCount);

        if(_bRun == false)
            break;

//        fprintf(stderr, "wait for sync to finish\n");

        _pGlobalSyncBarrier->enter();

        Thread::getCurrentChangeList()->clear();

//        osgSleep(100);
    }

    fprintf(stderr, "Item run par stop\n");

    pThreadLocalItem = NULL;
}

void ItemController::setRunning(bool bVal)
{
    _bRun = false;
}

void ItemController::resolveLinks(void)
{
}


/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

MPThreadType ItemThread::_type(
    "OSGItemThread",
    "OSGThread",
    static_cast<CreateThreadF>(ItemThread::create),
    NULL);

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

ItemThread *ItemThread::find(Char8 *szName)
{
    BaseThread *pThread = ThreadManager::the()->findThread(szName);

    return dynamic_cast<ItemThread *>(pThread);
}

ItemThread::ObjTransitPtr ItemThread::get(Char8 *szName, bool bGlobal) 
{
    BaseThreadTransitPtr pThread = 
        ThreadManager::the()->getThread(szName,
                                        bGlobal,
                                        "OSGItemThread");

    return dynamic_pointer_cast<ItemThread>(pThread);
}

void ItemThread::setController(ItemController *pController)
{
    _pController = pController;
}

void ItemThread::setRunning(bool bVal)
{
    _pController->setRunning(bVal);
}


BaseThread *ItemThread::create(const Char8  *szName, 
                                     UInt32  uiId, 
                                     bool    bGlobal)
{
    return new ItemThread(szName, uiId, bGlobal);
}

ItemThread::ItemThread(const Char8 *szName, UInt32 uiId, bool bGlobal) :
     Inherited  (szName, 
                 uiId,
                 bGlobal),
    _pController(NULL   )
{
}

ItemThread::~ItemThread(void)
{
}

void ItemThread::workProc(void)
{
    OSG_ASSERT(_pController != NULL);

    _pController->runParallel();
}

VCORE_END_NAMESPACE
