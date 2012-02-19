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
#include "OSGVCoRECSMItemHandler.h"

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
    _pCSMItemHandler   (NULL ),
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
    _pCSMItemHandler   (NULL  ),
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
}

ItemController::ObjTransitPtr ItemController::create(void)
{
    return ObjTransitPtr(new ItemController());
}


/*----------------------------- class specific ----------------------------*/

void ItemController::dump(      UInt32    ,
                          const BitVector ) const
{
    SLOG << "Dump CSMDrawer NI" << std::endl;
}

void ItemController::setCSMItemHandler(CSMItemHandler *pCSMItemHandler)
{
    _pCSMItemHandler = pCSMItemHandler;
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


    // Sync back init changes

    _pLocalSyncBarrier->enter(_uiLocalSyncCount);

    _pItemThread->getChangeList()->applyNoClear();

    commitChanges();

    _pLocalSyncBarrier->enter(_uiLocalSyncCount);

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

void ItemController::syncProducer(UInt32 uiFrame)
{
    _pLocalSyncBarrier->enter(_uiLocalSyncCount);

//    fprintf(stderr, "sync item\n");

    _pItemThread->getChangeList()->applyNoClear();

    _pLocalSyncBarrier->enter(_uiLocalSyncCount);

    commitChanges();

    _pGlobalSyncBarrier->enter();
}

void ItemController::runParallel(void)
{
    fprintf(stderr, "Item run par\n");

    _bRun = true;

    fprintf(stderr, "basic init \n");

    CSMItemHandlerUnrecPtr pThreadLocalItem = 
        Aspect::initializeFrom<CSMItemHandler *>(_pCSMItemHandler);

    commitChanges();
    Thread::getCurrentChangeList()->clear();

    if(pThreadLocalItem != NULL)
    {
        OSGBaseItem *pItem = pThreadLocalItem->getItem();
     
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

        _pLocalSyncBarrier ->enter(_uiLocalSyncCount);

        if(_bRun == false)
            break;

        if(_pCSMItemHandler != NULL)
        {
            Item *pItem = _pCSMItemHandler->getItem();

            Aspect::syncContainersFrom(pItem);
        }

        _pGlobalSyncBarrier->enter();

        commitChanges();

        Thread::getCurrentChangeList()->clear();

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
