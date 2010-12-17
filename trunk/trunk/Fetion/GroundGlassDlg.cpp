
#include "StdAfx.h"
#include "GroundGlassDlg.h"
#include "Gauss.h"


#define __base_super					CHighEfficiencyDlg

CGroundGlassDlg::CGroundGlassDlg(HINSTANCE hInstance, HWND hParentWnd, int nIconId)
: __base_super(hInstance, hParentWnd, nIconId)
{
	m_pPassWordEdit = NULL;
	m_pUserComboBox = NULL;
	m_pUserLogo = NULL;
	m_pLink1 = NULL;
	m_pLink2 = NULL;
	m_pLink3 = NULL;
	m_pLink4 = NULL;
	m_pStatic = NULL;
	m_pL1 = NULL;
	m_pL2 = NULL;
	m_pYdLogo = NULL;
	m_pCheckBox1 = NULL;
	m_pCheckBox2 = NULL;
	m_pLogonBtn = NULL;

	m_pUiManager = &m_UiManager;
}

CGroundGlassDlg::~CGroundGlassDlg(void)
{
}

LRESULT CGroundGlassDlg::OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam)
{
	int nW = 250, nH = 470;

	MINMAXINFO *pMmInfo = (MINMAXINFO *)lParam;
	if (pMmInfo != NULL)
	{
		pMmInfo->ptMinTrackSize.x = nW;
		pMmInfo->ptMinTrackSize.y = nH;
	}

	return __base_super::OnGetMinMaxInfo(wParam, lParam);
}

void CGroundGlassDlg::OnCreate()
{
	__base_super::OnCreate();

	//m_Blend是结构体BLENDFUNCTION的对象，用于指定两个DC(画图设备)的融合方式。
	m_Blend.BlendOp = AC_SRC_OVER;
	m_Blend.BlendFlags = 0;
	m_Blend.AlphaFormat = AC_SRC_OVER;
	m_Blend.SourceConstantAlpha = 255;

	// 设置默认大小
	this->CenterWindow(260, 480);

	m_nTimer = this->SetTimer(30);

	CString strSkinDir = CSysUnit::GetAppPath();

	CString strPicPath = strSkinDir + _T("SkinImage\\bj1.png");
	m_pStatic = m_UiManager.CreateBfStatic(this, CRect(0, 0, 0, 0), 0, strPicPath, IT_PNG);
	if (m_pStatic == NULL)
	{
		::MessageBox(m_hParent, _T("初始化 m_pStatic 失败，程序无法启动！"), MSG_TITLE, MB_OK | MB_ICONSTOP);
		::PostMessage(m_hParent, WM_CLOSE, NULL, NULL);
		return;
	}
	m_pStatic->SetFullDrawImage(true);

	strPicPath = strSkinDir + _T("SkinImage\\YDLogo.png");
	m_pYdLogo = m_UiManager.CreateBfStatic(this, CRect(0, 0, 0, 0), 0, strPicPath, IT_PNG);
	if (m_pYdLogo == NULL)
	{
		::MessageBox(m_hParent, _T("初始化 m_pYdLogo 失败，程序无法启动！"), MSG_TITLE, MB_OK | MB_ICONSTOP);
		::PostMessage(m_hParent, WM_CLOSE, NULL, NULL);
		return;
	}

	m_pL1 = m_UiManager.CreateBfStatic(this, CRect(0, 0, 0, 0), 0, _T(""), IT_PNG);
	if (m_pL1 == NULL)
	{
		::MessageBox(m_hParent, _T("初始化 m_pL1 失败，程序无法启动！"), MSG_TITLE, MB_OK | MB_ICONSTOP);
		::PostMessage(m_hParent, WM_CLOSE, NULL, NULL);
		return;
	}
	m_pL1->SetWindowText(_T("|"));
	m_pL1->SetWindowTextColor(Color(122, 151, 165));

	m_pL2 = m_UiManager.CreateBfStatic(this, CRect(0, 0, 0, 0), 0, _T(""), IT_PNG);
	if (m_pL2 == NULL)
	{
		::MessageBox(m_hParent, _T("初始化 m_pL2 失败，程序无法启动！"), MSG_TITLE, MB_OK | MB_ICONSTOP);
		::PostMessage(m_hParent, WM_CLOSE, NULL, NULL);
		return;
	}
	m_pL2->SetWindowText(_T("|"));
	m_pL2->SetWindowTextColor(Color(122, 151, 165));

	m_pLink1 = m_UiManager.CreateBfLinkStatic(this, CRect(0, 0, 0, 0), WND_ID_LOGON_LINK_1, 0, _T(""), IT_PNG);
	if (m_pLink1 == NULL)
	{
		::MessageBox(m_hParent, _T("初始化 m_pLink1 失败，程序无法启动！"), MSG_TITLE, MB_OK | MB_ICONSTOP);
		::PostMessage(m_hParent, WM_CLOSE, NULL, NULL);
		return;
	}
	m_pLink1->SetWindowText(_T("注册用户"));

	m_pLink2 = m_UiManager.CreateBfLinkStatic(this, CRect(0, 0, 0, 0), WND_ID_LOGON_LINK_2, 0, _T(""), IT_PNG);
	if (m_pLink2 == NULL)
	{
		::MessageBox(m_hParent, _T("初始化 m_pLink2 失败，程序无法启动！"), MSG_TITLE, MB_OK | MB_ICONSTOP);
		::PostMessage(m_hParent, WM_CLOSE, NULL, NULL);
		return;
	}
	m_pLink2->SetWindowText(_T("找回密码"));

	m_pLink3 = m_UiManager.CreateBfLinkStatic(this, CRect(0, 0, 0, 0), WND_ID_LOGON_LINK_3, 0, _T(""), IT_PNG);
	if (m_pLink3 == NULL)
	{
		::MessageBox(m_hParent, _T("初始化 m_pLink3 失败，程序无法启动！"), MSG_TITLE, MB_OK | MB_ICONSTOP);
		::PostMessage(m_hParent, WM_CLOSE, NULL, NULL);
		return;
	}
	m_pLink3->SetWindowText(_T("网络设置"));

	m_pLink4 = m_UiManager.CreateBfLinkStatic(this, CRect(0, 0, 0, 0), WND_ID_LOGON_LINK_4, 0, _T(""), IT_PNG);
	if (m_pLink4 == NULL)
	{
		::MessageBox(m_hParent, _T("初始化 m_pLink4 失败，程序无法启动！"), MSG_TITLE, MB_OK | MB_ICONSTOP);
		::PostMessage(m_hParent, WM_CLOSE, NULL, NULL);
		return;
	}
	m_pLink4->SetWindowText(_T("使用帮助"));

	m_pPassWordEdit = m_UiManager.CreateBfEdit(this, CRect(0, 0, 0, 0), WND_ID_LOGON_PSW_EDIT, 0, _T(""), IT_PNG);
	if (m_pPassWordEdit == NULL)
	{
		::MessageBox(m_hParent, _T("初始化 m_pPassWordEdit 失败，程序无法启动！"), MSG_TITLE, MB_OK | MB_ICONSTOP);
		::PostMessage(m_hParent, WM_CLOSE, NULL, NULL);
		return;
	}

	m_pUserComboBox = m_UiManager.CreateBfComboBox(this, CRect(0, 0, 0, 0), WND_ID_LOGON_USER_COMBO_BOX, 0, _T(""), IT_PNG);
	if (m_pUserComboBox == NULL)
	{
		::MessageBox(m_hParent, _T("初始化 m_pUserComboBox 失败，程序无法启动！"), MSG_TITLE, MB_OK | MB_ICONSTOP);
		::PostMessage(m_hParent, WM_CLOSE, NULL, NULL);
		return;
	}
	COMBO_DATA ComData;
	ComData.nImageType = IT_PNG;
	ComData.strImagePath = strSkinDir + _T("SkinImage\\Earth.png");
	ComData.strTextId = _T("11111111");
	ComData.strTextName = _T("太子");
	m_pUserComboBox->AddComboItem(ComData);
	ComData.strImagePath = strSkinDir + _T("SkinImage\\Cool.png");
	ComData.strTextId = _T("778428399");
	ComData.strTextName = _T("山大王");
	m_pUserComboBox->AddComboItem(ComData);
	ComData.nImageType = IT_PNG;
	ComData.nImageType = IT_PNG;
	ComData.strImagePath = strSkinDir + _T("SkinImage\\Child.png");
	ComData.strTextId = _T("22223333");
	ComData.strTextName = _T("天子");
	m_pUserComboBox->AddComboItem(ComData);
	ComData.nImageType = IT_PNG;
	ComData.strImagePath = strSkinDir + _T("SkinImage\\Spice.png");
	ComData.strTextId = _T("4567890");
	ComData.strTextName = _T("有神仙吗");
	m_pUserComboBox->AddComboItem(ComData);
	ComData.nImageType = IT_PNG;
	ComData.strImagePath = strSkinDir + _T("SkinImage\\Cartoon.png");
	ComData.strTextId = _T("765837458");
	ComData.strTextName = _T("夜来丑");
	m_pUserComboBox->AddComboItem(ComData);
	strPicPath = strSkinDir + _T("SkinImage\\closed.png");
	m_pUserComboBox->SetCloseButtonImage(BSC_THREE, strPicPath, IT_PNG);

	ComData = m_pUserComboBox->GetSelectData();
	if (ComData.strImagePath.GetLength() > 0)
	{
		m_pUserLogo = m_UiManager.CreateBfMouseMoveStatic(this, CRect(0, 0, 0, 0), WND_ID_LOGON_USER_LOGO, 0, ComData.strImagePath, ComData.nImageType);
	}
	else
	{
		strPicPath = strSkinDir + _T("SkinImage\\Cartoon.png");
		m_pUserLogo = m_UiManager.CreateBfMouseMoveStatic(this, CRect(0, 0, 0, 0), WND_ID_LOGON_USER_LOGO, 0, strPicPath, IT_PNG);
	}
	if (m_pUserLogo == NULL)
	{
		::MessageBox(m_hParent, _T("初始化 m_pUserLogo 失败，程序无法启动！"), MSG_TITLE, MB_OK | MB_ICONSTOP);
		::PostMessage(m_hParent, WM_CLOSE, NULL, NULL);
		return;
	}
	m_pUserLogo->SetDrawImageWane(20);

	m_pCheckBox1 = m_UiManager.CreateBfCheckBox(this, CRect(0, 0, 0, 0), 0, 0, _T(""), IT_PNG);
	if (m_pCheckBox1 == NULL)
	{
		::MessageBox(m_hParent, _T("初始化 m_pCheckBox1 失败，程序无法启动！"), MSG_TITLE, MB_OK | MB_ICONSTOP);
		::PostMessage(m_hParent, WM_CLOSE, NULL, NULL);
		return;
	}
	m_pCheckBox1->SetWindowText(_T("记住密码"));

	m_pCheckBox2 = m_UiManager.CreateBfCheckBox(this, CRect(0, 0, 0, 0), 0, 0, _T(""), IT_PNG);
	if (m_pCheckBox2 == NULL)
	{
		::MessageBox(m_hParent, _T("初始化 m_pCheckBox2 失败，程序无法启动！"), MSG_TITLE, MB_OK | MB_ICONSTOP);
		::PostMessage(m_hParent, WM_CLOSE, NULL, NULL);
		return;
	}
	m_pCheckBox2->SetWindowText(_T("自动登录"));

	m_pLogonBtn = m_UiManager.CreateBfDrawButton(this, CRect(0, 0, 0, 0), WND_ID_LOGON_BTN);
	if (m_pLogonBtn == NULL)
	{
		::MessageBox(m_hParent, _T("初始化 m_pLogonBtn 失败，程序无法启动！"), MSG_TITLE, MB_OK | MB_ICONSTOP);
		::PostMessage(m_hParent, WM_CLOSE, NULL, NULL);
		return;
	}
	m_pLogonBtn->SetWindowText(_T("登录"));

	CSysUnit::SetWindowToTransparence(m_hWnd, true);
}

LRESULT CGroundGlassDlg::OnSize(HDWP hWinPoslnfo, WPARAM wParam, LPARAM lParam)
{
	int cx = LOWORD(lParam); 
	int cy = HIWORD(lParam);

	if (m_pStatic != NULL)
	{
		//m_pStatic->MoveWindow(CRect(0, 0, cx, cy), hWinPoslnfo);
	}

	if (m_pUserLogo != NULL)
	{
		int nH = 80, nW = 80;
		int nLeft = (cx - nW) / 2;
		int nTop = 130;

		m_pUserLogo->MoveWindow(CRect(nLeft, nTop, nLeft + nW, nTop + nH), hWinPoslnfo);
	}

	if (m_pLink1 != NULL && m_pLink2 != NULL && m_pLink3 != NULL && m_pLink4 != NULL
	&& m_pL1 != NULL && m_pL2 != NULL && m_pYdLogo != NULL)
	{
		CRect LRect1(0, 0, 0, 0), LRect2(0, 0, 0, 0), LRect3(0, 0, 0, 0), LRect4(0, 0, 0, 0);
		CRect LR1(0, 0, 0, 0), LR2(0, 0, 0, 0), YdRect(0, 0, 0, 0);

		int nW = 60, nH = 15;

		LRect1.left = cx / 2 - nW + 10;
		LRect1.right = LRect1.left + nW;
		LRect1.top = cy - 50;
		LRect1.bottom = LRect1.top + nH;
		m_pLink1->MoveWindow(LRect1, hWinPoslnfo);

		CResImage *pRes = m_pYdLogo->GetResImage();
		if (pRes != NULL)
		{
			Image *pImage = pRes->GetImage();
			if (pImage != NULL)
			{
				int nHL = pImage->GetHeight();
				int nWL = pImage->GetWidth();

				YdRect.top = LRect1.bottom - 5;
				YdRect.bottom = YdRect.top + nHL;
				YdRect.right = LRect1.left - 15;
				YdRect.left = YdRect.right - nWL;
				m_pYdLogo->MoveWindow(YdRect, hWinPoslnfo);
			}
		}

		LR1 = LRect1;
		LR1.left = LRect1.right;
		LR1.right = LR1.left + 5;
		m_pL1->MoveWindow(LR1, hWinPoslnfo);

		LRect2 = LRect1;
		LRect2.left = LRect1.right + 20;
		LRect2.right = LRect2.left + nW;
		m_pLink2->MoveWindow(LRect2, hWinPoslnfo);

		LRect3 = LRect1;
		LRect3.top = LRect1.bottom + 10;
		LRect3.bottom = LRect3.top + nH;
		m_pLink3->MoveWindow(LRect3, hWinPoslnfo);

		LR2 = LRect3;
		LR2.left = LRect3.right;
		LR2.right = LR2.left + 5;
		m_pL2->MoveWindow(LR2, hWinPoslnfo);

		LRect4 = LRect2;
		LRect4.top = LRect2.bottom + 10;
		LRect4.bottom = LRect4.top + nH;
		m_pLink4->MoveWindow(LRect4, hWinPoslnfo);
	}

	if (m_pPassWordEdit != NULL && m_pUserComboBox != NULL && m_pCheckBox1 != NULL && m_pCheckBox2 != NULL)
	{
		CRect EditRect(0, 0, 0, 0), UserRect(0, 0, 0, 0), Ch1(0, 0, 0, 0), Ch2(0, 0, 0, 0);

		int nW = 185, nH = 21;

		EditRect.left = (cx - nW) / 2;
		EditRect.right = EditRect.left + nW;
		EditRect.top = 275;
		EditRect.bottom = EditRect.top + nH;
		m_pPassWordEdit->MoveWindow(EditRect, hWinPoslnfo);

		UserRect = EditRect;
		UserRect.bottom = EditRect.top - 10;
		UserRect.top = UserRect.bottom - nH;
		m_pUserComboBox->MoveWindow(UserRect, hWinPoslnfo);

		nW = 75;
		nH = 15;
		Ch1.left = EditRect.left + 2;
		Ch1.right = Ch1.left + nW;
		Ch1.top = EditRect.bottom + 8;
		Ch1.bottom = Ch1.top + nH;
		m_pCheckBox1->MoveWindow(Ch1, hWinPoslnfo);

		Ch2 = Ch1;
		Ch2.right = EditRect.right;
		Ch2.left = Ch2.right - Ch1.Width();
		m_pCheckBox2->MoveWindow(Ch2, hWinPoslnfo);
	}

	if (m_pLogonBtn != NULL)
	{
		CRect LogonRect(0, 0, 0, 0);

		int nW = 80, nH = 25;
		LogonRect.top = 350;
		LogonRect.bottom = LogonRect.top + nH;
		LogonRect.left = (cx - nW) / 2;
		LogonRect.right = LogonRect.left + nW;

		m_pLogonBtn->MoveWindow(LogonRect, hWinPoslnfo);
	}

	RedrawWindow();
	return __base_super::OnSize(hWinPoslnfo, wParam, lParam);;
}

// 鼠标左键按下消息
void CGroundGlassDlg::DUI_OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	if (wParam == WND_ID_LOGON_USER_COMBO_BOX)
	{
		if (m_pUserComboBox != NULL && m_pUserLogo != NULL)
		{
			COMBO_DATA &ComData = m_pUserComboBox->GetSelectData();
			m_pUserLogo->SetBkgndImage(0, ComData.strImagePath, ComData.nImageType);
			m_pUserLogo->RedrawWindow();
		}
	}
}

// 鼠标左键抬起消息
void CGroundGlassDlg::DUI_OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	if (wParam == WND_ID_LOGON_BTN)
	{
		wParam = DWM_SYS_CMD_CLOSE;
	}
	else if (wParam == WND_ID_LOGON_LINK_1 || wParam == WND_ID_LOGON_LINK_2
		|| wParam == WND_ID_LOGON_LINK_3 || wParam == WND_ID_LOGON_LINK_4)
	{
		ShellExecute(0, _T("open"), _T("http://fangshunbao.blog.sohu.com/"), NULL, NULL, SW_SHOWMAXIMIZED);
	}

	__base_super::DUI_OnLButtonUp(wParam, lParam);
}

// 鼠标左键双击消息
void CGroundGlassDlg::DUI_OnLButtonDblClk(WPARAM wParam, LPARAM lParam)
{
	__base_super::DUI_OnLButtonDblClk(wParam, lParam);
}

// 鼠标进入窗口
void CGroundGlassDlg::DUI_OnMouseHover(WPARAM wParam, LPARAM lParam)
{
	__base_super::DUI_OnMouseHover(wParam, lParam);

	if (wParam == WND_ID_LOGON_USER_LOGO)
	{
		::PostMessage(m_hParent, WM_CLOSE, NULL, NULL);
	}
}

// 鼠标离开窗口
void CGroundGlassDlg::DUI_OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	__base_super::DUI_OnMouseLeave(wParam, lParam);

	if (wParam == WND_ID_LOGON_USER_LOGO)
	{
	}
}

LRESULT CGroundGlassDlg::OnMoving(WPARAM wParam, LPARAM lParam)
{
	LRESULT lRet = __base_super::OnMoving(wParam, lParam);
	this->RedrawWindow();

//	HDC hDc = ::GetDC(this->GetSafeHandle());
//	OnPaint(hDc);
//	::ReleaseDC(this->GetSafeHandle(), hDc);

	return lRet;
}

LRESULT CGroundGlassDlg::OnSizing(WPARAM wParam, LPARAM lParam)
{
	LRESULT lRet = __base_super::OnSizing(wParam, lParam);
	this->RedrawWindow();

//	HDC hDc = ::GetDC(this->GetSafeHandle());
//	OnPaint(hDc);
//	::ReleaseDC(this->GetSafeHandle(), hDc);

	return lRet;
}

LRESULT CGroundGlassDlg::OnTimer(WPARAM wParam, LPARAM lParam)
{
	if (m_nTimer == (int)wParam)
		this->RedrawWindow();

	return __base_super::OnTimer(wParam, lParam);
}

void CGroundGlassDlg::OnPaint(HDC hPaintDc)
{
	CSysUnit::SetWindowToTransparence(m_hWnd, true);

	CRect WndRect = this->GetClientRect();
	m_BmpDc.Create(WndRect.Width(), WndRect.Height(), false);

	HDC hMemoryDC = m_BmpDc.GetSafeHdc();
	HBITMAP hMemoryBitmap = m_BmpDc.GetBmpHandle();
	if (hMemoryDC != NULL && hMemoryBitmap != NULL)
	{
		Graphics DoGrap(hMemoryDC);

		SolidBrush FillBrush(Color(255, 0, 255, 255));
		DoGrap.FillRectangle(&FillBrush, 0, 0, WndRect.Width(), WndRect.Height());

//////////////////////////////////////////////////////////////////////////

		WndRect = this->GetWindowRect();
		CUiMethod::GetScreenBitmap(hMemoryDC, WndRect);

//		CGaussBlur::GaussIIRBlurImage((BYTE *)m_BmpDc.GetBits(), m_BmpDc.GetDcSize().cx, m_BmpDc.GetDcSize().cy,
//			32, 6, 6);




//////////////////////////////////////////////////////////////////////////

		// 开始画图
		m_pUiManager->OnPaint(hMemoryDC, WndRect);

		WndRect = this->GetClientRect();
		DrawFetionBkgndLine(hMemoryDC, WndRect);

		{
			WndRect = this->GetWindowRect();
			POINT ptWinPos = {WndRect.left, WndRect.top};
			POINT ptSrc = {0, 0};
			SIZE sizeWindow = {WndRect.Width(), WndRect.Height()};
			::UpdateLayeredWindow(m_hWnd, hPaintDc, &ptWinPos, &sizeWindow, hMemoryDC, &ptSrc, 0, &m_Blend, ULW_ALPHA);
		}

		{
			//	CSysUnit::SetWindowToTransparence(m_hWnd, false);
			//	::BitBlt(hPaintDc, 0, 0, WndRect.Width(), WndRect.Height(),
			//		hMemoryDC, 0, 0, SRCCOPY);
		}
	}
}

BOOL CGroundGlassDlg::DrawHBITMAP(HDC hDstDc, CRect DstRect, HBITMAP hSrcBmp)
{
	BOOL bRet = FALSE;

	if (hSrcBmp != NULL && hDstDc != NULL)
	{
		HDC hMemoryDC = ::CreateCompatibleDC(hDstDc);
		if (hMemoryDC != NULL)
		{
			::SelectObject(hMemoryDC, hSrcBmp);

			::BitBlt(hDstDc, DstRect.left, DstRect.top, DstRect.Width(), DstRect.Height(), hMemoryDC, 0, 0, SRCCOPY);

			bRet = TRUE;
			::DeleteDC(hMemoryDC);
		}
	}

	return bRet;
}
