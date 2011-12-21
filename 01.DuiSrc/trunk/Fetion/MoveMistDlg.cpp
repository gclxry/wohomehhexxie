
#include "StdAfx.h"
#include "MoveMistDlg.h"
#include "shobjidl.h"

#define __base_super					CHighEfficiencyDlg


CMoveMistDlg::CMoveMistDlg(HINSTANCE hInstance, HWND hParentWnd, int nIconId)
: __base_super(hInstance, hParentWnd, nIconId)
{
	::CoInitialize(NULL);
	AddBfStyle(BFS_MODAL_DLG);

	m_pUiManager = &m_UiManager;
	m_pBmpDc = NULL;
	m_bIsMoveMistDlg = true;
}

CMoveMistDlg::~CMoveMistDlg(void)
{
}

void CMoveMistDlg::OnCreate()
{
	__base_super::OnCreate();

	// m_Blend是结构体BLENDFUNCTION的对象，用于指定两个DC(画图设备)的融合方式。
	m_Blend.BlendOp = AC_SRC_OVER;
	m_Blend.BlendFlags = 0;
	m_Blend.AlphaFormat = AC_SRC_ALPHA;
	m_Blend.SourceConstantAlpha = 255;

	HidenTaskbar();
}

void CMoveMistDlg::CloseWindow()
{
	m_nCloseAlpha = m_Blend.SourceConstantAlpha = 255;
	m_nCloseTimer = this->SetTimer(25);
}

LRESULT CMoveMistDlg::OnSize(HDWP hWinPoslnfo, WPARAM wParam, LPARAM lParam)
{
	int cx = LOWORD(lParam);
	int cy = HIWORD(lParam);

	CRect WndRect = this->GetClientRect();


	return __base_super::OnSize(hWinPoslnfo, wParam, lParam);
}

void CMoveMistDlg::OnPaint(HDC hPaintDc)
{
	if (m_pBmpDc != NULL && m_pBmpDc->GetSafeHdc() != NULL)
	{
		CSysUnit::SetWindowToTransparence(m_hWnd, true);
		CRect WndRect = this->GetWindowRect();
		POINT ptWinPos = {WndRect.left, WndRect.top};
		POINT ptSrc = {0, 0};
		SIZE sizeWindow = {WndRect.Width(), WndRect.Height()};
		::UpdateLayeredWindow(m_hWnd, hPaintDc, &ptWinPos, &sizeWindow, m_pBmpDc->GetSafeHdc(), &ptSrc, 0, &m_Blend, ULW_ALPHA);
	}
}

LRESULT CMoveMistDlg::OnTimer(WPARAM wParam, LPARAM lParam)
{
	if (m_nCloseTimer == (int)wParam)
	{
		m_nCloseAlpha -= 20;
		if (m_nCloseAlpha <= 0)
		{
			EndThisDialog();
			return 0;
		}
		m_Blend.SourceConstantAlpha = (BYTE)m_nCloseAlpha;
		this->RedrawWindow();
	}
	
	return __base_super::OnTimer(wParam, lParam);
}

void CMoveMistDlg::HidenTaskbar()
{
	HRESULT hr = NULL;
	ITaskbarList* pTaskbarList = NULL;

	hr = CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_INPROC_SERVER, IID_ITaskbarList, (void**)&pTaskbarList);

	if (hr == S_OK && pTaskbarList != NULL)
	{
		pTaskbarList->HrInit();

		::SetWindowLong(m_hWnd, GWL_STYLE, GetWindowLong(m_hWnd, GWL_STYLE) & (~WS_CAPTION));
		::SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE) & (~WS_EX_APPWINDOW));
		::SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_TOOLWINDOW);

		pTaskbarList->DeleteTab(m_hWnd);
		pTaskbarList->Release();
	}
}
