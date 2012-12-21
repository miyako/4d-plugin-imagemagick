/*
 *  functions_imgk.h
 *  Time
 *
 *  Created by miyako on 2012/10/30.
 *
 */

#include "4DPluginAPI.h"
#include "4DPlugin.h"

#include "IMImage2.h"

IMImage2 *_objectCreate(unsigned int *index);
IMImage2 *_objectGet(unsigned int i);
void _objectDelete(unsigned int i);

// --- Image Object
void IM_New_Object(sLONG_PTR *pResult, PackagePtr pParams);
void IM_Clear_Object(sLONG_PTR *pResult, PackagePtr pParams);
void IM_Copy(sLONG_PTR *pResult, PackagePtr pParams);
void IM_Create(sLONG_PTR *pResult, PackagePtr pParams);

// --- Image Usage
void IM_Open_File(sLONG_PTR *pResult, PackagePtr pParams);
void IM_Save_File(sLONG_PTR *pResult, PackagePtr pParams);
void IM_Get_Image_Properties(sLONG_PTR *pResult, PackagePtr pParams);
void IM_Set_Image_Properties(sLONG_PTR *pResult, PackagePtr pParams);
void IM_Modify_Image(sLONG_PTR *pResult, PackagePtr pParams);
void IM_Open_Blob(sLONG_PTR *pResult, PackagePtr pParams);
void IM_Save_Blob(sLONG_PTR *pResult, PackagePtr pParams);
void IM_Draw(sLONG_PTR *pResult, PackagePtr pParams);

// --- Utilities
void IM_Get_Last_Error(sLONG_PTR *pResult, PackagePtr pParams);
void IM_Get_Format_List(sLONG_PTR *pResult, PackagePtr pParams);
