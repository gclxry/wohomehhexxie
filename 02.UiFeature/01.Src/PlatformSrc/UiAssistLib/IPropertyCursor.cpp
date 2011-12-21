
#include "stdafx.h"
#include "..\..\Inc\IPropertyCursor.h"
#include "..\..\Inc\UiFeatureDefs.h"

IPropertyCursor::IPropertyCursor()
{
}

IPropertyCursor::~IPropertyCursor()
{

}

bool IPropertyCursor::IsRightData()
{
	return false;
}

PROP_TYPE IPropertyCursor::GetPropType()
{
	return PT_CURSOR;
}

bool IPropertyCursor::ReadResourceXmlProperty(XmlNode* pXmlNode)
{
	if (pXmlNode == NULL)
		return false;

	return true;
}
