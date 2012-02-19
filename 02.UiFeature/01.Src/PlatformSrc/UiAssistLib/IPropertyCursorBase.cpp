
#include "stdafx.h"
#include "..\..\Inc\IPropertyCursorBase.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\ICommonFun.h"

IPropertyCursorBase::IPropertyCursorBase()
{
	SetObjectType(PROP_TYPE_CURSOR_BASE_NAME);

	m_bIsActiveProp = true;
	// �Ƿ���ϵͳĬ�Ϲ��
	m_bIsSysCursor = true;
	// ���ID
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

// д��xml
bool IPropertyCursorBase::AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode)
{
	// �������Ч���ԣ���д��XML
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

// �Ƿ�Ϊϵͳ���
bool IPropertyCursorBase::IsSystemCursor()
{
	return m_bIsSysCursor;
}

// ����ϵͳ���
void IPropertyCursorBase::SetSystemCursor(bool bIsSysCursor)
{
	m_bIsSysCursor = bIsSysCursor;
}

// ���ù��ID
void IPropertyCursorBase::SetCursorId(int nId)
{
	m_nCursorId = nId;
}
