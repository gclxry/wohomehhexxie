
#include "DirectUiManager.h"

CDirectUiManager::CDirectUiManager(void)
{
	m_hParent = NULL;
	m_pParentDlg = NULL;
	m_pDoGrap = NULL;
	m_hMemoryDC = NULL;
	m_DcRect.SetRectEmpty();

	m_BkgndColor.SetValue(Color::MakeARGB(255, 236, 233, 216));
	m_OutRingColor.SetValue(Color::MakeARGB(255, 163, 163, 163));
	m_InRingColor.SetValue(Color::MakeARGB(255, 255, 255, 255));

	m_nTrueWndCtns = 0;
}

CDirectUiManager::~CDirectUiManager(void)
{
}

//-----------------------------------------------------------------------------
// 描述: 初始化GDI引擎
//-----------------------------------------------------------------------------
bool CDirectUiManager::InitManager(CDirectUiBaseDlg *pParentDlg)
{
	if (pParentDlg != NULL)
	{
		m_pParentDlg = pParentDlg;
		m_hParent = m_pParentDlg->GetSafeHandle();
	}

	return IS_SAVE_HANDLE(m_hParent);
}

// 删除所有窗口
void CDirectUiManager::ClearAllDirectUiWindow()
{
	m_WndList.ClearAll();
}

void CDirectUiManager::ClearDirectUiWindow(CDirectUiWindow *pWnd)
{
	if (pWnd != NULL)
	{
		m_WndList.DeleteSpWndObj(pWnd);
	}
}

bool CDirectUiManager::IsReady()
{
	return IS_SAVE_HANDLE(m_hParent);
}

CBfComboSelBtnBar* CDirectUiManager::CreateBfComboSelBtnBar(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId)
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


CBfCaptionBar* CDirectUiManager::CreateBfCaptionBar(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, bool bHaveMinBtn, bool bHaveMaxBtn)
{
	CBfCaptionBar *pWnd = NULL;
	if (IsReady())
	{
		pWnd = new CBfCaptionBar;
		if (pWnd != NULL)
		{
			pWnd->SetHaveMinBtn(bHaveMinBtn);
			pWnd->SetHaveMaxBtn(bHaveMaxBtn);
			if (!pWnd->CreateWnd(m_pParentDlg, this, pMsgCtrl, WndRect, 0, DWT_BAR_CAPTION)|| !pWnd->InitBar())
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

CBfFlash* CDirectUiManager::CreateBfFlash(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, CString strFlashPath)
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

CBfStatic* CDirectUiManager::CreateBfStatic(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nImageId, CString strImagePath, IMAGE_TYPE nImageType)
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

CBfPictureButton* CDirectUiManager::CreateBfPictureButton(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId, BTN_STA_CTNS nPicStas, int nImageId, CString strImagePath, IMAGE_TYPE nImageType)
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

CBfDropDownButton* CDirectUiManager::CreateBfDropDownButton(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId, int nImageId, CString strImagePath, IMAGE_TYPE nImageType)
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

CBfGraduatedDropDownButton* CDirectUiManager::CreateBfGraduatedDropDownButton(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId, int nImageId, CString strImagePath, IMAGE_TYPE nImageType)
{
	CBfGraduatedDropDownButton *pWnd = NULL;
	if (IsReady())
	{
		pWnd = new CBfGraduatedDropDownButton;
		if (pWnd != NULL)
		{
			if (!pWnd->CreateWnd(m_pParentDlg, this, pMsgCtrl, WndRect, nWndId, DWT_DROPDOWN_GRADIENT_BUTTON, nImageId, strImagePath, nImageType))
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

CBfNormalGraduatedButton* CDirectUiManager::CreateBfNormalGraduatedButton(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId, int nImageId, CString strImagePath, IMAGE_TYPE nImageType)
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

CBfDrawButton* CDirectUiManager::CreateBfDrawButton(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId, int nImageId, CString strImagePath, IMAGE_TYPE nImageType)
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

CBfGifStatic* CDirectUiManager::CreateBfGifStatic(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId, int nImageId, CString strImagePath)
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

CBfMouseMoveStatic* CDirectUiManager::CreateBfMouseMoveStatic(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId, int nImageId, CString strImagePath, IMAGE_TYPE nImageType)
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

CBfLinkStatic* CDirectUiManager::CreateBfLinkStatic(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId, int nImageId, CString strImagePath, IMAGE_TYPE nImageType)
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

CBfEdit* CDirectUiManager::CreateBfEdit(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId, int nImageId, CString strImagePath, IMAGE_TYPE nImageType)
{
	CBfEdit *pWnd = NULL;
	if (IsReady())
	{
		pWnd = new CBfEdit(m_pParentDlg->m_hInstance);
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

CBfRichEdit* CDirectUiManager::CreateBfRichEdit(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId)
{
	CBfRichEdit *pWnd = NULL;
	if (IsReady())
	{
		pWnd = new CBfRichEdit();
		if (pWnd != NULL)
		{
			if (!pWnd->CreateWnd(m_pParentDlg, this, pMsgCtrl, WndRect, nWndId, DWT_RICH_EDIT))
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

CBfCheckBox* CDirectUiManager::CreateBfCheckBox(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId, int nImageId, CString strImagePath, IMAGE_TYPE nImageType)
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

CBfComboBox* CDirectUiManager::CreateBfComboBox(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId, int nImageId, CString strImagePath, IMAGE_TYPE nImageType)
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

void CDirectUiManager::OnPaint(HDC hMemoryDC, CRect &WndRect, UI_BK_TYPE UiBkType)
{
	Graphics DoGrap(hMemoryDC);

	m_pDoGrap = &DoGrap;
	m_hMemoryDC = hMemoryDC;
	m_DcRect = WndRect;

	// 填充背景色
	DrawNormalBkgnd();
	
	if (UiBkType == UBT_FETION)
	{
		DrawFetionBkgnd();
	}

	for (WndObj *pWndObj = m_WndList.TopObj(); pWndObj != NULL; pWndObj = m_WndList.NextObj(pWndObj))
	{
		if (pWndObj->pWnd != NULL)
			((CDirectUiWindow*)(pWndObj->pWnd))->OnPaintProc(m_pDoGrap, m_hMemoryDC);
	}

	// 填充背景线圈
	if (UiBkType == UBT_NORMAL)
	{
		DrawNormalBkgndLine();
	}
	else if (UiBkType == UBT_FETION)
	{
		DrawFetionBkgndLine();
	}
}

void CDirectUiManager::OnPaintRgn(CRect &WndRect, Graphics *pGraphics)
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

void CDirectUiManager::DrawNormalBkgnd()
{
	// 填充背景色
	SolidBrush FillBrush(m_BkgndColor);
	m_pDoGrap->FillRectangle(&FillBrush, 0, 0, m_DcRect.Width(), m_DcRect.Height());
}

void CDirectUiManager::DrawNormalBkgndLine()
{
	// 画边框线
	Pen OutPen(m_OutRingColor);
	Pen InPen(m_InRingColor);

	m_pDoGrap->DrawRectangle(&OutPen, m_DcRect.left, m_DcRect.top, m_DcRect.Width() - 1, m_DcRect.Height() - 1);
	m_pDoGrap->DrawRectangle(&InPen, m_DcRect.left + 1, m_DcRect.top + 1, m_DcRect.Width() - 3, m_DcRect.Height() - 3);
}

void CDirectUiManager::DrawFetionBkgnd()
{
	// 填充背景色
	int nUp = 230;
	Point p1(0, 0), p2(0, nUp);
	Color col1(49, 176, 218), col2(218, 241, 255);
	LinearGradientBrush lgBrush(p1, p2, col1, col2);
	m_pDoGrap->FillRectangle(&lgBrush, 0, 0, m_DcRect.Width(), nUp);

	int nDown = 120;
	p1 = Point(0, m_DcRect.Height() - nDown);
	p2 = Point(0, m_DcRect.Height());
	col1 = Color(218, 241, 255);
	col2 = Color(160, 214, 241);
	LinearGradientBrush lgBrush1(p1, p2, col1, col2);
	m_pDoGrap->FillRectangle(&lgBrush1, 0, p1.Y + 1, m_DcRect.Width(), nDown);
}

void CDirectUiManager::DrawFetionBkgndLine()
{
	// 画边框线
	Pen OutPen(m_OutRingColor);
	Pen InPen(m_InRingColor);

	Point aPointList[9];
	int nCut = 2;

	for (int i = 1; i >= 0; i--)
	{
		int nRD = 1;
		CRect UserDcRect = m_DcRect;

		aPointList[0].X = UserDcRect.left + i;
		aPointList[0].Y = UserDcRect.top + nCut;

		aPointList[1].X = UserDcRect.left + nCut;
		aPointList[1].Y = UserDcRect.top + i;

		aPointList[2].X = UserDcRect.right - nCut;
		aPointList[2].Y = UserDcRect.top + i;

		aPointList[3].X = UserDcRect.right - nRD - i;
		aPointList[3].Y = UserDcRect.top + nCut;

		aPointList[4].X = UserDcRect.right - nRD - i;
		aPointList[4].Y = UserDcRect.bottom - nCut - 1;

		aPointList[5].X = UserDcRect.right - nCut - 1;
		aPointList[5].Y = UserDcRect.bottom - nRD - i;

		aPointList[6].X = UserDcRect.left + nCut;
		aPointList[6].Y = UserDcRect.bottom - nRD - i;

		aPointList[7].X = UserDcRect.left + i;
		aPointList[7].Y = UserDcRect.bottom - nCut - 1;

		aPointList[8].X = UserDcRect.left + i;
		aPointList[8].Y = UserDcRect.top + nCut;

		if (i == 0)
			m_pDoGrap->DrawLines(&OutPen, aPointList, 9);
		else
			m_pDoGrap->DrawLines(&InPen, aPointList, 9);
	}

	// 最大化后不需要画
	if (!m_bIsWndMax && !m_pParentDlg->IsSetBfStyle(BFS_MODAL_DLG))
	{
		// 画右下角斜线
		CRect DcRect = m_DcRect;
		Point RightUp(DcRect.right - 5, DcRect.bottom - 13);
		Point LeftDown(DcRect.right - 14, DcRect.bottom - 4);
		m_pDoGrap->DrawLine(&OutPen, RightUp, LeftDown);

		RightUp.Y += 4;
		LeftDown.X += 4;
		m_pDoGrap->DrawLine(&OutPen, RightUp, LeftDown);
	}
}

bool CDirectUiManager::OnMouseMove(UINT nFlags, CPoint point)
{
	bool bRet = false;

	for (WndObj *pWndObj = m_WndList.TopObj(); pWndObj != NULL; pWndObj = m_WndList.NextObj(pWndObj))
	{
		if (pWndObj->pWnd != NULL)
			((CDirectUiWindow*)(pWndObj->pWnd))->OnMouseMoveProc(nFlags, point);
	}

	return bRet;
}

void CDirectUiManager::OnTimer(int nTimerId)
{
	for (WndObj *pWndObj = m_WndList.TopObj(); pWndObj != NULL; pWndObj = m_WndList.NextObj(pWndObj))
	{
		if (pWndObj->pWnd != NULL)
			((CDirectUiWindow*)(pWndObj->pWnd))->OnTimer(nTimerId);
	}
}

void CDirectUiManager::OnActivateApp(WPARAM wParam, LPARAM lParam)
{
	for (WndObj *pWndObj = m_WndList.TopObj(); pWndObj != NULL; pWndObj = m_WndList.NextObj(pWndObj))
	{
		if (pWndObj->pWnd != NULL)
			((CDirectUiWindow*)(pWndObj->pWnd))->OnActivateApp(wParam, lParam);
	}
}

void CDirectUiManager::OnDestroy()
{
	for (WndObj *pWndObj = m_WndList.TopObj(); pWndObj != NULL; pWndObj = m_WndList.NextObj(pWndObj))
	{
		if (pWndObj->pWnd != NULL)
			((CDirectUiWindow*)(pWndObj->pWnd))->OnDestroy();
	}

	CDirectUiWindow::UnloadDirectUiWindow();
}

bool CDirectUiManager::OnLButtonDown(UINT nFlags, CPoint point)
{
	bool bRet = false;

	for (WndObj *pWndObj = m_WndList.TopObj(); pWndObj != NULL; pWndObj = m_WndList.NextObj(pWndObj))
	{
		CDirectUiWindow *pWnd = (CDirectUiWindow *)(pWndObj->pWnd);
		if (pWnd != NULL)
		{
			if (pWnd->OnLButtonDownProc(nFlags, point))
				break;
		}
	}

	return bRet;
}

bool CDirectUiManager::OnLButtonUp(UINT nFlags, CPoint point)
{
	bool bRet = false;

	for (WndObj *pWndObj = m_WndList.TopObj(); pWndObj != NULL; pWndObj = m_WndList.NextObj(pWndObj))
	{
		CDirectUiWindow *pWnd = (CDirectUiWindow *)(pWndObj->pWnd);
		if (pWnd != NULL)
		{
			if (pWnd->OnLButtonUpProc(nFlags, point))
				break;
		}
	}
	CDirectUiWindow::SetLButtonUp();

	return bRet;
}

bool CDirectUiManager::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	bool bRet = false;

	for (WndObj *pWndObj = m_WndList.TopObj(); pWndObj != NULL; pWndObj = m_WndList.NextObj(pWndObj))
	{
		CDirectUiWindow *pWnd = (CDirectUiWindow *)(pWndObj->pWnd);
		if (pWnd != NULL)
		{
			if (pWnd->OnLButtonDblClkProc(nFlags, point))
				break;
		}
	}

	return bRet;
}

void CDirectUiManager::DrawCenterImage(Graphics *pDoGrap, Image *pDrawImage, CRect &DstRect, int nWaneEllipse)
{
	if (pDoGrap != NULL && pDrawImage != NULL)
	{
		CRect ImgRect(0, 0, pDrawImage->GetWidth(), pDrawImage->GetHeight());

		Rect DstRect1;
		// 图片比输出的矩形要大的时候
		if (DstRect.Width() < ImgRect.Width() || DstRect.Height() < ImgRect.Height())
		{
			DstRect1 = Rect(CRect2Rect(DstRect));
		}
		else
		{
			CRect NewDstRect(0, 0, 0, 0);

			NewDstRect.left = DstRect.left + (DstRect.Width() - ImgRect.Width()) / 2;
			NewDstRect.right = NewDstRect.left + ImgRect.Width();
			NewDstRect.top = DstRect.top + (DstRect.Height() - ImgRect.Height()) / 2;
			NewDstRect.bottom = NewDstRect.top + ImgRect.Height();

			DstRect1 = Rect(CRect2Rect(NewDstRect));
		}

		if (nWaneEllipse > 0)
		{
			HRGN hRgn = ::CreateRoundRectRgn(DstRect1.X, DstRect1.Y,
				DstRect1.X + DstRect1.Width + 1, DstRect1.Y + DstRect1.Height + 1,
				DstRect1.Width / nWaneEllipse, DstRect1.Height / nWaneEllipse);

			pDoGrap->SetClip(hRgn, CombineModeReplace);
			pDoGrap->DrawImage(pDrawImage, DstRect1, ImgRect.left, ImgRect.top, ImgRect.Width(), ImgRect.Height(), UnitPixel);
			::DeleteObject(hRgn);
			pDoGrap->ResetClip();
		}
		else
		{
			pDoGrap->DrawImage(pDrawImage, DstRect1, ImgRect.left, ImgRect.top, ImgRect.Width(), ImgRect.Height(), UnitPixel);
		}
	}
}

void CDirectUiManager::DrawImage(Graphics *pDoGrap, Image *pDrawImage, CRect &DstRect, CRect &SrcRect)
{
	if (pDoGrap != NULL && pDrawImage != NULL)
	{
		Rect DstRect1 = CRect2Rect(DstRect);
		pDoGrap->DrawImage(pDrawImage, DstRect1, SrcRect.left, SrcRect.top, SrcRect.Width(), SrcRect.Height(), UnitPixel);
	}
}

void CDirectUiManager::DrawWndText(Graphics *pDoGrap, WND_TEXT &WndText)
{
	if (pDoGrap != NULL && !WndText.strText.IsEmpty())
	{
		FontFamily DFamily(WndText.strFontName);
		Font DFont(&DFamily, (REAL)WndText.nFontHeight, WndText.FStyle, UnitPixel);
		SolidBrush DBrush(WndText.TextColor);

		pDoGrap->DrawString(WndText.strText, -1, &DFont, WndText.TextRectF, &WndText.OutFormat, &DBrush);
	}
}

void CDirectUiManager::DrawText(Graphics *pDoGrap, CString strText, CRect TextRect, CString strFontName, int nFontHeight, FontStyle FStyle, Color nTextColor, StringFormat &OutFormat)
{
	if (pDoGrap != NULL && !strText.IsEmpty())
	{
		FontFamily DFamily(strFontName);
		Font DFont(&DFamily, (REAL)nFontHeight, FStyle, UnitPixel);
		SolidBrush DBrush(nTextColor);

		RectF Rf = CRect2RectF(TextRect);
		pDoGrap->DrawString(strText, -1, &DFont, Rf, &OutFormat, &DBrush);
	}
}

void CDirectUiManager::DrawRectLine(Color nLineColor, CRect DstRect)
{
	if (IsReady())
	{
		Pen LinePen(nLineColor);
		m_pDoGrap->DrawRectangle(&LinePen, DstRect.left, DstRect.top, DstRect.Width() - 1, DstRect.Height() - 1);
	}
}

void CDirectUiManager::DrawColor(Color nBkgndColor, CRect DstRect)
{
	if (IsReady())
	{
		// 填充背景色
		SolidBrush FillBrush(nBkgndColor);
		m_pDoGrap->FillRectangle(&FillBrush, DstRect.left, DstRect.top, DstRect.Width(), DstRect.Height());
	}
}
