
#include "stdafx.h"
#include "..\..\Inc\IPropertyBool.h"
#include "..\..\Inc\UiFeatureDefs.h"

IPropertyBool::IPropertyBool()
{
	SetObjectType(PROP_TYPE_BOOL_NAME);
	m_bBoolData = false;
}

IPropertyBool::~IPropertyBool()
{

}

bool IPropertyBool::ReadResourceXmlProperty(XmlNode* pXmlNode)
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
	m_bBoolData = (atoi(psz_data) != 0);

	return true;
}

void IPropertyBool::SetValue(bool bBoolData)
{
	m_bBoolData = bBoolData;
}

bool IPropertyBool::GetValue()
{
	return m_bBoolData;
}
