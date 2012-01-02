
#pragma once
#include "IWindowBase.h"
#include "IControlBase.h"

class IKernelWindow
{
public:
	virtual IPropertySkinManager* GetSkinManager() = 0;

//////////////////////////////////////////////////////////////////////////
// Builder 使用函数
	// 创建/打开一个新的皮肤工程
	virtual bool BD_OpenProject(char *pszSkinDir, char *pszSkinName) = 0;
	// 取得所有支持的控件
	virtual CONTROL_REG_MAP *BD_GetRegisterControl() = 0;
	// 创建一个Builder使用的空的窗口
	virtual IWindowBase* BD_CreateWindowEmptyPropetry() = 0;
	// 创建一个Builder使用的窗口，并配置上属性
	virtual IWindowBase* BD_CreateWindowByPropetry(IPropertyWindow *pPropWnd) = 0;
	// 创建一个Builder使用的空的控件
	virtual IControlBase* BD_CreateControlEmptyPropetry(IWindowBase *pParentWnd, IControlBase *pParentCtrl, char *pszNewCtrlTypeName) = 0;
	// 保存皮肤包
	virtual bool BD_SaveProject(char *pszSkinDir, char *pszSkinName) = 0;
	// 关闭一个工程
	virtual bool BD_CloseProject() = 0;

//////////////////////////////////////////////////////////////////////////
	// 一个对话框从一个皮肤包里使用指定的对话框皮肤资源初始化自己
	// 窗口释放皮肤资源的释放在内部自动完成
	virtual IWindowBase* PG_InitFeatureSkin(HWND hWnd, char *pszSkinPath, char *pszWndName) = 0;
	// 一个对话框释放皮肤资源，这个Kernel内核会调用，外部对话框不需要调用
	virtual void PG_ReleaseFeatureSkin(HWND hWnd) = 0;
};
