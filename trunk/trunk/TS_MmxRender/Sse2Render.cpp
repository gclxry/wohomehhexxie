
#include "StdAfx.h"
#include "Sse2Render.h"

CSse2Render::CSse2Render(void)
{
}

CSse2Render::~CSse2Render(void)
{
}

// ʹ��32λ��͸��ֵ��ɫֵ���һ��λͼ����
void CSse2Render::ARGB32_FillBitmapBuffer(DWORD *pBmpData, CSize BmpSize, BYTE byA, BYTE byR, BYTE byG, BYTE byB)
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
		mov		edi, pBmpData			// Ŀ��Ĵ���
		mov		ecx, nLoops				// ѭ������
		dec		ecx
LOOP_S:
		movq	mm0, [dwColorList]		// ����Ҫ���Ƶ�64λ���ݿ���MMX�Ĵ�����
		movq	[edi], mm0				// ��64λ���ݿ�����MMX�Ĵ����п�����Ŀ���ڴ���
		add		edi, 8					// ����2������֮�������
		loop	LOOP_S
		emms
	}

	// ������һ������
	if (((BmpSize.cx * BmpSize.cy) % 2) > 0)
		pBmpData[BmpSize.cx * BmpSize.cy - 1] = dwColor;
}

// sse2 32λ��͸��ֵɫ�黭ˢ
void CSse2Render::ARGB32_SolidBrush(DWORD *pDstBmpData, CSize BmpSize, CRect BrushRect, BYTE byA, BYTE byR, BYTE byG, BYTE byB)
{
	if (pDstBmpData == NULL || BmpSize.cx == 0 || BmpSize.cy == 0 || BrushRect.IsRectEmpty() || byA == 0)
		return;

	if (byA == 255)
	{
	}
	else
	{
		DWORD dwOvrColor[2] = { BGRA_MARK(byB,byG,byR,byA), BGRA_MARK(byB,byG,byR,byA) };
		DWORD *pDwOvrColor = dwOvrColor;

		int nLoops = (BmpSize.cx * BmpSize.cy) / 2;
		__asm
		{
			pxor		xmm2, xmm2	// ��MM2��0
			mov			edx, pDstBmpData	// ȡ32bit���ص�ַ��edx
			mov			eax, pDwOvrColor
			mov			ecx, nLoops
			dec			ecx

			// dst = ((ovr - dst) * ovr.alpha) / 256 + dst
LOOP_S:
			movq		mm0, qword ptr [edx]	// ȡ2������ֵ����mm0��Ŀ�����ص�
			movq		mm1, qword ptr [eax]	// ȡ2������ֵ����mm1���������ص�

			movq2dq		xmm0, mm0	// ��2������ֵ����xmm0��64bit
			movq2dq		xmm1, mm1

			punpcklbw	xmm0, xmm2	// ��չ64λ���ݵ�128λ����32λһ������Ϊ��λ�������ɼ�����
			punpcklbw	xmm1, xmm2

//			movdq2q		mm4, xmm0	// TTT ������ʾֵ
//			movdq2q		mm5, xmm1	// TTT ������ʾֵ

			movdqu		xmm3, xmm1	// Ϊ��ȡ�ø������ص��alphaֵ
			punpckhwd	xmm3, xmm3	// �����ƶ���˫��
			punpckhwd	xmm3, xmm3	// �����ƶ�������
			punpckhwd	xmm3, xmm3	// ˫���ƶ������֣����Էֱ����ÿ����ɫֵ��alpha�Ļ����

//			movdq2q		mm4, xmm3	// TTT ������ʾֵ

			movdqu		xmm4, xmm0
			movdqu		xmm5, xmm1

			psubusw		xmm4, xmm1	// Source-Overlay,���ͼ�
			psubusw		xmm5, xmm0	// Overlay-Source,���ͼ�

			pmullw		xmm4, xmm3	// Alpha * (Source-Overlay)
			pmullw		xmm5, xmm3	// Alpha * (Overlay-Source)

			psrlw		xmm4, 8		// ����256,now mm4 get the result,(Source-Overlay)<0 ����
			psrlw		xmm5, 8		// ����256,now mm5 get the result,(Overlay-Source)>0 ����


			paddusw		xmm0, xmm5	// ���ͼӵ�ԭͼ��D=Alpha*(O-S)+S,(Source-Overlay)<0 ����
			psubusw		xmm0, xmm4	// ���ͼӵ�ԭͼ��D=S-Alpha*(S-O),(Overlay-Source)>0 ����
			packuswb	xmm0, xmm0	// ��������32bit

			movdq2q		mm0, xmm0	// ������
			movq		[edx], mm0
			add			edx, 8

			loop		LOOP_S
			emms
		}

		if ((BmpSize.cx * BmpSize.cy) % 2 > 1)
		{
		}
	}
}
