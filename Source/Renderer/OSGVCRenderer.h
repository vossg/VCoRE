/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

#ifndef _OSGVCRENDERER_H_
#define _OSGVCRENDERER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGVCRendererBase.h"

#include "OSGRenderAction.h"

OSG_BEGIN_NAMESPACE

/*! \brief VCRenderer class. See \ref
           PageVCoreRendererVCRenderer for a description.
*/

class OSG_VCORERENDERER_DLLMAPPING VCRenderer : public VCRendererBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef VCRendererBase Inherited;
    typedef VCRenderer     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */

    virtual void init();
    virtual void update();


    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in VCRendererBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    VCRenderer(void);
    VCRenderer(const VCRenderer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~VCRenderer(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}    */

    RenderAction* _renderAction;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class VCRendererBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const VCRenderer &source);
};

typedef VCRenderer *VCRendererP;

OSG_END_NAMESPACE

#include "OSGVCRendererBase.inl"
#include "OSGVCRenderer.inl"

#endif /* _OSGVCRENDERER_H_ */
