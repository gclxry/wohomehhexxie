
#include "BfNormalGraduatedButton.h"


CBfNormalGraduatedButton::CBfNormalGraduatedButton(void)
{
}

CBfNormalGraduatedButton::~CBfNormalGraduatedButton(void)
{
}

void CBfNormalGraduatedButton::DrawGraduatedButton(int nDrawSta)
{
	// 外圈
	Pen OutPen(Color(200, 25, 100, 120));
	CRect OutRect(m_WndRect);
	OutRect.right -= 1;
	OutRect.bottom -= 1;
	m_pDoGrap->DrawLine(&OutPen, OutRect.left + 1, OutRect.top, OutRect.right - 1, OutRect.top);
	m_pDoGrap->DrawLine(&OutPen, OutRect.right, OutRect.top + 1, OutRect.right, OutRect.bottom - 1);
	m_pDoGrap->DrawLine(&OutPen, OutRect.left + 1, OutRect.bottom, OutRect.right - 1, OutRect.bottom);
	m_pDoGrap->DrawLine(&OutPen, OutRect.left, OutRect.top + 1, OutRect.left, OutRect.bottom - 1);

	// 内圈
	CRect InRect(OutRect);
	InRect.left += 1;
	InRect.top += 1;
	Point p1(InRect.left, InRect.top - 1), p2(InRect.left, InRect.top + InRect.Height());
	Color col1(200, 255, 255, 255), col2(200, 180, 222, 248);
	LinearGradientBrush lgBrush(p1, p2, col1, col2);
	Pen InPen(&lgBrush);
	m_pDoGrap->DrawRectangle(&InPen, InRect.left, InRect.top, InRect.Width() - 1, InRect.Height() - 1);

	// 最内圈高光
	if (nDrawSta == GRADUATE_STA_LBUTTONDOWN)
	{
		CRect InBRect(InRect);
		InBRect.left += 1;
		InBRect.top += 1;
		InBRect.right -= 1;
		InBRect.bottom -= 1;
		p1 = Point(InBRect.left, InBRect.top + (InBRect.Height() / 2)), p2 = Point(InBRect.left, InBRect.bottom);
		LinearGradientBrush lgBrush1(p1, p2, m_DownColor, m_UpColor);
		m_pDoGrap->FillRectangle(&lgBrush1, InBRect.left, p1.Y + 1, InBRect.Width(), (InBRect.Height() / 2) - 1);
	}
	else if (nDrawSta == GRADUATE_STA_NORMAL)
	{
		CRect InBRect(InRect);
		InBRect.left += 1;
		InBRect.top += 1;
		InBRect.right -= 1;
		InBRect.bottom -= 1;
		p1 = Point(InBRect.left, InBRect.top - 1), p2 = Point(InBRect.left, InBRect.top + (InBRect.Height() / 2));
		LinearGradientBrush lgBrush1(p1, p2, m_UpColor, m_DownColor);
		m_pDoGrap->FillRectangle(&lgBrush1, InBRect.left, InBRect.top, InBRect.Width(), (InBRect.Height() / 2));
	}

	// 四角虚幻
	Color xhColor(50, 50, 50, 50);
	SolidBrush xhBrush(xhColor);
	// 左上角
	CRect JRect(m_WndRect);
	JRect.right = JRect.left + 2;
	JRect.bottom = JRect.top + 2;
	m_pDoGrap->FillRectangle(&xhBrush, JRect.left, JRect.top, JRect.Width(), JRect.Height());
	// 右上角
	JRect = m_WndRect;
	JRect.left = JRect.right - 2;
	JRect.bottom = JRect.top + 2;
	m_pDoGrap->FillRectangle(&xhBrush, JRect.left, JRect.top, JRect.Width(), JRect.Height());
	// 左下角
	JRect = m_WndRect;
	JRect.right = JRect.left + 2;
	JRect.top = JRect.bottom - 2;
	m_pDoGrap->FillRectangle(&xhBrush, JRect.left, JRect.top, JRect.Width(), JRect.Height());
	// 右下角
	JRect = m_WndRect;
	JRect.left = JRect.right - 2;
	JRect.top = JRect.bottom - 2;
	m_pDoGrap->FillRectangle(&xhBrush, JRect.left, JRect.top, JRect.Width(), JRect.Height());
}
