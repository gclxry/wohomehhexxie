
#pragma once
#include "..\..\Inc\IKernelWindow.h"
#include "IPropertySkinManagerImpl.h"

class IWindowBaseImpl;
typedef map<HWND, IWindowBaseImpl*>		WINDOW_IMPL_MAP;

class IKernelWindowImpl : public IKernelWindow
{
public:
	IKernelWindowImpl(void);
	virtual ~IKernelWindowImpl(void);

	static IKernelWindow* GetInstance();

	virtual IPropertySkinManager* GetSkinManager();

//////////////////////////////////////////////////////////////////////////
	// Builder 使用函数
	// 取得所有支持的控件
	virtual CONTROL_REG_MAP *BuilderRegisterControl();
	// 创建一个Builder使用的空的窗口
	virtual IWindowBase* BuilderCreateEmptyWindow();
	// 创建一个Builder使用的窗口，并配置上属性
	virtual IWindowBase* BuilderCreatePropetryWindow(IPropertyWindow *pPropWnd);
	// 保存皮肤包
	virtual bool BuilderSaveSkin(char *pszSkinDir, char *pszSkinName);

//////////////////////////////////////////////////////////////////////////
	// 一个对话框从一个皮肤包里使用指定的对话框皮肤资源初始化自己
	virtual IWindowBase* InitFeatureSkin(HWND hWnd, char *pszSkinPath, char *pszWndName);
	// 一个对话框释放皮肤资源，这个Kernel内核会调用，外部对话框不需要调用
	virtual void ReleaseFeatureSkin(HWND hWnd);

private:
	void ReleaseKernelWindow();

private:
	WINDOW_IMPL_MAP m_WndImplMap;
	// 所有支持的控件
	CONTROL_REG_MAP m_CtrlRegMap;
	// Builder中使用的hwnd的索引值
	int m_nBuilderHwnd;
	IPropertySkinManagerImpl *m_pSkinMgr;
};
