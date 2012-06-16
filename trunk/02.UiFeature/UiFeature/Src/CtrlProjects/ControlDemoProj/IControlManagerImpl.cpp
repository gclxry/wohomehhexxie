
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
																		else\
																		{\
																			pRetCtrl->SetControlDllManager(this);\
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

// ɾ��һ���ؼ���ע����Ϣ
void IControlManagerImpl::DeleteRegControlInfo(CONTROL_REG* pReg)
{
	SAFE_DELETE(pReg);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��Ҫ�޸ĺ���չ�ĺ���
// ȡ������֧�ֵĿؼ�
void IControlManagerImpl::SetRegControlMap(CONTROL_REG_TLIST *pCtrlMap)
{
	if (pCtrlMap == NULL)
		return;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// ��ӿؼ�������2����Builder����ע��ؼ�
	SetRegControl(pCtrlMap, "�����ؼ���", CTRL_NAME_BASE_PANEL, "�Ի��򱳾������ؼ�");
	SetRegControl(pCtrlMap, "�����ؼ���", CTRL_NAME_BUTTON, "��ť�ؼ�");
	SetRegControl(pCtrlMap, "�����ؼ���", CTRL_NAME_STATICBOX, "�ı��ؼ�");
	SetRegControl(pCtrlMap,	"�����ؼ���", CTRL_NAME_LINK_LABLE, "���Ӱ�ť�ؼ�");
	SetRegControl(pCtrlMap,	"�����ؼ���", CTRL_NAME_CHECK_BOX, "��ѡ��");
	SetRegControl(pCtrlMap,	"�����ؼ���", CTRL_NAME_TAB_BAR, "TabBar�ؼ�");

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

// ����һ���ؼ�������Ϊ����1�ĺ�
ICtrlInterface* IControlManagerImpl::CreateCtrl(char *pCtrlType)
{
	if (pCtrlType == NULL)
		return NULL;

	ICtrlInterface *pRetCtrl = NULL;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// ��ӿؼ�������4������һ���ؼ�
	CREATE_CONTROL(CTRL_NAME_BASE_PANEL, ICtrlPanelImpl);
	CREATE_CONTROL(CTRL_NAME_BUTTON, ICtrlButtonImpl);
	CREATE_CONTROL(CTRL_NAME_STATICBOX, ICtrlStaticBoxImpl);
	CREATE_CONTROL(CTRL_NAME_LINK_LABLE, ICtrlLinkLableImpl);
	CREATE_CONTROL(CTRL_NAME_CHECK_BOX, ICtrlCheckBoxImpl);
	CREATE_CONTROL(CTRL_NAME_TAB_BAR, ICtrlTabBarImpl);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
	DELETE_CONTROL(CTRL_NAME_BASE_PANEL, ICtrlPanelImpl);
	DELETE_CONTROL(CTRL_NAME_BUTTON, ICtrlButtonImpl);
	DELETE_CONTROL(CTRL_NAME_STATICBOX, ICtrlStaticBoxImpl);
	DELETE_CONTROL(CTRL_NAME_LINK_LABLE, ICtrlLinkLableImpl);
	DELETE_CONTROL(CTRL_NAME_CHECK_BOX, ICtrlCheckBoxImpl);
	DELETE_CONTROL(CTRL_NAME_TAB_BAR, ICtrlTabBarImpl);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	return false;
}
