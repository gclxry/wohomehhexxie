
#pragma once

#include "MmxBase.h"


class CMmxRender : public CMmxBase
{
public:
	CMmxRender(void);
	~CMmxRender(void);

	// 使用32位带透明值颜色值填充一段位图数据
	virtual void ARGB32_FillBitmapBuffer(DWORD *pBmpData, CSize BmpSize, BYTE byA, BYTE byR, BYTE byG, BYTE byB);
	// 32位带透明值色块画刷
	virtual void ARGB32_SolidBrush(DWORD *pDstBmpData, CSize BmpSize, CRect BrushRect, BYTE byA, BYTE byR, BYTE byG, BYTE byB);

	// 设置一副位图为指定颜色
	// pBmpData：内存位图的BTIMAP数据
	// BmpSize：内存位图的大小，单位像素
	// dwColor：需要设置的颜色值（默认值：不透明纯白）
	virtual void ARGB32_ClearBitmap(__inout BYTE *pBmpData, __in CSize BmpSize, __in DWORD dwColor = 0xFFFFFFFF);

	// 设置内存指定区域的Alpha值。
	// pbyDst：内存位图的BTIMAP数据
	// DstSize：内存位图的大小，单位像素
	// SetRect：需要设置的位图的位置
	// bySetA：alpha值
	virtual void ARGB32_ClearAlpha(__inout BYTE *pbyDst, __in CSize DstSize, __in CRect SetRect, __in BYTE bySetA);

	// 替换指定的Alpha值。
	// pbyDst：内存位图的BTIMAP数据
	// DstSize：内存位图的大小，单位像素
	// SetRect：需要设置的位图的位置
	// byComA：指定需要替换的Alpha值
	// bySetA：alpha值
	virtual void ARGB32_CoverAlpha(__inout BYTE *pbyDst, __in CSize DstSize, __in CRect SetRect, __in BYTE byComA, __in BYTE bySetA);

private:
	// 设置符合BITMAP内存数据的矩形
	virtual void SetCoverRect(__in CSize DstSize, __inout CRect &SetRect);
};
