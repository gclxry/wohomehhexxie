
#include "BfDrawButton.h"


CBfDrawButton::CBfDrawButton(void)
{
}

CBfDrawButton::~CBfDrawButton(void)
{
}

void CBfDrawButton::OnPaint()
{
	if (IsMouseDown())
	{
		DrawButton(Color(44, 98, 139),
			Color(229, 244, 252), Color(196, 229, 246),
			Color(152, 209, 239), Color(104, 179, 219),
			Color(100, 52, 87, 114), Color(52, 87, 114), RGB(212, 212, 212));
	}
	else
	{
		if (IsMouseHover())
		{
			DrawButton(Color(60, 127, 177),
				Color(234, 246, 253), Color(217, 240, 252),
				Color(190, 230, 253), Color(167, 217, 245),
				Color(100, 105, 150, 184), Color(105, 150, 184), RGB(255, 255, 255));
		}
		else
		{
			DrawButton(Color(112, 112, 112),
				Color(242, 242, 242), Color(235, 235, 235),
				Color(221, 221, 221), Color(207, 207, 207),
				Color(100, 145, 145, 145), Color(145, 145, 145), RGB(255, 255, 255));
		}
	}
}

void CBfDrawButton::DrawButton(Color OutR, Color UpBegin, Color UpEnd, Color DownBegin, Color DownEnd, Color BRColor, Color SRColor, COLORREF PtColor)
{
	CRect WndRect = m_WndRect;
	// 填充背景色
	SolidBrush FillBrush(Color(255, 255, 255));
	m_pDoGrap->FillRectangle(&FillBrush, WndRect.left, WndRect.top, WndRect.Width(), WndRect.Height());

	// 按钮外圈
	Pen OutLine(OutR);
	CRect OutRect(WndRect);
	OutRect.right--;
	OutRect.bottom--;
	RectF GRt = CUiMethod::CRect2RectF(OutRect);
	m_pDoGrap->DrawRectangle(&OutLine, GRt);

	// 上半部分高光
	CRect UpHRect(WndRect);
	UpHRect.left += 2;
	UpHRect.top += 2;
	UpHRect.right -= 2;
	UpHRect.bottom = (WndRect.Height() / 2) + WndRect.top;
	Point Pt1 = Point(UpHRect.left, UpHRect.top - 1), Pt2 = Point(UpHRect.left, UpHRect.bottom);
	LinearGradientBrush lgBrush1(Pt1, Pt2, UpBegin, UpEnd);
	m_pDoGrap->FillRectangle(&lgBrush1, UpHRect.left, UpHRect.top, UpHRect.Width(), UpHRect.Height());

	// 下半部分高光
	CRect DownHRect(WndRect);
	DownHRect.top = UpHRect.bottom;
	DownHRect.left += 2;
	DownHRect.right -= 2;
	DownHRect.bottom -= 2;
	Pt1 = Point(DownHRect.left, DownHRect.top - 1);
	Pt2 = Point(DownHRect.left, DownHRect.bottom);
	LinearGradientBrush lgBrush2(Pt1, Pt2, DownBegin, DownEnd);
	m_pDoGrap->FillRectangle(&lgBrush2, DownHRect.left, DownHRect.top, DownHRect.Width(), DownHRect.Height());

	// 四角高光
	Draw4Corner(BRColor, SRColor, PtColor);

	// 画焦点
	DrawFocus();

	// 文字
	DrawBtnText();
}

void CBfDrawButton::DrawFocus()
{
	if (IsInFocus())
	{
		CRect WndRect(0, 0, 0, 0), OutRect(0, 0, 0, 0), InRect(0, 0, 0, 0);
		WndRect = m_WndRect;

		OutRect = WndRect;
		OutRect.left++;
		OutRect.top++;
		OutRect.right -= 2;
		OutRect.bottom -= 2;
		Pen Pn1(Color(150, 68, 198, 247));
		RectF GRt = CUiMethod::CRect2RectF(OutRect);
		m_pDoGrap->DrawRectangle(&Pn1, GRt);

		InRect = OutRect;
		InRect.left++;
		InRect.top++;
		InRect.right--;
		InRect.bottom--;
		Pen Pn2(Color(100, 133, 188, 203));
		GRt = CUiMethod::CRect2RectF(InRect);
		m_pDoGrap->DrawRectangle(&Pn2, GRt);
	}
}

void CBfDrawButton::DrawBtnText()
{
	if (IsEnable())
		m_WndTextInfo.TextColor = Color(254, 0, 0, 0);
	else
		m_WndTextInfo.TextColor = Color(254, 128, 128, 128);

	m_WndTextInfo.TextRectF = CUiMethod::CRect2RectF(m_WndRect);
	m_WndTextInfo.TextRectF.Y += 1;

	CGdiPlusDraw::DrawWndText(m_pDoGrap, m_WndTextInfo);
}

// 四角高光
void CBfDrawButton::Draw4Corner(Color BRColor, Color SRColor, COLORREF PtColor)
{
	CRect WndRect = m_WndRect;

	CPoint Pt(0, 0);
	SolidBrush BRBrush(BRColor), SRBrush(SRColor);
	CRect BRRect(WndRect), SRRect(WndRect);
	RectF RtF;

	//////////////////////////////////////////////////////////////////////////////
	// 左上角
	BRRect = WndRect;
	BRRect.right = BRRect.left + 3;
	BRRect.bottom = BRRect.top + 3;
	RtF = CUiMethod::CRect2RectF(BRRect);
	m_pDoGrap->FillRectangle(&BRBrush, RtF);

	SRRect = BRRect;
	SRRect.right--;
	SRRect.bottom--;
	RtF = CUiMethod::CRect2RectF(SRRect);
	m_pDoGrap->FillRectangle(&SRBrush, RtF);

	Pt.x = WndRect.left + 2;
	Pt.y = WndRect.top + 2;
	::SetPixel(m_hMemoryDC, Pt.x, Pt.y, PtColor);

	Pt.x = WndRect.left;
	Pt.y = WndRect.top;
	::SetPixel(m_hMemoryDC, Pt.x, Pt.y, PtColor);

	//////////////////////////////////////////////////////////////////////////////
	// 右上角
	BRRect = WndRect;
	BRRect.left = BRRect.right - 3;
	BRRect.bottom = BRRect.top + 3;
	RtF = CUiMethod::CRect2RectF(BRRect);
	m_pDoGrap->FillRectangle(&BRBrush, RtF);

	SRRect = BRRect;
	SRRect.left++;
	SRRect.bottom--;
	RtF = CUiMethod::CRect2RectF(SRRect);
	m_pDoGrap->FillRectangle(&SRBrush, RtF);

	Pt.x = BRRect.left;
	Pt.y = BRRect.bottom - 1;
	::SetPixel(m_hMemoryDC, Pt.x, Pt.y, PtColor);

	Pt.x = BRRect.right - 1;
	Pt.y = BRRect.top;
	::SetPixel(m_hMemoryDC, Pt.x, Pt.y, PtColor);

	//////////////////////////////////////////////////////////////////////////////
	// 右下角
	BRRect = WndRect;
	BRRect.left = BRRect.right - 3;
	BRRect.top = BRRect.bottom - 3;
	RtF = CUiMethod::CRect2RectF(BRRect);
	m_pDoGrap->FillRectangle(&BRBrush, RtF);

	SRRect = BRRect;
	SRRect.left++;
	SRRect.top++;
	RtF = CUiMethod::CRect2RectF(SRRect);
	m_pDoGrap->FillRectangle(&SRBrush, RtF);

	Pt.x = BRRect.left;
	Pt.y = BRRect.top;
	::SetPixel(m_hMemoryDC, Pt.x, Pt.y, PtColor);

	Pt.x = BRRect.right - 1;
	Pt.y = BRRect.bottom - 1;
	::SetPixel(m_hMemoryDC, Pt.x, Pt.y, PtColor);

	//////////////////////////////////////////////////////////////////////////////
	// 左下角
	BRRect = WndRect;
	BRRect.right = BRRect.left + 3;
	BRRect.top = BRRect.bottom - 3;
	RtF = CUiMethod::CRect2RectF(BRRect);
	m_pDoGrap->FillRectangle(&BRBrush, RtF);

	SRRect = BRRect;
	SRRect.right--;
	SRRect.top++;
	RtF = CUiMethod::CRect2RectF(SRRect);
	m_pDoGrap->FillRectangle(&SRBrush, RtF);

	Pt.x = BRRect.right - 1;
	Pt.y = BRRect.top;
	::SetPixel(m_hMemoryDC, Pt.x, Pt.y, PtColor);

	Pt.x = BRRect.left;
	Pt.y = BRRect.bottom - 1;
	::SetPixel(m_hMemoryDC, Pt.x, Pt.y, PtColor);
}
