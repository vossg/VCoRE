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

#ifndef _OSGVCOREVCWINDOW_H_
#define _OSGVCOREVCWINDOW_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGWindow.h"
#include "OSGRenderAction.h"
#include "OSGSimpleSceneManager.h"

#include "OSGVCoREVCWindowBase.h"
#include "OSGVCoREVCViewarea.h"
#include "OSGVCoREVCWindowEvents.h"

OSG_BEGIN_NAMESPACE

class SimpleSceneManager;
OSG_END_NAMESPACE

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

class App;

class OSG_VCORESYSTEM_DLLMAPPING VCWindowDesc
{
  public:
    
    std::string _szTitle;
    bool        _bVisible;
    bool        _bFullscreen;
    Vec2i       _vSize;
    Vec2i       _vPosition;
    bool        _bDrawCursor;
    Int32       _iSampleCount;
    bool        _bStereoBuffer;

    VCWindowDesc(void);
};

/*! \brief VCWindow is the basic NodeCore for inner nodes in the tree.
    \ingroup GrpSystemNodeCoreGroupsCores
    \ingroup GrpLibOSGSystem
    \includebasedoc
 */

class OSG_VCORESYSTEM_DLLMAPPING VCWindow : public VCWindowBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         detail);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Type                                  */
    /*! \{                                                                 */

    void sendEvent(VCWindowEvent *pEvent);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Action Callbacks                       */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */

    virtual void tick(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Field Access                          */
    /*! \{                                                                 */

    virtual bool init(UInt32  uiInitPhase,
                      App    *pApp       );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

    protected:

    typedef VCWindowBase Inherited;

    WindowUnrecPtr              _pOSGWin;
    RenderActionRefPtr          _pAction;
    SimpleSceneManagerRefPtr    _pMgr;

    // sends events to VCWindow (or whoever listens)
    VCWindowEventSource         _oWindowEventSource; 

    // receives events from VCWindow (or whoever is sending)
    VCWindowEventSink           _oWindowEventSink;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VCWindow(void);
    VCWindow(const VCWindow &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~VCWindow(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Type                                  */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Init                                  */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Action Callbacks                       */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class VCWindowBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const VCWindow &source);

    /*---------------------------------------------------------------------*/
    /*! \name                       Python Related                         */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Python Related                         */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
};

typedef VCWindow *VCWindowP;

OSG_END_NAMESPACE

#include "OSGVCoREVCWindowBase.inl"
#include "OSGVCoREVCWindow.inl"

#endif /* _OSGVCOREVCWINDOW_H_ */
