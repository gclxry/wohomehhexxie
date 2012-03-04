
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
// 自动化测试消息值
#define UM_AUTO_TEST								(UM_UI_BASE_DEF_MSG + 3)
// 控件注册要取得的消息
#define UM_REG_CTRL_MSG								(UM_UI_BASE_DEF_MSG + 4)
// 控件注销要取得的消息
#define UM_UNREG_CTRL_MSG							(UM_UI_BASE_DEF_MSG + 5)

// 用于绘制动画的固定定时器ID
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

// 属性资源xml文件
// Window配置资源xml文件
#define LAYOUT_XML_NAME								"Layout.xml"
#define WINDOWS_XML_NAME							"Windows.xml"
#define CONTROLS_XML_NAME							"Controls.xml"
#define RESOURCE_XML_NAME							"Resource.xml"

// 控件预览图、icon文件的存放路径，这个只有Builder使用，内核并不使用
#define CONTROL_IMAGE_DIR							_T("ControlsRes\\")
// 所有皮肤文件集中存放的地方
#define SKIN_DATA_DIR								"SkinData\\"
#define SKIN_OBJECT_ID								"objid"
// 一个窗口或者一个控件的所有属性节点的根节点：属性组的object type name
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

// 得到矩形宽度
#define RECT_WIDTH(GetRct)							((GetRct).right-(GetRct).left)
// 得到矩形宽度
#define RECT_HEIGHT(GetRct)							((GetRct).bottom-(GetRct).top)
// 初始化矩形为空
#define INIT_RECT(SetEmRect)						((SetEmRect).left=(SetEmRect).right=(SetEmRect).top=(SetEmRect).bottom=0)
// 设置矩形
#define SET_RECT(SetRct,nL,nT,nR,nB)				(SetRct.left=nL,SetRct.top=nT,SetRct.right=nR,SetRct.bottom=nB)
// 判断矩形是否不为空
#define IS_RECT_NOT_EMPTY(CheckRect)				((RECT_WIDTH(CheckRect)>0)&&((RECT_HEIGHT(CheckRect)>0))
// 判断矩形是否为空
#define IS_RECT_EMPTY(CheckRect)					((RECT_WIDTH(CheckRect)<=0)||(RECT_HEIGHT(CheckRect)<=0))

// 解决GDI+的Alpha融合中Alpha融合进位误差的问题，程序默认的Alpha的最大值为254，而非255
#define MAX_ALPHA									(254)

// 正常光标 标准的箭头
#define UF_IDC_ARROW			(32512)
// 十字架光标
#define UF_IDC_CROSS			(32515)
// 双箭头指向西北和东南
#define UF_IDC_SIZENWSE			(32642)
// 双箭头指向东北和西南
#define UF_IDC_SIZENESW			(32643)
// 双箭头指向东西
#define UF_IDC_SIZEWE			(32644)
// 双箭头指向南北
#define UF_IDC_SIZENS			(32645)
// 四向箭头指向东、西、南、北
#define UF_IDC_SIZEALL			(32646)
// 标准的箭头和小沙漏
#define UF_IDC_APPSTARTING		(32650)
// 标准的箭头和问号
#define UF_IDC_HELP				(32651)
// 工字光标
#define UF_IDC_IBEAM			(32513)
// 禁止圈
#define UF_IDC_NO				(32648)
// 垂直箭头
#define UF_IDC_UPARROW			(32516)
// 沙漏
#define UF_IDC_WAIT				(32514)
// 手势点击
#define UF_IDC_HAND				(32649)

// 改变控件、窗口大小的位置
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
