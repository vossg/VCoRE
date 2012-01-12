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

#ifndef _OSGVCOREVCNATIVEGLUTWINDOWHANDLER_H_
#define _OSGVCOREVCNATIVEGLUTWINDOWHANDLER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGVCoREVCNativeWindowHandler.h"

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

class App;
class VCWindowDesc;

/*! \brief VCNativeGLUTWindow is the basic NodeCore for inner nodes in the tree.
    \ingroup GrpSystemNodeCoreGroupsCores
    \ingroup GrpLibOSGSystem
    \includebasedoc
 */

class OSG_VCORESYSTEM_DLLMAPPING VCNativeGLUTWindowHandler : 
    public VCNativeWindowHandler
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    static void setupApp(App &oApp);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Type                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Action Callbacks                       */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Field Access                          */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef VCNativeWindowHandler                 Inherited;
    typedef VCNativeGLUTWindowHandler             Self;

    typedef VCNativeWindowHandlerTransitPtr       NWinHandlerTransitPtr;
    typedef std::map<Int32, 
                     VCNativeGLUTWindowHandler *> WindowHandlerBag;

    static bool             _bGlutInitialized;
    static WindowHandlerBag _mWindowHandlerBag;

    Int32 _iWinID;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VCNativeGLUTWindowHandler(const VCWindowDesc &oDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~VCNativeGLUTWindowHandler(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Type                                  */
    /*! \{                                                                 */

    static 
      Int32                 enterEventLoop    (      void               );

    static 
      NWinHandlerTransitPtr createNativeWindow(const VCWindowDesc &oDesc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Init                                  */
    /*! \{                                                                 */

    static VCNativeGLUTWindowHandler *findWindowHandler       (Int32 iId   );
    static VCNativeGLUTWindowHandler *getWindowHandlerByIndex (Int32 iIndex);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Action Callbacks                       */
    /*! \{                                                                 */

    // glut callbacks

    static void reshape(Int32  u, 
                        Int32  v     );
    static void display(void         );
    static void idle   (void         );
    static void mouse  (Int32  button, 
                        Int32  state, 
                        Int32  x, 
                        Int32  y     );
    static void motion (Int32  x, 
                        Int32  y     );
    static void keyUp  (UChar8 key, 
                        Int32  x, 
                        Int32  y     );
    static void keyDown(UChar8 key, 
                        Int32  x, 
                        Int32  y     );


    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    // prohibit default functions (move to 'public' if you need one)
    VCNativeGLUTWindowHandler(const VCNativeGLUTWindowHandler &source);
    void operator =(const VCNativeGLUTWindowHandler &source);

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

typedef VCNativeGLUTWindowHandler *VCNativeGLUTWindowHandlerP;

VCORE_END_NAMESPACE

#include "OSGVCoREVCNativeGLUTWindowHandler.inl"

#endif /* _OSGVCOREVCNATIVEGLUTWINDOWHANDLER_H_ */
