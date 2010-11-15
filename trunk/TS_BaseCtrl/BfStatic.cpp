
#include "BfStatic.h"


CBfStatic::CBfStatic(void)
{
	m_bIsDrawBkgndColor = false;
	m_bIsFullDraw = false;
	m_nWaneEllipse = 0;
}

CBfStatic::~CBfStatic(void)
{
}

void CBfStatic::OnPaint()
{
	// ���Ʊ���ɫ
	if (m_bIsDrawBkgndColor)
	{
		CGdiPlusDraw::DrawColor(m_pDoGrap, m_BkColor, m_WndRect);
	}

	// ���Ʊ���ͼ
	if (m_BkgndImage.IsReady())
	{
		if (m_bIsFullDraw)
		{
			CRect SrcRect(0, 0, m_BkgndImage.GetImage()->GetWidth(), m_BkgndImage.GetImage()->GetHeight());
			CGdiPlusDraw::DrawImage(m_pDoGrap, m_BkgndImage.GetImage(), m_WndRect, SrcRect);
		}
		else
		{
			CGdiPlusDraw::DrawCenterImage(m_pDoGrap, m_BkgndImage.GetImage(), m_WndRect, m_nWaneEllipse);
		}
	}

	// ����������Ϣ
	if (!m_WndTextInfo.strText.IsEmpty())
	{
		if (m_WndTextInfo.IsEmpty())
			SetDefaultFont();

		FontFamily DefaultFamily(m_WndTextInfo.strFontName);
		Font DefaultFont(&DefaultFamily, (REAL)m_WndTextInfo.nFontHeight, m_WndTextInfo.FStyle, UnitPixel);
		SolidBrush DefaultBrush(m_WndTextInfo.TextColor);

		CGdiPlusDraw::DrawWndText(m_pDoGrap, m_WndTextInfo);
	}
}
