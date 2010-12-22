
#include "StdAfx.h"
#include "Sse2Render.h"

CSse2Render::CSse2Render(void)
{
}

CSse2Render::~CSse2Render(void)
{
}

// 使用32位带透明值颜色值填充一段位图数据
void CSse2Render::ARGB32_FillBitmapBuffer(DWORD *pBmpData, CSize BmpSize, BYTE byA, BYTE byR, BYTE byG, BYTE byB)
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

// sse2 32位带透明值色块画刷
void CSse2Render::ARGB32_SolidBrush(DWORD *pDstBmpData, CSize BmpSize, CRect BrushRect, BYTE byA, BYTE byR, BYTE byG, BYTE byB)
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
			// 算法流程
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
