
#pragma once
#include "IWindowBase.h"

class IKernelWindow
{
public:
	virtual IPropertySkinManager* GetSkinManager() = 0;

//////////////////////////////////////////////////////////////////////////
// Builder 使用函数
	// 取得所有支持的控件
	virtual CONTROL_REG_MAP *BuilderRegisterControl() = 0;
	// 创建一个Builder使用的空的窗口
	virtual IWindowBase* BuilderCreateEmptyWindow() = 0;
	// 创建一个Builder使用的窗口，并配置上属性
	virtual IWindowBase* BuilderCreatePropetryWindow(IPropertyWindow *pPropWnd) = 0;
	// 保存皮肤包
	virtual bool BuilderSaveSkin(char *pszSkinDir, char *pszSkinName) = 0;

//////////////////////////////////////////////////////////////////////////
	// 一个对话框从一个皮肤包里使用指定的对话框皮肤资源初始化自己
	// 窗口释放皮肤资源的释放在内部自动完成
	virtual IWindowBase* InitFeatureSkin(HWND hWnd, char *pszSkinPath, char *pszWndName) = 0;
	// 一个对话框释放皮肤资源，这个Kernel内核会调用，外部对话框不需要调用
	virtual void ReleaseFeatureSkin(HWND hWnd) = 0;
};
