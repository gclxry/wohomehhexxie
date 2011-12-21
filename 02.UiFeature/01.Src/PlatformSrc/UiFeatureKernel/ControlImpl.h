
#pragma once
#include "..\..\Inc\UiFeatureControl.h"

class CControlImpl
{
public:
	CControlImpl(void);
	virtual ~CControlImpl(void);

	static CControlImpl* GetInstance();

	void SetRegControlMap(CONTROL_REG_MAP *pCtrlMap);

private:
	bool LoadDll();
	IControlManager* GetControlManager();

private:
	HMODULE m_hControlDll;
};
