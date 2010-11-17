
#include "BaseCtrlManager.h"

CBaseCtrlManager::CBaseCtrlManager(void)
{
}

CBaseCtrlManager::~CBaseCtrlManager(void)
{
}

CBfComboSelBtnBar* CBaseCtrlManager::CreateBfComboSelBtnBar(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId)
{
	CBfComboSelBtnBar *pWnd = NULL;
	if (IsReady())
	{
		pWnd = new CBfComboSelBtnBar;
		if (pWnd != NULL)
		{
			if (!pWnd->CreateWnd(m_pParentDlg, this, pMsgCtrl, WndRect, nWndId, DWT_BAR_COMBO_SELECT_BUTTON)|| !pWnd->InitBar())
			{
				SAVE_DELETE(pWnd);
			}
			else
			{
				m_WndList.NewWndObj(pWnd);
			}
		}
	}

	return pWnd;
}


CBfFlash* CBaseCtrlManager::CreateBfFlash(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, CString strFlashPath)
{
	CBfFlash *pWnd = NULL;
	if (IsReady())
	{
		pWnd = new CBfFlash;
		if (pWnd != NULL)
		{
			if (!pWnd->CreateWnd(m_pParentDlg, this, pMsgCtrl, WndRect, 0, DWT_FLASH))
			{
				SAVE_DELETE(pWnd);
			}
			else
			{
				if (m_WndList.NewWndObj(pWnd) != NULL)
				{
					pWnd->PlayFlash(strFlashPath);
				}
				else
				{
					SAVE_DELETE(pWnd);
				}
			}
		}
	}

	return pWnd;
}

CBfStatic* CBaseCtrlManager::CreateBfStatic(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nImageId, CString strImagePath, IMAGE_TYPE nImageType)
{
	CBfStatic *pWnd = NULL;
	if (IsReady())
	{
		pWnd = new CBfStatic;
		if (pWnd != NULL)
		{
			if (!pWnd->CreateWnd(m_pParentDlg, this, pMsgCtrl, WndRect, 0, DWT_STATIC, nImageId, strImagePath, nImageType))
			{
				SAVE_DELETE(pWnd);
			}
			else
			{
				m_WndList.NewWndObj(pWnd);
			}
		}
	}

	return pWnd;
}

CBfPictureButton* CBaseCtrlManager::CreateBfPictureButton(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId, BTN_STA_CTNS nPicStas, int nImageId, CString strImagePath, IMAGE_TYPE nImageType)
{
	CBfPictureButton *pWnd = NULL;
	if (IsReady())
	{
		pWnd = new CBfPictureButton;
		if (pWnd != NULL)
		{
			if (!pWnd->CreateWnd(m_pParentDlg, this, pMsgCtrl, WndRect, nWndId, DWT_BUTTON, nImageId, strImagePath, nImageType))
			{
				SAVE_DELETE(pWnd);
			}
			else
			{
				pWnd->SetBtnPicStas(nPicStas);
				m_WndList.NewWndObj(pWnd);
			}
		}
	}

	return pWnd;
}

CBfDropDownButton* CBaseCtrlManager::CreateBfDropDownButton(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId, int nImageId, CString strImagePath, IMAGE_TYPE nImageType)
{
	CBfDropDownButton *pWnd = NULL;
	if (IsReady())
	{
		pWnd = new CBfDropDownButton;
		if (pWnd != NULL)
		{
			if (!pWnd->CreateWnd(m_pParentDlg, this, pMsgCtrl, WndRect, nWndId, DWT_COMBO_BOX_DROPDOWN_BUTTON, nImageId, strImagePath, nImageType))
			{
				SAVE_DELETE(pWnd);
			}
			else
			{
				m_WndList.NewWndObj(pWnd);
			}
		}
	}

	return pWnd;
}

CBfNormalGraduatedButton* CBaseCtrlManager::CreateBfNormalGraduatedButton(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId, int nImageId, CString strImagePath, IMAGE_TYPE nImageType)
{
	CBfNormalGraduatedButton *pWnd = NULL;
	if (IsReady())
	{
		pWnd = new CBfNormalGraduatedButton;
		if (pWnd != NULL)
		{
			if (!pWnd->CreateWnd(m_pParentDlg, this, pMsgCtrl, WndRect, nWndId, DWT_GRADIENT_BUTTON, nImageId, strImagePath, nImageType))
			{
				SAVE_DELETE(pWnd);
			}
			else
			{
				m_WndList.NewWndObj(pWnd);
			}
		}
	}

	return pWnd;
}

CBfDrawButton* CBaseCtrlManager::CreateBfDrawButton(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId, int nImageId, CString strImagePath, IMAGE_TYPE nImageType)
{
	CBfDrawButton *pWnd = NULL;
	if (IsReady())
	{
		pWnd = new CBfDrawButton;
		if (pWnd != NULL)
		{
			if (!pWnd->CreateWnd(m_pParentDlg, this, pMsgCtrl, WndRect, nWndId, DWT_BUTTON, nImageId, strImagePath, nImageType))
			{
				SAVE_DELETE(pWnd);
			}
			else
			{
				m_WndList.NewWndObj(pWnd);
			}
		}
	}

	return pWnd;
}

CBfGifStatic* CBaseCtrlManager::CreateBfGifStatic(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId, int nImageId, CString strImagePath)
{
	CBfGifStatic *pWnd = NULL;
	if (IsReady())
	{
		pWnd = new CBfGifStatic;
		if (pWnd != NULL)
		{
			if (!pWnd->CreateWnd(m_pParentDlg, this, pMsgCtrl, WndRect, nWndId, DWT_GIF_STATIC, nImageId, strImagePath, IT_GIF))
			{
				SAVE_DELETE(pWnd);
			}
			else
			{
				m_WndList.NewWndObj(pWnd);
			}
		}
	}

	return pWnd;
}

CBfMouseMoveStatic* CBaseCtrlManager::CreateBfMouseMoveStatic(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId, int nImageId, CString strImagePath, IMAGE_TYPE nImageType)
{
	CBfMouseMoveStatic *pWnd = NULL;
	if (IsReady())
	{
		pWnd = new CBfMouseMoveStatic;
		if (pWnd != NULL)
		{
			if (!pWnd->CreateWnd(m_pParentDlg, this, pMsgCtrl, WndRect, nWndId, DWT_MOUSEMOVE_STATIC, nImageId, strImagePath, nImageType))
			{
				SAVE_DELETE(pWnd);
			}
			else
			{
				m_WndList.NewWndObj(pWnd);
			}
		}
	}

	return pWnd;
}

CBfLinkStatic* CBaseCtrlManager::CreateBfLinkStatic(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId, int nImageId, CString strImagePath, IMAGE_TYPE nImageType)
{
	CBfLinkStatic *pWnd = NULL;
	if (IsReady())
	{
		pWnd = new CBfLinkStatic;
		if (pWnd != NULL)
		{
			if (!pWnd->CreateWnd(m_pParentDlg, this, pMsgCtrl, WndRect, nWndId, DWT_LINK_STATIC, nImageId, strImagePath, nImageType))
			{
				SAVE_DELETE(pWnd);
			}
			else
			{
				m_WndList.NewWndObj(pWnd);
			}
		}
	}

	return pWnd;
}

CBfEdit* CBaseCtrlManager::CreateBfEdit(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId, int nImageId, CString strImagePath, IMAGE_TYPE nImageType)
{
	CBfEdit *pWnd = NULL;
	if (IsReady())
	{
		pWnd = new CBfEdit(CWindowBase::ms_hInstance);
		if (pWnd != NULL)
		{
			if (!pWnd->CreateWnd(m_pParentDlg, this, pMsgCtrl, WndRect, nWndId, DWT_EDIT, nImageId, strImagePath, nImageType))
			{
				SAVE_DELETE(pWnd);
			}
			else
			{
				m_WndList.NewWndObj(pWnd);
			}
		}
	}

	return pWnd;
}

CBfCheckBox* CBaseCtrlManager::CreateBfCheckBox(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId, int nImageId, CString strImagePath, IMAGE_TYPE nImageType)
{
	CBfCheckBox *pWnd = NULL;
	if (IsReady())
	{
		pWnd = new CBfCheckBox;
		if (pWnd != NULL)
		{
			if (!pWnd->CreateWnd(m_pParentDlg, this, pMsgCtrl, WndRect, nWndId, DWT_CHECK_BOX, nImageId, strImagePath, nImageType))
			{
				SAVE_DELETE(pWnd);
			}
			else
			{
				m_WndList.NewWndObj(pWnd);
			}
		}
	}

	return pWnd;
}

CBfComboBox* CBaseCtrlManager::CreateBfComboBox(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId, int nImageId, CString strImagePath, IMAGE_TYPE nImageType)
{
	CBfComboBox *pWnd = NULL;
	if (IsReady())
	{
		pWnd = new CBfComboBox;
		if (pWnd != NULL)
		{
			m_WndList.NewWndObj(pWnd);
			pWnd->CreateWnd(m_pParentDlg, this, pMsgCtrl, WndRect, nWndId, DWT_COMBO_BOX, nImageId, strImagePath, nImageType);
		}
	}

	return pWnd;
}


void CBaseCtrlManager::OnPaintRgn(CRect &WndRect, Graphics *pGraphics)
{
	if (pGraphics != NULL)
	{
		m_pDoGrap = pGraphics;

		//	m_hMemoryDC = pGraphics->GetHDC();
		//	HBRUSH hbr = (HBRUSH)::GetStockObject(LTGRAY_BRUSH);
		//	CRect FillR(0, 0, 50, 50);
		//	::FillRect(m_hMemoryDC, &FillR, hbr);
		//	pGraphics->ReleaseHDC(m_hMemoryDC);

		m_DcRect = WndRect;

		int nCut = 100;

		SolidBrush FillBrush(Color(0, 255, 255, 255));
		m_pDoGrap->FillRectangle(&FillBrush, 0, 0, m_DcRect.Width(), m_DcRect.Height());

		SolidBrush FillBrush1(Color(90, 255, 130, 100));
		m_pDoGrap->FillRectangle(&FillBrush1, nCut, nCut, m_DcRect.Width() - nCut * 2, m_DcRect.Height() - nCut * 2);

		SolidBrush FillBrush2(Color(253, 0, 0, 255));
		m_pDoGrap->FillRectangle(&FillBrush2, nCut, 200, m_DcRect.Width() - nCut * 2, m_DcRect.Height() - nCut * 3);

		for (WndObj *pWndObj = m_WndList.TopObj(); pWndObj != NULL; pWndObj = m_WndList.NextObj(pWndObj))
		{
			if (pWndObj->pWnd != NULL)
				((CDirectUiWindow*)(pWndObj->pWnd))->OnPaintProc(m_pDoGrap, m_hMemoryDC);
		}
	}
}
