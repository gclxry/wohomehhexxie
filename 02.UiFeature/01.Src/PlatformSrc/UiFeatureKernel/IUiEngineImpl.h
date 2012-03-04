
#pragma once
#include "..\..\Inc\IUiEngine.h"

// API:AlphaBlend
typedef WINGDIAPI BOOL (WINAPI *PFNALPHABLEND)(HDC, int, int, int, int, HDC, int, int, int, int, BLENDFUNCTION);
// API:TransparentBlt
typedef WINGDIAPI BOOL (WINAPI *PFNTRANSPARENTBLT)(HDC, int, int, int, int, HDC, int, int, int, int, UINT);
// API:GradientFill
typedef WINGDIAPI BOOL (WINAPI *PFNGRADIENTFILL)(HDC, PTRIVERTEX, ULONG, PVOID, ULONG, ULONG);
// API:DrawShadowText
typedef WINGDIAPI int (WINAPI *PDRAWSHADOWTEXT)(HDC, LPCWSTR, UINT, const RECT *, DWORD, COLORREF, COLORREF, int, int);


class IUiEngineImpl : public IUiEngine
{
public:
	IUiEngineImpl(void);
	virtual ~IUiEngineImpl(void);

	static IUiEngine* GetInstance();

	virtual bool AlphaBlend(CDrawingBoard &DestMemDc, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest,
		CDrawingBoard &SrcMemDc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, BLENDFUNCTION *pBlendFunction = NULL);

	virtual bool AlphaBlend(CDrawingBoard &DestMemDc, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest,
		CDrawingBoard &SrcMemDc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, int nAlpha);

	virtual bool AlphaBlend(HDC DestMemDc, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest,
		CDrawingBoard &SrcMemDc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, int nAlpha);

	// ªÊ÷∆“ı”∞Œƒ◊÷
	virtual int DrawShadowText(HDC hdc, LPCWSTR pszText, UINT cch, const RECT *pRect, DWORD dwFlags,
		COLORREF crText, COLORREF crShadow, int ixOffset, int iyOffset);

private:
	void LoadImpl();

private:
	BLENDFUNCTION m_Blend;

//////////////////////////////////////////////////////////////////////////
	// msimg32.dll
	HMODULE m_hMsimg32Dll;
	PFNALPHABLEND AlphaBlendImpl;
	PFNTRANSPARENTBLT TransparentBltImpl;
	PFNGRADIENTFILL GradientFillImpl;

//////////////////////////////////////////////////////////////////////////
	// comctl32.dll
	HMODULE m_hComctl32Dll;
	PDRAWSHADOWTEXT DrawShadowTextImpl;
};
