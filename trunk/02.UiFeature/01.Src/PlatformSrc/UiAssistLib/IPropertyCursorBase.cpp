
#include "stdafx.h"
#include "..\..\Inc\IPropertyCursorBase.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\ICommonFun.h"

IPropertyCursorBase::IPropertyCursorBase()
{
	SetObjectType(PROP_TYPE_CURSOR_BASE_NAME);

	m_bIsActiveProp = true;
	// 是否是系统默认光标
	m_bIsSysCursor = true;
	// 光标ID
	m_nCursorId = 0;
}

IPropertyCursorBase::~IPropertyCursorBase()
{

}

bool IPropertyCursorBase::IsRightData()
{
	return (m_nCursorId > 0);
}

bool IPropertyCursorBase::ReadPropertyFromXmlNode(XmlNode* pXmlNode)
{
	if (pXmlNode == NULL)
		return false;

	char* psz_id = JabberXmlGetAttrValue(pXmlNode, SKIN_OBJECT_ID);
	char* psz_name = JabberXmlGetAttrValue(pXmlNode, "name");
	char* psz_issyscursor = JabberXmlGetAttrValue(pXmlNode, "issyscursor");
	char* psz_cursorid = JabberXmlGetAttrValue(pXmlNode, "cursorid");
	if (psz_id == NULL || psz_name == NULL || psz_issyscursor == NULL || psz_cursorid == NULL)
		return false;

	SetObjectId((const char *)psz_id);
	SetObjectName((const char *)psz_name);

	m_bIsSysCursor = (psz_issyscursor[0] == '1');
	m_nCursorId = atoi(psz_cursorid);

	return true;
}

// 写入xml
bool IPropertyCursorBase::AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode)
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
	pPropNode->AddAttribute("issyscursor", (m_bIsSysCursor ? "1" : "0"));
	AddIntAttrToNode(pPropNode, "cursorid", m_nCursorId);

	return true;
}

// 是否为系统光标
bool IPropertyCursorBase::IsSystemCursor()
{
	return m_bIsSysCursor;
}

// 设置系统光标
void IPropertyCursorBase::SetSystemCursor(bool bIsSysCursor)
{
	m_bIsSysCursor = bIsSysCursor;
}

// 设置光标ID
void IPropertyCursorBase::SetCursorId(int nId)
{
	m_nCursorId = nId;
}
