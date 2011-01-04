
#include "StdAfx.h"
#include "MmxRender.h"

CMmxRender::CMmxRender(void)
{
}

CMmxRender::~CMmxRender(void)
{
}

// 使用32位带透明值颜色值填充一段位图数据
void CMmxRender::ARGB32_FillBitmapBuffer(DWORD *pBmpData, CSize BmpSize, BYTE byA, BYTE byR, BYTE byG, BYTE byB)
{
	if (pBmpData == NULL || BmpSize.cx == 0 || BmpSize.cy == 0)
		return;

	DWORD dwColor = 0;
	if (byA > 0)
	{
		// 根据一个像素的RGBA值，进行本像素的alpha混合
		PIXEL_ALPHA_SET(byA,byR,byG,byB,dwColor);
	}
	// 64位色块数据
	DWORD dwColorList[2] = {dwColor, dwColor};

	// 一次复制2个像素
	int nLoops = (BmpSize.cx * BmpSize.cy) / 2;
	__asm
	{
		mov		edi, pBmpData			// 目标寄存器
		mov		ecx, nLoops				// 循环次数
		dec		ecx
LOOP_S:
		movq	mm0, [dwColorList]		// 将需要复制的64位数据拷贝MMX寄存器中
		movq	[edi], mm0				// 将64位数据拷贝从MMX寄存器中拷贝到目标内存中
		add		edi, 8					// 操作2个像素之后的数据
		loop	LOOP_S
		emms
	}

	// 填充最后一个像素
	if (((BmpSize.cx * BmpSize.cy) % 2) > 0)
		pBmpData[BmpSize.cx * BmpSize.cy - 1] = dwColor;
}

// mmx 32位带透明值色块画刷
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
			pxor		mm2, mm2	// 把MM2清0
			mov			edx, pDstBmpData	// 取32bit像素地址到edx
			mov			eax, dwOvrColor
			mov			ecx, nLoops
			dec			ecx

			// dst = (ovr * ovr.alpha) / 256 + dst - (dst * ovr.alpha) / 256
			// dst = ((ovr - dst) * ovr.alpha) / 256 + dst
LOOP_S:
			movd		mm0, [edx]	// 把Source像素值取到mm0低32bit
			movd		mm1, eax	// 把Overlay像素值取到mm1低32bit
			punpcklbw	mm0, mm2	// Source:8 bit到16 bit以容纳结果,32bit expand to 64 bit
			punpcklbw	mm1, mm2	// Overlay:8 bit到16 bit以容纳结果.32bit expand to 64 bit
			movq		mm3, mm1	// 因为要用Overlay的Alpha值
			punpckhwd	mm3, mm3	// 高字移动到双字
			punpckhdq	mm3, mm3	// 双字移动到四字，可以分别计算每个颜色值的alpha的混合啦
			movq		mm4, mm0
			movq		mm5, mm1
			psubusw		mm4, mm1	// Source-Overlay,饱和减
			psubusw		mm5, mm0	// Overlay-Source,饱和减
			pmullw		mm4, mm3	// Alpha * (Source-Overlay)
			pmullw		mm5, mm3	// Alpha * (Overlay-Source)
			psrlw		mm4, 8		// 除以256,now mm4 get the result,(Source-Overlay)<0 部分
			psrlw		mm5, 8		// 除以256,now mm5 get the result,(Overlay-Source)>0 部分
			paddusw		mm0, mm5	// 饱和加到原图象D=Alpha*(O-S)+S,(Source-Overlay)<0 部分
			psubusw		mm0, mm4	// 饱和加到原图象D=S-Alpha*(S-O),(Overlay-Source)>0 部分
			packuswb	mm0, mm0	// 紧缩到低32bit

			movd		[edx], mm0	// 保存结果
			add			edx, 4		// 操作下一个像素

			loop		LOOP_S

			emms
		}
	}
}

// 设置符合bitmap内存数据的矩形
void CMmxRender::SetCoverRect(__in CSize DstSize, __inout CRect &SetRect)
{
	if (SetRect.left < 0)
		SetRect.left = 0;

	if (SetRect.top < 0)
		SetRect.top = 0;

	if (SetRect.right > DstSize.cx)
		SetRect.right = DstSize.cx;

	if (SetRect.bottom > DstSize.cy)
		SetRect.bottom = DstSize.cy;

	// 翻转矩形
	int nHeight = SetRect.Height();
	int nTop = DstSize.cy - SetRect.top - SetRect.Height();

	SetRect.top = nTop;
	SetRect.bottom = SetRect.top + nHeight;
}

// 设置内存指定区域的Alpha值
void CMmxRender::ARGB32_CoverAlpha(__inout BYTE *pbyDst, __in CSize DstSize, __in CRect SetRect, __in BYTE byComA, __in BYTE bySetA)
{
	if (pbyDst == NULL || DstSize.cx == 0 || DstSize.cy == 0 || SetRect.IsRectEmpty())
		return;

	SetCoverRect(DstSize, SetRect);

	int nLoops = SetRect.Width();
	int nLine = SetRect.top;
	int nLineEnd = SetRect.bottom;

	__asm
	{
		jmp         CURRENT_LINE_SET_BEING

		LINE_SET_BEING:
		mov         ecx, dword ptr [nLine]
		add         ecx, 1
		mov         dword ptr [nLine], ecx

		CURRENT_LINE_SET_BEING:
		mov         ecx, dword ptr [nLine]
		cmp         ecx, dword ptr [nLineEnd]
		jge         RECT_SET_END

			// 设置一行像素
			__asm
			{
				// 计算每一行开始的像素地址，存入 eax
				// C语言计算公式：BYTE *pbyLineDst = pbyDst + (DstSize.cx * nLine * 4) + (SetRect.left * 4);
				mov		eax, dword ptr [DstSize]
				imul	eax, dword ptr [nLine]
				mov		ecx, dword ptr [pbyDst]
				lea		edx, [ecx+eax*4]
				mov		eax, dword ptr [SetRect]
				lea		ecx, [edx+eax*4]
				mov		eax, ecx

				// eax：当前需要操作的像素的内存地址
				// ebx：一行像素的操作个数的计数器
				// edx：保存用于比较的数据

				// 初始化每一行的循环
				mov		ebx, 0
				movzx	edx, byte ptr [byComA]
				jmp		CURRENT_LINE_PIX_BEGIN

				// 下一个像素的开始
			NEXT_LINE_PIX_BEGIN:
				add		ebx, 1

					// 当前一行的每一个循环的开始
				CURRENT_LINE_PIX_BEGIN:
					cmp		ebx, dword ptr [nLoops]
					jge		LINE_SET_END

					movzx	ecx, byte ptr [eax+3]
					cmp		ecx, edx
					jne		PIX_SET_END

						mov		cl, byte ptr [bySetA]
						mov		byte ptr [eax+3], cl

					PIX_SET_END:
						add		eax, 4

				jmp		NEXT_LINE_PIX_BEGIN
			LINE_SET_END:
			}
			jmp		LINE_SET_BEING
		
		RECT_SET_END:
	}
}

// 设置内存指定区域的Alpha值
void CMmxRender::ARGB32_ClearAlpha(__inout BYTE *pbyDst, __in CSize DstSize, __in CRect SetRect, __in BYTE bySetA)
{
	if (pbyDst == NULL || DstSize.cx == 0 || DstSize.cy == 0 || SetRect.IsRectEmpty())
		return;

	SetCoverRect(DstSize, SetRect);

	int nLoops = SetRect.Width() / 2;
	int nRem = SetRect.Width() % 2;

	BYTE *pbyA = &bySetA;
	DWORD dwA = bySetA;
	DWORD dwSetA[2] = { dwA, dwA };
	DWORD *pdwA = dwSetA;

	// 初始化各个寄存器的值
	__asm
	{
		mov		ebx, dword ptr [pdwA]
		movq	mm1, [ebx]
		pslld	mm1, 24
		mov		ebx, dwA
	}

	for (int nLine = SetRect.top; nLine < SetRect.bottom; nLine++)
	{
		// 设置一行像素
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
			// 一行的像素为奇数个，设置最后一个像素
			__asm
			{
				sub		edx, 4
				mov		esi, edx
				mov		[esi+3], 00H
				mov		[esi+3], bl
			}
		}
	}

	// 清除MMX的状态
	__asm
	{
		emms
	}
}

/*
// 老外写的mmx
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
// 汇编 32位带透明值色块画刷
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
			__asm							// 逐个像素计算alpha融合
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
			add		esi, 4					// 操作下一个像素
			loop	LOOP_S
			emms
		}
	}
}

// C 32位带透明值色块画刷
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
