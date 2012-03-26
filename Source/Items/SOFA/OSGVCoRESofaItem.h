/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2012 by the OpenSG Forum                    *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: dirk 'at' opensg.org                                             * 
 *          gerrit.voss 'at' vossg.org                                       *
 *          carsten_neumann 'at' gmx.net                                     *
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

#ifndef _OSGVCORESOFAITEM_H_
#define _OSGVCORESOFAITEM_H_
#ifdef __sgi
#pragma once
#endif

#if __GNUC__ >= 4 || __GNUC_MINOR__ >=3
//#pragma GCC diagnostic warning "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#endif

#include "OSGConfig.h"
#include "OSGVCoRESofaItemBase.h"
#include "OSGPathHandler.h"
#include "OSGCamera.h"
#include "OSGComponentTransform.h"

#include "OSGShadowStage.h"
#include "OSGChunkOverrideGroup.h"
#include "OSGSofaShadowGraph.h"


// SOFA
#include <sofa/simulation/common/Node.h>
#include <sofa/gui/PickHandler.h>

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

class App;

/*! \brief OSGTestSceneItem is the basic NodeCore for inner nodes in the tree.
    \ingroup GrpSystemNodeCoreGroupsCores
    \ingroup GrpLibOSGSystem
    \includebasedoc
 */

class OSG_VCOREITEMSOFA_DLLMAPPING SofaItem : public SofaItemBase
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

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Action Callbacks                       */
    /*! \{                                                                 */

    void postOSGLoading(void);

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

    virtual bool init      (UInt32  uiInitPhase,
                            App    *pApp       );

    virtual bool initialize(void               );

    /*! \}                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Field Access                          */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

    protected:

    typedef SofaItemBase                            Inherited;

    static  PathHandler                            _oPathHandler;
    
    ComponentTransform                            *_pTransform;
    Real32                                         _fAngle;

    // SOFA
    sofa::simulation::Node::SPtr                   _pGRoot;
    sofa::gui::PickHandler                         _oPick;

    ShadowStageUnrecPtr                            _pShadowStage;
    ChunkOverrideGroupUnrecPtr                     _pChunkOverrideGroup;
    NodeUnrecPtr                                   _pScene;

    // Shadow scene graph
    // to replace the above after testing
    sofa::component::visualmodel::OSG2_ShadowGraph _pShadowGraph;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SofaItem(void);
    SofaItem(const SofaItem &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SofaItem(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Type                                  */
    /*! \{                                                                 */

    virtual void tick(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Init                                  */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Helper                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Action Callbacks                       */
    /*! \{                                                                 */

    void           initDefaults     (void                              );
    NodeTransitPtr buildSceneGraph  (sofa::simulation::Node::SPtr pRoot);
    void           destroySofaSCN   (void                              );
    void           destroySceneGraph(void                              );

    void           printMouse       (void                              ) const;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SofaItemBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SofaItem &source);

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

typedef SofaItem *SofaItemP;

OSG_END_NAMESPACE

#include "OSGVCoRESofaItemBase.inl"
#include "OSGVCoRESofaItem.inl"

#endif /* _OSGVCORESOFAITEM_H_ */
