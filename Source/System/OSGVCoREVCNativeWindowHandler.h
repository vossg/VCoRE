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

#ifndef _OSGVCOREVCNATIVEWINDOWHANDLER_H_
#define _OSGVCOREVCNATIVEWINDOWHANDLER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGVCoRESystemDef.h"
#include "OSGMemoryObject.h"
#include "OSGWindow.h"

#include "OSGVCoREVCWindowEvents.h"

#include <map>
#include <string>

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

class VCNativeWindow;

/*! \brief VCNativeWindowHandler class
 */

class OSG_VCORESYSTEM_DLLMAPPING VCNativeWindowHandler : public MemoryObject
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef MemoryObject          Inherited;
    typedef VCNativeWindowHandler Self;
    
    OSG_GEN_INTERNAL_MEMOBJPTR(VCNativeWindowHandler);

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
    
    VCNativeWindowHandler(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Parameters                                */
    /*! \{                                                                 */

    // send event utility functions
    void sendDisplayWindowEvent (void                                         );
    void sendResizeWindowEvent  (Int32                            width, 
                                 Int32                            height      );
    void sendMouseWindowEvent   (Int32                            x, 
                                 Int32                            y, 
                                 Int32                            iButton, 
                                 Int32                            iButtonState);
    void sendKeyboardWindowEvent(Int32                            x, 
                                 Int32                            y, 
                                 Int32                            iKey,
                                 VCKeyboardWindowEvent::EventType eEventType  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Main methods                               */
    /*! \{                                                                 */
    
    void setWindow(VCNativeWindow *pWin);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Exclusion                                 */
    /*! \{                                                                 */
    
    virtual Window *getOSGWindow(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    WindowUnrecPtr  _pOSGWin;
    VCNativeWindow *_pWin;

    /*---------------------------------------------------------------------*/
    /*! \name                Parameter Helpers                             */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~VCNativeWindowHandler(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    /*==========================  PRIVATE  ================================*/

  private:

    // prohibit default functions (move to 'public' if you need one)
    VCNativeWindowHandler(const VCNativeWindowHandler &source);
    void operator =(const VCNativeWindowHandler &source);

};

typedef VCNativeWindowHandler *VCNativeWindowHandlerP;

OSG_GEN_MEMOBJPTR(VCNativeWindowHandler);

VCORE_END_NAMESPACE

#endif /* _OSGVCNATIVEWINDOWHANDLER_H_ */
