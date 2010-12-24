
#include "BfComboSelBtnBar.h"
#include "BaseCtrlManager.h"

// 关闭按钮的大小
#define CLOSE_BTN_W				(11)
#define CLOSE_BTN_H				(10)

CBfComboSelBtnBar::CBfComboSelBtnBar(void)
{
	m_pLogoStatic = NULL;
	m_pBkgndStatic = NULL;
	m_pIdStatic = NULL;
	m_pNameStatic = NULL;
	m_pCloseButton = NULL;

	m_bIsSelect = false;
}

CBfComboSelBtnBar::~CBfComboSelBtnBar(void)
{
}

void CBfComboSelBtnBar::ReleaseWindow()
{
	if (m_pUiManager != NULL)
	{
		m_pUiManager->ClearDirectUiWindow(m_pBkgndStatic);
		m_pUiManager->ClearDirectUiWindow(m_pLogoStatic);
		m_pUiManager->ClearDirectUiWindow(m_pIdStatic);
		m_pUiManager->ClearDirectUiWindow(m_pNameStatic);
		m_pUiManager->ClearDirectUiWindow(m_pCloseButton);
		m_pUiManager->ClearDirectUiWindow(this);
	}
}

bool CBfComboSelBtnBar::InitBar()
{
	return true;
}

// 窗口是否初始化
bool CBfComboSelBtnBar::IsReady()
{
	return (CBfBaseBar::IsReady()
		&& m_pLogoStatic != NULL
		&& m_pBkgndStatic != NULL
		&& m_pIdStatic != NULL
		&& m_pNameStatic != NULL
		&& m_pCloseButton != NULL);
}

void CBfComboSelBtnBar::SetComboItem(COMBO_DATA &ComboData)
{
	m_ComboData = ComboData;

	if (m_pBkgndStatic != NULL)
	{
		m_pBkgndStatic->SetWindowColor(Color(55, 143, 207));
		m_pBkgndStatic->SetDrawBkgndColor(true);
	}

	if (m_pLogoStatic != NULL)
		m_pLogoStatic->SetBkgndImage(0, m_ComboData.strImagePath, m_ComboData.nImageType);

	if (m_pIdStatic != NULL)
		m_pIdStatic->SetWindowText(m_ComboData.strTextId);

	if (m_pNameStatic != NULL)
		m_pNameStatic->SetWindowText(m_ComboData.strTextName);

	this->RedrawWindow();
}

bool CBfComboSelBtnBar::CreateWnd(CDirectUiDlg *pParentDlg, CDirectUiManager *pUiManager, CDirectUiWindowMsgCtrl *pMsgCtrl,
							 CRect WndRect, int nWndId, WND_TYPE WndType, int nImageId, CString strImagePath, IMAGE_TYPE nImageType)
{
	bool bRet = false;
	if (pUiManager != NULL)
	{
		CBaseCtrlManager *pBaseCMgr = (CBaseCtrlManager*)pUiManager;

		m_pBkgndStatic = pBaseCMgr->CreateBfStatic(pMsgCtrl, CRect(0, 0, 0, 0));
		bRet = (m_pBkgndStatic != NULL);

		if (bRet)
		{
			int nNewWndId = nWndId | COMBO_COLSE_BTN_ID_SIGN;
			m_pCloseButton = pBaseCMgr->CreateBfPictureButton(pMsgCtrl, CRect(0, 0, 0, 0), nNewWndId, BSC_THREE);
			bRet = (m_pCloseButton != NULL);
		}

		if (bRet)
		{
			int nNewWndId = nWndId | COMBO_SEL_BTN_ID_SIGN;
			bRet = CDirectUiWindow::CreateWnd(pParentDlg, pUiManager, pMsgCtrl, WndRect, nNewWndId, WndType, nImageId, strImagePath, nImageType);
		}

		if (bRet)
		{
			m_pLogoStatic = pBaseCMgr->CreateBfStatic(pMsgCtrl, CRect(0, 0, 0, 0));
			bRet = (m_pLogoStatic != NULL);
			if (bRet)
				m_pLogoStatic->SetDrawImageWane();
		}

		if (bRet)
		{
			m_pIdStatic = pBaseCMgr->CreateBfStatic(pMsgCtrl, CRect(0, 0, 0, 0));
			bRet = (m_pIdStatic != NULL);
			if (bRet)
				m_pIdStatic->SetWindowTextColor(Color(254, 255, 255, 255));
		}

		if (bRet)
		{
			m_pNameStatic = pBaseCMgr->CreateBfStatic(pMsgCtrl, CRect(0, 0, 0, 0));
			bRet = (m_pNameStatic != NULL);
		}
	}

	return bRet;
}

void CBfComboSelBtnBar::SetCloseButtonImage(BTN_STA_CTNS nStas, CString strImagePath, IMAGE_TYPE nImageType)
{
	if (m_pCloseButton != NULL)
	{
		m_pCloseButton->SetBtnPicStas(nStas);
		m_pCloseButton->SetBkgndImage(0, strImagePath, nImageType);
	}
}

bool CBfComboSelBtnBar::OnDirectUiWindowMsgProc(int nMsgId, DWM_INFO &MsgInfo)
{
	bool bRet = false;
	if (IsReady())
	{
		bRet = true;
		if (nMsgId == DWM_LBUTTONUP)
		{
			m_pMsgCtrl->OnDirectUiWindowMsgProc(DWM_LBUTTONUP, MsgInfo);
		}
		else if (nMsgId == DWM_MOUSEHOVER)
		{
			DUI_OnMouseHover(MsgInfo.wParam, MsgInfo.lParam);
		}
	}

	return bRet;
}

void CBfComboSelBtnBar::DUI_OnMouseHover(WPARAM wParam, LPARAM lParam)
{
	CPoint pt(m_WndRect.left, m_WndRect.top);
	this->OnMouseHover(pt);
}

void CBfComboSelBtnBar::OnMouseHover(CPoint point)
{
	DWM_INFO MsgInfo;
	MsgInfo.wParam = m_nWndId;
	MsgInfo.lParam = NULL;
	m_pMsgCtrl->OnDirectUiWindowMsgProc(DWM_MOUSEHOVER, MsgInfo);
}

void CBfComboSelBtnBar::OnMouseLeave(CPoint point)
{
	::RedrawWindow(m_hParent, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
}

void CBfComboSelBtnBar::MoveWindow(CRect ToRect, HDWP hWinPoslnfo)
{
	if (IsReady())
	{
		m_WndRect = ToRect;

		if (m_pBkgndStatic != NULL)
		{
			m_pBkgndStatic->SetVisable(m_bIsSelect);
			m_pBkgndStatic->MoveWindow(m_WndRect, hWinPoslnfo);
		}

		int nCut = 1;
		CRect LogoRect(m_WndRect);
		LogoRect.left += nCut;
		LogoRect.top += nCut;
		LogoRect.bottom -= nCut;
		LogoRect.right = LogoRect.left + LogoRect.Height();

		if (m_pLogoStatic != NULL)
			m_pLogoStatic->MoveWindow(LogoRect, hWinPoslnfo);

		CRect NameRect(m_WndRect), IdRect(m_WndRect);
		if (m_bIsSelect)
		{
			if (m_pNameStatic != NULL)
			{
				NameRect.left = LogoRect.right + 8;
				NameRect.top += 7;
				NameRect.bottom = m_WndRect.bottom - m_WndRect.Height() / 2;
				m_pNameStatic->MoveWindow(NameRect, hWinPoslnfo);
			}

			if (m_pIdStatic != NULL)
			{
				IdRect.left = LogoRect.right + 8;
				IdRect.top = m_WndRect.bottom - m_WndRect.Height() / 2;
				IdRect.bottom -= 7;
				m_pIdStatic->MoveWindow(IdRect, hWinPoslnfo);
			}
		}
		else
		{
			if (m_pNameStatic != NULL)
			{
				NameRect.top += 2;
				NameRect.left = LogoRect.right + 8;
				m_pNameStatic->MoveWindow(NameRect, hWinPoslnfo);
			}
		}

		if (m_pIdStatic != NULL)
			m_pIdStatic->SetVisable(m_bIsSelect);

		if (m_pCloseButton)
		{
			CRect CloseRect(0, 0, 0, 0);
			CloseRect.top = m_WndRect.top + (m_WndRect.Height() - CLOSE_BTN_H) / 2;
			CloseRect.bottom = CloseRect.top + CLOSE_BTN_H;
			CloseRect.right = m_WndRect.right - 10;
			CloseRect.left = CloseRect.right - CLOSE_BTN_W;

			m_pCloseButton->MoveWindow(CloseRect, hWinPoslnfo);
			m_pCloseButton->SetVisable(m_bIsSelect);
		}
	}
}
