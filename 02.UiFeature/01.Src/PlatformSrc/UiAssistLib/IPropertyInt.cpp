
#include "stdafx.h"
#include "..\..\Inc\IPropertyInt.h"
#include "..\..\Inc\UiFeatureDefs.h"

IPropertyInt::IPropertyInt()
{
	SetObjectType(PROP_TYPE_INT_NAME);
	m_nIntData = 0;
}

IPropertyInt::~IPropertyInt()
{

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
	SetObjectName((const char *)psz_name);
	m_nIntData = atoi(psz_data);

	return true;
}
