
#include "StdAfx.h"
#include "ICtrlButtonImpl.h"

// ��갴�±�־
#define MOUSE_FLAG_DOWN								(0x0000001UL)

ICtrlButtonImpl::ICtrlButtonImpl(void)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_BUTTON);

	m_mouseFlag = 0;
	m_enumBtnState = BtnStateNormal;

	m_pPropButtonTypeCombo = NULL;
	m_pPropText = NULL;
	m_pPropRgnGroup = NULL;
	m_pPropRgnMaskImage = NULL;
	m_hRgn = NULL;

	for (int i = 0; i < BtnStateNum; i++)
	{
		m_pPropImages[i] = NULL;
		m_pPropFonts[i] = NULL;
	}

	m_bIsCheck = false;

	m_pPropCheckBtnGroup = NULL;
	m_pPropShowPanelName = NULL;
	m_pCheckPanel = NULL;
}

ICtrlButtonImpl::~ICtrlButtonImpl(void)
{
	if (m_hRgn != NULL)
	{
		::DeleteObject(m_hRgn);
		m_hRgn = NULL;
	}
}

void ICtrlButtonImpl::SetButtonText(const char* pszText)
{
	if(NULL == pszText || NULL == m_pPropText)
		return;

	m_pPropText->SetString(const_cast<char*>(pszText));
}

const char* ICtrlButtonImpl::GetButtonText()
{
	if(NULL == m_pPropText)
		return NULL;

	return m_pPropText->GetString();
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlButtonImpl::CreateControlPropetry(bool bIsNewCtrl)
{
	m_pPropButtonTypeCombo = (IPropertyComboBox*)CreatePropetry(NULL, OTID_COMBOBOX, "ButtonType", "��ť����");
	if(NULL != m_pPropButtonTypeCombo)
	{
		if (m_pWindowBase->IsDesignMode())
		{
			m_pPropButtonTypeCombo->AppendString("��ͨ��ť");
			m_pPropButtonTypeCombo->AppendString("Rgn��ť");
			m_pPropButtonTypeCombo->AppendString("Check��ť");

			if (m_pPropButtonTypeCombo->GetSelect() < 0 || m_pPropButtonTypeCombo->GetSelect() >= m_pPropButtonTypeCombo->GetDataCounts())
				m_pPropButtonTypeCombo->SetSelect(0);
		}
	}

	//���ñ���ͼƬ
	IPropertyGroup* pImagePropGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "ButtonImage", "Button�ı���ͼƬGroup");
	m_pPropImages[BtnStateNormal] = (IPropertyImage*)CreatePropetry(pImagePropGroup, OTID_IMAGE, "NormalImage", "Normal״̬��Button�ı���ͼƬ");
	m_pPropImages[BtnStateHover] = (IPropertyImage*)CreatePropetry(pImagePropGroup, OTID_IMAGE, "HoverImage", "Hover״̬��Button�ı���ͼƬ");
	m_pPropImages[BtnStateDown] = (IPropertyImage*)CreatePropetry(pImagePropGroup, OTID_IMAGE, "LButtonDownImage", "����������״̬��Button�ı���ͼƬ");
	m_pPropImages[BtnStateFocus] = (IPropertyImage*)CreatePropetry(pImagePropGroup, OTID_IMAGE, "FocusImage", "�õ�����ʱButton�ı���ͼƬ");
	m_pPropImages[BtnStateDisable] = (IPropertyImage*)CreatePropetry(pImagePropGroup, OTID_IMAGE, "DisableImage", "����״̬��Button�ı���ͼƬ");

	//��������
	IPropertyGroup* pfontPropGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "ButtonFont", "Button������Group");
	m_pPropFonts[BtnStateNormal] = (IPropertyFont*)CreatePropetry(pfontPropGroup, OTID_FONT, "NormalFont", "Normal״̬��Button������");
	m_pPropFonts[BtnStateHover] = (IPropertyFont*)CreatePropetry(pfontPropGroup, OTID_FONT, "HoverFont", "Hover״̬��Button������");
	m_pPropFonts[BtnStateDown] = (IPropertyFont*)CreatePropetry(pfontPropGroup, OTID_FONT, "LButtonDownFont", "����������״̬��Button������");
	m_pPropFonts[BtnStateFocus] = (IPropertyFont*)CreatePropetry(pfontPropGroup, OTID_FONT, "FocusFont", "�õ�����ʱButton������");
	m_pPropFonts[BtnStateDisable] = (IPropertyFont*)CreatePropetry(pfontPropGroup, OTID_FONT, "DisableFont", "����״̬��Button������");

	//����Button����ʾ������
	m_pPropText = (IPropertyString*)CreatePropetry(NULL, OTID_STRING, "Text", "Button����ʾ������");
	if (m_pPropText != NULL && bIsNewCtrl)
		m_pPropText->SetString("��ť��ʾ���ı�");

	// ����Rgn��ť����
	m_pPropRgnGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "RgnButton","Rgn��ť");
	// Rgn���������ɰ�ͼƬ���������ɰ�ͼƬ����Ϊ����ɫ��RGBֵΪ0ʱ�������ز���ʾ
	m_pPropRgnMaskImage = (IPropertyImage*)CreatePropetry(m_pPropRgnGroup, OTID_IMAGE, "MaskImage", "Rgn�ɰ�ͼƬ,����Ϊ����ɫ��RGBֵΪ0ʱ�������ز���ʾ");

	// Check Button
	m_pPropCheckBtnGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "CheckButton","CheckButton��ť");
	m_pPropShowPanelName = (IPropertyString*)CreatePropetry(m_pPropCheckBtnGroup, OTID_STRING, "ShowPanelName", "���ڿ�����ʾ�����ص�Panel��ObjectName");
	
	return true;
}

// ��ʼ���ؼ�
void ICtrlButtonImpl::OnCreate()
{
	if (NULL != m_pPropButtonTypeCombo && m_pPropButtonTypeCombo->GetSelect() == BT_RGN_BUTTON)
		SetRgn();
}

// �ؼ���ʼ�����
void ICtrlButtonImpl::OnFinalCreate()
{
}

// ���ٿؼ�
void ICtrlButtonImpl::OnDestroy()
{
}

// ���ƿؼ�
void ICtrlButtonImpl::OnPaint(CDrawingBoard &DrawBoard)
{
	if (IsEnable()) 
	{
		if (m_enumBtnState == BtnStateDisable)
			m_enumBtnState = BtnStateNormal;
	}
	else
	{
		// Disable���Ѿ��ػ����״̬�²����ػ�
		if (m_enumBtnState == BtnStateDisable)
			return;

		m_enumBtnState = BtnStateDisable;
	}

	BTNSTATE BtnState = m_enumBtnState;
	if (m_bIsCheck && (BtnState == BtnStateNormal || BtnState == BtnStateHover))
		BtnState = BtnStateDown;

	if (NULL != m_pPropImages[BtnState])
		m_pPropImages[BtnState]->DrawImage(DrawBoard, GetClientRect());

	if (NULL != m_pPropFonts[BtnState])
		m_pPropFonts[BtnState]->DrawFontText(DrawBoard, const_cast<char *>(m_pPropText->GetString()), GetClientRect());
}

void ICtrlButtonImpl::OnMouseEnter(POINT pt)
{
	if (m_mouseFlag & MOUSE_FLAG_DOWN)
		ChangeButtonStyle(BtnStateDown);
	else
		ChangeButtonStyle(BtnStateHover);

	if (m_pWindowBase != NULL)
		m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_BUTTON_ENTER, NULL, NULL);
}

// ����Ƴ�
void ICtrlButtonImpl::OnMouseLeave(POINT pt)
{
	ChangeButtonStyle(BtnStateNormal);

	if (m_pWindowBase != NULL)
		m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_BUTTON_LEAVE, NULL, NULL);
}

// ���������
void ICtrlButtonImpl::OnLButtonDown(POINT pt)
{
	m_mouseFlag |= MOUSE_FLAG_DOWN;
	ChangeButtonStyle(BtnStateDown);

	if (m_pWindowBase != NULL)
		m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_BUTTON_DOWN, NULL, NULL);
}

// ������˫��
void ICtrlButtonImpl::OnLButtonDbClick(POINT pt)
{
	OnLButtonDown(pt);
}

// ������̧��
void ICtrlButtonImpl::OnLButtonUp(POINT pt)
{
	if (m_pPropButtonTypeCombo != NULL && m_pPropButtonTypeCombo->GetSelect() == BT_CHECK_BUTTON)
		SetCheck(true, false);

	m_mouseFlag &= ~MOUSE_FLAG_DOWN;
	ChangeButtonStyle(IsMousehover() ? BtnStateHover : BtnStateNormal);

	if (m_pWindowBase != NULL)
		m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_BUTTON_UP, NULL, NULL);
}

// ����Ҽ����
void ICtrlButtonImpl::OnRButtonDown(POINT pt)
{
	if (m_pWindowBase != NULL)
		m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_BUTTON_R_BTN_DOWN, NULL, NULL);
}

// �ؼ�ȡ�ý��㣬ͨ��Tab����ת������ؼ�
void ICtrlButtonImpl::OnSetFocus()
{
	if(!IsMousehover())
		ChangeButtonStyle(BtnStateFocus);
}

// �ؼ�ʧȥ����
void ICtrlButtonImpl::OnKillFocus()
{
	if(!IsMousehover())
		ChangeButtonStyle(BtnStateNormal);
}

void ICtrlButtonImpl::ChangeButtonStyle(BTNSTATE state)
{
	if(state != m_enumBtnState)
	{
		m_enumBtnState = state;
		RedrawControl(true);
	}
}

// ����Ƿ������˿ؼ�ָ����RGN����Ĭ�Ϸ���true�������ؼ�����RGN����
bool ICtrlButtonImpl::OnCheckMouseInRgn(POINT pt)
{
	if (NULL != m_pPropButtonTypeCombo && m_pPropButtonTypeCombo->GetSelect() == BT_RGN_BUTTON)
		return (::PtInRegion(m_hRgn, pt.x, pt.y) == TRUE);

	return true;
}

// ���ݸ���ͼƬ����RGN
bool ICtrlButtonImpl::SetRgn()
{
	HRGN rgnTemp = ::CreateRectRgn(0, 0, 0, 0);
	SIZE szMask = {0, 0};
	m_pPropRgnMaskImage->InitImage();

	if (NULL == m_pPropRgnMaskImage || NULL == m_pPropRgnMaskImage->GetImageBaseProp()
	|| NULL == m_pPropRgnMaskImage->GetImageBaseProp()->GetDrawingImage())
		return false;

	BYTE* pImageData = m_pPropRgnMaskImage->GetImageBaseProp()->GetDrawingImage()->GetBits();
	if (NULL == pImageData)
		return false;

	if (m_hRgn != NULL)
	{
		::DeleteObject(m_hRgn);
		m_hRgn = NULL;
	}
	m_hRgn = ::CreateRectRgn(0, 0, 0, 0);

	szMask = m_pPropRgnMaskImage->GetImageSize();
	for (int nHeight = szMask.cy - 1; nHeight >= 0; nHeight--)
	{
		for (int nWidth = 0; nWidth < szMask.cx; nWidth++)
		{
			unsigned int nPos = (nHeight * szMask.cx + nWidth) * 4;
			unsigned int nColor = pImageData[nPos] + pImageData[nPos + 1] + pImageData[nPos + 2];

			if (0 < nColor)	// �Ǻ�ɫ����
			{
				rgnTemp = ::CreateRectRgn(nWidth, (szMask.cy - nHeight), nWidth+1, (szMask.cy - nHeight) + 1);
				::CombineRgn(m_hRgn, m_hRgn, rgnTemp, RGN_OR);
			}
		}
	}
	::DeleteObject(rgnTemp);
	return true;
}

// check button ģʽ��
void ICtrlButtonImpl::SetCheck(bool bIsCheck, bool bRedraw)
{
	if (m_pPropButtonTypeCombo == NULL || m_pPropButtonTypeCombo->GetSelect() != BT_CHECK_BUTTON)
		return;

	m_bIsCheck = bIsCheck;

	if (GetCheckPanel() != NULL)
	{
		m_pCheckPanel->SetVisible(m_bIsCheck);
		m_pCheckPanel->RedrawControl(bRedraw);
	}

	this->RedrawControl(bRedraw);
}

bool ICtrlButtonImpl::IsCheck()
{
	if (m_pPropButtonTypeCombo == NULL || m_pPropButtonTypeCombo->GetSelect() != BT_CHECK_BUTTON)
		return false;

	return m_bIsCheck;
}

IControlBase* ICtrlButtonImpl::GetCheckPanel()
{
	if (m_pPropButtonTypeCombo != NULL && m_pPropButtonTypeCombo->GetSelect() == BT_CHECK_BUTTON)
	{
		if (m_pCheckPanel == NULL && m_pWindowBase != NULL && m_pPropShowPanelName != NULL && m_pPropShowPanelName->GetLength() > 0)
			m_pCheckPanel = m_pWindowBase->GetControl((char*)m_pPropShowPanelName->GetString());
	}
	else
	{
		m_pCheckPanel = NULL;
	}

	return m_pCheckPanel;
}

// Builderˢ�����ԣ��˺�����ֻҪ���¼��ؿؼ����Լ���
void ICtrlButtonImpl::OnBuilderRefreshProp(IPropertyBase* pPropBase)
{
	m_pCheckPanel = NULL;
	GetCheckPanel();
}

// ����ӿڻ��������Ի����ʼ����ɵ�ʱ�����
// �ؼ�ͨ����������ӿڣ�����������ӿں�����ͨ�������ؼ�������ȡ�õ�ǰ�Ի�����������ؼ���
void ICtrlButtonImpl::OnWindowFinalCreate()
{
	OnBuilderRefreshProp(NULL);

	if (m_pWindowBase != NULL && !m_pWindowBase->IsDesignMode() && GetCheckPanel() != NULL)
	{
		m_pCheckPanel->SetVisible(m_bIsCheck);
		m_pCheckPanel->RedrawControl(false);
	}
}
