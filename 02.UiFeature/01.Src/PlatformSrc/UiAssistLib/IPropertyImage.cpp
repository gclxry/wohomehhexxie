
#include "stdafx.h"
#include "..\..\Inc\IPropertyImage.h"
#include "..\..\Inc\UiFeatureDefs.h"

IPropertyImage::IPropertyImage()
{
	SetObjectType(PROP_TYPE_IMAGE_NAME);
	m_pImageBaseProp = NULL;
	m_strImageBaseName = "";
}

IPropertyImage::~IPropertyImage()
{

}

const char * IPropertyImage::GetImageBaseName()
{
	return (m_strImageBaseName.c_str());
}

bool IPropertyImage::IsRightData()
{
	return (m_strImageBaseName.size() > 0);
}

IPropertyImageBase* IPropertyImage::GetImageBaseProp()
{
	return m_pImageBaseProp;
}

// 从XML节点读取属性值，并放入属性队列
bool IPropertyImage::ReadResourceXmlProperty(XmlNode* pXmlNode)
{
	if (pXmlNode == NULL)
		return false;

	char* psz_id = JabberXmlGetAttrValue(pXmlNode, SKIN_OBJECT_ID);
	char* psz_name = JabberXmlGetAttrValue(pXmlNode, "name");
	char* psz_imagebasename = JabberXmlGetAttrValue(pXmlNode, "imagebasename");
	if (psz_id == NULL || psz_name == NULL || psz_imagebasename == NULL)
		return false;

	SetObjectId((const char *)psz_id);
	SetObjectName((const char *)psz_name);
	m_strImageBaseName = psz_imagebasename;

	return true;
}
