
#include "StdAfx.h"
#include "IControlManagerImpl.h"
#include "..\..\Inc\UiFeatureDefs.h"


IControlManager *GetControlManager()
{
	return IControlManagerImpl::GetInstance();
}

IControlManagerImpl::IControlManagerImpl(void)
{
}

IControlManagerImpl::~IControlManagerImpl(void)
{
	int i = 0;
	i++;
}

IControlManager* IControlManagerImpl::GetInstance()
{
	static IControlManagerImpl _ControlManagerInstance;
	return &_ControlManagerInstance;
}

// ����һ��֧�ֵĿؼ��Ľڵ�
void IControlManagerImpl::SetRegControl(CONTROL_REG_MAP *pCtrlMap, string strCtrlGroupName, string strCtrlName, string strControlImg, string strControlInfo)
{
	if (pCtrlMap == NULL)
		return;

	CONTROL_REG RegInfo;

	RegInfo.strControlImg = strControlImg;
	RegInfo.strCtrlGroupName = strCtrlGroupName;
	RegInfo.strCtrlName = strCtrlName;
	RegInfo.strDllName = NAME_CONTROL_DLL;
	RegInfo.strControlInfo = strControlInfo;

	pCtrlMap->insert(pair<string, CONTROL_REG>(RegInfo.strCtrlName, RegInfo));
}

//////////////////////////////////////////////////////////////////////////
// ��Ҫ�޸ĺ���չ�ĺ���
// ȡ������֧�ֵĿؼ�
void IControlManagerImpl::SetRegControlMap(CONTROL_REG_MAP *pCtrlMap)
{
	if (pCtrlMap == NULL)
		return;

	pCtrlMap->clear();

	// ע��һ���ؼ�
	SetRegControl(pCtrlMap, "�����ؼ�", "Button", "Ctrl (1).png", "������ť�ؼ�");
	SetRegControl(pCtrlMap, "�����ؼ�", "CheckBox", "Ctrl (2).png", "���� CheckBox �ؼ�");
	SetRegControl(pCtrlMap, "��Ŀ��ؼ�", "StaticBox", "Ctrl (3).png", "������̬�ı��ؼ���");
	SetRegControl(pCtrlMap, "��Ŀ��ؼ�", "Link", "Ctrl (4).png", "���������ӿؼ�");
	// ע��һ���ؼ�
}
