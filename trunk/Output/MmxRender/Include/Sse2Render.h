
#pragma once

#include "MmxBase.h"


class CSse2Render : public CMmxBase
{
public:
	CSse2Render(void);
	~CSse2Render(void);

	// 使用32位带透明值颜色值填充一段位图数据
	virtual void ARGB32_FillBitmapBuffer(DWORD *pBmpData, CSize BmpSize, BYTE byA, BYTE byR, BYTE byG, BYTE byB);
	// 32位带透明值色块画刷
	virtual void ARGB32_SolidBrush(DWORD *pDstBmpData, CSize BmpSize, CRect BrushRect, BYTE byA, BYTE byR, BYTE byG, BYTE byB);
};
