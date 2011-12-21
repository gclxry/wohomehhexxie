
#include "BfLinkStatic.h"

#pragma warning(disable:4311)

CBfLinkStatic::CBfLinkStatic(void)
{
}

CBfLinkStatic::~CBfLinkStatic(void)
{
}

void CBfLinkStatic::MoveWindow(const CRect &ToRect, HDWP hWinPoslnfo)
{
	CBfStatic::MoveWindow(ToRect, hWinPoslnfo);

//	if (IsReady())
//	{
//		// TBD ��������
//		CRect TextRect = GetWndTextRect();
//		m_WndRect.right = m_WndRect.left + TextRect.Width() + 2;
//	}
}

void CBfLinkStatic::OnPaint()
{
	if (IsMouseHover())
	{
		WND_TEXT NormalInfo;
		WND_TEXT MouseMoveInfo;

		CopyFontInfo(m_WndTextInfo, NormalInfo);
		CopyFontInfo(m_WndTextInfo, MouseMoveInfo);
		MouseMoveInfo.FStyle = (FontStyle)(FontStyleUnderline | MouseMoveInfo.FStyle);
		MouseMoveInfo.TextColor = Color(254, 255, 0, 0);
		CopyFontInfo(MouseMoveInfo, m_WndTextInfo);

		CBfStatic::OnPaint();

		CopyFontInfo(NormalInfo, m_WndTextInfo);
	}
	else
	{
		CBfStatic::OnPaint();
	}
}

void CBfLinkStatic::CopyFontInfo(WND_TEXT &From, WND_TEXT &To)
{
	To.strFontName = From.strFontName;
	To.nFontHeight = From.nFontHeight;
	To.FStyle = From.FStyle;
	To.TextColor = From.TextColor;
	To.strText = From.strText;
	To.TextRectF = From.TextRectF;
}

void CBfLinkStatic::OnMouseHover(CPoint point)
{
	if (AllowMouseMoveMsg())
	{
		// �������Ӱ�ť��������ֵ���״
		::SetClassLong(m_hParent, GCL_HCURSOR, (LONG)::LoadCursor(NULL, IDC_HAND));
		this->RedrawWindow();
	}
}

void CBfLinkStatic::OnMouseLeave(CPoint point)
{
	if (AllowMouseMoveMsg())
	{
		// �˳������ڣ����ָ�Ϊ������״
		::SetClassLong(m_hParent, GCL_HCURSOR, (LONG)::LoadCursor(NULL, IDC_ARROW));
		this->RedrawWindow();
	}
}

void CBfLinkStatic::OnLButtonUp(CPoint point)
{
	if (AllowMouseDownMsg())
	{
		if (!PtInRect(&m_WndRect, point))
		{
			OnMouseLeave(point);
		}
	}
}

void CBfLinkStatic::SetMouseActive(bool bIsActive)
{
	if (bIsActive)
	{
		m_dwWndAttr |= DWP_MSG_MOUSEDOWN;
		m_dwWndAttr |= DWP_MSG_MOUSEMOUSE;
	}
	else
	{
		m_dwWndAttr &= ~DWP_MSG_MOUSEDOWN;
		m_dwWndAttr &= ~DWP_MSG_MOUSEMOUSE;
	}
}
