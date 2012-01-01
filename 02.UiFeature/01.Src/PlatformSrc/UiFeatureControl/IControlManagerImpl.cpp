
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

// 设置一个支持的控件的节点
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
// 需要修改和扩展的函数
// 取得所有支持的控件
void IControlManagerImpl::SetRegControlMap(CONTROL_REG_MAP *pCtrlMap)
{
	if (pCtrlMap == NULL)
		return;
	pCtrlMap->clear();

	// 添加控件，步骤2：向Builder工具注册控件
	SetRegControl(pCtrlMap, "基本控件", CTRL_NAME_BASE_PANEL, "BasePanel.png", "对话框背景、面板控件");
}

// 创建一个控件，参数为步骤1的宏
ICtrlInterface* IControlManagerImpl::CreateCtrl(char *pCtrlType, char *pszObjectId)
{
	if (pCtrlType == NULL || pszObjectId == NULL)
		return NULL;

	ICtrlInterface *pRetCtrl = NULL;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// 添加控件，步骤4：创建一个控件
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

// 销毁一个控件
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

	// 添加控件，步骤5：销毁一个控件
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
