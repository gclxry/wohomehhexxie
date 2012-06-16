
#pragma once
#include "CDrawingBoard.h"

class IUiEngine
{
public:
	virtual bool AlphaBlend(CDrawingBoard &DestMemDc, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest,
		CDrawingBoard &SrcMemDc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, BLENDFUNCTION *pBlendFunction = NULL) = 0;

	virtual bool AlphaBlend(CDrawingBoard &DestMemDc, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest,
		CDrawingBoard &SrcMemDc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, int nAlpha) = 0;

	virtual bool AlphaBlend(HDC DestMemDc, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest,
		CDrawingBoard &SrcMemDc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, int nAlpha) = 0;

	// ªÊ÷∆“ı”∞Œƒ◊÷
	virtual int DrawShadowText(HDC hdc, LPCWSTR pszText, UINT cch, const RECT *pRect, DWORD dwFlags,
		COLORREF crText, COLORREF crShadow, int ixOffset, int iyOffset) = 0;

	virtual bool BitBlt(HDC hdc, int x, int y, int cx, int cy, HDC hdcSrc, int x1, int y1, DWORD rop) = 0;
	virtual bool StretchBlt(HDC hdcDest, int xDest, int yDest, int wDest, int hDest, HDC hdcSrc, int xSrc, int ySrc, int wSrc, int hSrc, DWORD rop) = 0;
};
