
#pragma once

#include <Windows.h>
#include <string>
#include <map>
#include <vector>
using namespace std;

///// 重要消息值，外界程序不能与之重复 /////////////////////////////////////////////////////////////////////
// UI内核内部自定义消息值
#define UM_UI_BASE_DEF_MSG							(WM_APP + 0x2C00)
// 需要外部对话框接受的消息：使用皮肤初始化窗口正确结束
#define UM_INIT_WINDOW_SUCCESS						(UM_UI_BASE_DEF_MSG + 1)
// 需要外部对话框接受的消息：使用皮肤初始化窗口异常
#define UM_INIT_WINDOW_ERROR						(UM_UI_BASE_DEF_MSG + 2)
// 初始化子类化Window
#define UM_INIT_WINDOW_BASE							(UM_UI_BASE_DEF_MSG + 3)
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define NAME_KERNEL									_T("UiFeatureKernel.dll")

#define NAME_KERNEL_DLL								("UiFeatureKernel.dll")
#define NAME_ENGINE_DLL								("UiFeatureEngine.dll")
#define NAME_CONTROL_DLL							("UiFeatureControl.dll")
#define NAME_ZIP_DLL								("UiFeatureZip.dll")

// 属性资源xml文件
#define RESOURCE_XML_NAME							("Resource.xml")
// Window配置资源xml文件
#define WINDOWS_XML_NAME							("Windows.xml")
#define CONTROLS_XML_NAME							("Controls.xml")
#define LAYOUT_XML_NAME								("Layout.xml")

// 控件预览图、icon文件的存放路径，这个只有Builder使用，内核并不使用
#define CONTROL_IMAGE_DIR							_T("ControlsRes\\")
// 所有皮肤文件集中存放的地方
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

// 得到矩形宽度
#define RECT_WIDTH(GetRct)							((GetRct).right-(GetRct).left)
// 得到矩形宽度
#define RECT_HEIGHT(GetRct)							((GetRct).bottom-(GetRct).top)
// 判断矩形是否不为空
#define IS_RECT_NOT_EMPTY(CheckRect)				((((CheckRect).right-(CheckRect).left)>0)&&(((CheckRect).bottom-(CheckRect).top)>0))
// 判断矩形是否为空
#define IS_RECT_EMPTY(CheckRect)					((((CheckRect).right-(CheckRect).left)<=0)||(((CheckRect).bottom-(CheckRect).top)<=0))
// 初始化矩形为空
#define INIT_RECT(SetEmRect)						((SetEmRect).left=(SetEmRect).right=(SetEmRect).top=(SetEmRect).bottom=0)
// 设置矩形
#define SET_RECT(SetRct,nL,nT,nR,nB)				(SetRct.left=nL,SetRct.top=nT,SetRct.right=nR,SetRct.bottom=nB)

// 解决GDI+的Alpha融合中Alpha融合进位误差的问题，程序默认的Alpha的最大值为254，而非255
#define MAX_ALPHA									(254)
