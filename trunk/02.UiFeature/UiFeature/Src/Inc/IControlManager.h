//////////////////////////////////////////////////////////////////////////
// ���ں˹������еĿؼ�

#pragma once
#include "IControlBase.h"
#include "ICtrlInterface.h"

class IControlManager
{
public:
	// ȡ������֧�ֵĿؼ�
	virtual void SetRegControlMap(CONTROL_REG_TLIST *pCtrlMap) = 0;
	// ����һ���ؼ�������Ϊ����1�ĺ�
	virtual ICtrlInterface* CreateCtrl(char *pCtrlType) = 0;
	// ����һ���ؼ�
	virtual bool ReleaseCtrl(ICtrlInterface **ppCtrl) = 0;
	// ɾ��һ���ؼ���ע����Ϣ
	virtual void DeleteRegControlInfo(CONTROL_REG* pReg) = 0;
};

//////////////////////////////////////////////////////////////////////////
// �ؼ��ԡ��ںˡ��Ľӿ�
IControlManager *GetControlManager();
typedef IControlManager* (*GETCONTROLMANAGER)();
