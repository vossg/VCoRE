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

#ifndef _OSGVCOREITEMCONTROLLER_H_
#define _OSGVCOREITEMCONTROLLER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGVCoRECSMDef.h"
#include "OSGMemoryObject.h"
#include "OSGRefCountPtr.h"
#include "OSGThread.h"
#include "OSGBarrier.h"
#include "OSGTime.h"

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

class ItemThread;
class CSMItem;

OSG_GEN_MEMOBJPTR(ItemThread);

/*! \brief CSMDrawer class. See \ref
           PageContribCSMDrawer for a description.
*/

class OSG_VCORECSM_DLLMAPPING ItemController : public MemoryObject
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    OSG_GEN_INTERNAL_MEMOBJPTR(ItemController);

    typedef MemoryObject   Inherited;
    typedef ItemController Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    void setCSMItem          (CSMItem *pCSMItem);
    void setGlobalSyncBarrier(Barrier *pBarrier);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    bool init        (UInt32 uiAspect);
    void shutdown    (void           );

    void syncProducer(void           );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    void postSync(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Output                                  */
    /*! \{                                                                 */

    virtual void resolveLinks       (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    void frame(Time oTime, UInt32 uiFrame);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static ObjTransitPtr create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in CSMDrawerBase.

    CSMItem             *_pCSMItem;
    ItemThreadRefPtr     _pItemThread;

    Thread              *_pSyncFromThread;
    BarrierRefPtr        _pLocalSyncBarrier;
    Barrier             *_pGlobalSyncBarrier;

    UInt32               _uiLocalSyncCount;
    UInt32               _uiSwapCount;
    bool                 _bParallel;
    bool                 _bRun;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ItemController(void);
    ItemController(const ItemController &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ItemController(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    void runParallel        (void               );
    void setRunning         (bool   bVal        );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class ItemThread;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ItemController &source);
};

typedef ItemController *ItemControllerP;

OSG_GEN_MEMOBJPTR(ItemController);


class OSG_VCORECSM_DLLMAPPING ItemThread : public Thread
{

    /*==========================  PUBLIC  =================================*/

  public:

    OSG_GEN_INTERNAL_MEMOBJPTR(ItemThread);

    /*---------------------------------------------------------------------*/
    /*! \name                 Reference Counting                           */
    /*! \{                                                                 */

    static ObjTransitPtr  get (Char8 *szName, bool bGlobal);
    static ItemThread    *find(Char8 *szName);

    /*---------------------------------------------------------------------*/
    /*! \name                 Reference Counting                           */
    /*! \{                                                                 */

    void setController(ItemController *pController);
    void setRunning   (bool            bVal       );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef Thread        Inherited;

    static  MPThreadType    _type;
            ItemController *_pController;

    /*---------------------------------------------------------------------*/
    /*! \name                 Reference Counting                           */
    /*! \{                                                                 */

    static BaseThread *create(const Char8  *szName, 
                                    UInt32  uiId,
                                    bool    bGlobal);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
 
    ItemThread(const Char8 *szName, UInt32 uiId, bool bGlobal);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~ItemThread(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual void workProc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
   /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    ItemThread(const ItemThread &source);
    void operator =(const ItemThread &source);
};


OSG_END_NAMESPACE

#include "OSGVCoREItemController.inl"

#endif /* _OSGVCOREITEMCONTROLLER_H_ */
