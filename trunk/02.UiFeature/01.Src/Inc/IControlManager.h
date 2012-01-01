//////////////////////////////////////////////////////////////////////////
// ���ں˹������еĿؼ�

#pragma once
#include "IControlBase.h"
#include "ICtrlInterface.h"

// ��ӿؼ�������1����дһ���ؼ����ƺꡣע�⣬�ؼ����Ʋ�����ͬ
#define CTRL_NAME_BASE_PANEL					("Panel")

class IControlManager
{
public:
	// ȡ������֧�ֵĿؼ�
	virtual void SetRegControlMap(CONTROL_REG_MAP *pCtrlMap) = 0;
	// ����һ���ؼ�������Ϊ����1�ĺ�
	virtual ICtrlInterface* CreateCtrl(char *pCtrlType, char *pszObjectId) = 0;
	// ����һ���ؼ�
	virtual bool ReleaseCtrl(ICtrlInterface **ppCtrl) = 0;
};
