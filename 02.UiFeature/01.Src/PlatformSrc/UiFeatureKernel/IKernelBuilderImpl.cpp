
#include "StdAfx.h"
#include "IKernelBuilderImpl.h"
#include "..\..\Inc\IPropertySkinManager.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "ControlImpl.h"

IKernelBuilderImpl::IKernelBuilderImpl(void)
{
	m_CtrlRegMap.clear();
}

IKernelBuilderImpl::~IKernelBuilderImpl(void)
{
//	for (CONTROL_REG_MAP::iterator pItem = m_CtrlRegMap.begin(); pItem != m_CtrlRegMap.end(); pItem++)
//	{
//		CONTROL_REG* pRegCtrl = pItem->second;
//		SAFE_DELETE(pRegCtrl);
//	}
	m_CtrlRegMap.clear();
}

IKernelBuilder* IKernelBuilderImpl::GetInstance()
{
	static IKernelBuilderImpl _KernelBuilderInstance;
	return &_KernelBuilderInstance;
}

// 取得所有支持的控件
CONTROL_REG_MAP* IKernelBuilderImpl::GetRegControlMap()
{
	CControlImpl::GetInstance()->SetRegControlMap(&m_CtrlRegMap);
	return &m_CtrlRegMap;
}
