
#include "StdAfx.h"
#include "IControlManagerImpl.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IControlManager.h"
#include "ICtrlAnimationExpandImpl.h"

// ����һ���ؼ��ĺ�
#define CREATE_CONTROL(ctrl_name, ctrl_class_type)				{if (lstrcmpiA(pCtrlType, ctrl_name) == 0)\
																{\
																	ctrl_class_type *pCtrl = new ctrl_class_type;\
																	if (pCtrl != NULL)\
																	{\
																		pRetCtrl = dynamic_cast<ICtrlInterface*>(pCtrl);\
																		if (pRetCtrl == NULL)\
																		{\
																			SAFE_DELETE(pCtrl);\
																		}\
																	}\
																}}


// ����һ���ؼ��ĺ�
#define DELETE_CONTROL(ctrl_name, ctrl_class_type)				{if (lstrcmpiA(pszObjType, ctrl_name) == 0)\
																{\
																	ctrl_class_type *pPanel = dynamic_cast<ctrl_class_type*>(*ppCtrl);\
																	if (pPanel != NULL)\
																	{\
																		SAFE_DELETE(pPanel);\
																		*ppCtrl = NULL;\
																		return true;\
																	}\
																}}

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
	RegInfo.strDllName = "UiFeatureAnimationControl.dll";
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// ��ӿؼ�������2����Builder����ע��ؼ�
	SetRegControl(pCtrlMap, "�����ؼ���", CTRL_NAME_ANIMATION_EXPAND, "AnimationExpand.png", "����չ�������ؼ�");
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

// ����һ���ؼ�������Ϊ����1�ĺ�
ICtrlInterface* IControlManagerImpl::CreateCtrl(char *pCtrlType, char *pszObjectId)
{
	if (pCtrlType == NULL || pszObjectId == NULL)
		return NULL;

	ICtrlInterface *pRetCtrl = NULL;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// ��ӿؼ�������4������һ���ؼ�
	CREATE_CONTROL(CTRL_NAME_ANIMATION_EXPAND, ICtrlAnimationExpandImpl);

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
		*ppCtrl = NULL;
		return true;
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// ��ӿؼ�������5������һ���ؼ�
	DELETE_CONTROL(CTRL_NAME_ANIMATION_EXPAND, ICtrlAnimationExpand);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	return false;
}
