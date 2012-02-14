
#include "stdafx.h"
#include "WindowResize.h"
#include "IWindowBaseImpl.h"

// 移动的像素值
#define MOVE_PIX						(4)

CWindowResize::CWindowResize()
{
	m_pWindowBase = NULL;
	m_OldRect.left = m_OldRect.right = m_OldRect.bottom = m_OldRect.top = 0;
	m_uNcHitTest = -1;

	m_nMaxWidth = -1;
	m_nMaxHeight = -1;
	m_nMinWidth = -1;
	m_nMinHeight = -1;
}

CWindowResize::~CWindowResize()
{
	m_pWindowBase = NULL;
	m_OldRect.left = m_OldRect.right = m_OldRect.bottom = m_OldRect.top = 0;
	m_uNcHitTest = -1;
}

UINT CWindowResize::GetHitType()
{
	return m_uNcHitTest;
}

bool CWindowResize::IsInResize()
{
	return (m_pWindowBase != NULL);
}

VOID CWindowResize::InitResizeInfo(IWindowBaseImpl *pWndBase, UINT uNcHitTest, int nMaxWidth, int nMaxHeight, int nMinWidth, int nMinHeight)
{
	if (m_pWindowBase == NULL && pWndBase != NULL && pWndBase->GetSafeHwnd() != NULL && ::IsWindow(pWndBase->GetSafeHwnd()))
	{
		::SetCapture(pWndBase->GetSafeHwnd());
		m_pWindowBase = pWndBase;
		m_uNcHitTest = uNcHitTest;
		::GetWindowRect(pWndBase->GetSafeHwnd(), &m_OldRect);

		m_nMaxWidth = nMaxWidth;
		m_nMaxHeight = nMaxHeight;
		m_nMinWidth = nMinWidth;
		m_nMinHeight = nMinHeight;
	}
}

VOID CWindowResize::UnInit()
{
	if (m_pWindowBase != NULL && m_pWindowBase->GetSafeHwnd() != NULL && ::IsWindow(m_pWindowBase->GetSafeHwnd()))
	{
		::ReleaseCapture();
		m_pWindowBase = NULL;
		m_uNcHitTest = -1;
		m_OldRect.left = m_OldRect.right = m_OldRect.bottom = m_OldRect.top = 0;

		m_nMaxWidth = -1;
		m_nMaxHeight = -1;
		m_nMinWidth = -1;
		m_nMinHeight = -1;
	}
}

bool CWindowResize::MoveWindowToRect(RECT &MoveRect)
{
	bool bRet = false;
	if (m_pWindowBase != NULL && m_pWindowBase->GetSafeHwnd() != NULL && ::IsWindow(m_pWindowBase->GetSafeHwnd()))
	{
		memcpy(&MoveRect, &m_OldRect, sizeof(RECT));

		POINT CurMousePos;
		::GetCursorPos(&CurMousePos);

		POINT OldPt;
		if (HTLEFT == m_uNcHitTest)
		{
			OldPt.x = m_OldRect.left;
			if ((OldPt.x - CurMousePos.x >= MOVE_PIX) || (CurMousePos.x - OldPt.x >= MOVE_PIX))
			{
				MoveRect.left = CurMousePos.x;
				bRet = true;
			}
		}
		else if (HTTOPLEFT == m_uNcHitTest)
		{
			OldPt.x = m_OldRect.left;
			OldPt.y = m_OldRect.top;
			if ((OldPt.x - CurMousePos.x >= MOVE_PIX) || (CurMousePos.x - OldPt.x >= MOVE_PIX) ||
				(OldPt.y - CurMousePos.y >= MOVE_PIX) || (CurMousePos.y - OldPt.y >= MOVE_PIX))
			{
				MoveRect.left = CurMousePos.x;
				MoveRect.top = CurMousePos.y;
				bRet = true;
			}
		}
		else if (HTRIGHT == m_uNcHitTest)
		{
			OldPt.x = m_OldRect.right;
			if ((OldPt.x - CurMousePos.x >= MOVE_PIX) || (CurMousePos.x - OldPt.x >= MOVE_PIX))
			{
				MoveRect.right = CurMousePos.x;
				bRet = true;
			}
		}
		else if (HTTOP == m_uNcHitTest)
		{
			OldPt.y = m_OldRect.top;
			if ((OldPt.y - CurMousePos.y >= MOVE_PIX) || (CurMousePos.y - OldPt.y >= MOVE_PIX))
			{
				MoveRect.top = CurMousePos.y;
				bRet = true;
			}
		}
		else if (HTBOTTOM == m_uNcHitTest)
		{
			OldPt.y = m_OldRect.bottom;
			if ((OldPt.y - CurMousePos.y >= MOVE_PIX) || (CurMousePos.y - OldPt.y >= MOVE_PIX))
			{
				MoveRect.bottom = CurMousePos.y;
				bRet = true;
			}
		}
		else if (HTBOTTOMLEFT == m_uNcHitTest)
		{
			OldPt.x = m_OldRect.left;
			OldPt.y = m_OldRect.bottom;
			if ((OldPt.x - CurMousePos.x >= MOVE_PIX) || (CurMousePos.x - OldPt.x >= MOVE_PIX) ||
				(OldPt.y - CurMousePos.y >= MOVE_PIX) || (CurMousePos.y - OldPt.y >= MOVE_PIX))
			{
				MoveRect.left = CurMousePos.x;
				MoveRect.bottom = CurMousePos.y;
				bRet = true;
			}
		}
		else if (HTTOPRIGHT == m_uNcHitTest)
		{
			OldPt.x = m_OldRect.right;
			OldPt.y = m_OldRect.top;
			if ((OldPt.x - CurMousePos.x >= MOVE_PIX) || (CurMousePos.x - OldPt.x >= MOVE_PIX) ||
				(OldPt.y - CurMousePos.y >= MOVE_PIX) || (CurMousePos.y - OldPt.y >= MOVE_PIX))
			{
				MoveRect.right = CurMousePos.x;
				MoveRect.top = CurMousePos.y;
				bRet = true;
			}
		}
		else if (HTBOTTOMRIGHT == m_uNcHitTest)
		{
			OldPt.x = m_OldRect.right;
			OldPt.y = m_OldRect.bottom;
			if ((OldPt.x - CurMousePos.x >= MOVE_PIX) || (CurMousePos.x - OldPt.x >= MOVE_PIX) ||
				(OldPt.y - CurMousePos.y >= MOVE_PIX) || (CurMousePos.y - OldPt.y >= MOVE_PIX))
			{
				MoveRect.right = CurMousePos.x;
				MoveRect.bottom = CurMousePos.y;
				bRet = true;
			}
		}

		if (bRet)
		{
			int nWidth = MoveRect.right - MoveRect.left;
			int nHeight = MoveRect.bottom - MoveRect.top;
			// 边界判断
			if (HTLEFT == m_uNcHitTest || HTTOPLEFT == m_uNcHitTest || HTBOTTOMLEFT == m_uNcHitTest)
			{
				if (m_nMaxWidth != -1 && nWidth > m_nMaxWidth)
					MoveRect.left = MoveRect.right - m_nMaxWidth;

				if (m_nMinWidth != -1 && nWidth < m_nMinWidth)
					MoveRect.left = MoveRect.right - m_nMinWidth;
			}

			if (HTRIGHT == m_uNcHitTest || HTTOPRIGHT == m_uNcHitTest || HTBOTTOMRIGHT == m_uNcHitTest)
			{
				if (m_nMaxWidth != -1 && nWidth > m_nMaxWidth)
					MoveRect.right = MoveRect.left + m_nMaxWidth;

				if (m_nMinWidth != -1 && nWidth < m_nMinWidth)
					MoveRect.right = MoveRect.left + m_nMinWidth;
			}

			if (HTTOP == m_uNcHitTest || HTTOPLEFT == m_uNcHitTest || HTTOPRIGHT == m_uNcHitTest)
			{
				if (m_nMaxHeight != -1 && nHeight > m_nMaxHeight)
					MoveRect.top = MoveRect.bottom - m_nMaxHeight;

				if (m_nMinHeight != -1 && nHeight < m_nMinHeight)
					MoveRect.top = MoveRect.bottom - m_nMinHeight;
			}

			if (HTBOTTOM == m_uNcHitTest || HTBOTTOMLEFT == m_uNcHitTest || HTBOTTOMRIGHT == m_uNcHitTest)
			{
				if (m_nMaxHeight != -1 && nHeight > m_nMaxHeight)
					MoveRect.bottom = MoveRect.top + m_nMaxHeight;

				if (m_nMinHeight != -1 && nHeight < m_nMinHeight)
					MoveRect.bottom = MoveRect.top + m_nMinHeight;
			}

			if (m_OldRect.left == MoveRect.left &&
				m_OldRect.right == MoveRect.right &&
				m_OldRect.top == MoveRect.top &&
				m_OldRect.bottom == MoveRect.bottom)
			{
				bRet = false;
			}
			else
			{
				m_OldRect = MoveRect;
			}
		}
	}
	return bRet;
}
