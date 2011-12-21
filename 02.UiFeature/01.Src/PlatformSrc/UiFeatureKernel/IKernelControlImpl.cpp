
#include "StdAfx.h"
#include "IKernelControlImpl.h"

IKernelControlImpl::IKernelControlImpl(void)
{
}

IKernelControlImpl::~IKernelControlImpl(void)
{
}

IKernelControl* IKernelControlImpl::GetInstance()
{
	static IKernelControlImpl _KernelControlInstance;
	return &_KernelControlInstance;
}
