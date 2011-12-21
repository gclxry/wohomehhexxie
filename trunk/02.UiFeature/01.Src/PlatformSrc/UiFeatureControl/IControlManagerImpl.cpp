
#include "StdAfx.h"
#include "IControlManagerImpl.h"
#include "..\..\Inc\UiFeatureDefs.h"


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
void IControlManagerImpl::SetRegControl(CONTROL_REG_MAP *pCtrlMap, string strCtrlGroupName, string strCtrlName, string strControlImg)
{
	if (pCtrlMap == NULL)
		return;

	CONTROL_REG *pRegInfo = new CONTROL_REG;
	if (pRegInfo == NULL)
		return;

	pRegInfo->strControlImg = strControlImg;
	pRegInfo->strCtrlGroupName = strCtrlGroupName;
	pRegInfo->strCtrlName = strCtrlName;
	pRegInfo->strDllName = NAME_CONTROL_DLL;

	pCtrlMap->insert(pair<string, CONTROL_REG*>(pRegInfo->strCtrlName, pRegInfo));
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
	SetRegControl(pCtrlMap, "�����ؼ�", "Button", "Ctrl (1).png");
	SetRegControl(pCtrlMap, "�����ؼ�", "CheckBox", "Ctrl (2).png");
	SetRegControl(pCtrlMap, "��Ŀ��ؼ�", "StaticBox", "Ctrl (3).png");
	SetRegControl(pCtrlMap, "��Ŀ��ؼ�", "Link", "Ctrl (4).png");
	// ע��һ���ؼ�
}
