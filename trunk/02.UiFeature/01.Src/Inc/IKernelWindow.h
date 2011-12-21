
#pragma once
#include "IWindowBase.h"

class IKernelWindow
{
public:
	// 一个对话框从一个皮肤包里使用指定的对话框皮肤资源初始化自己
	// 窗口释放皮肤资源的释放在内部自动完成
	virtual IWindowBase* InitFeatureSkin(HWND hWnd, char *pszSkinPath, char *pszWndName) = 0;
	// 一个对话框释放皮肤资源，这个Kernel内核会调用，外部对话框不需要调用
	virtual void ReleaseFeatureSkin(HWND hWnd) = 0;
};
