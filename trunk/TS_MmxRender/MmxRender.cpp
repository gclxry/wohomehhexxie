
#include "StdAfx.h"
#include "MmxRender.h"

CMmxRender::CMmxRender(void)
{
}

CMmxRender::~CMmxRender(void)
{
}

// ����AlphaΪָ��ֵ
void CMmxRender::ARGB32_CoverAlpha(DWORD *pBmpData, CSize BmpSize, BYTE byA)
{
	if (pBmpData == NULL || BmpSize.cx == 0 || BmpSize.cy == 0)
		return;

	for (int i = 0; i < (BmpSize.cx * BmpSize.cy); i++)
	{
		BYTE *pRgba = (BYTE*)&(pBmpData[i]);
		pRgba += 3;
		*pRgba = byA;
	}
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

// mmx 32λ��͸��ֵɫ�黭ˢ
void CMmxRender::ARGB32_SolidBrush(DWORD *pDstBmpData, CSize BmpSize, CRect BrushRect, BYTE byA, BYTE byR, BYTE byG, BYTE byB)
{
	if (pDstBmpData == NULL || BmpSize.cx == 0 || BmpSize.cy == 0 || BrushRect.IsRectEmpty() || byA == 0)
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
void CMmxRender::ARGB32_SetAlpha(__inout BYTE *pbyDst, __in CSize DstSize, __in CRect SetRect, __in BYTE bySetA)
{
	if (pbyDst == NULL || DstSize.cx == 0 || DstSize.cy == 0 || SetRect.IsRectEmpty())
		return;

	if (SetRect.left < 0)
		SetRect.left = 0;

	if (SetRect.top < 0)
		SetRect.top = 0;

	if (SetRect.right > DstSize.cx)
		SetRect.right = DstSize.cx;

	if (SetRect.bottom > DstSize.cy)
		SetRect.bottom = DstSize.cy;

	// ��ת����
	CRect TRect(SetRect);
	TRect.top = DstSize.cy - SetRect.top - SetRect.Height();
	TRect.bottom = TRect.top + SetRect.Height();
	SetRect = TRect;

	BYTE *pbyA = &bySetA;
	DWORD dwA = bySetA;
	DWORD dwSetA[2] = { dwA, dwA };
	DWORD *pdwA = dwSetA;

	for (int nLine = SetRect.top; nLine < SetRect.bottom; nLine++)
	{
		BYTE *pbyLineDst = pbyDst + (DstSize.cx * nLine * 4) + (SetRect.left * 4);

		int nLoops = SetRect.Width() / 2;
		__asm
		{
			mov		edx, dword ptr [pbyLineDst]
			mov		eax, dword ptr [pdwA]
			movq	mm1, [eax]
			pslld	mm1, 24
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

			emms
		}

		if (SetRect.Width() % 2 > 0)
		{
			__asm
			{
				sub		edx, 4
				mov		eax, dwA
				mov		esi, edx
				mov		[esi+3], 00H
				mov		[esi+3], al
			}
		}
	}
}

/*
// ����д��mmx
// The assembler code which does the blending is actually really simple. From my additive blender, there's two parts. The first part initializes three of the MMX registers:

__asm {
movd    mm5, one
movd    mm6, alpha
pxor    mm7, mm7
punpcklbw  mm5, mm7
punpcklbw  mm6, mm7
paddw    mm6, mm5
}
// The second part loops through each pixel to be drawn and blends them appropriately:

hile (ty <= ty2) 

line = (unsigned long*)source->line[sy]; 
line = (unsigned long*)target->line[ty]; 
x = sx1; tx = tx1; 
hile (tx <= tx2) 

l = sline[sx]; 
f (!masked || sl != skip_colour) 
{ 
tl = tline[tx]; 
__asm { 
movd mm0, sl 
movd mm1, tl 
punpcklbw mm0, mm7 
punpcklbw mm1, mm7 

pmullw mm0, mm6 
psrlw mm0, 8 
paddusw mm1, mm0 

packuswb mm1, mm7 
movd tl, mm1 
} 
tline[tx] = tl; 
} 
sx++; tx++; 
} 
sy++; ty++; 
} 

*/
/*
// ��� 32λ��͸��ֵɫ�黭ˢ
void CMmxRender::ARGB32_SolidBrush(BYTE *pBmpData, CSize BmpSize, CRect BrushRect, BYTE byA, BYTE byR, BYTE byG, BYTE byB)
{
	if (pBmpData == NULL || BmpSize.cx == 0 || BmpSize.cy == 0 || BrushRect.IsRectEmpty() || byA == 0)
		return;

	if (byA == 255)
	{
	}
	else
	{
		int nLoops = BmpSize.cx * BmpSize.cy;
		__asm
		{
			mov		esi, pBmpData

			movzx	edx, byA
			mov		ebx, 00FFH
			sub		ebx, edx

			mov		ecx, nLoops
			dec		ecx
LOOP_S:
			__asm							// ������ؼ���alpha�ں�
			{
				TW0_PIXEL_ALPHA_SET(byB,byA,0)
				TW0_PIXEL_ALPHA_SET(byG,byA,1)
				TW0_PIXEL_ALPHA_SET(byR,byA,2)

				movzx	eax, [esi+3]
				mov		edx, 00FFH
				sub		edx, eax
				imul	edx, ebx
				shr		edx, 8
				mov		eax, 00FFH
				sub		eax, edx
				mov		[esi+3], al
			}
			add		esi, 4					// ������һ������
			loop	LOOP_S
			emms
		}
	}
}

// C 32λ��͸��ֵɫ�黭ˢ
void CMmxRender::ARGB32_SolidBrush(BYTE *pBmpData, CSize BmpSize, CRect BrushRect, BYTE byA, BYTE byR, BYTE byG, BYTE byB)
{
	if (pBmpData == NULL || BmpSize.cx == 0 || BmpSize.cy == 0 || BrushRect.IsRectEmpty() || byA == 0)
		return;

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
}
*/
