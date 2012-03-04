
#pragma once

// 32位ARGB颜色值制作
#define BGRA_MARK(b,g,r,a)          (((BYTE)(b)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(r))<<16)|(((DWORD)(BYTE)(a))<<24))

class CMmxBase
{
public:
	CMmxBase();
	virtual ~CMmxBase();

	// 替换指定的Alpha值。
	// pbyDst：内存位图的BTIMAP数据
	// DstSize：内存位图的大小，单位像素
	// SetRect：需要设置的位图的位置
	// byComA：指定需要替换的Alpha值
	// bySetA：alpha值
	virtual void BGRA32_CoverAlpha(__inout BYTE *pbyDst, __in SIZE DstSize, __in RECT SetRect, __in BYTE byComA, __in BYTE bySetA);

protected:
	// 设置符合BITMAP内存数据的矩形
	void SetCoverRect(__in SIZE DstSize, __inout RECT &SetRect);
};
