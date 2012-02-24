//////////////////////////////////////////////////////////////////////////
// ���ں˹������еĿؼ�

#pragma once
#include "IControlBase.h"
#include "ICtrlInterface.h"
#include "Control\ICtrlPanel.h"
#include "Control\ICtrlAnimationControl.h"

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
