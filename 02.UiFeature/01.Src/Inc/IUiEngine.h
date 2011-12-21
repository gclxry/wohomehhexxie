
#pragma once
#include "..\..\Inc\CMemoryDC.h"

class IUiEngine
{
public:
	virtual bool AlphaBlend(CMemoryDC &DestMemDc, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest,
		CMemoryDC &SrcMemDc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, BLENDFUNCTION *pBlendFunction = NULL) = 0;

};
