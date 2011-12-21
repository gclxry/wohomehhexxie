
#include "stdafx.h"
#include "..\..\Inc\IPropertyBool.h"
#include "..\..\Inc\UiFeatureDefs.h"

IPropertyBool::IPropertyBool()
{
}

IPropertyBool::~IPropertyBool()
{

}

bool IPropertyBool::IsRightData()
{
	return false;
}

PROP_TYPE IPropertyBool::GetPropType()
{
	return PT_BOOL;
}

bool IPropertyBool::ReadResourceXmlProperty(XmlNode* pXmlNode)
{
	if (pXmlNode == NULL)
		return false;

	return true;
}
