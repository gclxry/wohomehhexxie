
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
		emms							// MMX状态清零
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

//	for (int i = 0; i < BmpSize.cx * BmpSize.cy; i++)
//	{
		DWORD dwC = pBmpData[0];
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
//		pBmpData[i] = BGRA_MARK(byDB,byDG,byDR,byDA);
//	}


	if (byA == 255)
	{
	}
	else
	{
		float fAlphaS = 0.0;
		float *pfAlphaS = &fAlphaS;

		float fAlphaD = 0.0;
		float *pfAlphaD = &fAlphaD;

//		BYTE *pbySa = &byA;
//		BYTE *pbySr = &byR;
//		BYTE *pbySg = &byG;
//		BYTE *pbySb = &byB;

		int nLoops = BmpSize.cx * BmpSize.cy;
		__asm
		{
			emms							// MMX状态清零
			mov		esi, pBmpData			// 目标寄存器

			movzx	edx, byA
			mov		ebx, 00FFH
			sub		ebx, edx

			mov		ecx, nLoops				// 循环次数
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
			add		esi, 4					// 操作4字节之后的数据
			loop	LOOP_S
			emms
		}
	}
}
