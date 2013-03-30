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

#include "OSGVCoREWorker.h"
#include "OSGVCoREItem.h"

#include "OSGNameAttachment.h"

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

// Documentation for this class is emited in the
// OSGVCoREWorkerBase.cpp file.
// To modify it, please change the .fcd file (OSGPythonScript.fcd) and
// regenerate the base file.

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void Worker::changed(ConstFieldMaskArg whichField,
                     UInt32            origin,
                          BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}


/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void Worker::dump(      UInt32    uiIndent,
                  const BitVector bvFlags) const
{
    Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

Worker::Worker(void) :
    Inherited()
{
}

Worker::Worker(const Worker &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

Worker::~Worker(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Intersect                                   */

void Worker::tick(void)
{
    MFItemsType::const_iterator iIt  = _mfItems.begin();
    MFItemsType::const_iterator iEnd = _mfItems.end  ();

    for(; iIt != iEnd; ++iIt)
    {
        (*iIt)->tick();
    }
}

/*-------------------------------------------------------------------------*/
/*                                Init                                     */

void Worker::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

bool Worker::init(UInt32 uiInitPhase, App *pApp)
{
    fprintf(stderr, "Worker::init %s (%x)\n", 
            getName(this),
            uiInitPhase);

    MFItemsType::const_iterator iIt  = _mfItems.begin();
    MFItemsType::const_iterator iEnd = _mfItems.end  ();

    for(; iIt != iEnd; ++iIt)
    {
        (*iIt)->init(uiInitPhase, pApp);
    }

    return true;
}

VCORE_END_NAMESPACE
