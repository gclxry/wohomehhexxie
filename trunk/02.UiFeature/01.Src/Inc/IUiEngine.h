
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
};
