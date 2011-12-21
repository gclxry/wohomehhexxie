
#pragma once
#include "IUiEngine.h"

IUiEngine *GetUiEngineInterface();
typedef IUiEngine* (*GETUIENGINEINTERFACE)();
