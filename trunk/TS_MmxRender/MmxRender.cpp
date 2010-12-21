
#include "StdAfx.h"
#include "MmxRender.h"

CMmxRender::CMmxRender(void)
{
}

CMmxRender::~CMmxRender(void)
{
}

// ʹ��32λ��͸��ֵ��ɫֵ���һ��λͼ����
void CMmxRender::ARGB32_FillBitmapBuffer(DWORD *pBmpData, CSize BmpSize, BYTE byA, BYTE byR, BYTE byG, BYTE byB)
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

	// һ�θ���2������
	int nLoops = (BmpSize.cx * BmpSize.cy) / 2;
	__asm
	{
		emms							// MMX״̬����
		mov		edi, pBmpData			// Ŀ��Ĵ���
		mov		ecx, nLoops			// ѭ������
LOOP_S:
		movq	mm0, [dwColorList]		// ����Ҫ���Ƶ�64λ���ݿ���MMX�Ĵ�����
		movq	[edi], mm0				// ��64λ���ݿ�����MMX�Ĵ����п�����Ŀ���ڴ���
		add		edi, 8					// ����8�ֽ�֮�������
		dec		ecx						// ��������1
		jnz		LOOP_S
		emms							// �ָ�FPΪ����״̬
	}

	// ������һ������
	if (((BmpSize.cx * BmpSize.cy) % 2) > 0)
		pBmpData[BmpSize.cx * BmpSize.cy - 1] = dwColor;
}

// 32λ��͸��ֵɫ�黭ˢ
void CMmxRender::ARGB32_SolidBrush(DWORD *pBmpData, CSize BmpSize, CRect BrushRect, BYTE byA, BYTE byR, BYTE byG, BYTE byB)
{
	if (pBmpData == NULL || BmpSize.cx == 0 || BmpSize.cy == 0 || BrushRect.IsRectEmpty())
		return;
/*
	for (int i = 0; i < BmpSize.cx * BmpSize.cy; i++)
	{
		DWORD dwC = pBmpData[i];
		BYTE byDA = (BYTE)(dwC>>24);
		BYTE byDR = (BYTE)(dwC>>16);
		BYTE byDG = (BYTE)(dwC>>8);
		BYTE byDB = (BYTE)dwC;

		float fAlpha = (float)byA / (float)255.0;
		byDR = (BYTE)((float)byR * fAlpha + (1.0 - fAlpha) * (float)byDR);
		byDG = (BYTE)((float)byG * fAlpha + (1.0 - fAlpha) * (float)byDG);
		byDB = (BYTE)((float)byB * fAlpha + (1.0 - fAlpha) * (float)byDB);

		float fAlphaD = (float)byDA / (float)255.0;
		byDA = (BYTE)((1.0 - (1.0 - fAlpha) * (1.0 - fAlphaD)) * 255.0);
		pBmpData[i] = BGRA_MARK(byDB,byDG,byDR,byDA);
	}
	*/

	__asm
	{

	}
}
