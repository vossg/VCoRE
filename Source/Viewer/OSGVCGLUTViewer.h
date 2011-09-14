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

#ifndef _OSGVCGLUTVIEWER_H_
#define _OSGVCGLUTVIEWER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGVCGLUTViewerBase.h"

#include "OSGWindow.h"
#include "OSGSimpleSceneManager.h"

OSG_BEGIN_NAMESPACE

/*! \brief VCGLUTViewer class. See \ref
           PageVCoreViewerVCGLUTViewer for a description.
*/

class OSG_VCOREVIEWER_DLLMAPPING VCGLUTViewer : public VCGLUTViewerBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef VCGLUTViewerBase Inherited;
    typedef VCGLUTViewer     Self;

    virtual bool init(void);

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

    // Variables should all be in VCGLUTViewerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    VCGLUTViewer(void);
    VCGLUTViewer(const VCGLUTViewer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~VCGLUTViewer(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class VCGLUTViewerBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const VCGLUTViewer &source);


    static bool           _bGLUTInitialized;
//    static CSMGLUTWindow *_pGLUTWindow;

    Int32          _iGlutWinId;
    WindowRecPtr   _pWindow;

    static void glutKeyHandler        (UChar8 key, 
        Int32, 
        Int32       );

    static void glutReshapeHandler    (Int32 w, 
        Int32 h     );

    static void glutFrameHandler      (void           );

    static void glutMouseHandler      (Int32 iButton, 
        Int32 iState,
        Int32 x,       
        Int32 y      );

    static void glutMouseMotionHandler(Int32 x, 
        Int32 y      );

};

typedef VCGLUTViewer *VCGLUTViewerP;

OSG_END_NAMESPACE

#include "OSGVCGLUTViewerBase.inl"
#include "OSGVCGLUTViewer.inl"

#endif /* _OSGVCGLUTVIEWER_H_ */
