
#include "stdafx.h"
#include "..\..\Inc\IPropertyImageBase.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IUiFeatureKernel.h"
#include "..\..\Inc\ICommonFun.h"
#include "CGifImage.h"

IPropertyImageBase::IPropertyImageBase()
{
	SetObjectType(PROP_TYPE_IMAGE_BASE_NAME);

	m_pZipFile = NULL;
	m_nUseCtns = 0;
	InitPropImageBase(&m_ImageProp);

	INIT_RECT(m_rctXuLieDraw);
	m_bIsTimerDrawEnd = true;

	m_pGifImg = new CGifImage;
	m_nGifCurFrameTime = -1;
	m_nGifTimeCtns = 0;
}

IPropertyImageBase::~IPropertyImageBase()
{
	SAFE_DELETE(m_pGifImg);
}

void IPropertyImageBase::InitPropImageBase(IMAGE_BASE_PROP *pImgBaseProp)
{
	if (pImgBaseProp == NULL)
		return;

	pImgBaseProp->bIsZipFile = true;
	pImgBaseProp->strFileName = "";
	pImgBaseProp->ImgPlayType = IPT_STATIC_IMG;
	pImgBaseProp->ImgShowType = IST_PINGPU;
	pImgBaseProp->ImgLoopType = ILT_LOOP_1;
	pImgBaseProp->ImgBoFangType = IBFT_ZHENGXIANG;
	pImgBaseProp->bIsDrawJggMid = false;
	INIT_RECT(pImgBaseProp->RectInImage);
	INIT_RECT(pImgBaseProp->jggInfo);
}

ZIP_FILE* IPropertyImageBase::GetZipFile()
{
	return m_pZipFile;
}

void IPropertyImageBase::SetZipFile(ZIP_FILE *pZipFile, bool bCreateMemDc)
{
	m_DrawImg.Delete();
	m_pZipFile = pZipFile;

	if (m_pZipFile == NULL)
	{
		InitPropImageBase(&m_ImageProp);
		return;
	}

	m_ImageProp.bIsZipFile = true;
	m_ImageProp.strFileName = pZipFile->strFileName;

	if (bCreateMemDc && m_pZipFile != NULL)
	{
		INIT_RECT(m_ImageProp.RectInImage);
		if (m_ImageProp.ImgPlayType == IPT_GIF)
		{
			if (m_pGifImg != NULL)
			{
				if (m_pGifImg->CreateByMem(m_pZipFile->pFileData, m_pZipFile->dwSrcFileLen))
				{
					m_ImageProp.RectInImage.right = m_pGifImg->GetImageSize().cx;
					m_ImageProp.RectInImage.bottom = m_pGifImg->GetImageSize().cy;

					m_nGifTimeCtns = 0;
					if (m_ImageProp.ImgBoFangType == IBFT_ZHENGXIANG)
					{
						// 正向播放
						m_nGifCurFrameTime = m_pGifImg->SetCurrentPlayFrame(0);
					}
					else
					{
						// 反向播放
						m_nGifCurFrameTime = m_pGifImg->SetCurrentPlayFrame(m_pGifImg->GetFrameCounts() - 1);
					}
				}
			}
		}
		else
		{
			m_DrawImg.CreateByMem(m_pZipFile->pFileData, m_pZipFile->dwSrcFileLen);
			if (IS_SAFE_HANDLE(m_DrawImg.GetSafeHdc()))
			{
				m_ImageProp.RectInImage.right = m_DrawImg.GetDcSize().cx;
				m_ImageProp.RectInImage.bottom = m_DrawImg.GetDcSize().cy;
			}
		}
	}
}

bool IPropertyImageBase::IsRightData()
{
	return (m_ImageProp.strFileName.c_str() > 0 && RECT_WIDTH(m_ImageProp.RectInImage) > 0 && RECT_HEIGHT(m_ImageProp.RectInImage) > 0);
}

// 初始化Image，将Image加载到内存，程序默认是没有加载图片数据的
void IPropertyImageBase::InitImage()
{
	if (m_ImageProp.ImgPlayType == IPT_GIF)
		InitGifImage();
	else
		InitStaticImage();
}

SIZE IPropertyImageBase::GetImageSize()
{
	InitImage();

	SIZE sizImg;
	sizImg.cx = sizImg.cy = 0;
	if (m_ImageProp.ImgPlayType == IPT_GIF)
	{
		if (m_pGifImg != NULL)
		{
			sizImg = m_pGifImg->GetImageSize();
		}
	}
	else
	{
		sizImg = m_DrawImg.GetDcSize();
	}
	return sizImg;
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
	XmlNode* pAnimation = JabberXmlGetChild(pXmlNode, "animation");
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
	char* psz_drawmid = JabberXmlGetAttrValue(pJgg, "drawmid");

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

	// 为了兼容以前测试皮肤
	if (psz_drawmid == NULL)
		m_ImageProp.bIsDrawJggMid = false;
	else
		m_ImageProp.bIsDrawJggMid = (psz_drawmid[0] == '1');

	if (pAnimation != NULL)
	{
		char* psz_playtype = JabberXmlGetAttrValue(pAnimation, "playtype");
		char* psz_looptype = JabberXmlGetAttrValue(pAnimation, "looptype");
		char* psz_bofangtype = JabberXmlGetAttrValue(pAnimation, "bofangtype");
		if (psz_playtype == NULL || psz_looptype == NULL || psz_bofangtype == NULL)
			return false;

		m_ImageProp.ImgPlayType = (IMAGE_PLAY_TYPE)atoi(psz_playtype);
		m_ImageProp.ImgLoopType = (IMAGE_LOOP_TYPE)atoi(psz_looptype);
		m_ImageProp.ImgBoFangType = (IMAGE_BOFANG_TYPE)atoi(psz_bofangtype);
	}

	return true;
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
	pNode_jgg->AddAttribute("drawmid", (m_ImageProp.bIsDrawJggMid ? "1" : "0"));

	CUiXmlWriteNode* pNode_animation = XmlStrObj.CreateNode(pPropNode, "animation");
	if (pNode_animation == NULL)
		return false;
	AddIntAttrToNode(pNode_animation, "playtype", m_ImageProp.ImgPlayType);
	AddIntAttrToNode(pNode_animation, "looptype", m_ImageProp.ImgLoopType);
	AddIntAttrToNode(pNode_animation, "bofangtype", m_ImageProp.ImgBoFangType);

	return true;
}

bool IPropertyImageBase::InitStaticImage()
{
	if (!IS_SAFE_HANDLE(m_DrawImg.GetSafeHdc()))
	{
		// 普通图片
		if (m_pZipFile == NULL)
		{
			if (m_ImageProp.bIsZipFile)
			{
				BYTE *pBuffer = NULL;
				int nLen = 0;
				if (GetUiKernel() == NULL || !GetUiKernel()->FindUnZipFile(m_ImageProp.strFileName.c_str(), &pBuffer, &nLen))
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

	return IS_SAFE_HANDLE(m_DrawImg.GetSafeHdc());
}

bool IPropertyImageBase::DrawImage(CDrawingBoard &DstDc, RECT DstRct, int nAlpha)
{
	return DrawImage(DstDc.GetSafeHdc(), DstRct, nAlpha);
}

bool IPropertyImageBase::DrawImage(HDC hDc, RECT DstRct, int nAlpha)
{
	if (GetUiKernel() == NULL || GetUiKernel()->GetUiEngine() == NULL)
		return false;

	InitImage();

	if (m_ImageProp.ImgPlayType == IPT_GIF)
	{
		if (m_pGifImg == NULL || m_pGifImg->GetImage() == NULL)
			return false;
	}
	else
	{
		if (!IS_SAFE_HANDLE(m_DrawImg.GetSafeHdc()))
			return false;
	}

	m_bIsTimerDrawEnd = true;
	if (m_ImageProp.ImgPlayType == IPT_STATIC_IMG)
	{
		// 静态图片
		if (IST_ALL_LASHEN == m_ImageProp.ImgShowType)
		{
			return DrawImage_AllLaShen(hDc, DstRct, nAlpha);
		}
		else if (IST_PINGPU == m_ImageProp.ImgShowType)
		{
			return DrawImage_PingPu(hDc, DstRct, nAlpha);
		}
		else if (IST_JGG_LASHEN == m_ImageProp.ImgShowType)
		{
			return DrawImage_JggLaShen(hDc, DstRct, nAlpha);
		}
	}
	else if (m_ImageProp.ImgPlayType == IPT_GIF)
	{
		Graphics DoGrap(hDc);
		Rect DstRect1 = Rect(DstRct.left, DstRct.top, RECT_WIDTH(DstRct), RECT_HEIGHT(DstRct));
		DoGrap.DrawImage(m_pGifImg->GetImage(), DstRect1, 0, 0, m_pGifImg->GetImageSize().cx, m_pGifImg->GetImageSize().cy, UnitPixel);
	}
	else if (m_ImageProp.ImgPlayType == IPT_IMAGE_XULIE)
	{
		// 序列图片
		InitDrawXuLieRect();

		int nDstWidth = RECT_WIDTH(DstRct);
		int nDstHeight = RECT_HEIGHT(DstRct);
		int nSrcWidth = RECT_WIDTH(m_rctXuLieDraw);
		int nSrcHeight = RECT_HEIGHT(m_rctXuLieDraw);
		if (nDstHeight <= 0 || nDstWidth <= 0 || nSrcWidth <= 0 || nSrcHeight <= 0)
			return true;

		return GetUiKernel()->GetUiEngine()->AlphaBlend(hDc, DstRct.left, DstRct.top, nDstWidth, nDstHeight,
			m_DrawImg, m_rctXuLieDraw.left, m_rctXuLieDraw.top, nSrcWidth, nSrcHeight, nAlpha);
	}

	return false;
}

bool IPropertyImageBase::DrawImage_AllLaShen(CDrawingBoard &DstDc, RECT DstRct, int nAlpha)
{
	return DrawImage_AllLaShen(DstDc.GetSafeHdc(), DstRct, nAlpha);
}

bool IPropertyImageBase::DrawImage_AllLaShen(HDC hDstDc, RECT DstRct, int nAlpha)
{
	if (hDstDc == NULL || GetUiKernel() == NULL || GetUiKernel()->GetUiEngine() == NULL)
		return false;

	int nDstWidth = RECT_WIDTH(DstRct);
	int nDstHeight = RECT_HEIGHT(DstRct);
	int nSrcWidth = RECT_WIDTH(m_ImageProp.RectInImage);
	int nSrcHeight = RECT_HEIGHT(m_ImageProp.RectInImage);
	if (nDstHeight <= 0 || nDstWidth <= 0 || nSrcWidth <= 0 || nSrcHeight <= 0)
		return true;

	return GetUiKernel()->GetUiEngine()->AlphaBlend(hDstDc, DstRct.left, DstRct.top, nDstWidth, nDstHeight,
		m_DrawImg, m_ImageProp.RectInImage.left, m_ImageProp.RectInImage.top, nSrcWidth, nSrcHeight, nAlpha);
}

bool IPropertyImageBase::DrawImage_PingPu(CDrawingBoard &DstDc, RECT DstRct, int nAlpha)
{
	return DrawImage_PingPu(DstDc.GetSafeHdc(), DstRct, nAlpha);
}

bool IPropertyImageBase::DrawImage_PingPu(HDC hDstDc, RECT DstRct, int nAlpha)
{
	if (hDstDc == NULL || GetUiKernel() == NULL || GetUiKernel()->GetUiEngine() == NULL)
		return false;

	int nDstWidth = RECT_WIDTH(DstRct);
	int nDstHeight = RECT_HEIGHT(DstRct);
	int nSrcWidth = RECT_WIDTH(m_ImageProp.RectInImage);
	int nSrcHeight = RECT_HEIGHT(m_ImageProp.RectInImage);
	if (nDstHeight <= 0 || nDstWidth <= 0 || nSrcWidth <= 0 || nSrcHeight <= 0)
		return true;

	for (int nZong = 0; nZong < nDstHeight; nZong += nSrcHeight)
	{
		for (int nHeng = 0; nHeng < nDstWidth; nHeng += nSrcWidth)
		{
			// 横向绘制
			if (!GetUiKernel()->GetUiEngine()->AlphaBlend(hDstDc, DstRct.left + nHeng, DstRct.top + nZong, nSrcWidth, nSrcHeight,
				m_DrawImg, m_ImageProp.RectInImage.left, m_ImageProp.RectInImage.top, nSrcWidth, nSrcHeight, nAlpha))
				return false;
		}
	}

	return true;
}

bool IPropertyImageBase::DrawImage_JggLaShen(CDrawingBoard &DstDc, RECT DstRct, int nAlpha)
{
	return DrawImage_JggLaShen(DstDc.GetSafeHdc(), DstRct, nAlpha);
}

bool IPropertyImageBase::DrawImage_JggLaShen(HDC hDstDc, RECT DstRct, int nAlpha)
{
	if (hDstDc == NULL || GetUiKernel() == NULL || GetUiKernel()->GetUiEngine() == NULL)
		return false;

	int nDstWidth = RECT_WIDTH(DstRct);
	int nDstHeight = RECT_HEIGHT(DstRct);
	int nSrcWidth = RECT_WIDTH(m_ImageProp.RectInImage);
	int nSrcHeight = RECT_HEIGHT(m_ImageProp.RectInImage);
	if (nDstHeight <= 0 || nDstWidth <= 0 || nSrcWidth <= 0 || nSrcHeight <= 0)
		return true;

	if (m_ImageProp.jggInfo.left > 0)
	{
		// 左上角
		if (m_ImageProp.jggInfo.top > 0)
		{
			if (!GetUiKernel()->GetUiEngine()->AlphaBlend(hDstDc, DstRct.left, DstRct.top,
				m_ImageProp.jggInfo.left, m_ImageProp.jggInfo.top,
				m_DrawImg, m_ImageProp.RectInImage.left, m_ImageProp.RectInImage.top,
				m_ImageProp.jggInfo.left, m_ImageProp.jggInfo.top, nAlpha))
				return false;
		}

		// 左下角
		if (m_ImageProp.jggInfo.bottom > 0)
		{
			if (!GetUiKernel()->GetUiEngine()->AlphaBlend(hDstDc, DstRct.left, DstRct.bottom - m_ImageProp.jggInfo.bottom,
				m_ImageProp.jggInfo.left, m_ImageProp.jggInfo.bottom,
				m_DrawImg, m_ImageProp.RectInImage.left, m_ImageProp.RectInImage.bottom - m_ImageProp.jggInfo.bottom,
				m_ImageProp.jggInfo.left, m_ImageProp.jggInfo.bottom, nAlpha))
				return false;
		}

		// 左侧
		if (!GetUiKernel()->GetUiEngine()->AlphaBlend(hDstDc, DstRct.left, DstRct.top + m_ImageProp.jggInfo.top,
			m_ImageProp.jggInfo.left, RECT_HEIGHT(DstRct) - m_ImageProp.jggInfo.top - m_ImageProp.jggInfo.bottom,
			m_DrawImg, m_ImageProp.RectInImage.left, m_ImageProp.RectInImage.top + m_ImageProp.jggInfo.top,
			m_ImageProp.jggInfo.left, RECT_HEIGHT(m_ImageProp.RectInImage) - m_ImageProp.jggInfo.top - m_ImageProp.jggInfo.bottom, nAlpha))
			return false;
	}

	if (m_ImageProp.jggInfo.right > 0)
	{
		// 右上角
		if (m_ImageProp.jggInfo.top > 0)
		{
			if (!GetUiKernel()->GetUiEngine()->AlphaBlend(hDstDc, DstRct.right - m_ImageProp.jggInfo.right, DstRct.top,
				m_ImageProp.jggInfo.right, m_ImageProp.jggInfo.top,
				m_DrawImg, m_ImageProp.RectInImage.right - m_ImageProp.jggInfo.right, m_ImageProp.RectInImage.top,
				m_ImageProp.jggInfo.right, m_ImageProp.jggInfo.top, nAlpha))
				return false;
		}

		// 右下角
		if (m_ImageProp.jggInfo.bottom > 0)
		{
			if (!GetUiKernel()->GetUiEngine()->AlphaBlend(hDstDc, DstRct.right - m_ImageProp.jggInfo.right, DstRct.bottom - m_ImageProp.jggInfo.bottom,
				m_ImageProp.jggInfo.right, m_ImageProp.jggInfo.bottom,
				m_DrawImg, m_ImageProp.RectInImage.right - m_ImageProp.jggInfo.right, m_ImageProp.RectInImage.bottom - m_ImageProp.jggInfo.bottom,
				m_ImageProp.jggInfo.right, m_ImageProp.jggInfo.bottom, nAlpha))
				return false;
		}

		// 右侧
		if (!GetUiKernel()->GetUiEngine()->AlphaBlend(hDstDc, DstRct.right - m_ImageProp.jggInfo.right, DstRct.top + m_ImageProp.jggInfo.top,
			m_ImageProp.jggInfo.right, RECT_HEIGHT(DstRct) - m_ImageProp.jggInfo.top - m_ImageProp.jggInfo.bottom,
			m_DrawImg, m_ImageProp.RectInImage.right - m_ImageProp.jggInfo.right, m_ImageProp.RectInImage.top + m_ImageProp.jggInfo.top,
			m_ImageProp.jggInfo.right, RECT_HEIGHT(m_ImageProp.RectInImage) - m_ImageProp.jggInfo.top - m_ImageProp.jggInfo.bottom, nAlpha))
			return false;
	}

	// 上方
	if (m_ImageProp.jggInfo.top > 0)
	{
		if (!GetUiKernel()->GetUiEngine()->AlphaBlend(hDstDc, DstRct.left + m_ImageProp.jggInfo.left, DstRct.top,
			RECT_WIDTH(DstRct) - m_ImageProp.jggInfo.left - m_ImageProp.jggInfo.right, m_ImageProp.jggInfo.top,
			m_DrawImg, m_ImageProp.RectInImage.left + m_ImageProp.jggInfo.left, m_ImageProp.RectInImage.top,
			RECT_WIDTH(m_ImageProp.RectInImage) - m_ImageProp.jggInfo.left - m_ImageProp.jggInfo.right, m_ImageProp.jggInfo.top, nAlpha))
			return false;
	}

	// 下方
	if (m_ImageProp.jggInfo.bottom > 0)
	{
		if (!GetUiKernel()->GetUiEngine()->AlphaBlend(hDstDc, DstRct.left + m_ImageProp.jggInfo.left, DstRct.bottom - m_ImageProp.jggInfo.bottom,
			RECT_WIDTH(DstRct) - m_ImageProp.jggInfo.left - m_ImageProp.jggInfo.right, m_ImageProp.jggInfo.bottom,
			m_DrawImg, m_ImageProp.RectInImage.left + m_ImageProp.jggInfo.left, m_ImageProp.RectInImage.bottom - m_ImageProp.jggInfo.bottom,
			RECT_WIDTH(m_ImageProp.RectInImage) - m_ImageProp.jggInfo.left - m_ImageProp.jggInfo.right, m_ImageProp.jggInfo.bottom, nAlpha))
			return false;
	}

	if (m_ImageProp.bIsDrawJggMid)
	{
		// 中间
		return GetUiKernel()->GetUiEngine()->AlphaBlend(hDstDc, DstRct.left + m_ImageProp.jggInfo.left, DstRct.top + m_ImageProp.jggInfo.top,
			RECT_WIDTH(DstRct) - m_ImageProp.jggInfo.left - m_ImageProp.jggInfo.right,
			RECT_HEIGHT(DstRct) - m_ImageProp.jggInfo.top - m_ImageProp.jggInfo.bottom,
			m_DrawImg, m_ImageProp.RectInImage.left + m_ImageProp.jggInfo.left, m_ImageProp.RectInImage.top + m_ImageProp.jggInfo.top,
			RECT_WIDTH(m_ImageProp.RectInImage) - m_ImageProp.jggInfo.left - m_ImageProp.jggInfo.right,
			RECT_HEIGHT(m_ImageProp.RectInImage) - m_ImageProp.jggInfo.top - m_ImageProp.jggInfo.bottom, nAlpha);
	}

	return true;
}

bool IPropertyImageBase::SetXuLieDrawInTimer()
{
	if (InitDrawXuLieRect())
		return true;

	if (m_ImageProp.ImgBoFangType == IBFT_ZHENGXIANG)
	{
		// 正向播放
		if (m_rctXuLieDraw.right >= m_DrawImg.GetDcSize().cx)
		{
			if (m_ImageProp.ImgLoopType == ILT_LOOP_1)
				return false;

			INIT_RECT(m_rctXuLieDraw);
			InitDrawXuLieRect();
		}
		else
		{
			m_rctXuLieDraw.left += RECT_WIDTH(m_ImageProp.RectInImage);
			m_rctXuLieDraw.right = m_rctXuLieDraw.left + RECT_WIDTH(m_ImageProp.RectInImage);
		}
	}
	else
	{
		// 反向播放
		if (m_rctXuLieDraw.left <= 0)
		{
			if (m_ImageProp.ImgLoopType == ILT_LOOP_1)
				return false;

			INIT_RECT(m_rctXuLieDraw);
			InitDrawXuLieRect();
		}
		else
		{
			m_rctXuLieDraw.right = m_rctXuLieDraw.left;
			m_rctXuLieDraw.left = m_rctXuLieDraw.right - RECT_WIDTH(m_ImageProp.RectInImage);
		}
	}

	if (m_rctXuLieDraw.left < 0)
		m_rctXuLieDraw.left = 0;

	if (m_rctXuLieDraw.right < 0)
		m_rctXuLieDraw.right = 0;

	if (m_rctXuLieDraw.left > m_DrawImg.GetDcSize().cx)
		m_rctXuLieDraw.left = m_DrawImg.GetDcSize().cx;

	if (m_rctXuLieDraw.right > m_DrawImg.GetDcSize().cx)
		m_rctXuLieDraw.right = m_DrawImg.GetDcSize().cx;

	return true;
}

bool IPropertyImageBase::InitDrawXuLieRect()
{
	if (RECT_WIDTH(m_rctXuLieDraw) <= 0 || RECT_HEIGHT(m_rctXuLieDraw) <= 0)
	{
		if (m_ImageProp.ImgBoFangType == IBFT_ZHENGXIANG)
		{
			m_rctXuLieDraw.left = m_rctXuLieDraw.top = 0;
			m_rctXuLieDraw.right = RECT_WIDTH(m_ImageProp.RectInImage);
			m_rctXuLieDraw.bottom = RECT_HEIGHT(m_ImageProp.RectInImage);
		}
		else
		{
			m_rctXuLieDraw.right = m_DrawImg.GetDcSize().cx;
			m_rctXuLieDraw.left = m_rctXuLieDraw.right - RECT_WIDTH(m_ImageProp.RectInImage);
			m_rctXuLieDraw.top = 0;
			m_rctXuLieDraw.bottom = RECT_HEIGHT(m_ImageProp.RectInImage);
		}
		return true;
	}
	return false;
}

bool IPropertyImageBase::OnDrawAnimation()
{
	if (m_ImageProp.ImgPlayType == IPT_STATIC_IMG)
		return false;

	// 已经计算完毕，等待刷新界面
	if (!m_bIsTimerDrawEnd)
		return true;

	if (m_ImageProp.ImgPlayType == IPT_GIF)
	{
		if (!SetGifDrawInTimer())
			return false;
	}
	else if (m_ImageProp.ImgPlayType == IPT_IMAGE_XULIE)
	{
		if (!SetXuLieDrawInTimer())
			return false;
	}
	else
	{
		return false;
	}

	m_bIsTimerDrawEnd = false;
	return true;
}

bool IPropertyImageBase::SetGifDrawInTimer()
{
	if (m_pGifImg == NULL || m_nGifCurFrameTime == -1)
		return false;

	m_nGifTimeCtns += UM_DFT_ANIMATION_TIMER_100S;
	if (m_ImageProp.ImgBoFangType == IBFT_ZHENGXIANG)
	{
		// 正向播放
		if (m_nGifTimeCtns >= m_nGifCurFrameTime)
		{
			m_nGifTimeCtns = 0;
			int nCur = m_pGifImg->GetCurrentPlayFrame() + 1;
			if (m_ImageProp.ImgLoopType == ILT_LOOP_1 && nCur >= m_pGifImg->GetFrameCounts())
				return false;

			m_nGifCurFrameTime = m_pGifImg->SetCurrentPlayFrame(nCur);
		}
	}
	else
	{
		// 反向播放
		if (m_nGifTimeCtns >= m_nGifCurFrameTime)
		{
			m_nGifTimeCtns = 0;
			int nCur = m_pGifImg->GetCurrentPlayFrame() - 1;
			if (m_ImageProp.ImgLoopType == ILT_LOOP_1 && nCur < 0)
				return false;

			if (nCur < 0)
				nCur = m_pGifImg->GetFrameCounts() - 1;

			m_nGifCurFrameTime = m_pGifImg->SetCurrentPlayFrame(nCur);
		}
	}

	return true;
}

void IPropertyImageBase::InitGifImage()
{
	if (m_pGifImg == NULL || m_pGifImg->GetImage() != NULL)
		return;

	// 普通图片
	if (m_pZipFile == NULL)
	{
		if (m_ImageProp.bIsZipFile)
		{
			BYTE *pBuffer = NULL;
			int nLen = 0;
			if (GetUiKernel() == NULL || !GetUiKernel()->FindUnZipFile(m_ImageProp.strFileName.c_str(), &pBuffer, &nLen))
				return;

			m_pGifImg->CreateByMem(pBuffer, nLen);
		}
		else
		{
			m_pGifImg->CreateByFile(m_ImageProp.strFileName.c_str());
		}
	}
	else
	{
		m_pGifImg->CreateByMem(m_pZipFile->pFileData, m_pZipFile->dwSrcFileLen);
	}

	m_nGifTimeCtns = 0;
	if (m_ImageProp.ImgBoFangType == IBFT_ZHENGXIANG)
	{
		// 正向播放
		m_nGifCurFrameTime = m_pGifImg->SetCurrentPlayFrame(0);
	}
	else
	{
		// 反向播放
		m_nGifCurFrameTime = m_pGifImg->SetCurrentPlayFrame(m_pGifImg->GetFrameCounts() - 1);
	}
}

// 得到图片的内存DC
CDrawingImage* IPropertyImageBase::GetDrawingImage()
{
	return &m_DrawImg;
}
