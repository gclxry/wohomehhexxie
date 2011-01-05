
// 两个像素覆盖的 alpha 融合算法
// dst = ((ovr - dst) * ovr.alpha) / 256 + dst
// Dst.Red = Src.Red * Src.alpha + (1-Src.alpha) * Dst.Red ;
// Dst.Green = Src.Green * Src.alpha + (1-Src.alpha) * Dst.Green;
// Dst.Blue = Src.Blue * Src.alpha + (1-Src.alpha) * Dst.Blue ;
// Dst.Alpha = 1 - (1 - Src.Alpha1) * ( 1 - Dst.Alpha)

#pragma once

#include <atltypes.h>
#include "CPUID.h"

// 32位ARGB颜色值制作
#define BGRA_MARK(b,g,r,a)          (((BYTE)(b)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(r))<<16)|(((DWORD)(BYTE)(a))<<24))

class CMmxBase
{
public:
	CMmxBase(void);
	~CMmxBase(void);

	// 替换指定的Alpha值。
	// pbyDst：内存位图的BTIMAP数据
	// DstSize：内存位图的大小，单位像素
	// SetRect：需要设置的位图的位置
	// byComA：指定需要替换的Alpha值
	// bySetA：alpha值
	virtual void ARGB32_CoverAlpha(__inout BYTE *pbyDst, __in CSize DstSize, __in CRect SetRect, __in BYTE byComA, __in BYTE bySetA);

protected:
	// 设置符合BITMAP内存数据的矩形
	virtual void SetCoverRect(__in CSize DstSize, __inout CRect &SetRect);

protected:
	CPUID m_CpuSupport;
};
