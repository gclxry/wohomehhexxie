
#include "stdafx.h"
#include "..\..\Inc\IPropertyGroup.h"
#include "..\..\Inc\UiFeatureDefs.h"

IPropertyGroup::IPropertyGroup()
{
	SetObjectType(PROP_TYPE_GROUP_NAME);
	m_PropVec.clear();
}

IPropertyGroup::~IPropertyGroup()
{

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

	char* psz_id = JabberXmlGetAttrValue(pXmlNode, SKIN_OBJECT_ID);
	char* psz_name = JabberXmlGetAttrValue(pXmlNode, "name");
	if (psz_id == NULL || psz_name == NULL)
		return false;

	SetObjectId((const char *)psz_id);
	SetObjectName((const char *)psz_name);

	return true;
}

// 追加一个属性
void IPropertyGroup::AppendProperty(IPropertyBase* pProperty)
{
	if (pProperty == NULL)
		return;

	m_PropVec.push_back(pProperty);
}
