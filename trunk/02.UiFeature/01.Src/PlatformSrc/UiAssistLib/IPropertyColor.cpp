
#include "stdafx.h"
#include "..\..\Inc\IPropertyColor.h"
#include "..\..\Inc\UiFeatureDefs.h"

IPropertyColor::IPropertyColor()
{
	SetObjectType("color");
}

IPropertyColor::~IPropertyColor()
{

}

bool IPropertyColor::IsRightData()
{
	return false;
}

PROP_TYPE IPropertyColor::GetPropType()
{
	return PT_COLOR;
}

bool IPropertyColor::ReadResourceXmlProperty(XmlNode* pXmlNode)
{
	if (pXmlNode == NULL)
		return false;

	return true;
}
