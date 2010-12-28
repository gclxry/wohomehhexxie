
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

	// 说明：将一张图片融合到另外一张图片上，alpha融合
	// pbyDst：源图像，最终覆盖后的图像数据
	// DstSize：源图像大小，单位像素
	// pbyOvr：将要覆盖到源图像上的图像数据
	// OvrSize：覆盖数据大小，单位像素
	// BlendPoint：融合的开始位置
	virtual void ARGB32_AlphaBlend(__inout BYTE *pbyDst, __in CSize DstSize, __in BYTE *pbyOvr, __in CSize OvrSize, __in CPoint BlendPoint);

	void CSse2Render::BlendESS0(unsigned char* src1, unsigned char* src2, unsigned char* dst, unsigned int count);

};
