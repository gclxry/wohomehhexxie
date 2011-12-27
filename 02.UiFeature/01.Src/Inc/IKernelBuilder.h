
#pragma once
#include "IControlBase.h"
#include "IPropertySkinManager.h"

class IKernelBuilder
{
public:
	// ȡ������֧�ֵĿؼ�
	virtual CONTROL_REG_MAP *GetRegControlMap() = 0;
	virtual IPropertySkinManager* GetSkinManager() = 0;
};
