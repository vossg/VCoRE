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

#include "OSGVCoREItem.h"

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

// Documentation for this class is emited in the
// OSGVCoREItemBase.cpp file.
// To modify it, please change the .fcd file (OSGPythonScript.fcd) and
// regenerate the base file.

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void Item::changed(ConstFieldMaskArg whichField,
                   UInt32            origin,
                   BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void Item::tick(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void Item::dump(      UInt32    uiIndent,
                const BitVector bvFlags) const
{
    Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

Item::Item(void) :
    Inherited()
{
}

Item::Item(const Item &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

Item::~Item(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Intersect                                   */

/*-------------------------------------------------------------------------*/
/*                                Init                                     */

void Item::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

FieldContainer *Item::findNamedComponent(const Char8 *szName) const
{
    return NULL;
}

bool Item::init(UInt32 uiInitPhase, VCoRE::App *pApp)
{
    fprintf(stderr, "Item::init\n");

    return true;
}

VCORE_END_NAMESPACE
