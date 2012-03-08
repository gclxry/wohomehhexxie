
#include "stdafx.h"
#include "..\..\Inc\IPropertyCursor.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IWindowBase.h"

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

	char* psz_id = JabberXmlGetAttrValue(pXmlNode, SKIN_OBJECT_ID);
	char* psz_name = JabberXmlGetAttrValue(pXmlNode, "name");
	char* psz_cursorbasename = JabberXmlGetAttrValue(pXmlNode, "cursorbasename");
	if (psz_id == NULL || psz_name == NULL || psz_cursorbasename == NULL)
		return false;

	SetObjectId((const char *)psz_id);
	SetObjectName((const char *)psz_name);
	SetRelevancyPropName(psz_cursorbasename);

	return true;
}

// 写入xml
bool IPropertyCursor::AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode)
{
	// 如果是无效属性，不写入XML
	if (!GetActivePropetry())
		return true;

	if (pParentXmlNode == NULL)
		return false;

	CUiXmlWriteNode* pPropNode = XmlStrObj.CreateNode(pParentXmlNode, "item");
	if (pPropNode == NULL)
		return false;

	pPropNode->AddAttribute(SKIN_OBJECT_ID, GetObjectId());
	pPropNode->AddAttribute("name", GetObjectName());
	pPropNode->AddAttribute("cursorbasename", GetRelevancyPropName());
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

// 显示鼠标手势
bool IPropertyCursor::ShowCursor(IWindowBase *pWndBase)
{
	if (GetCursorBaseProp() == NULL)
		return false;

	return GetCursorBaseProp()->ShowCursor(pWndBase);
}

// 恢复鼠标手势
bool IPropertyCursor::RecoverCursor(IWindowBase *pWndBase)
{
	if (GetCursorBaseProp() == NULL)
		return false;

	return GetCursorBaseProp()->RecoverCursor(pWndBase);
}
