
#include "stdafx.h"
#include "..\..\Inc\IPropertyCursor.h"
#include "..\..\Inc\UiFeatureDefs.h"

IPropertyCursor::IPropertyCursor()
{
	SetObjectType(PROP_TYPE_CURSOR_NAME);
}

IPropertyCursor::~IPropertyCursor()
{

}

bool IPropertyCursor::IsRightData()
{
	return false;
}

bool IPropertyCursor::ReadPropertyFromXmlNode(XmlNode* pXmlNode)
{
	if (pXmlNode == NULL)
		return false;

	return true;
}
