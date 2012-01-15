
#include "stdafx.h"
#include "..\..\Inc\IPropertyImageBase.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IUiFeatureKernel.h"
#include "..\..\Inc\ICommonFun.h"

IPropertyImageBase::IPropertyImageBase()
{
	SetObjectType(PROP_TYPE_IMAGE_BASE_NAME);

	m_pZipFile = NULL;
	m_nUseCtns = 0;
	m_ImageProp.bIsZipFile = true;
	m_ImageProp.strFileName = "";
	m_ImageProp.ImgShowType = IST_PINGPU;
	INIT_RECT(m_ImageProp.RectInImage);
	INIT_RECT(m_ImageProp.jggInfo);
}

IPropertyImageBase::~IPropertyImageBase()
{

}

ZIP_FILE* IPropertyImageBase::GetZipFile()
{
	return m_pZipFile;
}

void IPropertyImageBase::SetZipFile(ZIP_FILE *pZipFile)
{
	m_pZipFile = pZipFile;

	m_ImageProp.bIsZipFile = true;
	m_ImageProp.strFileName = pZipFile->strFileName;
	m_DrawImg.Delete();
}

bool IPropertyImageBase::IsRightData()
{
	return (m_ImageProp.strFileName.c_str() > 0 && RECT_WIDTH(m_ImageProp.RectInImage) > 0 && RECT_HEIGHT(m_ImageProp.RectInImage) > 0);
}

IMAGE_BASE_PROP* IPropertyImageBase::GetImageProp()
{
	return &m_ImageProp;
}

void IPropertyImageBase::SetImageProp(IMAGE_BASE_PROP* pImgProp)
{
	if (pImgProp == NULL)
		return;

	m_ImageProp = *pImgProp;
}

// 从XML节点读取属性值，并放入属性队列
bool IPropertyImageBase::ReadPropertyFromXmlNode(XmlNode* pXmlNode)
{
	if (pXmlNode == NULL)
		return false;

	char* psz_id = JabberXmlGetAttrValue(pXmlNode, SKIN_OBJECT_ID);
	char* psz_name = JabberXmlGetAttrValue(pXmlNode, "name");
	char* psz_imageinzip = JabberXmlGetAttrValue(pXmlNode, "imageinzip");
	char* psz_showtype = JabberXmlGetAttrValue(pXmlNode, "showtype");
	if (psz_id == NULL || psz_name == NULL || psz_imageinzip == NULL || psz_showtype == NULL)
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

	if (psz_left == NULL || psz_top == NULL || psz_right == NULL || psz_bottom == NULL || 
		psz_jgg_left == NULL || psz_jgg_top == NULL || psz_jgg_right == NULL || psz_jgg_bottom == NULL)
		return false;

	SetObjectId((const char *)psz_id);
	SetObjectName((const char *)psz_name);
	m_ImageProp.bIsZipFile = true;
	m_ImageProp.strFileName = psz_imageinzip;
	m_ImageProp.ImgShowType = (IMAGE_SHOW_TYPE)atoi(psz_showtype);

	m_ImageProp.RectInImage.left = atoi(psz_left);
	m_ImageProp.RectInImage.top = atoi(psz_top);
	m_ImageProp.RectInImage.right = atoi(psz_right);
	m_ImageProp.RectInImage.bottom = atoi(psz_bottom);

	m_ImageProp.jggInfo.left = atoi(psz_jgg_left);
	m_ImageProp.jggInfo.top = atoi(psz_jgg_top);
	m_ImageProp.jggInfo.right = atoi(psz_jgg_right);
	m_ImageProp.jggInfo.bottom = atoi(psz_jgg_bottom);

	return true;
}

bool IPropertyImageBase::DrawImage(CDrawingBoard &DstDc, RECT DstRct)
{
	if (GetUiKernel() == NULL || GetUiKernel()->GetUiEngine() == NULL)
		return false;

	if (!IS_SAFE_HANDLE(m_DrawImg.GetSafeHdc()))
	{
		if (m_pZipFile == NULL)
		{
			if (m_ImageProp.bIsZipFile)
			{
				BYTE *pBuffer = NULL;
				int nLen = 0;
				if (!GetUiKernel()->FindUnZipFile(m_ImageProp.strFileName.c_str(), &pBuffer, &nLen))
					return false;

				m_DrawImg.CreateByMem(pBuffer, nLen);
			}
			else
			{
				m_DrawImg.CreateByFile(m_ImageProp.strFileName.c_str());
			}
		}
		else
		{
			m_DrawImg.CreateByMem(m_pZipFile->pFileData, m_pZipFile->dwSrcFileLen);
		}
	}

	return GetUiKernel()->GetUiEngine()->AlphaBlend(DstDc, DstRct.left, DstRct.top, RECT_WIDTH(DstRct), RECT_HEIGHT(DstRct),
		m_DrawImg, 0, 0, m_DrawImg.GetDcSize().cx, m_DrawImg.GetDcSize().cy);
}

void IPropertyImageBase::SetActivePropetry(bool bIsActive)
{
	if (bIsActive)
		m_nUseCtns++;
	else
		m_nUseCtns--;

	if (m_nUseCtns > 0)
		m_bIsActiveProp = true;
	else
		m_bIsActiveProp = false;
}

bool IPropertyImageBase::GetActivePropetry()
{
//	return m_bIsActiveProp;
	return true;
}

// 写入xml
bool IPropertyImageBase::AppendToXmlNode(CUiXmlWrite &XmlStrObj, CUiXmlWriteNode* pParentXmlNode)
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
	pPropNode->AddAttribute("imageinzip", m_ImageProp.strFileName.c_str());
	AddIntAttrToNode(pPropNode, "showtype", m_ImageProp.ImgShowType);

	CUiXmlWriteNode* pNode_rectinimage = XmlStrObj.CreateNode(pPropNode, "rectinimage");
	if (pNode_rectinimage == NULL)
		return false;
	AddIntAttrToNode(pNode_rectinimage, "left", m_ImageProp.RectInImage.left);
	AddIntAttrToNode(pNode_rectinimage, "top", m_ImageProp.RectInImage.top);
	AddIntAttrToNode(pNode_rectinimage, "right", m_ImageProp.RectInImage.right);
	AddIntAttrToNode(pNode_rectinimage, "bottom", m_ImageProp.RectInImage.bottom);

	CUiXmlWriteNode* pNode_jgg = XmlStrObj.CreateNode(pPropNode, "jgg");
	if (pNode_jgg == NULL)
		return false;
	AddIntAttrToNode(pNode_jgg, "left", m_ImageProp.jggInfo.left);
	AddIntAttrToNode(pNode_jgg, "top", m_ImageProp.jggInfo.top);
	AddIntAttrToNode(pNode_jgg, "right", m_ImageProp.jggInfo.right);
	AddIntAttrToNode(pNode_jgg, "bottom", m_ImageProp.jggInfo.bottom);

	return true;
}
