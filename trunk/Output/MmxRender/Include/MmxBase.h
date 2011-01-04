
#pragma once

#include <atltypes.h>

// 32位ARGB颜色值制作
#define BGRA_MARK(b,g,r,a)          (((BYTE)(b)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(r))<<16)|(((DWORD)(BYTE)(a))<<24))

class CMmxBase
{
public:
	CMmxBase(void);
	~CMmxBase(void);

	// 初始化MMX渲染，判断当前CPU是否支持相应的指令集
	virtual bool InitMmx() { return false; };

	// 设置一副位图为指定颜色
	// pBmpData：内存位图的BTIMAP数据
	// BmpSize：内存位图的大小，单位像素
	// dwColor：需要设置的颜色值（默认值：不透明纯白）
	virtual void ARGB32_ClearBitmap(__inout BYTE *pBmpData, __in CSize BmpSize, __in DWORD dwColor) {};

	// 设置内存指定区域的Alpha值。
	// pbyDst：内存位图的BTIMAP数据
	// DstSize：内存位图的大小，单位像素
	// SetRect：需要设置的位图的位置
	// bySetA：alpha值
	virtual void ARGB32_ClearAlpha(__inout BYTE *pbyDst, __in CSize DstSize, __in CRect SetRect, __in BYTE bySetA) {};

	// 替换指定的Alpha值。
	// pbyDst：内存位图的BTIMAP数据
	// DstSize：内存位图的大小，单位像素
	// SetRect：需要设置的位图的位置
	// byComA：指定需要替换的Alpha值
	// bySetA：alpha值
	virtual void ARGB32_CoverAlpha(__inout BYTE *pbyDst, __in CSize DstSize, __in CRect SetRect, __in BYTE byComA, __in BYTE bySetA) {};

private:
	bool m_bIsSupport;
};

// 两个像素覆盖的 alpha 融合算法
// dst = ((ovr - dst) * ovr.alpha) / 256 + dst
// Dst.Red = Src.Red * Src.alpha + (1-Src.alpha) * Dst.Red ;
// Dst.Green = Src.Green * Src.alpha + (1-Src.alpha) * Dst.Green;
// Dst.Blue = Src.Blue * Src.alpha + (1-Src.alpha) * Dst.Blue ;
// Dst.Alpha = 1 - (1 - Src.Alpha1) * ( 1 - Dst.Alpha)
