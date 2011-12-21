
#pragma once
#include "..\..\Inc\IKernelBuilder.h"
#include "..\..\Inc\UiFeatureControl.h"

class IKernelBuilderImpl : public IKernelBuilder
{
public:
	IKernelBuilderImpl(void);
	virtual ~IKernelBuilderImpl(void);

	static IKernelBuilder* GetInstance();

	// ȡ������֧�ֵĿؼ�
	virtual CONTROL_REG_MAP *GetRegControlMap();

private:
	// ����֧�ֵĿؼ�
	CONTROL_REG_MAP		m_CtrlRegMap;
};
