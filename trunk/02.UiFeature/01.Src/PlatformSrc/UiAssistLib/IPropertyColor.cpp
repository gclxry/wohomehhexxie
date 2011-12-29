
#include "stdafx.h"
#include "..\..\Inc\IPropertyColor.h"
#include "..\..\Inc\UiFeatureDefs.h"

IPropertyColor::IPropertyColor()
{
	SetObjectType(PROP_TYPE_COLOR_NAME);
}

IPropertyColor::~IPropertyColor()
{

}

bool IPropertyColor::IsRightData()
{
	return false;
}

bool IPropertyColor::ReadPropertyFromXmlNode(XmlNode* pXmlNode)
{
	if (pXmlNode == NULL)
		return false;

	return true;
}
