
#include "StdAfx.h"
#include "ICtrlLinkLableImpl.h"
#include "..\..\Inc\IControlManager.h"


ICtrlLinkLableImpl::ICtrlLinkLableImpl(void)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_LINK_LABLE);

	m_bIsLButtonDown = false;

	m_pPropLinkText = NULL;
	m_pPropLinkUrl = NULL;
	m_pPropCursor = NULL;
	m_PropFontGroup = NULL;
	m_pPropFontNormal = NULL;
	m_pPropFontHover = NULL;
	m_pPropFontDown = NULL;
}

ICtrlLinkLableImpl::~ICtrlLinkLableImpl(void)
{
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlLinkLableImpl::CreateControlPropetry(bool bIsNewCtrl)
{
	m_pPropLinkText = (IPropertyString*)CreatePropetry(NULL, OTID_STRING, "LinkText", "��������ʾ������");
	m_pPropLinkUrl = (IPropertyString*)CreatePropetry(NULL, OTID_STRING, "LinkUrl", "������ָ��ĵ�ַ");
	m_pPropCursor = (IPropertyCursor*)CreatePropetry(NULL, OTID_CURSOR, "CursorStyle", "�����ӵ��������");
	m_PropFontGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "FontGroup", "��������ʾ����������");
	m_pPropFontNormal = (IPropertyFont*)CreatePropetry(m_PropFontGroup, OTID_FONT, "Normal", "����״̬��ʾ����������");
	m_pPropFontHover = (IPropertyFont*)CreatePropetry(m_PropFontGroup, OTID_FONT, "MouseHover", "���Hover״̬��ʾ����������");
	m_pPropFontDown = (IPropertyFont*)CreatePropetry(m_PropFontGroup, OTID_FONT, "MouseDown", "��갴��״̬��ʾ����������");

	return true;
}

// ��ʼ���ؼ�
void ICtrlLinkLableImpl::OnCreate()
{
}

// �ؼ���ʼ�����
void ICtrlLinkLableImpl::OnFinalCreate()
{
}

// ���ٿؼ�
void ICtrlLinkLableImpl::OnDestroy()
{
}

// ���ƿؼ�
void ICtrlLinkLableImpl::OnPaint(CDrawingBoard &DrawBoard)
{
	if (m_pPropFontNormal == NULL || m_pPropFontHover == NULL || m_pPropFontDown == NULL 
	 || m_pPropLinkText == NULL || m_pPropLinkText->GetLength() <= 0)
		return;

	IPropertyFont* pPropFont = m_pPropFontDown;
	if (!m_bIsLButtonDown)
	{
		if (IsMousehover())
			pPropFont = m_pPropFontHover;
		else
			pPropFont = m_pPropFontNormal;
	}

	if (pPropFont != NULL)
		pPropFont->DrawFontText(DrawBoard, (char*)m_pPropLinkText->GetString(), GetClientRect());
}

// ���������
void ICtrlLinkLableImpl::OnLButtonDown(POINT pt)
{
	m_bIsLButtonDown = true;
	this->RedrawControl(true);

	if (m_pWindowBase == NULL || m_pPropLinkUrl == NULL)
		return;

	m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_LINK_LABLE_DOWN, (WPARAM)m_pPropLinkUrl->GetString(), NULL);
}

// ������̧��
void ICtrlLinkLableImpl::OnLButtonUp(POINT pt)
{
	m_bIsLButtonDown = false;
	this->RedrawControl(true);

	if (m_pWindowBase == NULL || m_pPropLinkUrl == NULL)
		return;

	m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_LINK_LABLE_UP, (WPARAM)m_pPropLinkUrl->GetString(), NULL);
}

// ���ÿؼ����
IPropertyCursor* ICtrlLinkLableImpl::OnSetCursor(POINT pt)
{
	return m_pPropCursor;
}

// ������
void ICtrlLinkLableImpl::OnMouseEnter(POINT pt)
{
	this->RedrawControl(true);
}

// ����Ƴ�
void ICtrlLinkLableImpl::OnMouseLeave(POINT pt)
{
	this->RedrawControl(true);
}

// ����Link����
void ICtrlLinkLableImpl::SetLinkText(char *pText, bool bRedraw)
{
	if (m_pPropLinkText == NULL || pText == NULL)
		return;

	m_pPropLinkText->SetString(pText);
	this->RedrawControl(bRedraw);
}

// ����Link���ӵ�ַURL
void ICtrlLinkLableImpl::SetLinkUrl(char *pUrl)
{
	if (m_pPropLinkUrl == NULL || pUrl == NULL)
		return;

	m_pPropLinkUrl->SetString(pUrl);
}

// ȡ��Link���ӵ�ַURL
const char * ICtrlLinkLableImpl::GetLinkUrl()
{
	if (m_pPropLinkUrl == NULL)
		return NULL;

	return m_pPropLinkUrl->GetString();
}
