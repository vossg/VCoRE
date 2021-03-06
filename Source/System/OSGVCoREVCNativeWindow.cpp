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

#include "OSGVCoREVCNativeWindow.h"
#include "OSGNameAttachment.h"
#include "OSGVCoREApp.h"

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

// Documentation for this class is emited in the
// OSGVCoREVCNativeWindowBase.cpp file.
// To modify it, please change the .fcd file (OSGPythonScript.fcd) and
// regenerate the base file.

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void VCNativeWindow::changed(ConstFieldMaskArg whichField,
                             UInt32            origin,
                             BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void VCNativeWindow::dump(      UInt32    uiIndent,
                          const BitVector bvFlags) const
{
    Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VCNativeWindow::VCNativeWindow(void) :
     Inherited         (    ),
    _pWinHandler       (NULL)
{
}

VCNativeWindow::VCNativeWindow(const VCNativeWindow &source) :
     Inherited         (source),
    _pWinHandler       (NULL  )
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VCNativeWindow::~VCNativeWindow(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Intersect                                   */

void VCNativeWindow::resolveLinks(void)
{
    Inherited::resolveLinks();

    _pWinHandler = NULL;
}

/*-------------------------------------------------------------------------*/
/*                                Init                                     */

void VCNativeWindow::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

bool VCNativeWindow::init(UInt32 uiInitPhase, App *pApp)
{
    fprintf(stderr, "VCNativeWindow::init %s (%d)\n", 
            getName(this), uiInitPhase);

    if(0x0000 != (uiInitPhase & ::OSG::InitPhase::LoadReferences))
    {
        VCWindowDesc oWinDesc;

        oWinDesc._szTitle  = "VCoRE App";
        oWinDesc._vSize    = Vec2i(512, 512);
        oWinDesc._bVisible = true;

        _pWinHandler = pApp->createNativeWindowHandler(oWinDesc);

        fprintf(stderr, "got window handler %p\n",
                _pWinHandler.get());

        if(_pWinHandler != NULL)
            _pWinHandler->setWindow(this);

        _pOSGWin = _pWinHandler->getOSGWindow();

        _pOSGWin->init();
    }

    Inherited::init(uiInitPhase, pApp);

    return true;
}

VCORE_END_NAMESPACE
