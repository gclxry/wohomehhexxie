
#include "BfComboBox.h"
#include "BaseCtrlManager.h"

//#include "resource.h"
#define IDD_COMBO_BOX_SELECE_DLG					(129)
// Logo 图片窗口ID
#define COMBO_BOX_LOGO_STATIC_ID					(100)
// 下拉按钮窗口ID
#define COMBO_BOX_DROP_DOWN_BTN_ID					(101)
// 编辑框ID
#define COMBO_BOX_EDIT_ID							(102)

CBfComboBox::CBfComboBox(void)
{
	m_pSelectDlg = NULL;
	m_pEdit = NULL;
	m_pLogoStatic = NULL;
	m_pDropDownBtn = NULL;
	m_SelDlgPos.SetRectEmpty();
	m_ComboDataList.clear();
}

CBfComboBox::~CBfComboBox(void)
{
	if (m_pSelectDlg != NULL)
	{
		delete m_pSelectDlg;
		m_pSelectDlg = NULL;
	}
}


void CBfComboBox::AddComboItem(COMBO_DATA &ComboData)
{
	m_ComboDataList.push_back(ComboData);

	if (m_ComboDataList.size() == 1)
		SetCurrentComboData(ComboData);
}

void CBfComboBox::SetCloseButtonImage(BTN_STA_CTNS nStas, CString strImagePath, IMAGE_TYPE nImageType)
{
	if (m_pSelectDlg != NULL)
		m_pSelectDlg->SetCloseButtonImage(nStas, strImagePath, nImageType);
}

void CBfComboBox::OnPaint()
{
	// 绘制背景图
	if (m_BkgndImage.IsReady())
		CGdiPlusDraw::DrawCenterImage(m_pDoGrap, m_BkgndImage.GetImage(), m_WndRect);
	else
		CGdiPlusDraw::DrawColor(m_pDoGrap, Color(255, 255, 255), m_WndRect);

	CGdiPlusDraw::DrawRectLine(m_pDoGrap, Color(192, 192, 192), m_WndRect);

	if (IsMouseHover())
	{
		CRect OutRect(m_WndRect);
		OutRect.left++;
		OutRect.top++;
		OutRect.right--;
		OutRect.bottom--;
		CGdiPlusDraw::DrawRectLine(m_pDoGrap, Color(133, 228, 255), OutRect);
	}
}

void CBfComboBox::MoveWindow(CRect ToRect, HDWP hWinPoslnfo)
{
	CDirectUiWindow::MoveWindow(ToRect, hWinPoslnfo);

	m_SelDlgPos = m_WndRect;
	m_SelDlgPos.top = m_WndRect.bottom + 1;
	m_SelDlgPos.bottom = m_SelDlgPos.top + 100;

	int nCut = 2;
	CRect EditRect(ToRect);
	EditRect.top += nCut;
	EditRect.bottom -= nCut;
	EditRect.left += (nCut + EditRect.Height());
	EditRect.right -= (nCut + EditRect.Height());

	if (m_pEdit != NULL)
		m_pEdit->MoveWindow(EditRect, hWinPoslnfo);

	if (m_pLogoStatic != NULL)
	{
		CRect LogoRect(ToRect);
		LogoRect.top += nCut;
		LogoRect.bottom -= nCut;
		LogoRect.left += nCut;
		LogoRect.right = LogoRect.left + EditRect.Height();
		m_pLogoStatic->MoveWindow(LogoRect, hWinPoslnfo);
	}

	if (m_pDropDownBtn != NULL)
	{
		CRect BtnRect(ToRect);
		BtnRect.top += nCut;
		BtnRect.bottom -= nCut;
		BtnRect.right -= nCut;
		BtnRect.left = BtnRect.right - BtnRect.Height();
		m_pDropDownBtn->MoveWindow(BtnRect, hWinPoslnfo);
	}
}

bool CBfComboBox::CreateWnd(CDirectUiDlg *pParentDlg, CDirectUiManager *pUiManager, CDirectUiWindowMsgCtrl *pMsgCtrl,
							 CRect WndRect, int nWndId, WND_TYPE WndType, int nImageId, CString strImagePath, IMAGE_TYPE nImageType)
{
	bool bRet = false;
	if (nWndId > 0 && pUiManager != NULL)
	{
		CBaseCtrlManager *pBaseCMgr = (CBaseCtrlManager*)pUiManager;

		m_pLogoStatic = pBaseCMgr->CreateBfMouseMoveStatic(this, CRect(0, 0, 0, 0), COMBO_BOX_LOGO_STATIC_ID);
		bRet = (m_pLogoStatic != NULL);
		if (bRet)
			m_pLogoStatic->SetDrawImageWane(5);

		if (bRet)
		{
			m_pDropDownBtn = pBaseCMgr->CreateBfDropDownButton(this, CRect(0, 0, 0, 0), COMBO_BOX_DROP_DOWN_BTN_ID);
			bRet = (m_pDropDownBtn != NULL);
		}

		if (bRet)
		{
			m_pEdit = pBaseCMgr->CreateBfEdit(this, CRect(0, 0, 0, 0), COMBO_BOX_EDIT_ID);
			bRet = (m_pEdit != NULL);
			if (bRet)
				m_pEdit->SetDrawFrame(false);
		}

		if (bRet)
			bRet = CDirectUiWindow::CreateWnd(pParentDlg, pUiManager, pMsgCtrl, WndRect, nWndId, WndType, nImageId, strImagePath, nImageType);

		if (bRet)
		{
			m_pSelectDlg = new CBfComboBoxSelectDlg(CWindowBase::ms_hInstance, m_hParent, this);
			bRet = (m_pSelectDlg != NULL);
			if (m_pSelectDlg != NULL)
				m_pSelectDlg->SetComboBox(this);
		}
	}

	return bRet;
}

bool CBfComboBox::OnDirectUiWindowMsgProc(int nMsgId, DWM_INFO &MsgInfo)
{
	bool bRet = false;
	if (IsReady())
	{
		bRet = true;
		if (nMsgId == DWM_LBUTTONDOWN)
		{
			DUI_OnLButtonDown(MsgInfo.wParam, MsgInfo.lParam);
		}
		else if (nMsgId == DWM_MOUSEHOVER)
		{
			DUI_OnMouseHover(MsgInfo.wParam, MsgInfo.lParam);
		}
		else if (nMsgId == DWM_MOUSELEAVE)
		{
			DUI_OnMouseLeave(MsgInfo.wParam, MsgInfo.lParam);
		}
	}

	return bRet;
}

// 鼠标左键按下消息
void CBfComboBox::DUI_OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	if (wParam == COMBO_BOX_DROP_DOWN_BTN_ID)
	{
		// 按下下拉按钮，显示下拉选择项
		if (m_pSelectDlg != NULL && m_pParentDlg != NULL)
		{
			// 冻结窗口，不接受鼠标移动消息
			m_pParentDlg->SetFreezeDlg(true);

			m_pSelectDlg->DoModal();

			// TBD 这是不同窗口
			CHighEfficiencyDlg::SetNeetLButtonUpMsg();
			::SetActiveWindow(m_hParent);
			// 解冻窗口，接受鼠标移动消息
			m_pParentDlg->SetFreezeDlg(false);
		}
	}
}

// 鼠标进入窗口
void CBfComboBox::DUI_OnMouseHover(WPARAM wParam, LPARAM lParam)
{
	DWM_INFO MsgInfo;
	MsgInfo.wParam = m_nWndId;
	MsgInfo.lParam = NULL;

	m_pMsgCtrl->OnDirectUiWindowMsgProc(DWM_MOUSEHOVER, MsgInfo);
}

// 鼠标离开窗口
void CBfComboBox::DUI_OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	if (wParam == COMBO_BOX_DROP_DOWN_BTN_ID)
	{
	}
}

void CBfComboBox::SetCurrentComboData(COMBO_DATA &ComboData)
{
	m_CurComData = ComboData;

	if (m_pLogoStatic != NULL)
	{
		m_pLogoStatic->SetBkgndImage(0, m_CurComData.strImagePath, m_CurComData.nImageType);
		m_pLogoStatic->RedrawWindow();
	}

	if (m_pEdit != NULL)
	{
		m_pEdit->SetWindowText(ComboData.strTextId);
		m_pEdit->RedrawWindow();
	}

	DWM_INFO m_MsgInfo;
	m_MsgInfo.wParam = m_nWndId;
	m_MsgInfo.lParam = NULL;
	m_pMsgCtrl->OnDirectUiWindowMsgProc(DWM_LBUTTONDOWN, m_MsgInfo);
}

void CBfComboBox::ClearData()
{
	if (m_pLogoStatic != NULL)
	{
		m_pLogoStatic->DeleteBkgndImage();
		m_pLogoStatic->RedrawWindow();
	}
}

void CBfComboBox::OnMouseHover(CPoint point)
{
	this->RedrawWindow();
}

void CBfComboBox::OnMouseLeave(CPoint point)
{
	this->RedrawWindow();
}
