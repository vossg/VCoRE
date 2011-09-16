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

#ifndef _OSGVCTESTSTAGE_H_
#define _OSGVCTESTSTAGE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGVCTestStageBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief VCTestStage class. See \ref
           PageVCoreGreatestHacksVCTestStage for a description.
*/

class OSG_VCOREGREATESTHACKS_DLLMAPPING VCTestStage : public VCTestStageBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef VCTestStageBase Inherited;
    typedef VCTestStage     Self;

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
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in VCTestStageBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    VCTestStage(void);
    VCTestStage(const VCTestStage &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~VCTestStage(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Draw                                       */
    /*! \{                                                                 */

    ActionBase::ResultE renderEnter(Action *action);
    ActionBase::ResultE renderLeave(Action *action);

    void                setupPartition(RenderPartition   *pPart,
        Window            *pWin,
        FrameBufferObject *pTarget,
        Camera            *pCam,
        Background        *pBack,
        Viewport          *pViewport );



    //class FBOComplex
    //{
    //public:
    //    OSG::FrameBufferObjectUnrecPtr _fbo;
    //    OSG::TextureBufferUnrecPtr     _texBuffer;
    //    OSG::ImageUnrecPtr _texImg;
    //    OSG::TextureObjChunkUnrecPtr   _texObj;
    //    OSG::TextureEnvChunkUnrecPtr   _texEnv;
    //    //    OSG::TextureObjChunkUnrecPtr   _depthTexObj;
    //    OSG::RenderBufferUnrecPtr      _depthBuffer;

    //    FBOComplex(Int32 w, Int32 h);
    //    void resize(Int32 w, Int32 h);
    //};
    //FBOComplex _fboComplex;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class VCTestStageBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const VCTestStage &source);
};

typedef VCTestStage *VCTestStageP;

OSG_END_NAMESPACE

#include "OSGVCTestStageBase.inl"
#include "OSGVCTestStage.inl"

#endif /* _OSGVCTESTSTAGE_H_ */
