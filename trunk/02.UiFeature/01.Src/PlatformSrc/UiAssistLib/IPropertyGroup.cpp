
#include "stdafx.h"
#include "..\..\Inc\IPropertyGroup.h"
#include "..\..\Inc\UiFeatureDefs.h"

IPropertyGroup::IPropertyGroup()
{
	m_GroupProp.nPropId = 0;
	m_GroupProp.strName = "";
	m_PropVec.clear();
}

IPropertyGroup::~IPropertyGroup()
{

}

bool IPropertyGroup::IsRightData()
{
	return (m_GroupProp.strName.size() > 0);
}

PROP_TYPE IPropertyGroup::GetPropType()
{
	return PT_GROUP;
}

// 取得Group下的属性列表
GROUP_PROP_VEC* IPropertyGroup::GetPropVec()
{
	return &m_PropVec;
}

bool IPropertyGroup::ReadResourceXmlProperty(XmlNode* pXmlNode)
{
	if (pXmlNode == NULL)
		return false;

	char* psz_id = JabberXmlGetAttrValue(pXmlNode, SKIN_PROP_ID);
	char* psz_name = JabberXmlGetAttrValue(pXmlNode, "name");
	if (psz_id == NULL || psz_name == NULL)
		return false;

	m_GroupProp.nPropId = atoi(psz_id);
	m_GroupProp.strName = psz_name;

	return true;
}
