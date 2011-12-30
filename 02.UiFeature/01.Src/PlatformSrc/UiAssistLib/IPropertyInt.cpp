
#include "stdafx.h"
#include "..\..\Inc\IPropertyInt.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\ICommonFun.h"

IPropertyInt::IPropertyInt()
{
	SetObjectType(PROP_TYPE_INT_NAME);
	m_nIntData = 0;
}

IPropertyInt::~IPropertyInt()
{

}

bool IPropertyInt::ReadPropertyFromXmlNode(XmlNode* pXmlNode)
{
	if (pXmlNode == NULL)
		return false;

	char* psz_id = JabberXmlGetAttrValue(pXmlNode, SKIN_OBJECT_ID);
	char* psz_name = JabberXmlGetAttrValue(pXmlNode, "name");
	char* psz_data = JabberXmlGetAttrValue(pXmlNode, "data");
	if (psz_id == NULL || psz_name == NULL || psz_data == NULL)
		return false;

	SetObjectId((const char *)psz_id);
	SetObjectName((const char *)psz_name);
	m_nIntData = atoi(psz_data);

	return true;
}

void IPropertyInt::SetValue(int nValue)
{
	m_nIntData = nValue;
}

int IPropertyInt::GetValue()
{
	return m_nIntData;
}

// Ð´Èëxml
bool IPropertyInt::AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode)
{
	if (pParentXmlNode == NULL)
		return false;

	CUiXmlWriteNode* pPropNode = XmlStrObj.CreateNode(pParentXmlNode, "item");
	if (pPropNode == NULL)
		return false;

	pPropNode->AddAttribute(SKIN_OBJECT_ID, GetObjectId());
	pPropNode->AddAttribute("name", GetObjectName());
	AddIntAttrToNode(pPropNode, "data", m_nIntData);

	return true;
}
