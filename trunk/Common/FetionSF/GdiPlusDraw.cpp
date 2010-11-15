
#include "GdiPlusDraw.h"
#include "UiMethod.h"

void CGdiPlusDraw::DrawCenterImage(Graphics *pDoGrap, Image *pDrawImage, CRect &DstRect, int nWaneEllipse)
{
	if (pDoGrap != NULL && pDrawImage != NULL)
	{
		CRect ImgRect(0, 0, pDrawImage->GetWidth(), pDrawImage->GetHeight());

		Rect DstRect1;
		// 图片比输出的矩形要大的时候
		if (DstRect.Width() < ImgRect.Width() || DstRect.Height() < ImgRect.Height())
		{
			DstRect1 = Rect(CUiMethod::CRect2Rect(DstRect));
		}
		else
		{
			CRect NewDstRect(0, 0, 0, 0);

			NewDstRect.left = DstRect.left + (DstRect.Width() - ImgRect.Width()) / 2;
			NewDstRect.right = NewDstRect.left + ImgRect.Width();
			NewDstRect.top = DstRect.top + (DstRect.Height() - ImgRect.Height()) / 2;
			NewDstRect.bottom = NewDstRect.top + ImgRect.Height();

			DstRect1 = Rect(CUiMethod::CRect2Rect(NewDstRect));
		}

		if (nWaneEllipse > 0)
		{
			HRGN hRgn = ::CreateRoundRectRgn(DstRect1.X, DstRect1.Y,
				DstRect1.X + DstRect1.Width + 1, DstRect1.Y + DstRect1.Height + 1,
				DstRect1.Width / nWaneEllipse, DstRect1.Height / nWaneEllipse);

			pDoGrap->SetClip(hRgn, CombineModeReplace);
			pDoGrap->DrawImage(pDrawImage, DstRect1, ImgRect.left, ImgRect.top, ImgRect.Width(), ImgRect.Height(), UnitPixel);
			::DeleteObject(hRgn);
			pDoGrap->ResetClip();
		}
		else
		{
			pDoGrap->DrawImage(pDrawImage, DstRect1, ImgRect.left, ImgRect.top, ImgRect.Width(), ImgRect.Height(), UnitPixel);
		}
	}
}

void CGdiPlusDraw::DrawImage(Graphics *pDoGrap, Image *pDrawImage, CRect &DstRect, CRect &SrcRect)
{
	if (pDoGrap != NULL && pDrawImage != NULL)
	{
		Rect DstRect1 = CUiMethod::CRect2Rect(DstRect);
		pDoGrap->DrawImage(pDrawImage, DstRect1, SrcRect.left, SrcRect.top, SrcRect.Width(), SrcRect.Height(), UnitPixel);
	}
}

void CGdiPlusDraw::DrawWndText(Graphics *pDoGrap, WND_TEXT &WndText)
{
	if (pDoGrap != NULL && !WndText.strText.IsEmpty())
	{
		FontFamily DFamily(WndText.strFontName);
		Font DFont(&DFamily, (REAL)WndText.nFontHeight, WndText.FStyle, UnitPixel);
		SolidBrush DBrush(WndText.TextColor);

		pDoGrap->DrawString(WndText.strText, -1, &DFont, WndText.TextRectF, &WndText.OutFormat, &DBrush);
	}
}

void CGdiPlusDraw::DrawText(Graphics *pDoGrap, CString strText, CRect TextRect, CString strFontName, int nFontHeight, FontStyle FStyle, Color nTextColor, StringFormat &OutFormat)
{
	if (pDoGrap != NULL && !strText.IsEmpty())
	{
		FontFamily DFamily(strFontName);
		Font DFont(&DFamily, (REAL)nFontHeight, FStyle, UnitPixel);
		SolidBrush DBrush(nTextColor);

		RectF Rf = CUiMethod::CRect2RectF(TextRect);
		pDoGrap->DrawString(strText, -1, &DFont, Rf, &OutFormat, &DBrush);
	}
}

void CGdiPlusDraw::DrawRectLine(Graphics *pDoGrap, Color nLineColor, CRect DstRect)
{
	if (pDoGrap != NULL)
	{
		Pen LinePen(nLineColor);
		pDoGrap->DrawRectangle(&LinePen, DstRect.left, DstRect.top, DstRect.Width() - 1, DstRect.Height() - 1);
	}
}

void CGdiPlusDraw::DrawColor(Graphics *pDoGrap, Color nBkgndColor, CRect DstRect)
{
	if (pDoGrap != NULL)
	{
		// 填充背景色
		SolidBrush FillBrush(nBkgndColor);
		pDoGrap->FillRectangle(&FillBrush, DstRect.left, DstRect.top, DstRect.Width(), DstRect.Height());
	}
}
