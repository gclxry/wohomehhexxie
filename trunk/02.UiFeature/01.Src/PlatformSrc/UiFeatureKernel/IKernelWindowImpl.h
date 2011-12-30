
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
	// Builder ʹ�ú���
	// ȡ������֧�ֵĿؼ�
	virtual CONTROL_REG_MAP *BuilderRegisterControl();
	// ����һ��Builderʹ�õĿյĴ���
	virtual IWindowBase* BuilderCreateEmptyWindow();
	// ����һ��Builderʹ�õĴ��ڣ�������������
	virtual IWindowBase* BuilderCreatePropetryWindow(IPropertyWindow *pPropWnd);
	// ����Ƥ����
	virtual bool BuilderSaveSkin(char *pszSkinDir, char *pszSkinName);

//////////////////////////////////////////////////////////////////////////
	// һ���Ի����һ��Ƥ������ʹ��ָ���ĶԻ���Ƥ����Դ��ʼ���Լ�
	virtual IWindowBase* InitFeatureSkin(HWND hWnd, char *pszSkinPath, char *pszWndName);
	// һ���Ի����ͷ�Ƥ����Դ�����Kernel�ں˻���ã��ⲿ�Ի�����Ҫ����
	virtual void ReleaseFeatureSkin(HWND hWnd);

private:
	void ReleaseKernelWindow();

private:
	WINDOW_IMPL_MAP m_WndImplMap;
	// ����֧�ֵĿؼ�
	CONTROL_REG_MAP m_CtrlRegMap;
	// Builder��ʹ�õ�hwnd������ֵ
	int m_nBuilderHwnd;
	IPropertySkinManagerImpl *m_pSkinMgr;
};
