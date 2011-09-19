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

#include "OSGVCoreApp.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emited in the
// OSGVCoreAppBase.cpp file.
// To modify it, please change the .fcd file (OSGPythonScript.fcd) and
// regenerate the base file.

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void VCoreApp::changed(ConstFieldMaskArg whichField,
                       UInt32            origin,
                       BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void VCoreApp::startFrom(const std::string &szAppFile)
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

        VCoreArena      *pTmpArena = NULL;
        VCoreRepository *pTmpRepo  = NULL;

        for(UInt32 i = 0; i < pCntCol->getMFContainers()->size(); ++i)
        {
            pTmpArena = 
                dynamic_cast<VCoreArena      *>(pCntCol->getContainers(i));
            pTmpRepo  = 
                dynamic_cast<VCoreRepository *>(pCntCol->getContainers(i));

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

void VCoreApp::run(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void VCoreApp::dump(      UInt32    uiIndent,
                    const BitVector bvFlags) const
{
    Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VCoreApp::VCoreApp(void) :
     Inherited   (),
    _oPathHandler()
{
}

VCoreApp::VCoreApp(const VCoreApp &source) :
     Inherited   (source),
    _oPathHandler(      )
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VCoreApp::~VCoreApp(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Intersect                                   */

/*-------------------------------------------------------------------------*/
/*                                Init                                     */

void VCoreApp::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

OSG_END_NAMESPACE
