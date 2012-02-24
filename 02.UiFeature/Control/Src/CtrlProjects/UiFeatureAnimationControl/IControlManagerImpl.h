
#pragma once
#include "..\..\Inc\IControlManager.h"

class IControlManagerImpl : public IControlManager
{
public:
	IControlManagerImpl(void);
	virtual ~IControlManagerImpl(void);

	static IControlManager* GetInstance();

	// ȡ������֧�ֵĿؼ�
	virtual void SetRegControlMap(CONTROL_REG_MAP *pCtrlMap);
	// ����һ���ؼ�������Ϊ����1�ĺ�
	virtual ICtrlInterface* CreateCtrl(char *pCtrlType, char *pszObjectId);
	// ����һ���ؼ�
	virtual bool ReleaseCtrl(ICtrlInterface **ppCtrl);

private:
	// ����һ��֧�ֵĿؼ��Ľڵ�
	void SetRegControl(CONTROL_REG_MAP *pCtrlMap, string strCtrlGroupName, string strCtrlName, string strControlImg, string strControlInfo);
};
