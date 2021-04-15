#ifndef __SCENEVIEWERDEFINED_H__
#define __SCENEVIEWERDEFINED_H__

//this is completely hokey, but for some reason the resource compiler
//ignores all of the defined include paths. 
#include /**/ <Inventor\mfc\SoMfcUserDefinedMsgs.h>

#define ID_INVENTORMENU_PICK			SOMFC_NEXTAVAILABLE_USERID + 1
#define ID_INVENTORMENU_VIEW			SOMFC_NEXTAVAILABLE_USERID + 2		
#define WM_XFORM_EDIT_GOODBYE			SOMFC_NEXTAVAILABLE_USERID + 3
#define WM_EDIT_COLOR_GOODBYE			SOMFC_NEXTAVAILABLE_USERID + 4
#define WM_MATERIAL_GOODBYE			SOMFC_NEXTAVAILABLE_USERID + 5
#define WM_LIGHT_GOODBYE			SOMFC_NEXTAVAILABLE_USERID + 6
#endif
