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

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

// Documentation for this class is emited in the
// OSGVCoREOSGSceneItemBase.cpp file.
// To modify it, please change the .fcd file (OSGPythonScript.fcd) and
// regenerate the base file.

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
        OSGSceneFileType::the().registerEndNodeCallback(
            OSGSceneItem::getClassType(),
            reinterpret_cast<OSGSceneFileType::Callback>(
                &OSGSceneItem::postOSGLoading));
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
    }

    return true;
}


VCORE_END_NAMESPACE
