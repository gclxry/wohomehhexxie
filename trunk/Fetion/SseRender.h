
#pragma once
#include <atltypes.h>


#define BGRA_MARK(b,g,r,a)          (((BYTE)(b)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(r))<<16)|(((DWORD)(BYTE)(a))<<24))

class CSseRender
{
public:
	CSseRender(void);
	~CSseRender(void);

	// 使用32位带透明值颜色值填充一段位图数据
	static void RGBA32_FillBitmapBuffer(DWORD *pBmpData, CSize BmpSize, DWORD dwColor);
	// 32位带透明值色块花刷
	static void SolidBrush32ARGB(DWORD *pImgData, CSize ImgSize, CRect DrawRect, DWORD dwColor);
};
