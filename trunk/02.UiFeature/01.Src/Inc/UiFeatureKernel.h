
#pragma once
#include "IKernelWindow.h"

//////////////////////////////////////////////////////////////////////////
// 内核对【对话框】的接口
IKernelWindow *GetKernelWindowInterface();
typedef IKernelWindow* (*GETKERNELWINDOWINTERFACE)();
