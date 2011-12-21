
#include "stdafx.h"
#include "..\..\Inc\UiFeatureKernel.h"
#include "IKernelWindowImpl.h"
#include "IKernelControlImpl.h"
#include "IKernelBuilderImpl.h"

// 内核对【对话框】的接口
IKernelWindow *GetKernelWindowInterface()
{
	return IKernelWindowImpl::GetInstance();
}

// 内核对【Control】的接口
IKernelControl *GetKernelControlInterface()
{
	return IKernelControlImpl::GetInstance();
}

// 内核对【Builder】的接口
IKernelBuilder *GetKernelBuilderInterface()
{
	return IKernelBuilderImpl::GetInstance();
}
