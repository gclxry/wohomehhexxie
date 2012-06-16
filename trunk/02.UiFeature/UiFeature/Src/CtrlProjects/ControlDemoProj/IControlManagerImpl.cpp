
#include "StdAfx.h"
#include "IControlManagerImpl.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IControlManager.h"
#include "IControlManagerImpl.h"
#include "ICtrlPanelImpl.h"
#include "ICtrlButtonImpl.h"
#include "ICtrlStaticBoxImpl.h"
#include "ICtrlLinkLableImpl.h"
#include "ICtrlCheckBoxImpl.h"
#include "ICtrlTabBarImpl.h"

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
																		else\
																		{\
																			pRetCtrl->SetControlDllManager(this);\
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
void IControlManagerImpl::SetRegControl(CONTROL_REG_TLIST *pCtrlMap, string strCtrlGroupName, string strCtrlName, string strControlInfo)
{
	if (pCtrlMap == NULL)
		return;

	CONTROL_REG* pRegInfo = new CONTROL_REG;
	if (pRegInfo == NULL)
		return;

	memset(pRegInfo, 0, sizeof(CONTROL_REG));

	pRegInfo->pCtrlMgr = this;
	sprintf_s(pRegInfo->strCtrlGroupName, MAX_PATH, "%s", strCtrlGroupName.c_str());
	sprintf_s(pRegInfo->strCtrlName, MAX_PATH, "%s", strCtrlName.c_str());
	sprintf_s(pRegInfo->strDllName, MAX_PATH, "%s", "ControlDemoProj.dll");
	sprintf_s(pRegInfo->strControlInfo, MAX_PATH, "%s", strControlInfo.c_str());

	pCtrlMap->PushBackObj(pRegInfo);
}

// 删除一个控件的注册信息
void IControlManagerImpl::DeleteRegControlInfo(CONTROL_REG* pReg)
{
	SAFE_DELETE(pReg);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 需要修改和扩展的函数
// 取得所有支持的控件
void IControlManagerImpl::SetRegControlMap(CONTROL_REG_TLIST *pCtrlMap)
{
	if (pCtrlMap == NULL)
		return;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// 添加控件，步骤2：向Builder工具注册控件
	SetRegControl(pCtrlMap, "基本控件组", CTRL_NAME_BASE_PANEL, "对话框背景、面板控件");
	SetRegControl(pCtrlMap, "基本控件组", CTRL_NAME_BUTTON, "按钮控件");
	SetRegControl(pCtrlMap, "基本控件组", CTRL_NAME_STATICBOX, "文本控件");
	SetRegControl(pCtrlMap,	"基本控件组", CTRL_NAME_LINK_LABLE, "链接按钮控件");
	SetRegControl(pCtrlMap,	"基本控件组", CTRL_NAME_CHECK_BOX, "多选框");
	SetRegControl(pCtrlMap,	"基本控件组", CTRL_NAME_TAB_BAR, "TabBar控件");

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

// 创建一个控件，参数为步骤1的宏
ICtrlInterface* IControlManagerImpl::CreateCtrl(char *pCtrlType)
{
	if (pCtrlType == NULL)
		return NULL;

	ICtrlInterface *pRetCtrl = NULL;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// 添加控件，步骤4：创建一个控件
	CREATE_CONTROL(CTRL_NAME_BASE_PANEL, ICtrlPanelImpl);
	CREATE_CONTROL(CTRL_NAME_BUTTON, ICtrlButtonImpl);
	CREATE_CONTROL(CTRL_NAME_STATICBOX, ICtrlStaticBoxImpl);
	CREATE_CONTROL(CTRL_NAME_LINK_LABLE, ICtrlLinkLableImpl);
	CREATE_CONTROL(CTRL_NAME_CHECK_BOX, ICtrlCheckBoxImpl);
	CREATE_CONTROL(CTRL_NAME_TAB_BAR, ICtrlTabBarImpl);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
	DELETE_CONTROL(CTRL_NAME_BASE_PANEL, ICtrlPanelImpl);
	DELETE_CONTROL(CTRL_NAME_BUTTON, ICtrlButtonImpl);
	DELETE_CONTROL(CTRL_NAME_STATICBOX, ICtrlStaticBoxImpl);
	DELETE_CONTROL(CTRL_NAME_LINK_LABLE, ICtrlLinkLableImpl);
	DELETE_CONTROL(CTRL_NAME_CHECK_BOX, ICtrlCheckBoxImpl);
	DELETE_CONTROL(CTRL_NAME_TAB_BAR, ICtrlTabBarImpl);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	return false;
}
