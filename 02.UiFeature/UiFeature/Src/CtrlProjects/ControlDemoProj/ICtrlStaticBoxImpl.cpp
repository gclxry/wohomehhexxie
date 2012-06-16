
#include "StdAfx.h"
#include "ICtrlStaticBoxImpl.h"
#include "..\..\Inc\IControlManager.h"
#include "..\..\Inc\ICommonFun.h"

ICtrlStaticBoxImpl::ICtrlStaticBoxImpl(void)
{
	// 添加控件，步骤3：向内核系统注册控件
	SetObjectType(CTRL_NAME_STATICBOX);
	m_pPropImage = NULL;
	m_pPropFont = NULL;
	m_pPropText = NULL;
}

ICtrlStaticBoxImpl::~ICtrlStaticBoxImpl(void)
{

}

// 设置控件文本
bool ICtrlStaticBoxImpl::SetText(char* pszText)
{
	if (NULL == pszText)
	{
		return false;
	}

	m_pPropText->SetString(pszText);

	return true;
}

// 派生控件用于创建属于自己的控件属性
bool ICtrlStaticBoxImpl::CreateControlPropetry(bool bIsNewCtrl)
{
	// 设置背景图片、字体、显示文字属性
	m_pPropImage = (IPropertyImage*)CreatePropetry(NULL, OTID_IMAGE, "Image", "背景图片");
	m_pPropFont = (IPropertyFont*)CreatePropetry(NULL, OTID_FONT, "Font", "字体");
	m_pPropText = (IPropertyString*)CreatePropetry(NULL, OTID_STRING, "Text", "显示的文字");

	if (bIsNewCtrl && m_pWindowBase != NULL)
	{
		// 获取默认字体
		IPropertyFontBase* pDefaultFontBase = m_pWindowBase->GetDefaultFontBase();
		if (pDefaultFontBase != NULL && m_pPropFont != NULL)
			m_pPropFont->SetFontBaseProp(pDefaultFontBase);

		// 设置默认不接受鼠标信息
		m_pPropBase_RcvMouseMsg->SetValue(false);
	}
	return true;
}

// 初始化控件
void ICtrlStaticBoxImpl::OnCreate()
{
	
}

// 控件初始化完毕
void ICtrlStaticBoxImpl::OnFinalCreate()
{

}

// 销毁控件
void ICtrlStaticBoxImpl::OnDestroy()
{

}

// 绘制控件
void ICtrlStaticBoxImpl::OnPaint(CDrawingBoard &DrawBoard)
{
	if (NULL != m_pPropImage)
		m_pPropImage->DrawImage(DrawBoard, this->GetClientRect());

	if (NULL != m_pPropFont)
	{
		m_pPropFont->DrawFontText(DrawBoard,
			const_cast<char *>(m_pPropText->GetString()),
			GetClientRect());
	}
}

bool ICtrlStaticBoxImpl::SetBackgroundImage(CDrawingImage* pBkImg)
{
	if (pBkImg == NULL || m_pPropImage == NULL || m_pWindowBase == NULL)
		return false;

	if (m_pPropImage->GetImageBaseProp() == NULL)
	{
		IPropertyImageBase* pImgBaseBase = (IPropertyImageBase*)m_pSkinPropMgr->CreateEmptyBaseProp(OTID_IMAGE_BASE);
		if (pImgBaseBase == NULL)
			return false;

		pImgBaseBase->SetObjectName("InLine.Static");
		m_pPropImage->SetImageBaseProp(pImgBaseBase);
	}

	if (m_pPropImage->GetImageBaseProp() == NULL)
		return false;

	IMAGE_BASE_PROP *pImgBaseProp = m_pPropImage->GetImageProp();
	if (pImgBaseProp == NULL)
		return false;

	CDrawingImage* pStaticBkImg = m_pPropImage->GetImageBaseProp()->GetDrawingImage();
	if (pStaticBkImg == NULL)
		return false;

	pStaticBkImg->Clone(*pBkImg, m_pWindowBase->GetUiKernel());

	InitPropImageBase(pImgBaseProp);
	pImgBaseProp->RectInImage.right = pStaticBkImg->GetDcSize().cx;
	pImgBaseProp->RectInImage.bottom = pStaticBkImg->GetDcSize().cy;

	return true;
}
