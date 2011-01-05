
#pragma once

#include "MmxBase.h"

class CMmxRender : public CMmxBase
{
public:
	CMmxRender(void);
	~CMmxRender(void);

	// 32λ��͸��ֵɫ�黭ˢ
	virtual void ARGB32_SolidBrush(DWORD *pDstBmpData, CSize BmpSize, CRect BrushRect, BYTE byA, BYTE byR, BYTE byG, BYTE byB);

	// ����һ��λͼΪָ����ɫ
	// pBmpData���ڴ�λͼ��BTIMAP����
	// BmpSize���ڴ�λͼ�Ĵ�С����λ����
	// dwColor����Ҫ���õ���ɫֵ��Ĭ��ֵ����͸�����ף�
	virtual void ARGB32_ClearBitmap(__inout BYTE *pBmpData, __in CSize BmpSize, __in DWORD dwColor);

	// �����ڴ�ָ�������Alphaֵ��
	// pbyDst���ڴ�λͼ��BTIMAP����
	// DstSize���ڴ�λͼ�Ĵ�С����λ����
	// SetRect����Ҫ���õ�λͼ��λ��
	// bySetA��alphaֵ
	virtual void ARGB32_ClearAlpha(__inout BYTE *pbyDst, __in CSize DstSize, __in CRect SetRect, __in BYTE bySetA);

private:
	bool m_bIsSupportMmx;
};
