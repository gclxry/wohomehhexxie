
#pragma once
#include "IWindowBase.h"
#include "IControlBase.h"

class IKernelWindow
{
public:
	virtual IPropertySkinManager* GetSkinManager() = 0;

//////////////////////////////////////////////////////////////////////////
// Builder ʹ�ú���
	// ����/��һ���µ�Ƥ������
	virtual bool BD_OpenProject(char *pszSkinDir, char *pszSkinName) = 0;
	// ȡ������֧�ֵĿؼ�
	virtual CONTROL_REG_MAP *BD_GetRegisterControl() = 0;
	// ����һ��Builderʹ�õĿյĴ���
	virtual IWindowBase* BD_CreateWindowEmptyPropetry() = 0;
	// ����һ��Builderʹ�õĴ��ڣ�������������
	virtual IWindowBase* BD_CreateWindowByPropetry(IPropertyWindow *pPropWnd) = 0;
	// ����һ��Builderʹ�õĿյĿؼ�
	virtual IControlBase* BD_CreateControlEmptyPropetry(IWindowBase *pParentWnd, IControlBase *pParentCtrl, char *pszNewCtrlTypeName) = 0;
	// ����Ƥ����
	virtual bool BD_SaveProject(char *pszSkinDir, char *pszSkinName) = 0;
	// �ر�һ������
	virtual bool BD_CloseProject() = 0;

//////////////////////////////////////////////////////////////////////////
	// һ���Ի����һ��Ƥ������ʹ��ָ���ĶԻ���Ƥ����Դ��ʼ���Լ�
	// �����ͷ�Ƥ����Դ���ͷ����ڲ��Զ����
	virtual IWindowBase* PG_InitFeatureSkin(HWND hWnd, char *pszSkinPath, char *pszWndName) = 0;
	// һ���Ի����ͷ�Ƥ����Դ�����Kernel�ں˻���ã��ⲿ�Ի�����Ҫ����
	virtual void PG_ReleaseFeatureSkin(HWND hWnd) = 0;
};
