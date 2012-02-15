
#include "stdafx.h"
#include "WindowResize.h"
#include "IWindowBaseImpl.h"
#include "..\..\Inc\UiFeatureDefs.h"

// 移动的像素值
#define MOVE_PIX							(4)

CWindowResize::CWindowResize()
{
	m_pWindowBase = NULL;
	INIT_RECT(m_OldRect);
	m_nNcHitTest = HTNOWHERE;
	m_bSupLayered = false;

	m_bStretching = false;
	m_nLeftSpace = 0;
	m_nRightSpace = 0;
	m_nTopSpace = 0;
	m_nBottomSpace = 0;

	m_bUseSize = false;
	m_nMaxWidth = 0;
	m_nMaxHeight = 0;
	m_nMinWidth = 0;
	m_nMinHeight = 0;
}

CWindowResize::~CWindowResize()
{
}

bool CWindowResize::IsInResize()
{
	return (m_nNcHitTest != HTNOWHERE);
}

void CWindowResize::InitResizeInfo(IWindowBaseImpl *pWndBase, IPropertyBool *pPropBase_Layered,
								   IPropertyBool *pPropSize_Enable,
								   IPropertyInt *pPropSize_MaxWidth, IPropertyInt *pPropSize_MaxHeight,
								   IPropertyInt *pPropSize_MinWidth, IPropertyInt *pPropSize_MinHeight,
								   IPropertyBool *pPropStretching_Enable,
								   IPropertyInt *pPropStretching_LeftSpace, IPropertyInt *pPropStretching_RightSpace,
								   IPropertyInt *pPropStretching_TopSpace, IPropertyInt *pPropStretching_BottomSpace)
{
	if (pWndBase == NULL || !IS_SAFE_HANDLE(pWndBase->GetSafeHandle()) || !::IsWindow(pWndBase->GetSafeHandle()) || pPropBase_Layered == NULL)
		return;

	if (pPropSize_Enable == NULL || pPropSize_MaxWidth == NULL || pPropSize_MaxHeight == NULL || pPropSize_MinWidth == NULL || pPropSize_MinHeight == NULL)
		return;

	if (pPropStretching_Enable == NULL || pPropStretching_LeftSpace == NULL || pPropStretching_RightSpace == NULL || pPropStretching_TopSpace == NULL || pPropStretching_BottomSpace == NULL)
		return;

	m_pWindowBase = pWndBase;

	m_bSupLayered = pPropBase_Layered->GetValue();

	m_bStretching = pPropStretching_Enable->GetValue();
	m_nLeftSpace = pPropStretching_LeftSpace->GetValue();
	m_nRightSpace = pPropStretching_RightSpace->GetValue();
	m_nTopSpace = pPropStretching_TopSpace->GetValue();
	m_nBottomSpace = pPropStretching_BottomSpace->GetValue();

	m_bUseSize = pPropSize_Enable->GetValue();
	m_nMaxWidth = pPropSize_MaxWidth->GetValue();
	m_nMaxHeight = pPropSize_MaxHeight->GetValue();
	m_nMinWidth = pPropSize_MinWidth->GetValue();
	m_nMinHeight = pPropSize_MinHeight->GetValue();
}

// 鼠标是否移动到了窗口可以进行拉伸操作的边缘
int CWindowResize::MouseMoveInWindowFrame(POINT pt)
{
	if (!m_bStretching || m_pWindowBase == NULL || !m_bStretching)
		return HTNOWHERE;

	RECT wndRct = m_pWindowBase->GetClientRect();

	// 先判断四角
	// 左上角
	if (m_nLeftSpace > 0 && m_nTopSpace > 0)
	{
		if (pt.x <= m_nLeftSpace && pt.y <= m_nTopSpace)
		{
			// 双箭头指向西北和东南
			m_pWindowBase->SetWindowCursor(UF_IDC_SIZENWSE);
			return HTTOPLEFT;
		}
	}

	// 左下角
	if (m_nLeftSpace > 0 && m_nBottomSpace > 0)
	{
		if (pt.x <= m_nLeftSpace && pt.y >= (RECT_HEIGHT(wndRct) - m_nBottomSpace))
		{
			// 双箭头指向东北和西南
			m_pWindowBase->SetWindowCursor(UF_IDC_SIZENESW);
			return HTBOTTOMLEFT;
		}
	}

	// 右上角
	if (m_nRightSpace > 0 && m_nTopSpace > 0)
	{
		if (pt.x >= (RECT_WIDTH(wndRct) - m_nRightSpace) && pt.y <= m_nTopSpace)
		{
			// 双箭头指向东北和西南
			m_pWindowBase->SetWindowCursor(UF_IDC_SIZENESW);
			return HTTOPRIGHT;
		}
	}

	// 右下角
	if (m_nRightSpace > 0 && m_nBottomSpace > 0)
	{
		if (pt.x >= (RECT_WIDTH(wndRct) - m_nRightSpace) && pt.y >= (RECT_HEIGHT(wndRct) - m_nBottomSpace))
		{
			// 双箭头指向西北和东南
			m_pWindowBase->SetWindowCursor(UF_IDC_SIZENWSE);
			return HTBOTTOMRIGHT;
		}
	}

	// 再判断四边
	// 左边
	if (m_nLeftSpace > 0 && pt.x <= m_nLeftSpace)
	{
		// 双箭头指向东西
		m_pWindowBase->SetWindowCursor(UF_IDC_SIZEWE);
		return HTLEFT;
	}

	// 右边
	if (m_nRightSpace > 0 && pt.x >= (RECT_WIDTH(wndRct) - m_nRightSpace))
	{
		// 双箭头指向东西
		m_pWindowBase->SetWindowCursor(UF_IDC_SIZEWE);
		return HTRIGHT;
	}

	// 上边
	if (m_nTopSpace > 0 && pt.y <= m_nTopSpace)
	{
		// 双箭头指向南北
		m_pWindowBase->SetWindowCursor(UF_IDC_SIZENS);
		return HTTOP;
	}

	// 下边
	if (m_nBottomSpace > 0 && pt.y >= (RECT_HEIGHT(wndRct) - m_nBottomSpace))
	{
		// 双箭头指向南北
		m_pWindowBase->SetWindowCursor(UF_IDC_SIZENS);
		return HTBOTTOM;
	}

	return HTNOWHERE;
}

bool CWindowResize::ResizeInLayeredWindow(RECT &OutOldRect, RECT &OutNewRect)
{
	INIT_RECT(OutOldRect);
	INIT_RECT(OutNewRect);

	if (m_pWindowBase == NULL || !m_bSupLayered || m_nNcHitTest == HTNOWHERE || !m_bStretching)
		return false;

	RECT MoveRect;
	memcpy(&MoveRect, &m_OldRect, sizeof(RECT));
	memcpy(&OutOldRect, &m_OldRect, sizeof(RECT));
	memcpy(&OutNewRect, &m_OldRect, sizeof(RECT));

	bool bRet = false;
	POINT CurMousePos, OldPt;

	CurMousePos.x = CurMousePos.y = OldPt.x = OldPt.y = 0;
	::GetCursorPos(&CurMousePos);

	if (HTLEFT == m_nNcHitTest)
	{
		OldPt.x = m_OldRect.left;
		if ((OldPt.x - CurMousePos.x >= MOVE_PIX) || (CurMousePos.x - OldPt.x >= MOVE_PIX))
		{
			MoveRect.left = CurMousePos.x;
			bRet = true;
		}
	}
	else if (HTTOPLEFT == m_nNcHitTest)
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
	else if (HTRIGHT == m_nNcHitTest)
	{
		OldPt.x = m_OldRect.right;
		if ((OldPt.x - CurMousePos.x >= MOVE_PIX) || (CurMousePos.x - OldPt.x >= MOVE_PIX))
		{
			MoveRect.right = CurMousePos.x;
			bRet = true;
		}
	}
	else if (HTTOP == m_nNcHitTest)
	{
		OldPt.y = m_OldRect.top;
		if ((OldPt.y - CurMousePos.y >= MOVE_PIX) || (CurMousePos.y - OldPt.y >= MOVE_PIX))
		{
			MoveRect.top = CurMousePos.y;
			bRet = true;
		}
	}
	else if (HTBOTTOM == m_nNcHitTest)
	{
		OldPt.y = m_OldRect.bottom;
		if ((OldPt.y - CurMousePos.y >= MOVE_PIX) || (CurMousePos.y - OldPt.y >= MOVE_PIX))
		{
			MoveRect.bottom = CurMousePos.y;
			bRet = true;
		}
	}
	else if (HTBOTTOMLEFT == m_nNcHitTest)
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
	else if (HTTOPRIGHT == m_nNcHitTest)
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
	else if (HTBOTTOMRIGHT == m_nNcHitTest)
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
		if (m_bUseSize)
		{
			int nWidth = MoveRect.right - MoveRect.left;
			int nHeight = MoveRect.bottom - MoveRect.top;
			// 边界判断
			if (HTLEFT == m_nNcHitTest || HTTOPLEFT == m_nNcHitTest || HTBOTTOMLEFT == m_nNcHitTest)
			{
				if (m_nMaxWidth != -1 && nWidth > m_nMaxWidth)
					MoveRect.left = MoveRect.right - m_nMaxWidth;

				if (m_nMinWidth != -1 && nWidth < m_nMinWidth)
					MoveRect.left = MoveRect.right - m_nMinWidth;
			}

			if (HTRIGHT == m_nNcHitTest || HTTOPRIGHT == m_nNcHitTest || HTBOTTOMRIGHT == m_nNcHitTest)
			{
				if (m_nMaxWidth != -1 && nWidth > m_nMaxWidth)
					MoveRect.right = MoveRect.left + m_nMaxWidth;

				if (m_nMinWidth != -1 && nWidth < m_nMinWidth)
					MoveRect.right = MoveRect.left + m_nMinWidth;
			}

			if (HTTOP == m_nNcHitTest || HTTOPLEFT == m_nNcHitTest || HTTOPRIGHT == m_nNcHitTest)
			{
				if (m_nMaxHeight != -1 && nHeight > m_nMaxHeight)
					MoveRect.top = MoveRect.bottom - m_nMaxHeight;

				if (m_nMinHeight != -1 && nHeight < m_nMinHeight)
					MoveRect.top = MoveRect.bottom - m_nMinHeight;
			}

			if (HTBOTTOM == m_nNcHitTest || HTBOTTOMLEFT == m_nNcHitTest || HTBOTTOMRIGHT == m_nNcHitTest)
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
				memcpy(&OutNewRect, &m_OldRect, sizeof(RECT));
			}
		}
		else
		{
			m_OldRect = MoveRect;
			memcpy(&OutNewRect, &m_OldRect, sizeof(RECT));
		}
	}

	return bRet;
}

bool CWindowResize::BeginResizeInLayeredWindow()
{
	if (m_pWindowBase == NULL || !m_bSupLayered || !m_bStretching)
		return false;

	POINT pt;
	pt.x = pt.y = 0;
	::ScreenToClient(m_pWindowBase->GetSafeHandle(), &pt);

	m_nNcHitTest = MouseMoveInWindowFrame(pt);
	if (m_nNcHitTest == HTNOWHERE)
		return false;

	::SetCapture(m_pWindowBase->GetSafeHandle());
	::GetWindowRect(m_pWindowBase->GetSafeHandle(), &m_OldRect);
	return true;
}

void CWindowResize::EndResizeInLayeredWindow()
{
	if (m_pWindowBase == NULL || !m_bSupLayered || m_nNcHitTest != HTNOWHERE || !m_bStretching)
		return;

	::ReleaseCapture();
	INIT_RECT(m_OldRect);
	m_nNcHitTest = HTNOWHERE;
	m_pWindowBase->SetWindowCursor(UF_IDC_ARROW);
}
