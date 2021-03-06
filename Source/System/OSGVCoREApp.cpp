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
#include "OSGSceneFileHandler.h"
#include "OSGOSGSceneFileType.h"
#include "OSGContainerCollection.h"
#include "OSGNameAttachment.h"

#include "OSGVCoREApp.h"
#include "OSGVCoREArena.h"
#include "OSGVCoRERepository.h"

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

// Documentation for this class is emited in the
// OSGVCoREAppBase.cpp file.
// To modify it, please change the .fcd file (OSGPythonScript.fcd) and
// regenerate the base file.

App::AppBag App::_sApps;

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void App::changed(ConstFieldMaskArg whichField,
                  UInt32            origin,
                  BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void App::setCreateNativeWindowFunc(const CreateWindowFunc &oFunc)
{
    _fCreateNativeWindowFunc = oFunc;
}

void App::setEventLoopFunc(const EventLoopFunc &oFunc)
{
    _fEventLoopFunc = oFunc;
}

void App::startFrom(const std::string &szAppFile)
{
    _oPathHandler.clearPathList();
    _oPathHandler.clearBaseFile();

    _oPathHandler.push_frontCurrentDir();

    std::string szAppFileResolved = 
        _oPathHandler.findFile(szAppFile.c_str());

    if(szAppFileResolved.empty() == true)
    {
        fprintf(stderr, "Could not find app file %s\n", 
                szAppFile.c_str());

        return;
    }

    _oPathHandler.setBaseFile(szAppFileResolved.c_str());

    OSG::SceneFileHandler::the()->setPathHandler(&_oPathHandler);

    FieldContainerUnrecPtr pCntRead = 
        OSG::OSGSceneFileType::the().readContainer(
            szAppFileResolved.c_str());

    ContainerCollectionUnrecPtr pCntCol = 
        dynamic_pointer_cast<ContainerCollection>(pCntRead);

    if(pCntCol != NULL)
    {
        fprintf(stderr, "Got collection with %ld containers ;)\n",
                pCntCol->getMFContainers()->size());

        Arena      *pTmpArena = NULL;
        Repository *pTmpRepo  = NULL;

        for(UInt32 i = 0; i < pCntCol->getMFContainers()->size(); ++i)
        {
            pTmpArena = 
                dynamic_cast<Arena      *>(pCntCol->getContainers(i));
            pTmpRepo  = 
                dynamic_cast<Repository *>(pCntCol->getContainers(i));

            if(pTmpArena != NULL)
            {
                fprintf(stderr, "Got arena %p\n",
                        pTmpArena);

                this->pushToArenas(pTmpArena);

                pTmpArena = NULL;
            }
            else if(pTmpRepo != NULL)
            {
                fprintf(stderr, "Got repo %p\n",
                        pTmpRepo);

                this->pushToRepositories(pTmpRepo);

                pTmpRepo = NULL;
            }
            else
            {
                fprintf(stderr, "Unknown vcore top element %p\n",
                        pCntCol->getContainers(i));
            }
        }

        pCntCol = NULL;
    }
}

bool App::init(void)
{
    fprintf(stderr, "App::init (LoadReferences)\n");

    MFArenasType::const_iterator aIt  = _mfArenas.begin();
    MFArenasType::const_iterator aEnd = _mfArenas.end  ();

    for(; aIt != aEnd; ++aIt)
    {
        (*aIt)->init(::OSG::InitPhase::LoadReferences, this);
    }

    fprintf(stderr, "App::init (ResolveReferences)\n");

    aIt  = _mfArenas.begin();

    for(; aIt != aEnd; ++aIt)
    {
        (*aIt)->init(::OSG::InitPhase::ResolveReferences, this);
    }

    return true;
}

void App::run(void)
{
    if(_fEventLoopFunc)
        _fEventLoopFunc();
}

App::NWinHandlerTransitPtr 
    App::createNativeWindowHandler(const VCWindowDesc &oDesc)
{
    NWinHandlerTransitPtr returnValue(NULL);

    if(_fCreateNativeWindowFunc)
        returnValue = _fCreateNativeWindowFunc(oDesc);

    return returnValue;
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void App::dump(      UInt32    uiIndent,
               const BitVector bvFlags) const
{
    Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

App::App(void) :
     Inherited   (),
    _oPathHandler()
{
}

App::App(const App &source) :
     Inherited   (source),
    _oPathHandler(      )
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

App::~App(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Intersect                                   */

void App::onCreate(const App *source)
{
    Inherited::onCreate(source);

    // Don't add the prototype instances to the list
    if(GlobalSystemState != Running)
        return;

    _sApps.insert(this);
}
 
void App::onDestroy(UInt32 uiContainerId)
{
    _sApps.erase(this);
}

/*-------------------------------------------------------------------------*/
/*                                Init                                     */

void App::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

void App::doTick(void)
{
    MFArenasType::const_iterator aIt  = _mfArenas.begin();
    MFArenasType::const_iterator aEnd = _mfArenas.end  ();

    for(; aIt != aEnd; ++aIt)
    {
        (*aIt)->tick();
    }
}

VCORE_END_NAMESPACE
