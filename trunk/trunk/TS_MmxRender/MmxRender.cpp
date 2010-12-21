
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
		emms
		mov		edi, pBmpData			// 目标寄存器
		mov		ecx, nLoops				// 循环次数
		dec		ecx
LOOP_S:
		movq	mm0, [dwColorList]		// 将需要复制的64位数据拷贝MMX寄存器中
		movq	[edi], mm0				// 将64位数据拷贝从MMX寄存器中拷贝到目标内存中
		add		edi, 8					// 操作8字节之后的数据
		loop	LOOP_S
		emms
	}

	// 填充最后一个像素
	if (((BmpSize.cx * BmpSize.cy) % 2) > 0)
		pBmpData[BmpSize.cx * BmpSize.cy - 1] = dwColor;
}

// 32位带透明值色块画刷
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
			emms
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
