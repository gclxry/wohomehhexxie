
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

const char * IPropertyCursor::GetCursorBaseName()
{
	return GetRelevancyPropName();
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

// 写入xml
bool IPropertyCursor::AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode)
{
	return true;
}

// 设置鼠标信息
void IPropertyCursor::SetCursorBaseProp(IPropertyCursorBase *pCursorProp)
{
	if (pCursorProp == NULL)
	{
		SetRelevancyProp(NULL);
		return;
	}

	IPropertyBase* pPropBase = dynamic_cast<IPropertyBase*>(pCursorProp);
	SetRelevancyProp(pPropBase);
}

IPropertyCursorBase* IPropertyCursor::GetCursorBaseProp()
{
	return dynamic_cast<IPropertyCursorBase*>(GetRelevancyProp());
}
