
#pragma once
#include "IUiFeatureKernel.h"

//////////////////////////////////////////////////////////////////////////
// 内核对【对话框】的接口
IUiFeatureKernel *GetKernelWindowInterface();
typedef IUiFeatureKernel* (*GETKERNELWINDOWINTERFACE)();
