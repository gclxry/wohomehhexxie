
#include "StdAfx.h"
#include "IControlManagerImpl.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IControlManager.h"
#include "ICtrlAnimationExpandImpl.h"

// 创建一个控件的宏
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


// 销毁一个控件的宏
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

// 设置一个支持的控件的节点
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
// 需要修改和扩展的函数
// 取得所有支持的控件
void IControlManagerImpl::SetRegControlMap(CONTROL_REG_MAP *pCtrlMap)
{
	if (pCtrlMap == NULL)
		return;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// 添加控件，步骤2：向Builder工具注册控件
	SetRegControl(pCtrlMap, "动画控件组", CTRL_NAME_ANIMATION_EXPAND, "AnimationExpand.png", "上下展开动画控件");
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

// 创建一个控件，参数为步骤1的宏
ICtrlInterface* IControlManagerImpl::CreateCtrl(char *pCtrlType, char *pszObjectId)
{
	if (pCtrlType == NULL || pszObjectId == NULL)
		return NULL;

	ICtrlInterface *pRetCtrl = NULL;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// 添加控件，步骤4：创建一个控件
	CREATE_CONTROL(CTRL_NAME_ANIMATION_EXPAND, ICtrlAnimationExpandImpl);

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
		*ppCtrl = NULL;
		return true;
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// 添加控件，步骤5：销毁一个控件
	DELETE_CONTROL(CTRL_NAME_ANIMATION_EXPAND, ICtrlAnimationExpand);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	return false;
}
