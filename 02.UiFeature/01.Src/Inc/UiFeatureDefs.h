
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
// ��ʼ�����໯Window
#define UM_INIT_WINDOW_BASE							(UM_UI_BASE_DEF_MSG + 3)
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define NAME_KERNEL									_T("UiFeatureKernel.dll")

#define NAME_KERNEL_DLL								("UiFeatureKernel.dll")
#define NAME_ENGINE_DLL								("UiFeatureEngine.dll")
#define NAME_CONTROL_DLL							("UiFeatureControl.dll")
#define NAME_ZIP_DLL								("UiFeatureZip.dll")

// ������Դxml�ļ�
#define RESOURCE_XML_NAME							("Resource.xml")
// Window������Դxml�ļ�
#define WINDOWS_XML_NAME							("Windows.xml")
#define CONTROLS_XML_NAME							("Controls.xml")
#define LAYOUT_XML_NAME								("Layout.xml")

// �ؼ�Ԥ��ͼ��icon�ļ��Ĵ��·�������ֻ��Builderʹ�ã��ں˲���ʹ��
#define CONTROL_IMAGE_DIR							_T("ControlsRes\\")
// ����Ƥ���ļ����д�ŵĵط�
#define SKIN_DATA_DIR								("SkinData\\")
#define SKIN_OBJECT_ID								("objid")

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
// �жϾ����Ƿ�Ϊ��
#define IS_RECT_NOT_EMPTY(CheckRect)				((((CheckRect).right-(CheckRect).left)>0)&&(((CheckRect).bottom-(CheckRect).top)>0))
// �жϾ����Ƿ�Ϊ��
#define IS_RECT_EMPTY(CheckRect)					((((CheckRect).right-(CheckRect).left)<=0)||(((CheckRect).bottom-(CheckRect).top)<=0))
// ��ʼ������Ϊ��
#define INIT_RECT(SetEmRect)						((SetEmRect).left=(SetEmRect).right=(SetEmRect).top=(SetEmRect).bottom=0)
// ���þ���
#define SET_RECT(SetRct,nL,nT,nR,nB)				(SetRct.left=nL,SetRct.top=nT,SetRct.right=nR,SetRct.bottom=nB)

// ���GDI+��Alpha�ں���Alpha�ںϽ�λ�������⣬����Ĭ�ϵ�Alpha�����ֵΪ254������255
#define MAX_ALPHA									(254)
