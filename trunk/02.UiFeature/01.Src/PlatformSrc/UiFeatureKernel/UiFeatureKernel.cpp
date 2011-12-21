
#include "stdafx.h"
#include "..\..\Inc\UiFeatureKernel.h"
#include "IKernelWindowImpl.h"
#include "IKernelControlImpl.h"
#include "IKernelBuilderImpl.h"

// �ں˶ԡ��Ի��򡿵Ľӿ�
IKernelWindow *GetKernelWindowInterface()
{
	return IKernelWindowImpl::GetInstance();
}

// �ں˶ԡ�Control���Ľӿ�
IKernelControl *GetKernelControlInterface()
{
	return IKernelControlImpl::GetInstance();
}

// �ں˶ԡ�Builder���Ľӿ�
IKernelBuilder *GetKernelBuilderInterface()
{
	return IKernelBuilderImpl::GetInstance();
}
