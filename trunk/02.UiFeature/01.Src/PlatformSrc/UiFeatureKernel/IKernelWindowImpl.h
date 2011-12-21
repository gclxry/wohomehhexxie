
#pragma once
#include "..\..\Inc\IKernelWindow.h"

class IWindowBaseImpl;
typedef map<HWND, IWindowBaseImpl*>		WINDOW_IMPL_MAP;

class IKernelWindowImpl : public IKernelWindow
{
public:
	IKernelWindowImpl(void);
	virtual ~IKernelWindowImpl(void);

	static IKernelWindow* GetInstance();

	// 一个对话框从一个皮肤包里使用指定的对话框皮肤资源初始化自己
	virtual IWindowBase* InitFeatureSkin(HWND hWnd, char *pszSkinPath, char *pszWndName);
	// 一个对话框释放皮肤资源，这个Kernel内核会调用，外部对话框不需要调用
	virtual void ReleaseFeatureSkin(HWND hWnd);

private:
	WINDOW_IMPL_MAP m_WndImplMap;
};
