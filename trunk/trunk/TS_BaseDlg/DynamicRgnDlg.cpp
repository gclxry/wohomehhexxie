
#include "DynamicRgnDlg.h"

#define __base_super					CHighEfficiencyDlg

CDynamicRgnDlg::CDynamicRgnDlg(HINSTANCE hInstance, HWND hParentWnd, int nIconId)
: CHighEfficiencyDlg(hInstance, hParentWnd, nIconId)
{
	m_pUiManager = NULL;
}

CDynamicRgnDlg::~CDynamicRgnDlg(void)
{
}

LRESULT CDynamicRgnDlg::OnNcHitTest(WPARAM wParam, LPARAM lParam)
{
	if (IsSetBfStyle(BFS_CAN_DRAW) && IsReady())
	{
		CPoint point(LOWORD(lParam), HIWORD(lParam));

		int nCheckPos = 5;
		int nRDPos = nCheckPos * 2;
		CRect WndRect(0, 0, 0, 0);
		::GetWindowRect(m_hWnd, &WndRect);

		if(point.x >= WndRect.right - nRDPos && point.y >= WndRect.bottom - nRDPos)
		{
			// ���½�
			return HTBOTTOMRIGHT;
		}
		else if(point.x >= WndRect.right - nRDPos && point.y <= WndRect.top + nRDPos)
		{
			// ���Ͻ�
			return HTTOPRIGHT;
		}
		else if(point.x <= WndRect.left + nRDPos && point.y <= WndRect.top + nRDPos)
		{
			// ���Ͻ�
			return HTTOPLEFT;
		}
		else if(point.x <= WndRect.left + nRDPos && point.y >= WndRect.bottom - nRDPos)
		{
			// ���½�
			return HTBOTTOMLEFT;
		}
		else if(point.x >= WndRect.right - nCheckPos)
		{
			// �ұ���
			return HTRIGHT;
		}
		else if(point.x <= WndRect.left + nCheckPos)
		{
			// �����
			return HTLEFT;
		}
		else if(point.y <= WndRect.top + nCheckPos)
		{
			// �ϱ���
			return HTTOP;
		}
		else if(point.y >= WndRect.bottom - nCheckPos)
		{
			// �±���
			return HTBOTTOM;
		}

		return __base_super::OnNcHitTest(wParam, lParam);
	}
	else
	{
		return ::DefWindowProc(m_hWnd, WM_NCHITTEST, wParam, lParam);
	}
}

// ������������Ϣ
void CDynamicRgnDlg::DUI_OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
}

// ������̧����Ϣ
void CDynamicRgnDlg::DUI_OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
}

// ������˫����Ϣ
void CDynamicRgnDlg::DUI_OnLButtonDblClk(WPARAM wParam, LPARAM lParam)
{
}

// �����봰��
void CDynamicRgnDlg::DUI_OnMouseHover(WPARAM wParam, LPARAM lParam)
{

}

// ����뿪����
void CDynamicRgnDlg::DUI_OnMouseLeave(WPARAM wParam, LPARAM lParam)
{

}

void CDynamicRgnDlg::OnCreate()
{
	if (IsReady())
	{
		// ��ʼ������
		m_pUiManager->InitManager(this);
		// ����Ĭ�ϴ�С
		this->CenterWindow(260, 480);
	}
}

void CDynamicRgnDlg::OnPaint(HDC hPaintDc)
{
	if (IsReady())
	{
		CRect WndRect = this->GetClientRect();

		HDC hMemoryDC = ::CreateCompatibleDC(hPaintDc);
		if (hMemoryDC != NULL)
		{
			HBITMAP hMemoryBitmap = ::CreateCompatibleBitmap(hPaintDc, WndRect.Width(), WndRect.Height());
			if (hMemoryBitmap != NULL)
			{
				::SelectObject(hMemoryDC, hMemoryBitmap);

				// ��ʼ��ͼ
				m_pUiManager->OnPaint(hMemoryDC, WndRect);

				::BitBlt(hPaintDc, 0, 0, WndRect.Width(), WndRect.Height(),
					hMemoryDC, 0, 0, SRCCOPY);

				::DeleteObject(hMemoryBitmap);
			}
			::DeleteDC(hMemoryDC);
		}
	}
}
