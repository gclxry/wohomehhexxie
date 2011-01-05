
#pragma once

#include "MmxBase.h"

class CMmxRender : public CMmxBase
{
public:
	CMmxRender(void);
	~CMmxRender(void);

	// 32位带透明值色块画刷
	virtual void ARGB32_SolidBrush(DWORD *pDstBmpData, CSize BmpSize, CRect BrushRect, BYTE byA, BYTE byR, BYTE byG, BYTE byB);

	// 设置一副位图为指定颜色
	// pBmpData：内存位图的BTIMAP数据
	// BmpSize：内存位图的大小，单位像素
	// dwColor：需要设置的颜色值（默认值：不透明纯白）
	virtual void ARGB32_ClearBitmap(__inout BYTE *pBmpData, __in CSize BmpSize, __in DWORD dwColor);

	// 设置内存指定区域的Alpha值。
	// pbyDst：内存位图的BTIMAP数据
	// DstSize：内存位图的大小，单位像素
	// SetRect：需要设置的位图的位置
	// bySetA：alpha值
	virtual void ARGB32_ClearAlpha(__inout BYTE *pbyDst, __in CSize DstSize, __in CRect SetRect, __in BYTE bySetA);

private:
	bool m_bIsSupportMmx;
};
