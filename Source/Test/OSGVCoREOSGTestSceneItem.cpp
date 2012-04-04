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

#include "OSGVCoREOSGTestSceneItem.h"
#include "OSGNameAttachment.h"
#include "OSGOSGSceneFileType.h"
#include "OSGSceneFileHandler.h"
#include "OSGImageFileHandler.h"
#include "OSGContainerCollection.h"
#include "OSGVCoRESystemDef.h"

#include "OSGNode.h"
#include "OSGSimpleGeometry.h"

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

// Documentation for this class is emited in the
// OSGVCoREOSGTestSceneItemBase.cpp file.
// To modify it, please change the .fcd file (OSGPythonScript.fcd) and
// regenerate the base file.

PathHandler OSGTestSceneItem::_oPathHandler;

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void OSGTestSceneItem::changed(ConstFieldMaskArg whichField,
                               UInt32            origin,
                               BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(0x0000 != (whichField & RotationSpeedFieldMask))
    {
        fprintf(stderr, "new rotation speed %f\n",
                _sfRotationSpeed.getValue());
    }

    if(0x0000 != (whichField & AnimateFieldMask))
    {
        fprintf(stderr, "new animate %d\n",
                UInt32(_sfAnimate.getValue()));
    }

    if(0x0000 != (whichField & RootFieldMask))
    {
        fprintf(stderr, "new root %p\n", this->getRoot());
    }
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void OSGTestSceneItem::dump(      UInt32    uiIndent,
                            const BitVector bvFlags) const
{
    Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

OSGTestSceneItem::OSGTestSceneItem(void) :
    Inherited()
{
}

OSGTestSceneItem::OSGTestSceneItem(const OSGTestSceneItem &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

OSGTestSceneItem::~OSGTestSceneItem(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Intersect                                   */

/*-------------------------------------------------------------------------*/
/*                                Init                                     */


void OSGTestSceneItem::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
#ifdef WIN32_X
        typedef OSGSceneFileType::PostLoadingDispatcher<
                  OSGTestSceneItem> PLDOSGTestSceneItem;

        OSGSceneFileType::the().registerEndNodeCallback(
            OSGTestSceneItem::getClassType(),
            boost::bind(&PLDOSGTestSceneItem::dispatch,
                        PLDOSGTestSceneItem(), _1)); 
#endif
    }
}

void OSGTestSceneItem::postOSGLoading(FileContextAttachment * const pContext)
{
    fprintf(stderr, "OSGTestSceneItem::postOSGLoading\n");

    Inherited::postOSGLoading(pContext);

#if 0
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
#endif
}

bool OSGTestSceneItem::init(UInt32 uiInitPhase, App *pApp)
{
    fprintf(stderr, "OSGTestSceneItem::init %s (%x)\n",
            getName(this),
            uiInitPhase);

#if 0
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
#endif

    return true;
}

bool OSGTestSceneItem::initialize(void)
{
    Node *pItemRoot  = this->getRoot();

    fprintf(stderr, "OSGTestSceneItem build scene : %p\n", pItemRoot);

    if(pItemRoot != NULL)
    {
        NodeUnrecPtr                pLocalRoot = Node::create();
        ComponentTransformUnrecPtr  pTr        = ComponentTransform::create();

        pLocalRoot->setCore(pTr);

        pTransform = pTr;

        NodeUnrecPtr pScene = makeTorus(.5, 2, 16, 16);

        pLocalRoot->addChild(pScene);

        pItemRoot->addChild(pLocalRoot);
    }

    return true;
}

void OSGTestSceneItem::tick(void)
{
//    fprintf(stderr, " OSGTestSceneItem::tick\n");

    if(pTransform != NULL && _sfAnimate.getValue() == true)
    {
        Quaternion qRot;

        qRot.setValueAsAxisRad(0.f, 1.f, 0.f, fAngle);

        pTransform->setRotation(qRot);

        fAngle += 0.01 * _sfRotationSpeed.getValue();
    }
}

VCORE_END_NAMESPACE
