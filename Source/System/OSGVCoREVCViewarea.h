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

#ifndef _OSGVCOREVCVIEWAREA_H_
#define _OSGVCOREVCVIEWAREA_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGVCoREVCViewareaBase.h"
#include "OSGViewport.h"

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

class App;

/*! \brief VCViewArea is the basic NodeCore for inner nodes in the tree.
    \ingroup GrpSystemNodeCoreGroupsCores
    \ingroup GrpLibOSGSystem
    \includebasedoc
 */

class OSG_VCORESYSTEM_DLLMAPPING VCViewarea : public VCViewareaBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef std::vector<ViewportUnrecPtr> ViewportStore;
    typedef ViewportStore::iterator       ViewportStoreIt;
    typedef ViewportStore::const_iterator ViewportStoreConstIt;

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

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Action Callbacks                       */
    /*! \{                                                                 */

    ViewportStoreConstIt beginViewports(void) const;
    ViewportStoreConstIt endViewports  (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Field Access                          */
    /*! \{                                                                 */

    virtual bool init(UInt32  uiInitPhase,
                      App    *pApp       );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

    protected:

    typedef VCViewareaBase  Inherited;

    ViewportStore        _vViewports;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VCViewarea(void);
    VCViewarea(const VCViewarea &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~VCViewarea(void);

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
    friend class VCViewareaBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const VCViewarea &source);

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

typedef VCViewarea *VCViewareaP;

VCORE_END_NAMESPACE

#include "OSGVCoREVCViewareaBase.inl"
#include "OSGVCoREVCViewarea.inl"

#endif /* _OSGVCOREVCVIEWAREA_H_ */
