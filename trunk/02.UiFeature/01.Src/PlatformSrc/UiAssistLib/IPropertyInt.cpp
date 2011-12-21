
#include "stdafx.h"
#include "..\..\Inc\IPropertyInt.h"
#include "..\..\Inc\UiFeatureDefs.h"

IPropertyInt::IPropertyInt()
{
}

IPropertyInt::~IPropertyInt()
{

}

bool IPropertyInt::IsRightData()
{
	return false;
}

PROP_TYPE IPropertyInt::GetPropType()
{
	return PT_INT;
}

bool IPropertyInt::ReadResourceXmlProperty(XmlNode* pXmlNode)
{
	if (pXmlNode == NULL)
		return false;

	return true;
}
