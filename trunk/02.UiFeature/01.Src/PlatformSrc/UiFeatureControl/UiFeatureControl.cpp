
#include "stdafx.h"
#include "..\..\Inc\UiFeatureControl.h"
#include "IControlManagerImpl.h"

IControlManager *GetControlManager()
{
	return IControlManagerImpl::GetInstance();
}
