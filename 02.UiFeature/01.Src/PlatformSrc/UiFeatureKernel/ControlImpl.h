
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

	// 取得所有支持的控件
	void SetRegControlMap(CONTROL_REG_MAP *pCtrlMap);
	// 创建一个控件，参数为步骤1的宏
	ICtrlInterface* CreateCtrl(char *pCtrlType, char *pszObjectId);
	// 销毁一个控件
	bool ReleaseCtrl(ICtrlInterface **ppCtrl);

private:
	bool LoadControlDll();
	IControlManager* GetControlManager();

private:
	CONTROL_DLL_VEC m_CtrlDllVec;
};
