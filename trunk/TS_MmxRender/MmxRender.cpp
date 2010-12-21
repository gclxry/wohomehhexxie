
#include "StdAfx.h"
#include "MmxRender.h"

CMmxRender::CMmxRender(void)
{
}

CMmxRender::~CMmxRender(void)
{
}

// ʹ��32λ��͸��ֵ��ɫֵ���һ��λͼ����
void CMmxRender::RGBA32_FillBitmapBuffer(DWORD *pBmpData, CSize BmpSize, BYTE byA, BYTE byR, BYTE byG, BYTE byB)
{
	if (pBmpData == NULL || BmpSize.cx == 0 || BmpSize.cy == 0)
		return;

	DWORD dwColor = 0;
	if (byA > 0)
	{
		// ����һ�����ص�RGBAֵ�����б����ص�alpha���
		PIXEL_ALPHA_SET(byA,byR,byG,byB,dwColor);
	}

	// 64λɫ������
	DWORD dwColorList[2] = {dwColor, dwColor};

	// һ������2������
	int nLoopsCtns = (BmpSize.cx * BmpSize.cy) / 2;

	__asm
	{
		emms							// MMX״̬����
		mov		edi, pBmpData			// Ŀ��Ĵ���
		mov		ecx, nLoopsCtns			// ѭ������
LOOP_S:
		movq	mm0, [dwColorList]		// ����Ҫ���Ƶ�64λ���ݿ���MMX�Ĵ�����
		movq	[edi], mm0				// ��64λ���ݿ�����MMX�Ĵ����п�����Ŀ���ڴ���
		add		edi, 8					// ����8�ֽ�֮�������
		dec		ecx						// ��������1
		jnz		LOOP_S
		emms							// �ָ�FPΪ����״̬
	}

	int nLast = (BmpSize.cx * BmpSize.cy) % 2;
	if (nLast > 0)
		pBmpData[BmpSize.cx * BmpSize.cy - 1] = dwColor;
}

/*
// ʹ��32λ��͸��ֵ��ɫֵ���һ��λͼ����
void CMmxRender::RGBA32_FillBitmapBuffer(DWORD *pBmpData, CSize BmpSize, BYTE byA, BYTE byR, BYTE byG, BYTE byB)
{
	if (pBmpData == NULL || BmpSize.cx == 0 || BmpSize.cy == 0)
		return;

	byR = (BYTE)((float)byR * ((float)byA / 255.0));
	byG = (BYTE)((float)byG * ((float)byA / 255.0));
	byB = (BYTE)((float)byB * ((float)byA / 255.0));

	// 64λɫ������
	DWORD dwColor = BGRA_MARK(byB, byG, byR, byA);
	DWORD dwColorList[2] = {dwColor, dwColor};

	// һ������2������
	int nLoopsCtns = (BmpSize.cx * BmpSize.cy) / 2;

	__asm
	{
		emms							// MMX״̬����
		mov		edi, pBmpData			// Ŀ��Ĵ���
		mov		ecx, nLoopsCtns			// ѭ������

LOOP_S:
		movq	mm0, [dwColorList]		// ����Ҫ���Ƶ�64λ���ݿ���MMX�Ĵ�����
		movq	[edi], mm0				// ��64λ���ݿ�����MMX�Ĵ����п�����Ŀ���ڴ���
		add		edi, 8					// ����8�ֽ�֮�������

		dec		ecx						// ��������1
		jnz		LOOP_S
		emms							// �ָ�FPΪ����״̬

	}
}
*/
