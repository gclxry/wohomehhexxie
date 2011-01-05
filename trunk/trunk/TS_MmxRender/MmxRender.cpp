
#include "StdAfx.h"
#include "MmxRender.h"

CMmxRender::CMmxRender(void)
{
	m_bIsSupportMmx = m_CpuSupport.IsMMX();
}

CMmxRender::~CMmxRender(void)
{
}

// mmx 32λ��͸��ֵɫ�黭ˢ
void CMmxRender::ARGB32_SolidBrush(DWORD *pDstBmpData, CSize BmpSize, CRect BrushRect, BYTE byA, BYTE byR, BYTE byG, BYTE byB)
{
	if (pDstBmpData == NULL || BmpSize.cx <= 0 || BmpSize.cy <= 0 || BrushRect.IsRectEmpty() || byA == 0)
		return;

	if (byA == 255)
	{
	}
	else
	{
		DWORD dwOvrColor = BGRA_MARK(byB,byG,byR,byA);

		int nLoops = BmpSize.cx * BmpSize.cy;
		__asm
		{
			pxor		mm2, mm2	// ��MM2��0
			mov			edx, pDstBmpData	// ȡ32bit���ص�ַ��edx
			mov			eax, dwOvrColor
			mov			ecx, nLoops
			dec			ecx

			// dst = (ovr * ovr.alpha) / 256 + dst - (dst * ovr.alpha) / 256
			// dst = ((ovr - dst) * ovr.alpha) / 256 + dst
LOOP_S:
			movd		mm0, [edx]	// ��Source����ֵȡ��mm0��32bit
			movd		mm1, eax	// ��Overlay����ֵȡ��mm1��32bit
			punpcklbw	mm0, mm2	// Source:8 bit��16 bit�����ɽ��,32bit expand to 64 bit
			punpcklbw	mm1, mm2	// Overlay:8 bit��16 bit�����ɽ��.32bit expand to 64 bit
			movq		mm3, mm1	// ��ΪҪ��Overlay��Alphaֵ
			punpckhwd	mm3, mm3	// �����ƶ���˫��
			punpckhdq	mm3, mm3	// ˫���ƶ������֣����Էֱ����ÿ����ɫֵ��alpha�Ļ����
			movq		mm4, mm0
			movq		mm5, mm1
			psubusw		mm4, mm1	// Source-Overlay,���ͼ�
			psubusw		mm5, mm0	// Overlay-Source,���ͼ�
			pmullw		mm4, mm3	// Alpha * (Source-Overlay)
			pmullw		mm5, mm3	// Alpha * (Overlay-Source)
			psrlw		mm4, 8		// ����256,now mm4 get the result,(Source-Overlay)<0 ����
			psrlw		mm5, 8		// ����256,now mm5 get the result,(Overlay-Source)>0 ����
			paddusw		mm0, mm5	// ���ͼӵ�ԭͼ��D=Alpha*(O-S)+S,(Source-Overlay)<0 ����
			psubusw		mm0, mm4	// ���ͼӵ�ԭͼ��D=S-Alpha*(S-O),(Overlay-Source)>0 ����
			packuswb	mm0, mm0	// ��������32bit

			movd		[edx], mm0	// ������
			add			edx, 4		// ������һ������

			loop		LOOP_S

			emms
		}
	}
}

// �����ڴ�ָ�������Alphaֵ
void CMmxRender::ARGB32_ClearAlpha(__inout BYTE *pbyDst, __in CSize DstSize, __in CRect SetRect, __in BYTE bySetA)
{
	if (pbyDst == NULL || DstSize.cx <= 0 || DstSize.cy <= 0 || SetRect.IsRectEmpty())
		return;

	SetCoverRect(DstSize, SetRect);

	int nLoops = SetRect.Width() / 2;
	int nRem = SetRect.Width() % 2;

	BYTE *pbyA = &bySetA;
	DWORD dwA = bySetA;
	DWORD dwSetA[2] = { dwA, dwA };
	DWORD *pdwA = dwSetA;

	// ��ʼ�������Ĵ�����ֵ
	__asm
	{
		mov		ebx, dword ptr [pdwA]
		movq	mm1, [ebx]
		pslld	mm1, 24
		mov		ebx, dwA
	}

	for (int nLine = SetRect.top; nLine < SetRect.bottom; nLine++)
	{
		// ����һ������
		BYTE *pbyLineDst = pbyDst + (DstSize.cx * nLine * 4) + (SetRect.left * 4);

		__asm
		{
			mov		edx, dword ptr [pbyLineDst]
			mov		ecx, nLoops
			dec		ecx

LOOP_S:
			movq	mm0, [edx]
			pslld	mm0, 8
			psrld	mm0, 8
			paddusb	mm0, mm1
			movq	[edx], mm0
			add		edx, 8
			loop	LOOP_S
		}

		if (nRem > 0)
		{
			// һ�е�����Ϊ���������������һ������
			__asm
			{
				sub		edx, 4
				mov		esi, edx
				mov		[esi+3], 00H
				mov		[esi+3], bl
			}
		}
	}

	// ���MMX��״̬
	__asm
	{
		emms
	}
}

// ����һ��λͼΪָ����ɫ
void CMmxRender::ARGB32_ClearBitmap(__inout BYTE *pBmpData, __in CSize BmpSize, __in DWORD dwColor)
{
	if (pBmpData == NULL || BmpSize.cx <= 0 || BmpSize.cy <= 0)
		return;

	// 64λɫ������
	DWORD dwColorList[2] = {dwColor, dwColor};

	// һ�θ���2������
	int nLoops = (BmpSize.cx * BmpSize.cy) / 2;

	__asm
	{
		mov		edi, pBmpData			// Ŀ��Ĵ���
		movq	mm0, [dwColorList]		// ����Ҫ���Ƶ�64λ���ݿ���MMX�Ĵ�����
		mov		ecx, nLoops				// ѭ������
		dec		ecx

LOOP_S:
		movq	[edi], mm0				// ��64λ���ݿ�����MMX�Ĵ����п�����Ŀ���ڴ���
		add		edi, 8					// ����2������֮�������
		loop	LOOP_S
		emms
	}

	// ������һ������
	if (((BmpSize.cx * BmpSize.cy) % 2) > 0)
		((DWORD*)pBmpData)[BmpSize.cx * BmpSize.cy - 1] = dwColor;
}
