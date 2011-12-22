
#include "stdafx.h"
#include "..\..\Inc\IPropertyImage.h"
#include "..\..\Inc\UiFeatureDefs.h"

IPropertyImage::IPropertyImage()
{
	m_ImageProp.strName = "";
	m_ImageProp.strZipFile = "";
	INIT_RECT(m_ImageProp.RectInImage);
	memset(&m_ImageProp.jggInfo, 0, sizeof(JGG_INFO));
}

IPropertyImage::~IPropertyImage()
{

}

bool IPropertyImage::IsRightData()
{
	return (m_ImageProp.strZipFile.c_str() > 0 && RECT_WIDTH(m_ImageProp.RectInImage) > 0 && RECT_HEIGHT(m_ImageProp.RectInImage) > 0);
}

IMAGE_PROP* IPropertyImage::GetImageProp()
{
	return &m_ImageProp;
}

void IPropertyImage::SetImageProp(IMAGE_PROP* pImgProp)
{
	if (pImgProp == NULL)
		return;

	m_ImageProp = *pImgProp;
}

// 取得属性类型
PROP_TYPE IPropertyImage::GetPropType()
{
	return PT_IMAGE;
}

// 从XML节点读取属性值，并放入属性队列
bool IPropertyImage::ReadResourceXmlProperty(XmlNode* pXmlNode)
{
	if (pXmlNode == NULL)
		return false;

	char* psz_name = JabberXmlGetAttrValue(pXmlNode, SKIN_PROP_NAME);
	char* psz_imageinzip = JabberXmlGetAttrValue(pXmlNode, "imageinzip");
	if (psz_name == NULL || psz_imageinzip == NULL)
		return false;

	XmlNode* pRectInImage = JabberXmlGetChild(pXmlNode, "rectinimage");
	XmlNode* pJgg = JabberXmlGetChild(pXmlNode, "jgg");
	if (pRectInImage == NULL || pJgg == NULL)
		return false;

	// rectinimage
	char* psz_left = JabberXmlGetAttrValue(pRectInImage, "left");
	char* psz_top = JabberXmlGetAttrValue(pRectInImage, "top");
	char* psz_right = JabberXmlGetAttrValue(pRectInImage, "right");
	char* psz_bottom = JabberXmlGetAttrValue(pRectInImage, "bottom");

	// jgg
	char* psz_jgg_left = JabberXmlGetAttrValue(pJgg, "left");
	char* psz_jgg_top = JabberXmlGetAttrValue(pJgg, "top");
	char* psz_jgg_right = JabberXmlGetAttrValue(pJgg, "right");
	char* psz_jgg_bottom = JabberXmlGetAttrValue(pJgg, "bottom");
	char* psz_leftstretch = JabberXmlGetAttrValue(pJgg, "leftstretch");
	char* psz_topstretch = JabberXmlGetAttrValue(pJgg, "topstretch");
	char* psz_rightstretch = JabberXmlGetAttrValue(pJgg, "rightstretch");
	char* psz_bottomstretch = JabberXmlGetAttrValue(pJgg, "bottomstretch");
	char* psz_middlestretch = JabberXmlGetAttrValue(pJgg, "middlestretch");

	if (psz_left == NULL || psz_top == NULL || psz_right == NULL || psz_bottom == NULL || 
		psz_jgg_left == NULL || psz_jgg_top == NULL || psz_jgg_right == NULL || psz_jgg_bottom == NULL || 
		psz_leftstretch == NULL || psz_topstretch == NULL || psz_rightstretch == NULL || psz_bottomstretch == NULL || 
		psz_middlestretch == NULL)
		return false;

	m_ImageProp.strName = psz_name;
	m_ImageProp.strZipFile = psz_imageinzip;

	m_ImageProp.RectInImage.left = atoi(psz_left);
	m_ImageProp.RectInImage.top = atoi(psz_top);
	m_ImageProp.RectInImage.right = atoi(psz_right);
	m_ImageProp.RectInImage.bottom = atoi(psz_bottom);

	m_ImageProp.jggInfo.nLeftSpace = atoi(psz_jgg_left);
	m_ImageProp.jggInfo.nTopSpace = atoi(psz_jgg_top);
	m_ImageProp.jggInfo.nRightSpace = atoi(psz_jgg_right);
	m_ImageProp.jggInfo.nBottomSpace = atoi(psz_jgg_bottom);
	m_ImageProp.jggInfo.bLeftStretch = (atoi(psz_leftstretch) != 0);
	m_ImageProp.jggInfo.bTopStretch = (atoi(psz_topstretch) != 0);
	m_ImageProp.jggInfo.bRightStretch = (atoi(psz_rightstretch) != 0);
	m_ImageProp.jggInfo.bBottomStretch = (atoi(psz_bottomstretch) != 0);
	m_ImageProp.jggInfo.bMiddleStretch = (atoi(psz_middlestretch) != 0);

	return true;
}
