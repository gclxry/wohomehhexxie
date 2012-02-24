
#pragma once
#include "..\..\Inc\UiFeatureControl.h"

struct CONTRL_DLL_INFO 
{
	HMODULE hDll;
	IControlManager* pCtrlMgr;
	string strPath;
};

typedef vector<CONTRL_DLL_INFO>		CONTROL_DLL_VEC;

class CControlImpl
{
public:
	CControlImpl(void);
	virtual ~CControlImpl(void);

	static CControlImpl* GetInstance();

	// ȡ������֧�ֵĿؼ�
	void SetRegControlMap(CONTROL_REG_MAP *pCtrlMap);
	// ����һ���ؼ�������Ϊ����1�ĺ�
	ICtrlInterface* CreateCtrl(char *pCtrlType, char *pszObjectId);
	// ����һ���ؼ�
	bool ReleaseCtrl(ICtrlInterface **ppCtrl);

private:
	bool LoadControlDll();
	IControlManager* GetControlManager();

private:
	CONTROL_DLL_VEC m_CtrlDllVec;
};
