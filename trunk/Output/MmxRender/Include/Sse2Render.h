
#pragma once

#include "MmxBase.h"


class CSse2Render : public CMmxBase
{
public:
	CSse2Render(void);
	~CSse2Render(void);

	// ʹ��32λ��͸��ֵ��ɫֵ���һ��λͼ����
	virtual void ARGB32_FillBitmapBuffer(DWORD *pBmpData, CSize BmpSize, BYTE byA, BYTE byR, BYTE byG, BYTE byB);
	// 32λ��͸��ֵɫ�黭ˢ
	virtual void ARGB32_SolidBrush(DWORD *pDstBmpData, CSize BmpSize, CRect BrushRect, BYTE byA, BYTE byR, BYTE byG, BYTE byB);

	// ˵������һ��ͼƬ�ںϵ�����һ��ͼƬ�ϣ�alpha�ں�
	// pbyDst��Դͼ�����ո��Ǻ��ͼ������
	// DstSize��Դͼ���С����λ����
	// pbyOvr����Ҫ���ǵ�Դͼ���ϵ�ͼ������
	// OvrSize���������ݴ�С����λ����
	// BlendPoint���ںϵĿ�ʼλ��
	virtual void ARGB32_AlphaBlend(__inout BYTE *pbyDst, __in CSize DstSize, __in BYTE *pbyOvr, __in CSize OvrSize, __in CPoint BlendPoint);

	void CSse2Render::BlendESS0(unsigned char* src1, unsigned char* src2, unsigned char* dst, unsigned int count);

};
