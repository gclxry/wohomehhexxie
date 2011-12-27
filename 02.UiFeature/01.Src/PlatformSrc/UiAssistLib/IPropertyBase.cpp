
#include "stdafx.h"
#include "..\..\Inc\IPropertyBase.h"
#include "..\..\Inc\UiFeatureDefs.h"

IPropertyBase::IPropertyBase()
{
	SetObjectType("PropertyBase");
}

IPropertyBase::~IPropertyBase()
{

}

bool IPropertyBase::IsRightData()
{
	return (strlen(this->GetObjectName()) > 0);
}
