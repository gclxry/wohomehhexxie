
#include "StdAfx.h"
#include "IControlManagerImpl.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IControlManager.h"
#include "..\..\Inc\ICtrlBasePanel.h"


IControlManager *GetControlManager()
{
	return IControlManagerImpl::GetInstance();
}

IControlManagerImpl::IControlManagerImpl(void)
{
}

IControlManagerImpl::~IControlManagerImpl(void)
{
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��Ҫ�޸ĺ���չ�ĺ���
// ȡ������֧�ֵĿؼ�
void IControlManagerImpl::SetRegControlMap(CONTROL_REG_MAP *pCtrlMap)
{
	if (pCtrlMap == NULL)
		return;
	pCtrlMap->clear();

	// ��ӿؼ�������2����Builder����ע��ؼ�
	SetRegControl(pCtrlMap, "�����ؼ�", CTRL_NAME_BASE_PANEL, "BasePanel.png", "�Ի��򱳾������ؼ�");
}

// ����һ���ؼ�������Ϊ����1�ĺ�
ICtrlInterface* IControlManagerImpl::CreateCtrl(char *pCtrlType, char *pszObjectId)
{
	if (pCtrlType == NULL || pszObjectId == NULL)
		return NULL;

	ICtrlInterface *pRetCtrl = NULL;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// ��ӿؼ�������4������һ���ؼ�
	if (lstrcmpiA(pCtrlType, CTRL_NAME_BASE_PANEL) == NULL)
	{
		ICtrlBasePanel *pCtrl = new ICtrlBasePanel;
		if (pCtrl != NULL)
		{
			pRetCtrl = dynamic_cast<ICtrlInterface*>(pCtrl);
			if (pRetCtrl == NULL)
			{
				SAFE_DELETE(pCtrl);
			}
		}
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (pRetCtrl == NULL)
		return NULL;

	pRetCtrl->SetObjectId(pszObjectId);
	return pRetCtrl;
}

// ����һ���ؼ�
bool IControlManagerImpl::ReleaseCtrl(ICtrlInterface **ppCtrl)
{
	if (ppCtrl == NULL || *ppCtrl == NULL)
		return false;

	const char * pszObjType = (*ppCtrl)->GetObjectType();
	if (pszObjType == NULL || strlen(pszObjType) <= 0)
	{
		SAFE_DELETE(*ppCtrl);
		return true;
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// ��ӿؼ�������5������һ���ؼ�
	if (lstrcmpiA(pszObjType, CTRL_NAME_BASE_PANEL) == NULL)
	{
		ICtrlBasePanel *pPanel = dynamic_cast<ICtrlBasePanel*>(*ppCtrl);
		if (pPanel != NULL)
		{
			SAFE_DELETE(pPanel);
			*ppCtrl = NULL;
			return true;
		}
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	SAFE_DELETE(*ppCtrl);
	return true;
}
