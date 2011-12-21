
#pragma once
#include "IKernelWindow.h"
#include "IKernelControl.h"
#include "IKernelBuilder.h"

//////////////////////////////////////////////////////////////////////////
// 内核对【对话框】的接口
IKernelWindow *GetKernelWindowInterface();
typedef IKernelWindow* (*GETKERNELWINDOWINTERFACE)();

//////////////////////////////////////////////////////////////////////////
// 内核对【Builder】的接口
IKernelBuilder *GetKernelBuilderInterface();
typedef IKernelBuilder* (*GETKERNELBUILDERINTERFACE)();


//////////////////////////////////////////////////////////////////////////
// 内核对【Control】的接口
IKernelControl *GetKernelControlInterface();
typedef IKernelControl* (*GETKERNELCONTROLINTERFACE)();


//////////////////////////////////////////////////////////////////////////
// 内核提供的导出类
