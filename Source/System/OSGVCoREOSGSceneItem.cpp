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

#include "OSGVCoREOSGSceneItem.h"
#include "OSGNameAttachment.h"
#include "OSGOSGSceneFileType.h"
#include "OSGSceneFileHandler.h"
#include "OSGImageFileHandler.h"
#include "OSGContainerCollection.h"

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

// Documentation for this class is emited in the
// OSGVCoREOSGSceneItemBase.cpp file.
// To modify it, please change the .fcd file (OSGPythonScript.fcd) and
// regenerate the base file.

PathHandler OSGSceneItem::_oPathHandler;

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void OSGSceneItem::changed(ConstFieldMaskArg whichField,
                           UInt32            origin,
                           BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void OSGSceneItem::dump(      UInt32    uiIndent,
                        const BitVector bvFlags) const
{
    Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

OSGSceneItem::OSGSceneItem(void) :
    Inherited()
{
}

OSGSceneItem::OSGSceneItem(const OSGSceneItem &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

OSGSceneItem::~OSGSceneItem(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Intersect                                   */

/*-------------------------------------------------------------------------*/
/*                                Init                                     */


void OSGSceneItem::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
#ifdef WIN32
        typedef OSGSceneFileType::PostLoadingDispatcher<
                  OSGSceneItem> PLDOSGSceneItem;

        OSGSceneFileType::the().registerEndNodeCallback(
            OSGSceneItem::getClassType(),
            boost::bind(&PLDOSGSceneItem::dispatch,
                        PLDOSGSceneItem(), _1)); 
#else
        OSGSceneFileType::the().registerEndNodeCallback(
            OSGSceneItem::getClassType(),
            reinterpret_cast<OSGSceneFileType::Callback>(
                &OSGSceneItem::postOSGLoading));
#endif
    }
}

void OSGSceneItem::postOSGLoading(void)
{
    fprintf(stderr, "OSGSceneItem::postOSGLoading\n");

    UInt32 i = 0;

    for(; i < _mfUrl.size(); ++i)
    {
        std::string szFilenameResolved = 
            SceneFileHandler::the()->getPathHandler()->findFile(
                _mfUrl[i].c_str());

        fprintf(stderr, "got %s -> %s\n",
                _mfUrl[i].c_str(),
                szFilenameResolved.c_str());

        if(szFilenameResolved.empty() == false)
        {
            setMatchedUrl(szFilenameResolved);

            break;
        }
    }


    for(; i < _mfGlobalUrl.size(); ++i)
    {
        std::string szFilenameResolved = 
            SceneFileHandler::the()->getPathHandler()->findFile(
                _mfGlobalUrl[i].c_str());

        fprintf(stderr, "got %s -> %s\n",
                _mfGlobalUrl[i].c_str(),
                szFilenameResolved.c_str());

        if(szFilenameResolved.empty() == false)
        {
            setMatchedGlobalUrl(szFilenameResolved);

            break;
        }
    }
}

bool OSGSceneItem::init(UInt32 uiInitPhase, App *pApp)
{
    fprintf(stderr, "OSGSceneItem::init %s (%x)\n",
            getName(this),
            uiInitPhase);

    if(0x0000 != (uiInitPhase & InitPhase::LoadReferences))
    {
        if(_sfMatchedUrl.getValue().empty() == false)
        {
            fprintf(stderr, "Loading %s\n",
                    _sfMatchedUrl.getValue().c_str());
            
            NodeUnrecPtr pRoot = SceneFileHandler::the()->read(
                _sfMatchedUrl.getValue().c_str(),
                NULL,
                NULL,
                false);
            
            fprintf(stderr, "got %p\n", pRoot.get());
            
            if(pRoot != NULL)
            {
                setRoot(pRoot);
            }
            else
            {
                fprintf(stderr, "  failed\n");
            }
        }


        if(_sfMatchedGlobalUrl.getValue().empty() == false)
        {
            fprintf(stderr, "Loading global %s\n",
                    _sfMatchedGlobalUrl.getValue().c_str());
            
            FieldContainerUnrecPtr pRes(NULL);

            _oPathHandler.pushState();

            _oPathHandler.setBaseFile(_sfMatchedGlobalUrl.getValue().c_str());

            ImageFileHandler::the()->setPathHandler(&_oPathHandler);

            fprintf(stderr, "loading osg file %s ...\n",
                    _sfMatchedGlobalUrl.getValue().c_str());

            pRes = OSG::OSGSceneFileType::the().readContainer(
                _sfMatchedGlobalUrl.getValue().c_str(),
                NULL);

            ImageFileHandler::the()->setPathHandler(NULL);

            _oPathHandler.popState();
            
            fprintf(stderr, "got global %p\n", pRes.get());
            
            if(pRes != NULL)
            {
                ContainerCollectionUnrecPtr pColl = 
                    dynamic_pointer_cast<ContainerCollection>(pRes);

                if(pColl != NULL)
                {
                    MFUnrecFieldContainerPtr::const_iterator fIt  = 
                        pColl->getMFContainers()->begin();

                    MFUnrecFieldContainerPtr::const_iterator fEnd = 
                        pColl->getMFContainers()->end();

                    while(fIt != fEnd)
                    {
                        this->pushToGlobals(*fIt);
                        ++fIt;
                    }   
                }
            }
            else
            {
                fprintf(stderr, "  failed\n");
            }

            fprintf(stderr, "got %ld globals\n",
                    _mfGlobals.size());

            if(_sfActiveCamera.getValue().empty() == false)
            {
                FieldContainer *pCnt = findNamedComponent(
                    _sfActiveCamera.getValue().c_str());

                Camera *pCam = dynamic_cast<Camera *>(pCnt);

                fprintf(stderr, "found camera %p\n",
                        pCam);

                setCamera(pCam);
            }
        }
    }

    return true;
}


VCORE_END_NAMESPACE
