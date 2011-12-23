
#include "stdafx.h"
#include "..\..\Inc\IPropertyBool.h"
#include "..\..\Inc\UiFeatureDefs.h"

IPropertyBool::IPropertyBool()
{
	m_BoolProp.nPropId = 0;
	m_BoolProp.strName = "";
	m_BoolProp.strPropInfo = "";
	m_BoolProp.bBoolData = false;
}

IPropertyBool::~IPropertyBool()
{

}

bool IPropertyBool::IsRightData()
{
	return (m_BoolProp.nPropId > 0 && m_BoolProp.strName.size() > 0);
}

PROP_TYPE IPropertyBool::GetPropType()
{
	return PT_BOOL;
}

bool IPropertyBool::ReadResourceXmlProperty(XmlNode* pXmlNode)
{
	if (pXmlNode == NULL)
		return false;

	char* psz_id = JabberXmlGetAttrValue(pXmlNode, SKIN_PROP_ID);
	char* psz_name = JabberXmlGetAttrValue(pXmlNode, "name");
	char* psz_data = JabberXmlGetAttrValue(pXmlNode, "data");
	if (psz_id == NULL || psz_name == NULL || psz_data == NULL)
		return false;

	m_BoolProp.nPropId = atoi(psz_id);
	m_BoolProp.strName = psz_name;
	m_BoolProp.bBoolData = (atoi(psz_data) != 0);

	return true;
}
