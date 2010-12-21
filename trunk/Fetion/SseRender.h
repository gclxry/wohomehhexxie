
#pragma once
#include <atltypes.h>


#define BGRA_MARK(b,g,r,a)          (((BYTE)(b)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(r))<<16)|(((DWORD)(BYTE)(a))<<24))

class CSseRender
{
public:
	CSseRender(void);
	~CSseRender(void);

	// ʹ��32λ��͸��ֵ��ɫֵ���һ��λͼ����
	static void RGBA32_FillBitmapBuffer1(DWORD *pBmpData, CSize BmpSize, BYTE byA, BYTE byR, BYTE byG, BYTE byB);
	static void RGBA32_FillBitmapBuffer(DWORD *pBmpData, CSize BmpSize, BYTE byA, BYTE byR, BYTE byG, BYTE byB);
	// 32λ��͸��ֵɫ�黨ˢ
	static void SolidBrush32ARGB(DWORD *pImgData, CSize ImgSize, CRect DrawRect, DWORD dwColor);
};
