
#pragma once
#include "IKernelWindow.h"
#include "IKernelBuilder.h"

//////////////////////////////////////////////////////////////////////////
// 内核对【对话框】的接口
IKernelWindow *GetKernelWindowInterface();
typedef IKernelWindow* (*GETKERNELWINDOWINTERFACE)();

//////////////////////////////////////////////////////////////////////////
// 内核对【Builder】的接口
IKernelBuilder *GetKernelBuilderInterface();
typedef IKernelBuilder* (*GETKERNELBUILDERINTERFACE)();
