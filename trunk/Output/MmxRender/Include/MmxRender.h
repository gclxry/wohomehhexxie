
#pragma once

#include "MmxBase.h"


class CMmxRender : public CMmxBase
{
public:
	CMmxRender(void);
	~CMmxRender(void);

	// ʹ��32λ��͸��ֵ��ɫֵ���һ��λͼ����
	virtual void ARGB32_FillBitmapBuffer(DWORD *pBmpData, CSize BmpSize, BYTE byA, BYTE byR, BYTE byG, BYTE byB);
	// 32λ��͸��ֵɫ�黭ˢ
	virtual void ARGB32_SolidBrush(DWORD *pDstBmpData, CSize BmpSize, CRect BrushRect, BYTE byA, BYTE byR, BYTE byG, BYTE byB);
	// ����AlphaΪָ��ֵ
	virtual void ARGB32_CoverAlpha(DWORD *pBmpData, CSize BmpSize, BYTE byA);
	// �����ڴ�ָ�������Alphaֵ��ע�⣬�ڴ�λͼ��λ�ú����۹۲��λ�����෴�ġ�
	virtual void ARGB32_SetAlpha(__inout BYTE *pbyDst, __in CSize DstSize, __in CRect SetRect, __in BYTE bySetA);
};
