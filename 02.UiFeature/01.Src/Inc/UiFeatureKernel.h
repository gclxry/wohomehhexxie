
#pragma once
#include "IKernelWindow.h"
#include "IKernelControl.h"
#include "IKernelBuilder.h"

//////////////////////////////////////////////////////////////////////////
// �ں˶ԡ��Ի��򡿵Ľӿ�
IKernelWindow *GetKernelWindowInterface();
typedef IKernelWindow* (*GETKERNELWINDOWINTERFACE)();

//////////////////////////////////////////////////////////////////////////
// �ں˶ԡ�Builder���Ľӿ�
IKernelBuilder *GetKernelBuilderInterface();
typedef IKernelBuilder* (*GETKERNELBUILDERINTERFACE)();


//////////////////////////////////////////////////////////////////////////
// �ں˶ԡ�Control���Ľӿ�
IKernelControl *GetKernelControlInterface();
typedef IKernelControl* (*GETKERNELCONTROLINTERFACE)();


//////////////////////////////////////////////////////////////////////////
// �ں��ṩ�ĵ�����
