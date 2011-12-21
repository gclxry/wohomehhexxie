
#include "stdafx.h"
#include "..\..\Inc\UiFeatureEngine.h"
#include "IUiEngineImpl.h"

IUiEngine *GetUiEngineInterface()
{
	return IUiEngineImpl::GetInstance();
}
