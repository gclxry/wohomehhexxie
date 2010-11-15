
#include "BfPictureButton.h"

CBfPictureButton::CBfPictureButton(void)
{
}

CBfPictureButton::~CBfPictureButton(void)
{
}

void CBfPictureButton::OnPaint()
{
	// 绘制背景图
	if (m_BkgndImage.IsReady())
	{
		Image * pImage = m_BkgndImage.GetImage();
		int nW = pImage->GetWidth() / m_nPicStas;
		int nLeft = 0;

		if (IsMouseDown())
		{
			nLeft = nW * 2;
		}
		else if (IsMouseHover())
		{
			nLeft = nW;
		}

		CRect SrcRect(nLeft, 0, nLeft + nW, pImage->GetHeight());
		CGdiPlusDraw::DrawImage(m_pDoGrap, m_BkgndImage.GetImage(), m_WndRect, SrcRect);
	}

	// 绘制文字信息
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
