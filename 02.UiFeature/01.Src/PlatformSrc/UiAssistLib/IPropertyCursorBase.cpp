
#include "stdafx.h"
#include "..\..\Inc\IPropertyCursorBase.h"
#include "..\..\Inc\UiFeatureDefs.h"

IPropertyCursorBase::IPropertyCursorBase()
{
	SetObjectType(PROP_TYPE_CURSOR_BASE_NAME);
}

IPropertyCursorBase::~IPropertyCursorBase()
{

}

bool IPropertyCursorBase::IsRightData()
{
	return false;
}

bool IPropertyCursorBase::ReadPropertyFromXmlNode(XmlNode* pXmlNode)
{
	if (pXmlNode == NULL)
		return false;

	return true;
}
