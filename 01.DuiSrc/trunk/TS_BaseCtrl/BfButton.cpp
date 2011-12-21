
#include "BfButton.h"

CBfButton::CBfButton(void)
{
}

CBfButton::~CBfButton(void)
{
}

void CBfButton::OnPaint()
{
	// ���Ʊ���ͼ
	if (m_BkgndImage.IsReady())
	{
		CGdiPlusDraw::DrawCenterImage(m_pDoGrap, m_BkgndImage.GetImage(), m_WndRect);
	}

	// ����������Ϣ
	if (!m_WndTextInfo.strText.IsEmpty())
	{
		if (m_WndTextInfo.IsEmpty())
		{
			SetDefaultFont();
			m_WndTextInfo.OutFormat.SetAlignment(StringAlignmentCenter); 
		}

		FontFamily DefaultFamily(m_WndTextInfo.strFontName);
		Font DefaultFont(&DefaultFamily, (REAL)m_WndTextInfo.nFontHeight, m_WndTextInfo.FStyle, UnitPixel);
		SolidBrush DefaultBrush(m_WndTextInfo.TextColor);

		CGdiPlusDraw::DrawWndText(m_pDoGrap, m_WndTextInfo);
	}
}

void CBfButton::OnLButtonDown(CPoint point)
{
	this->RedrawWindow();
}

void CBfButton::OnLButtonUp(CPoint point)
{
	this->RedrawWindow();
}

void CBfButton::OnMouseHover(CPoint point)
{
	this->RedrawWindow();
}

void CBfButton::OnMouseLeave(CPoint point)
{
	this->RedrawWindow();
}

void CBfButton::OnLoseFocus()
{
	this->RedrawWindow();
}
