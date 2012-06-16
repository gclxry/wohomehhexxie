
#include "StdAfx.h"
#include "ICtrlButtonImpl.h"

// 鼠标按下标志
#define MOUSE_FLAG_DOWN								(0x0000001UL)

ICtrlButtonImpl::ICtrlButtonImpl(void)
{
	// 添加控件，步骤3：向内核系统注册控件
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

// 派生控件用于创建属于自己的控件属性
bool ICtrlButtonImpl::CreateControlPropetry(bool bIsNewCtrl)
{
	m_pPropButtonTypeCombo = (IPropertyComboBox*)CreatePropetry(NULL, OTID_COMBOBOX, "ButtonType", "按钮类型");
	if(NULL != m_pPropButtonTypeCombo)
	{
		if (m_pWindowBase->IsDesignMode())
		{
			m_pPropButtonTypeCombo->AppendString("普通按钮");
			m_pPropButtonTypeCombo->AppendString("Rgn按钮");
			m_pPropButtonTypeCombo->AppendString("Check按钮");

			if (m_pPropButtonTypeCombo->GetSelect() < 0 || m_pPropButtonTypeCombo->GetSelect() >= m_pPropButtonTypeCombo->GetDataCounts())
				m_pPropButtonTypeCombo->SetSelect(0);
		}
	}

	//设置背景图片
	IPropertyGroup* pImagePropGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "ButtonImage", "Button的背景图片Group");
	m_pPropImages[BtnStateNormal] = (IPropertyImage*)CreatePropetry(pImagePropGroup, OTID_IMAGE, "NormalImage", "Normal状态下Button的背景图片");
	m_pPropImages[BtnStateHover] = (IPropertyImage*)CreatePropetry(pImagePropGroup, OTID_IMAGE, "HoverImage", "Hover状态下Button的背景图片");
	m_pPropImages[BtnStateDown] = (IPropertyImage*)CreatePropetry(pImagePropGroup, OTID_IMAGE, "LButtonDownImage", "按下鼠标左键状态下Button的背景图片");
	m_pPropImages[BtnStateFocus] = (IPropertyImage*)CreatePropetry(pImagePropGroup, OTID_IMAGE, "FocusImage", "得到焦点时Button的背景图片");
	m_pPropImages[BtnStateDisable] = (IPropertyImage*)CreatePropetry(pImagePropGroup, OTID_IMAGE, "DisableImage", "禁用状态下Button的背景图片");

	//设置字体
	IPropertyGroup* pfontPropGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "ButtonFont", "Button的字体Group");
	m_pPropFonts[BtnStateNormal] = (IPropertyFont*)CreatePropetry(pfontPropGroup, OTID_FONT, "NormalFont", "Normal状态下Button的字体");
	m_pPropFonts[BtnStateHover] = (IPropertyFont*)CreatePropetry(pfontPropGroup, OTID_FONT, "HoverFont", "Hover状态下Button的字体");
	m_pPropFonts[BtnStateDown] = (IPropertyFont*)CreatePropetry(pfontPropGroup, OTID_FONT, "LButtonDownFont", "按下鼠标左键状态下Button的字体");
	m_pPropFonts[BtnStateFocus] = (IPropertyFont*)CreatePropetry(pfontPropGroup, OTID_FONT, "FocusFont", "得到焦点时Button的字体");
	m_pPropFonts[BtnStateDisable] = (IPropertyFont*)CreatePropetry(pfontPropGroup, OTID_FONT, "DisableFont", "禁用状态下Button的字体");

	//设置Button上显示的文言
	m_pPropText = (IPropertyString*)CreatePropetry(NULL, OTID_STRING, "Text", "Button上显示的文字");
	if (m_pPropText != NULL && bIsNewCtrl)
		m_pPropText->SetString("按钮显示的文本");

	// 设置Rgn按钮属性
	m_pPropRgnGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "RgnButton","Rgn按钮");
	// Rgn区域会根据蒙版图片产生，当蒙版图片像素为纯黑色，RGB值为0时，此像素不显示
	m_pPropRgnMaskImage = (IPropertyImage*)CreatePropetry(m_pPropRgnGroup, OTID_IMAGE, "MaskImage", "Rgn蒙版图片,像素为纯黑色，RGB值为0时，此像素不显示");

	// Check Button
	m_pPropCheckBtnGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "CheckButton","CheckButton按钮");
	m_pPropShowPanelName = (IPropertyString*)CreatePropetry(m_pPropCheckBtnGroup, OTID_STRING, "ShowPanelName", "用于控制显示、隐藏的Panel的ObjectName");
	
	return true;
}

// 初始化控件
void ICtrlButtonImpl::OnCreate()
{
	if (NULL != m_pPropButtonTypeCombo && m_pPropButtonTypeCombo->GetSelect() == BT_RGN_BUTTON)
		SetRgn();
}

// 控件初始化完毕
void ICtrlButtonImpl::OnFinalCreate()
{
}

// 销毁控件
void ICtrlButtonImpl::OnDestroy()
{
}

// 绘制控件
void ICtrlButtonImpl::OnPaint(CDrawingBoard &DrawBoard)
{
	if (IsEnable()) 
	{
		if (m_enumBtnState == BtnStateDisable)
			m_enumBtnState = BtnStateNormal;
	}
	else
	{
		// Disable且已经重绘过的状态下不在重绘
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

// 鼠标移出
void ICtrlButtonImpl::OnMouseLeave(POINT pt)
{
	ChangeButtonStyle(BtnStateNormal);

	if (m_pWindowBase != NULL)
		m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_BUTTON_LEAVE, NULL, NULL);
}

// 鼠标左键点击
void ICtrlButtonImpl::OnLButtonDown(POINT pt)
{
	m_mouseFlag |= MOUSE_FLAG_DOWN;
	ChangeButtonStyle(BtnStateDown);

	if (m_pWindowBase != NULL)
		m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_BUTTON_DOWN, NULL, NULL);
}

// 鼠标左键双击
void ICtrlButtonImpl::OnLButtonDbClick(POINT pt)
{
	OnLButtonDown(pt);
}

// 鼠标左键抬起
void ICtrlButtonImpl::OnLButtonUp(POINT pt)
{
	if (m_pPropButtonTypeCombo != NULL && m_pPropButtonTypeCombo->GetSelect() == BT_CHECK_BUTTON)
		SetCheck(true, false);

	m_mouseFlag &= ~MOUSE_FLAG_DOWN;
	ChangeButtonStyle(IsMousehover() ? BtnStateHover : BtnStateNormal);

	if (m_pWindowBase != NULL)
		m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_BUTTON_UP, NULL, NULL);
}

// 鼠标右键点击
void ICtrlButtonImpl::OnRButtonDown(POINT pt)
{
	if (m_pWindowBase != NULL)
		m_pWindowBase->OnCtrlMessage(dynamic_cast<IControlBase*>(this), CM_BUTTON_R_BTN_DOWN, NULL, NULL);
}

// 控件取得焦点，通过Tab键跳转，激活控件
void ICtrlButtonImpl::OnSetFocus()
{
	if(!IsMousehover())
		ChangeButtonStyle(BtnStateFocus);
}

// 控件失去焦点
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

// 鼠标是否落在了控件指定的RGN区域，默认返回true，整个控件就是RGN区域
bool ICtrlButtonImpl::OnCheckMouseInRgn(POINT pt)
{
	if (NULL != m_pPropButtonTypeCombo && m_pPropButtonTypeCombo->GetSelect() == BT_RGN_BUTTON)
		return (::PtInRegion(m_hRgn, pt.x, pt.y) == TRUE);

	return true;
}

// 根据根据图片设置RGN
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

			if (0 < nColor)	// 非黑色区域
			{
				rgnTemp = ::CreateRectRgn(nWidth, (szMask.cy - nHeight), nWidth+1, (szMask.cy - nHeight) + 1);
				::CombineRgn(m_hRgn, m_hRgn, rgnTemp, RGN_OR);
			}
		}
	}
	::DeleteObject(rgnTemp);
	return true;
}

// check button 模式下
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

// Builder刷新属性，此函数中只要重新加载控件属性即可
void ICtrlButtonImpl::OnBuilderRefreshProp(IPropertyBase* pPropBase)
{
	m_pCheckPanel = NULL;
	GetCheckPanel();
}

// 这个接口会在整个对话框初始化完成的时候调用
// 控件通过派生这个接口，可以在这个接口函数里通过其他控件的名称取得当前对话框里的其他控件。
void ICtrlButtonImpl::OnWindowFinalCreate()
{
	OnBuilderRefreshProp(NULL);

	if (m_pWindowBase != NULL && !m_pWindowBase->IsDesignMode() && GetCheckPanel() != NULL)
	{
		m_pCheckPanel->SetVisible(m_bIsCheck);
		m_pCheckPanel->RedrawControl(false);
	}
}
