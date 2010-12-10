
#include "StdAfx.h"
#include "MoveMistDlg.h"

#define __base_super					CHighEfficiencyDlg


CMoveMistDlg::CMoveMistDlg(HINSTANCE hInstance, HWND hParentWnd, int nIconId)
: __base_super(hInstance, hParentWnd, nIconId)
{
//	DeleteBfStyle(BFS_CAN_DRAW);
	AddBfStyle(BFS_MODAL_DLG);
//	DeleteBfStyle(BFS_HAVE_MIN_BTN);
//	DeleteBfStyle(BFS_HAVE_MAX_BTN);

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

	//m_Blend是结构体BLENDFUNCTION的对象，用于指定两个DC(画图设备)的融合方式。
	m_Blend.BlendOp = AC_SRC_OVER;
	m_Blend.BlendFlags = 0;
	m_Blend.AlphaFormat = AC_SRC_ALPHA;
	m_Blend.SourceConstantAlpha = 255;

	// 设置窗体的透明特性
	//CSysUnit::SetWindowToTransparence(m_hWnd, true);
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
//	CSysUnit::SetWindowToTransparence(m_hWnd, true);

	if (m_pBmpDc != NULL && m_pBmpDc->GetSafeHdc() != NULL)
	{
		CRect WndRect = this->GetClientRect();
		::BitBlt(hPaintDc, 0, 0, WndRect.Width(), WndRect.Height(),
			m_pBmpDc->GetSafeHdc(), 0, 0, SRCCOPY);
	}
}

LRESULT CMoveMistDlg::OnTimer(WPARAM wParam, LPARAM lParam)
{
	return __base_super::OnTimer(wParam, lParam);
}
