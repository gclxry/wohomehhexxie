
#include "stdafx.h"
#include "..\..\Inc\IPropertyImage.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IControlBase.h"

IPropertyImage::IPropertyImage()
{
	SetObjectType(PROP_TYPE_IMAGE_NAME);
}

IPropertyImage::~IPropertyImage()
{

}

bool IPropertyImage::OnDrawAnimation()
{
	if (GetImageBaseProp() == NULL)
		return false;

	return GetImageBaseProp()->OnDrawAnimation();
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

void IPropertyImage::SetNeedRedraw()
{
	if (GetOwnerObject() == NULL)
		return;

	IControlBase *pCtrlBase = dynamic_cast<IControlBase*>(GetOwnerObject());
	if (pCtrlBase == NULL)
		return;

	pCtrlBase->RedrawControl();
}

void IPropertyImage::SetImageBaseProp(IPropertyImageBase* pNewImgBase)
{
	if (pNewImgBase == NULL)
	{
		SetRelevancyProp(NULL);
		SetNeedRedraw();
		return;
	}

	IPropertyBase* pPropBase = dynamic_cast<IPropertyBase*>(pNewImgBase);
	SetRelevancyProp(pPropBase);
	SetNeedRedraw();
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
	// 如果是无效属性，不写入XML
	if (!GetActivePropetry())
		return true;

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

bool IPropertyImage::DrawImage(CDrawingBoard &DstDc, RECT DstRct, int nAlpha)
{
	IPropertyImageBase *pImgBase = (IPropertyImageBase*)GetRelevancyProp();
	if (pImgBase == NULL)
		return false;

	return pImgBase->DrawImage(DstDc, DstRct, nAlpha);
}

void IPropertyImage::SetActivePropetry(bool bIsActive)
{
	m_bIsActiveProp = bIsActive;

	if (GetRelevancyProp() != NULL && !bIsActive)
		GetRelevancyProp()->SetActivePropetry(false);
}

bool IPropertyImage::GetActivePropetry()
{
	return m_bIsActiveProp;
}

SIZE IPropertyImage::GetImageSize()
{
	SIZE sizeImg;
	sizeImg.cx = sizeImg.cy = 0;

	if (GetImageBaseProp() != NULL)
		sizeImg = GetImageBaseProp()->GetImageSize();

	return sizeImg;
}