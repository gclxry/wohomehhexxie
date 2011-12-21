
#pragma once

#include "MmxRender.h"


class CSseRender : public CMmxRender
{
public:
	CSseRender(void);
	~CSseRender(void);

	// 32λ��͸��ֵɫ�黭ˢ
	virtual void ARGB32_SolidBrush(DWORD *pDstBmpData, CSize BmpSize, CRect BrushRect, BYTE byA, BYTE byR, BYTE byG, BYTE byB);

	// ˵������һ��ͼƬ�ںϵ�����һ��ͼƬ�ϣ�alpha�ں�
	// pbyDst��Դͼ�����ո��Ǻ��ͼ������
	// DstSize��Դͼ���С����λ����
	// pbyOvr����Ҫ���ǵ�Դͼ���ϵ�ͼ������
	// OvrSize���������ݴ�С����λ����
	// BlendPoint���ںϵĿ�ʼλ��
	virtual void ARGB32_AlphaBlend(__inout BYTE *pbyDst, __in CSize DstSize, __in BYTE *pbyOvr, __in CSize OvrSize, __in CPoint BlendPoint);

	virtual void BlendESS0(unsigned char* src1, unsigned char* src2, unsigned char* dst, unsigned int count);

private:
	bool m_bIsSupportSse;
};
