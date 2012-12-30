/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2013 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: dirk@opensg.org, gerrit.voss@vossg.org, carsten_neumann@gmx.net  *
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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 **     Do not change this file, changes should be done in the derived      **
 **     class VCRenderer
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGVCRENDERERBASE_H_
#define _OSGVCRENDERERBASE_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGVCoRERendererDef.h"

//#include "OSGBaseTypes.h"

#include "OSGVCoREItem.h" // Parent

#include "OSGWindow.h"                  // Windows type
#include "OSGVCoREVCRenderTask.h"       // RenderTasks type

#include "OSGVCoREVCRendererFields.h"

VCORE_BEGIN_NAMESPACE

OSG_IMPORT_NAMESPACE;

class VCRenderer;

//! \brief VCRenderer Base Class.

class OSG_VCORERENDERER_DLLMAPPING VCRendererBase : public Item
{
  public:

    typedef Item Inherited;
    typedef Item ParentContainer;

    typedef Inherited::TypeObject TypeObject;
    typedef TypeObject::InitPhase InitPhase;

    OSG_GEN_INTERNALPTR(VCRenderer);

    /*==========================  PUBLIC  =================================*/

  public:

    enum
    {
        WindowsFieldId = Inherited::NextFieldId,
        RenderTasksFieldId = WindowsFieldId + 1,
        NextFieldId = RenderTasksFieldId + 1
    };

    static const OSG::BitVector WindowsFieldMask =
        (TypeTraits<BitVector>::One << WindowsFieldId);
    static const OSG::BitVector RenderTasksFieldMask =
        (TypeTraits<BitVector>::One << RenderTasksFieldId);
    static const OSG::BitVector NextFieldMask =
        (TypeTraits<BitVector>::One << NextFieldId);
        
    typedef MFUnrecWindowPtr  MFWindowsType;
    typedef MFUnrecVCRenderTaskPtr MFRenderTasksType;

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static FieldContainerType &getClassType   (void);
    static UInt32              getClassTypeId (void);
    static UInt16              getClassGroupId(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                FieldContainer Get                            */
    /*! \{                                                                 */

    virtual       FieldContainerType &getType         (void);
    virtual const FieldContainerType &getType         (void) const;

    virtual       UInt32              getContainerSize(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Get                                 */
    /*! \{                                                                 */

            const MFUnrecWindowPtr    *getMFWindows        (void) const;
            const MFUnrecVCRenderTaskPtr *getMFRenderTasks    (void) const;


                  Window * getWindows        (const UInt32 index) const;

                  VCRenderTask * getRenderTasks    (const UInt32 index) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Ptr Field Set                                 */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Ptr MField Set                                */
    /*! \{                                                                 */

    void addWindow                 (Window * const value   );
    void assignWindows            (const MFUnrecWindowPtr  &value);
    void clearWindows               (void                         );
    void insertWindow         (UInt32               uiIndex,
                                             Window * const value   );
    void replaceWindow    (      UInt32         uiIndex,
                                             Window * const value   );
    void replaceWindowByObj (Window * const pOldElem,
                                             Window * const pNewElem);
    void subWindow       (UInt32               uiIndex );
    void subWindowByObj (Window * const value   );

    void addRenderTask             (VCRenderTask * const value   );
    void assignRenderTasks          (const MFUnrecVCRenderTaskPtr &value);
    void clearRenderTasks            (void                         );
    void insertIntoRenderTasks      (UInt32               uiIndex,
                                             VCRenderTask * const value   );
    void replaceInRenderTasks  (      UInt32         uiIndex,
                                             VCRenderTask * const value   );
    void replaceObjInRenderTasks (VCRenderTask * const pOldElem,
                                             VCRenderTask * const pNewElem);
    void subRenderTask   (UInt32               uiIndex );
    void removeObjFromRenderTasks(VCRenderTask * const value   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Access                              */
    /*! \{                                                                 */

    virtual SizeT  getBinSize (ConstFieldMaskArg  whichField);
    virtual void   copyToBin  (BinaryDataHandler &pMem,
                               ConstFieldMaskArg  whichField);
    virtual void   copyFromBin(BinaryDataHandler &pMem,
                               ConstFieldMaskArg  whichField);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    static  VCRendererTransitPtr  create          (void);
    static  VCRenderer           *createEmpty     (void);

    static  VCRendererTransitPtr  createLocal     (
                                               BitVector bFlags = FCLocal::All);

    static  VCRenderer            *createEmptyLocal(
                                              BitVector bFlags = FCLocal::All);

    static  VCRendererTransitPtr  createDependent  (BitVector bFlags);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Copy                                   */
    /*! \{                                                                 */

    virtual FieldContainerTransitPtr shallowCopy     (void) const;
    virtual FieldContainerTransitPtr shallowCopyLocal(
                                       BitVector bFlags = FCLocal::All) const;
    virtual FieldContainerTransitPtr shallowCopyDependent(
                                                      BitVector bFlags) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    static TypeObject _type;

    static       void   classDescInserter(TypeObject &oType);
    static const Char8 *getClassname     (void             );

    /*---------------------------------------------------------------------*/
    /*! \name                      Fields                                  */
    /*! \{                                                                 */

    MFUnrecWindowPtr  _mfWindows;
    MFUnrecVCRenderTaskPtr _mfRenderTasks;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VCRendererBase(void);
    VCRendererBase(const VCRendererBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~VCRendererBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Type                                  */
    /*! \{                                                                 */

    virtual       TypeObject &getFinalType(void);
    virtual const TypeObject &getFinalType(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     onCreate                                */
    /*! \{                                                                 */

    void onCreate(const VCRenderer *source = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Generic Field Access                      */
    /*! \{                                                                 */

    GetFieldHandlePtr  getHandleWindows         (void) const;
    EditFieldHandlePtr editHandleWindows        (void);
    GetFieldHandlePtr  getHandleRenderTasks     (void) const;
    EditFieldHandlePtr editHandleRenderTasks    (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    virtual void execSyncV(      FieldContainer    &oFrom,
                                 ConstFieldMaskArg  whichField,
                                 AspectOffsetStore &oOffsets,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo);

            void execSync (      VCRendererBase *pFrom,
                                 ConstFieldMaskArg  whichField,
                                 AspectOffsetStore &oOffsets,
                                 ConstFieldMaskArg  syncMode  ,
                           const UInt32             uiSyncInfo);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Edit                                   */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Aspect Create                            */
    /*! \{                                                                 */

#ifdef OSG_MT_CPTR_ASPECT
    virtual FieldContainer *createAspectCopy(
                                    const FieldContainer *pRefAspect) const;
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Edit                                   */
    /*! \{                                                                 */
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
    /*---------------------------------------------------------------------*/

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const VCRendererBase &source);
};

typedef VCRendererBase *VCRendererBaseP;

typedef CoredNodeRefPtr  <VCRenderer> VCRendererNodeRefPtr;
typedef CoredNodeMTRefPtr<VCRenderer> VCRendererNodeMTRefPtr;

VCORE_END_NAMESPACE

#endif /* _OSGVCRENDERERBASE_H_ */
