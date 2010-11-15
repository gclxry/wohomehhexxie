
#include "BfCheckBox.h"


CBfCheckBox::CBfCheckBox(void)
{
	m_bIsCheck = false;
}

CBfCheckBox::~CBfCheckBox(void)
{
}

void CBfCheckBox::SetCheck(bool bIsCheck)
{
	m_bIsCheck = bIsCheck;
	this->RedrawWindow();
}

void CBfCheckBox::MoveWindow(CRect ToRect, HDWP hWinPoslnfo)
{
	if (IsReady())
	{
		m_WndRect = ToRect;
		ToRect.left += (CHECK_BOX_HW + CHECK_BOX_HW / 2);
		SetTextRect(ToRect);
	}
}

void CBfCheckBox::OnLButtonDown(CPoint point)
{
	m_bIsCheck = !m_bIsCheck;
	this->RedrawWindow();
}

void CBfCheckBox::OnLButtonUp(CPoint point)
{
	this->RedrawWindow();
}

void CBfCheckBox::OnMouseHover(CPoint point)
{
	this->RedrawWindow();
}

void CBfCheckBox::OnMouseLeave(CPoint point)
{
	this->RedrawWindow();
}

void CBfCheckBox::OnPaint()
{
	// 绘制背景图
	if (m_BkgndImage.IsReady())
	{
		CGdiPlusDraw::DrawCenterImage(m_pDoGrap, m_BkgndImage.GetImage(), m_WndRect);
	}

	// 绘制方框
	CRect fkRect(m_WndRect);
	fkRect.right = fkRect.left + CHECK_BOX_HW;
	fkRect.top += 2;
	fkRect.bottom = fkRect.top + CHECK_BOX_HW;
	CGdiPlusDraw::DrawRectLine(m_pDoGrap, Color(137, 166, 184), fkRect);

	if (IsMouseHover())
	{
		CRect OutRect(fkRect);
		OutRect.left -= 1;
		OutRect.right += 1;
		OutRect.top -= 1;
		OutRect.bottom += 1;
		CGdiPlusDraw::DrawRectLine(m_pDoGrap, Color(156, 204, 237), OutRect);
	}

	// 绘制 √
	if (m_bIsCheck)
	{
		FontStyle FStyle = (FontStyle)(FontStyleRegular | FontStyleBold);
		int nFontHeight = 14;
		fkRect.left -= 3;
		fkRect.right += 10;

		CGdiPlusDraw::DrawText(m_pDoGrap, _T("√"), fkRect, m_WndTextInfo.strFontName, nFontHeight, FStyle,
			Color(104, 159, 21), m_WndTextInfo.OutFormat);
	}

	// 绘制文字信息
	if (!m_WndTextInfo.strText.IsEmpty())
	{
		if (m_WndTextInfo.IsEmpty())
			SetDefaultFont();

		CGdiPlusDraw::DrawWndText(m_pDoGrap, m_WndTextInfo);
	}
}
