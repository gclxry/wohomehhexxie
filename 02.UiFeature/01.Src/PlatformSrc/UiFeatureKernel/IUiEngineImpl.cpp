
#include "StdAfx.h"
#include "IUiEngineImpl.h"
#include "..\..\Inc\UiFeatureDefs.h"

IUiEngine *GetUiEngineInterface()
{
	return IUiEngineImpl::GetInstance();
}

IUiEngineImpl::IUiEngineImpl(void)
{
	m_Blend.BlendOp = AC_SRC_OVER;
	m_Blend.BlendFlags = 0;
	m_Blend.AlphaFormat = AC_SRC_ALPHA;
	m_Blend.SourceConstantAlpha = 255;
	m_hMsimg32Dll = NULL;
	AlphaBlendImpl = NULL;
	TransparentBltImpl = NULL;
	GradientFillImpl = NULL;

	LoadImpl();
}

IUiEngineImpl::~IUiEngineImpl(void)
{
	AlphaBlendImpl = NULL;
	TransparentBltImpl = NULL;
	GradientFillImpl = NULL;
	SAFE_FREE_LIBRARY(m_hMsimg32Dll);
}

IUiEngine* IUiEngineImpl::GetInstance()
{
	static IUiEngineImpl _UiEngineInstance;
	return &_UiEngineInstance;
}

void IUiEngineImpl::LoadImpl()
{
	m_hMsimg32Dll = LoadLibraryA("msimg32.dll");

	if (m_hMsimg32Dll != NULL)
	{
		AlphaBlendImpl = (PFNALPHABLEND)GetProcAddress(m_hMsimg32Dll, ("AlphaBlend"));
		TransparentBltImpl = (PFNTRANSPARENTBLT)GetProcAddress(m_hMsimg32Dll, ("TransparentBlt"));
		GradientFillImpl = (PFNGRADIENTFILL)GetProcAddress(m_hMsimg32Dll, ("GradientFill"));
	}
}

bool IUiEngineImpl::AlphaBlend(CDrawingBoard &DestMemDc, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest,
						CDrawingBoard &SrcMemDc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, BLENDFUNCTION *pBlendFunction)
{
	if (AlphaBlendImpl == NULL || !IS_SAFE_HANDLE(DestMemDc.GetSafeHdc()) || !IS_SAFE_HANDLE(SrcMemDc.GetSafeHdc()))
		return false;

	BLENDFUNCTION Blend;
	if (pBlendFunction != NULL)
		Blend = *pBlendFunction;
	else
		Blend = m_Blend;

	return (AlphaBlendImpl(DestMemDc.GetSafeHdc(), nXOriginDest, nYOriginDest, nWidthDest, nHeightDest,
		SrcMemDc.GetSafeHdc(), nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, Blend) == TRUE);
}

bool IUiEngineImpl::AlphaBlend(CDrawingBoard &DestMemDc, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest,
						CDrawingBoard &SrcMemDc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, int nAlpha)
{
	if (AlphaBlendImpl == NULL || !IS_SAFE_HANDLE(DestMemDc.GetSafeHdc()) || !IS_SAFE_HANDLE(SrcMemDc.GetSafeHdc()))
		return false;

	if (nAlpha < 0)
		nAlpha = 0;

	if (nAlpha > 255)
		nAlpha = 255;

	BLENDFUNCTION Blend = m_Blend;
	Blend.SourceConstantAlpha = nAlpha;

	return (AlphaBlendImpl(DestMemDc.GetSafeHdc(), nXOriginDest, nYOriginDest, nWidthDest, nHeightDest,
		SrcMemDc.GetSafeHdc(), nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, Blend) == TRUE);
}
