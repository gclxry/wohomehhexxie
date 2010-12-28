
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
	// 设置Alpha为指定值
	virtual void ARGB32_CoverAlpha(DWORD *pBmpData, CSize BmpSize, BYTE byA);

	// 设置内存指定区域的Alpha值，注意，内存位图的位置和肉眼观察的位置是相反的。
	// pbyDst：内存位图的BTIMAP数据
	// DstSize：内存位图的大小，单位像素
	// SetRect：需要设置的位图的位置【注意，内存位图的位置和肉眼观察的位置是相反的。】
	// bySetA：需要设置的alpha值
	virtual void ARGB32_SetAlpha(__inout BYTE *pbyDst, __in CSize DstSize, __in CRect SetRect, __in BYTE bySetA);
};
