
#include "BfDropDownButton.h"


CBfDropDownButton::CBfDropDownButton(void)
{
}

CBfDropDownButton::~CBfDropDownButton(void)
{
}

void CBfDropDownButton::OnPaint()
{
	DrawMouseMove();
	Normal_Sj();
}

void CBfDropDownButton::Normal_Sj()
{
	CRect SjRect(m_WndRect);	
	SjRect.left += (m_WndRect.Width() - DROP_SJ_W) / 2 + 1;
	SjRect.right = SjRect.left + DROP_SJ_W;
	SjRect.top += (m_WndRect.Height() - DROP_SJ_H) / 2;
	SjRect.bottom = SjRect.top + DROP_SJ_H;

	// 绘制三角形
	GraphicsPath path;
	Point p1(SjRect.left, SjRect.top);
	Point p2(SjRect.right, SjRect.top);
	Point p3(SjRect.left + DROP_SJ_W / 2, SjRect.bottom);
	path.AddLine(p1, p2);
	path.AddLine(p2, p3);
	path.AddLine(p3, p1);
	//创建Region
	Region region(&path);
	//填充区域
	m_pDoGrap->FillRegion(&SolidBrush(Color::Olive), &region);
}

void CBfDropDownButton::DrawMouseMove()
{
	if (IsMouseHover())
	{
		Point p1(m_WndRect.left, m_WndRect.top), p2(m_WndRect.left, m_WndRect.bottom);
		Color col1(150, 194, 239, 253), col2(180, 99, 182, 227);
		LinearGradientBrush lgBrush(p1, p2, col1, col2);
		m_pDoGrap->FillRectangle(&lgBrush, m_WndRect.left, m_WndRect.top, m_WndRect.Width(), m_WndRect.Height());

		Pen LeftPen(Color(192, 192, 192));
		m_pDoGrap->DrawLine(&LeftPen, m_WndRect.left, m_WndRect.top, m_WndRect.left, m_WndRect.bottom);
	}
}

void CBfDropDownButton::OnMouseHover(CPoint point)
{
	CBfButton::OnMouseHover(point);

	DWM_INFO MsgInfo;
	MsgInfo.wParam = m_nWndId;
	MsgInfo.lParam = NULL;

	m_pMsgCtrl->OnDirectUiWindowMsgProc(DWM_MOUSEHOVER, MsgInfo);
}

void CBfDropDownButton::OnMouseLeave(CPoint point)
{
	CBfButton::OnMouseLeave(point);

}
