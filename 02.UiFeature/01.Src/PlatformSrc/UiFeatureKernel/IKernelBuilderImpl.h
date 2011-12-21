
#pragma once
#include "..\..\Inc\IKernelBuilder.h"
#include "..\..\Inc\UiFeatureControl.h"

class IKernelBuilderImpl : public IKernelBuilder
{
public:
	IKernelBuilderImpl(void);
	virtual ~IKernelBuilderImpl(void);

	static IKernelBuilder* GetInstance();

	// 取得所有支持的控件
	virtual CONTROL_REG_MAP *GetRegControlMap();

private:
	// 所有支持的控件
	CONTROL_REG_MAP		m_CtrlRegMap;
};
