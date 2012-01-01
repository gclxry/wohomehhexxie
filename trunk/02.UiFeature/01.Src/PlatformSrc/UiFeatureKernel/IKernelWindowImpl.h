
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
	// ����/��һ���µ�Ƥ������
	virtual bool BD_OpenProject(char *pszSkinDir, char *pszSkinName);
	// ȡ������֧�ֵĿؼ�
	virtual CONTROL_REG_MAP *BD_GetRegisterControl();
	// ����һ��Builderʹ�õĿյĴ���
	virtual IWindowBase* BD_CreateWindowEmptyPropetry();
	// ����һ��Builderʹ�õĴ��ڣ�������������
	virtual IWindowBase* BD_CreateWindowByPropetry(IPropertyWindow *pPropWnd);
	// ����Ƥ����
	virtual bool BD_SaveProject(char *pszSkinDir, char *pszSkinName);
	// �ر�һ������
	virtual bool BD_CloseProject();

	// ����һ��Builderʹ�õĿյĿؼ�
	virtual IControlBase* BD_CreateCtrlEmptyPropetry(char *pszCtrlType);

//////////////////////////////////////////////////////////////////////////
	// һ���Ի����һ��Ƥ������ʹ��ָ���ĶԻ���Ƥ����Դ��ʼ���Լ�
	virtual IWindowBase* PG_InitFeatureSkin(HWND hWnd, char *pszSkinPath, char *pszWndName);
	// һ���Ի����ͷ�Ƥ����Դ�����Kernel�ں˻���ã��ⲿ�Ի�����Ҫ����
	virtual void PG_ReleaseFeatureSkin(HWND hWnd);

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
