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

#include "OSGVCoREViewarea.h"
#include "OSGNameAttachment.h"
#include "OSGFieldContainerUtils.h"

#include "OSGVCoREApp.h"

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

// Documentation for this class is emited in the
// OSGVCoREViewareaBase.cpp file.
// To modify it, please change the .fcd file (OSGPythonScript.fcd) and
// regenerate the base file.

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void Viewarea::changed(ConstFieldMaskArg whichField,
                       UInt32            origin,
                       BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void Viewarea::dump(      UInt32    uiIndent,
                    const BitVector bvFlags) const
{
    Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

Viewarea::Viewarea(void) :
    Inherited()
{
}

Viewarea::Viewarea(const Viewarea &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

Viewarea::~Viewarea(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Intersect                                   */

/*-------------------------------------------------------------------------*/
/*                                Init                                     */

void Viewarea::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

bool Viewarea::init(UInt32  uiInitPhase,
                    App    *pApp       )
{
    fprintf(stderr, "Viewarea::init %s (%d)\n", 
            getName(this), uiInitPhase);

    if(0x0000 != (uiInitPhase & InitPhase::ResolveReferences))
    {
        if(_sfRendererRef.getValue().empty() == false)
        {
            FieldContainer *pFC = 
                resolveFieldPath(_sfRendererRef.getValue().c_str(), 
                                 boost::bind(&App::findNamedComponent,
                                             pApp,
                                             _1));

            RendererItem *pRenderer = 
                dynamic_cast<RendererItem *>(pFC);

            fprintf(stderr, "resolved renderer (%s) %p | %p\n",
                    _sfRendererRef.getValue().c_str(),
                    pRenderer, pFC);
         
            if(pFC != NULL)
            {
                fprintf(stderr, "got %s\n",
                        pFC->getType().getCName());
            }
   
            if(pRenderer != NULL)
                setRenderer(pRenderer);
        }

        if(_sfRootRef.getValue().empty() == false)
        {
            FieldContainer *pFC = 
                resolveFieldPath(_sfRootRef.getValue().c_str(), 
                                 boost::bind(&App::findNamedComponent,
                                             pApp,
                                             _1));

            Node *pNode = dynamic_cast<Node *>(pFC);

            fprintf(stderr, "resolved root (%s) %p | %p\n",
                    _sfRootRef.getValue().c_str(),
                    pNode, pFC);

            if(pFC != NULL)
            {
                fprintf(stderr, "got %s\n",
                        pFC->getType().getCName());
            }

            if(pNode != NULL)
                setRoot(pNode);
        }
    }

    return true;
}


VCORE_END_NAMESPACE
