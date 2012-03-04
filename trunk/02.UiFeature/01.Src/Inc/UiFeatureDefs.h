
#pragma once

#include <Windows.h>
#include <string>
#include <map>
#include <vector>
using namespace std;

///// ��Ҫ��Ϣֵ������������֮�ظ� /////////////////////////////////////////////////////////////////////
// UI�ں��ڲ��Զ�����Ϣֵ
#define UM_UI_BASE_DEF_MSG							(WM_APP + 0x2C00)
// ��Ҫ�ⲿ�Ի�����ܵ���Ϣ��ʹ��Ƥ����ʼ��������ȷ����
#define UM_INIT_WINDOW_SUCCESS						(UM_UI_BASE_DEF_MSG + 1)
// ��Ҫ�ⲿ�Ի�����ܵ���Ϣ��ʹ��Ƥ����ʼ�������쳣
#define UM_INIT_WINDOW_ERROR						(UM_UI_BASE_DEF_MSG + 2)
// �Զ���������Ϣֵ
#define UM_AUTO_TEST								(UM_UI_BASE_DEF_MSG + 3)
// �ؼ�ע��Ҫȡ�õ���Ϣ
#define UM_REG_CTRL_MSG								(UM_UI_BASE_DEF_MSG + 4)
// �ؼ�ע��Ҫȡ�õ���Ϣ
#define UM_UNREG_CTRL_MSG							(UM_UI_BASE_DEF_MSG + 5)

// ���ڻ��ƶ����Ĺ̶���ʱ��ID
#define UM_DFT_ANIMATION_TIMER						(0x0000F001)
#define UM_DFT_ANIMATION_TIMER_100S					(100)
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define NAME_UIFEATURE_XML							"UiFeature.xml"
#define NAME_KERNEL_DLL								"UiFeatureKernel.dll"
#define NAME_FEATURE_RUN_TEST						"UiFeatureRun.exe"
#define NAME_UFP_TEMPLATE							"ufp.template"
#define NAME_SKIN_PROJ_EX_NAME						".ufp"
#define NAME_SKIN_FILE_EX_NAME						".ufd"

#define NAME_WINDOW_WIDTH							"@WindowWidth"
#define NAME_WINDOW_HEIGHT							"@WindowHeight"
#define NAME_SKIN_PROP_NAME_OBJ_ID					"@Object_Id"
#define NAME_SKIN_PROP_NAME_TYPE					"@Object_Type"
#define NAME_SKIN_PROP_NAME							"@Object_Name"
#define NAME_LAYOUT_TYPE							"@Layout_Type"
#define NAME_LAYOUT_WIDTH							"@Width"
#define NAME_LAYOUT_HEIGHT							"@Height"
#define NAME_LAYOUT_LEFTSPACE						"@LeftSpace"
#define NAME_LAYOUT_RIGHTSPACE						"@RightSpace"
#define NAME_LAYOUT_TOPSPACE						"@TopSpace"
#define NAME_LAYOUT_BOTTOMSPACE						"@BottomSpace"

// ������Դxml�ļ�
// Window������Դxml�ļ�
#define LAYOUT_XML_NAME								"Layout.xml"
#define WINDOWS_XML_NAME							"Windows.xml"
#define CONTROLS_XML_NAME							"Controls.xml"
#define RESOURCE_XML_NAME							"Resource.xml"

// �ؼ�Ԥ��ͼ��icon�ļ��Ĵ��·�������ֻ��Builderʹ�ã��ں˲���ʹ��
#define CONTROL_IMAGE_DIR							_T("ControlsRes\\")
// ����Ƥ���ļ����д�ŵĵط�
#define SKIN_DATA_DIR								"SkinData\\"
#define SKIN_OBJECT_ID								"objid"
// һ�����ڻ���һ���ؼ����������Խڵ�ĸ��ڵ㣺�������object type name
#define PROP_ROOT_TYPE_NAME							"Window_Or_Control_Property_Head"

#ifndef SAFE_CLOSE_HANDLE
#define SAFE_CLOSE_HANDLE(hHandle)					{if(hHandle!=NULL)::CloseHandle(hHandle);hHandle=NULL;};
#endif

#ifndef SAFE_FREE_LIBRARY
#define SAFE_FREE_LIBRARY(hHandle)					{if(hHandle!=NULL)::FreeLibrary(hHandle);hHandle=NULL;};
#endif

#ifndef IS_SAFE_HANDLE
#define IS_SAFE_HANDLE(hWnd)						((hWnd!=NULL)&&(hWnd!=INVALID_HANDLE_VALUE))
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(pMem)							{if((pMem)!=NULL){delete(pMem);(pMem) = NULL;}}
#endif

#ifndef SAFE_DELETE_LIST
#define SAFE_DELETE_LIST(pMem)						{if((pMem)!= NULL) {delete[](pMem);(pMem) = NULL;}}
#endif

#ifndef SAFE_FREE
#define SAFE_FREE(pMem)								{if(pMem!=NULL){free(pMem);(pMem)=NULL;}}
#endif

// �õ����ο��
#define RECT_WIDTH(GetRct)							((GetRct).right-(GetRct).left)
// �õ����ο��
#define RECT_HEIGHT(GetRct)							((GetRct).bottom-(GetRct).top)
// ��ʼ������Ϊ��
#define INIT_RECT(SetEmRect)						((SetEmRect).left=(SetEmRect).right=(SetEmRect).top=(SetEmRect).bottom=0)
// ���þ���
#define SET_RECT(SetRct,nL,nT,nR,nB)				(SetRct.left=nL,SetRct.top=nT,SetRct.right=nR,SetRct.bottom=nB)
// �жϾ����Ƿ�Ϊ��
#define IS_RECT_NOT_EMPTY(CheckRect)				((RECT_WIDTH(CheckRect)>0)&&((RECT_HEIGHT(CheckRect)>0))
// �жϾ����Ƿ�Ϊ��
#define IS_RECT_EMPTY(CheckRect)					((RECT_WIDTH(CheckRect)<=0)||(RECT_HEIGHT(CheckRect)<=0))

// ���GDI+��Alpha�ں���Alpha�ںϽ�λ�������⣬����Ĭ�ϵ�Alpha�����ֵΪ254������255
#define MAX_ALPHA									(254)

// ������� ��׼�ļ�ͷ
#define UF_IDC_ARROW			(32512)
// ʮ�ּܹ��
#define UF_IDC_CROSS			(32515)
// ˫��ͷָ�������Ͷ���
#define UF_IDC_SIZENWSE			(32642)
// ˫��ͷָ�򶫱�������
#define UF_IDC_SIZENESW			(32643)
// ˫��ͷָ����
#define UF_IDC_SIZEWE			(32644)
// ˫��ͷָ���ϱ�
#define UF_IDC_SIZENS			(32645)
// �����ͷָ�򶫡������ϡ���
#define UF_IDC_SIZEALL			(32646)
// ��׼�ļ�ͷ��Сɳ©
#define UF_IDC_APPSTARTING		(32650)
// ��׼�ļ�ͷ���ʺ�
#define UF_IDC_HELP				(32651)
// ���ֹ��
#define UF_IDC_IBEAM			(32513)
// ��ֹȦ
#define UF_IDC_NO				(32648)
// ��ֱ��ͷ
#define UF_IDC_UPARROW			(32516)
// ɳ©
#define UF_IDC_WAIT				(32514)
// ���Ƶ��
#define UF_IDC_HAND				(32649)

// �ı�ؼ������ڴ�С��λ��
enum SIZE_CTRL_TYPE
{
	SCT_NONE		= 0,
	SCT_LEFT_TOP,
	SCT_LEFT_MID,
	SCT_LEFT_BOTTOM,
	SCT_MID_TOP,
	SCT_MID_BOTTOM,
	SCT_RIGHT_TOP,
	SCT_RIGHT_MID,
	SCT_RIGHT_BOTTOM,
};
