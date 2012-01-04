
#include "stdafx.h"
#include "..\..\Inc\IPropertyImage.h"
#include "..\..\Inc\UiFeatureDefs.h"

IPropertyImage::IPropertyImage()
{
	SetObjectType(PROP_TYPE_IMAGE_NAME);
}

IPropertyImage::~IPropertyImage()
{

}

const char * IPropertyImage::GetImageBaseName()
{
	return GetRelevancyPropName();
}

bool IPropertyImage::IsRightData()
{
	return (GetRelevancyProp() != NULL);
}

IPropertyImageBase* IPropertyImage::GetImageBaseProp()
{
	return dynamic_cast<IPropertyImageBase*>(GetRelevancyProp());
}

void IPropertyImage::SetImageBaseProp(IPropertyImageBase* pNewImgBase)
{
	IPropertyBase* pPropBase = dynamic_cast<IPropertyBase*>(pNewImgBase);
	SetRelevancyProp(pPropBase);
}

// 从XML节点读取属性值，并放入属性队列
bool IPropertyImage::ReadPropertyFromXmlNode(XmlNode* pXmlNode)
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
	SetRelevancyPropName(psz_imagebasename);

	return true;
}

// 写入xml
bool IPropertyImage::AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode)
{
	if (pParentXmlNode == NULL)
		return false;

	CUiXmlWriteNode* pPropNode = XmlStrObj.CreateNode(pParentXmlNode, "item");
	if (pPropNode == NULL)
		return false;

	pPropNode->AddAttribute(SKIN_OBJECT_ID, GetObjectId());
	pPropNode->AddAttribute("name", GetObjectName());
	pPropNode->AddAttribute("imagebasename", GetRelevancyPropName());
	return true;
}

bool IPropertyImage::DrawImage(CDrawingBoard &DstDc, RECT DstRct)
{
	if (!IsRightData())
		return false;

	return true;
}
