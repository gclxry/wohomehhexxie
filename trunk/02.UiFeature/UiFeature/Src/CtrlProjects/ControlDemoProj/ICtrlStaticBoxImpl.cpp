
#include "StdAfx.h"
#include "ICtrlStaticBoxImpl.h"
#include "..\..\Inc\IControlManager.h"
#include "..\..\Inc\ICommonFun.h"

ICtrlStaticBoxImpl::ICtrlStaticBoxImpl(void)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_STATICBOX);
	m_pPropImage = NULL;
	m_pPropFont = NULL;
	m_pPropText = NULL;
}

ICtrlStaticBoxImpl::~ICtrlStaticBoxImpl(void)
{

}

// ���ÿؼ��ı�
bool ICtrlStaticBoxImpl::SetText(char* pszText)
{
	if (NULL == pszText)
	{
		return false;
	}

	m_pPropText->SetString(pszText);

	return true;
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlStaticBoxImpl::CreateControlPropetry(bool bIsNewCtrl)
{
	// ���ñ���ͼƬ�����塢��ʾ��������
	m_pPropImage = (IPropertyImage*)CreatePropetry(NULL, OTID_IMAGE, "Image", "����ͼƬ");
	m_pPropFont = (IPropertyFont*)CreatePropetry(NULL, OTID_FONT, "Font", "����");
	m_pPropText = (IPropertyString*)CreatePropetry(NULL, OTID_STRING, "Text", "��ʾ������");

	if (bIsNewCtrl && m_pWindowBase != NULL)
	{
		// ��ȡĬ������
		IPropertyFontBase* pDefaultFontBase = m_pWindowBase->GetDefaultFontBase();
		if (pDefaultFontBase != NULL && m_pPropFont != NULL)
			m_pPropFont->SetFontBaseProp(pDefaultFontBase);

		// ����Ĭ�ϲ����������Ϣ
		m_pPropBase_RcvMouseMsg->SetValue(false);
	}
	return true;
}

// ��ʼ���ؼ�
void ICtrlStaticBoxImpl::OnCreate()
{
	
}

// �ؼ���ʼ�����
void ICtrlStaticBoxImpl::OnFinalCreate()
{

}

// ���ٿؼ�
void ICtrlStaticBoxImpl::OnDestroy()
{

}

// ���ƿؼ�
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
