
#pragma once

#include "MmxBase.h"


class CMmxRender : public CMmxBase
{
public:
	CMmxRender(void);
	~CMmxRender(void);

	// ʹ��32λ��͸��ֵ��ɫֵ���һ��λͼ����
	virtual void RGBA32_FillBitmapBuffer(DWORD *pBmpData, CSize BmpSize, BYTE byA, BYTE byR, BYTE byG, BYTE byB);
	// 32λ��͸��ֵɫ�黨ˢ
//	virtual void SolidBrush32ARGB(DWORD *pImgData, CSize ImgSize, CRect DrawRect, DWORD dwColor);
};
