
#pragma once
#include "..\..\Inc\IUiEngine.h"

// API:AlphaBlend
typedef WINGDIAPI BOOL (WINAPI *PFNALPHABLEND)(HDC, int, int, int, int, HDC, int, int, int, int, BLENDFUNCTION);
// API:TransparentBlt
typedef WINGDIAPI BOOL (WINAPI *PFNTRANSPARENTBLT)(HDC, int, int, int, int, HDC, int, int, int, int, UINT);
// API:GradientFill
typedef WINGDIAPI BOOL (WINAPI *PFNGRADIENTFILL)(HDC, PTRIVERTEX, ULONG, PVOID, ULONG, ULONG);

class IUiEngineImpl : public IUiEngine
{
public:
	IUiEngineImpl(void);
	virtual ~IUiEngineImpl(void);

	static IUiEngine* GetInstance();

	virtual bool AlphaBlend(CDrawingBoard &DestMemDc, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest,
		CDrawingBoard &SrcMemDc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, BLENDFUNCTION *pBlendFunction = NULL);

	virtual bool AlphaBlend(CDrawingBoard &DestMemDc, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest,
		CDrawingImage &SrcImgDc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, BLENDFUNCTION *pBlendFunction = NULL);

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
};
