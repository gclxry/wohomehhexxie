
#include "stdafx.h"
#include "..\..\Inc\IPropertyInt.h"
#include "..\..\Inc\UiFeatureDefs.h"

IPropertyInt::IPropertyInt()
{
	SetObjectType(PROP_TYPE_INT_NAME);
	m_IntProp.strName = "";
	m_IntProp.strPropInfo = "";
	m_IntProp.nIntData = 0;
}

IPropertyInt::~IPropertyInt()
{

}

bool IPropertyInt::IsRightData()
{
	return (m_IntProp.strName.size() > 0);
}

bool IPropertyInt::ReadResourceXmlProperty(XmlNode* pXmlNode)
{
	if (pXmlNode == NULL)
		return false;

	char* psz_id = JabberXmlGetAttrValue(pXmlNode, SKIN_OBJECT_ID);
	char* psz_name = JabberXmlGetAttrValue(pXmlNode, "name");
	char* psz_data = JabberXmlGetAttrValue(pXmlNode, "data");
	if (psz_id == NULL || psz_name == NULL || psz_data == NULL)
		return false;

	SetObjectId((const char *)psz_id);
	m_IntProp.strName = psz_name;
	m_IntProp.nIntData = atoi(psz_data);

	return true;
}
