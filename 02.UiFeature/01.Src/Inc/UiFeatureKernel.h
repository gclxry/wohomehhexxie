
#pragma once
#include "IKernelWindow.h"
#include "IKernelBuilder.h"

//////////////////////////////////////////////////////////////////////////
// �ں˶ԡ��Ի��򡿵Ľӿ�
IKernelWindow *GetKernelWindowInterface();
typedef IKernelWindow* (*GETKERNELWINDOWINTERFACE)();

//////////////////////////////////////////////////////////////////////////
// �ں˶ԡ�Builder���Ľӿ�
IKernelBuilder *GetKernelBuilderInterface();
typedef IKernelBuilder* (*GETKERNELBUILDERINTERFACE)();
