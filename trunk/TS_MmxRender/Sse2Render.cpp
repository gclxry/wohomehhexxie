
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
		DWORD dwOvrColor[2] = { BGRA_MARK(byB,byG,byR,byA), BGRA_MARK(byB,byG,byR,byA) };
		DWORD *pDwOvrColor = dwOvrColor;

		int nLoops = (BmpSize.cx * BmpSize.cy) / 2;
		__asm
		{
			pxor		xmm2, xmm2	// 把MM2清0
			mov			edx, pDstBmpData	// 取32bit像素地址到edx
			mov			eax, pDwOvrColor
			mov			ecx, nLoops
			dec			ecx

			// dst = ((ovr - dst) * ovr.alpha) / 256 + dst
LOOP_S:
			movq		mm0, qword ptr [edx]	// 取2个像素值放入mm0，目标像素点
			movq		mm1, qword ptr [eax]	// 取2个像素值放入mm1，覆盖像素点

			movq2dq		xmm0, mm0	// 把2个像素值放入xmm0低64bit
			movq2dq		xmm1, mm1

			punpcklbw	xmm0, xmm2	// 扩展64位数据到128位，以32位一个像素为单位，以容纳计算结果
			punpcklbw	xmm1, xmm2

//			movdq2q		mm4, xmm0	// TTT 测试显示值
//			movdq2q		mm5, xmm1	// TTT 测试显示值

			movdqu		xmm3, xmm1	// 为了取得覆盖像素点的alpha值
			punpckhwd	xmm3, xmm3	// 高字移动到双字
			punpckhwd	xmm3, xmm3	// 高字移动到四字
			punpckhwd	xmm3, xmm3	// 双字移动到八字，可以分别计算每个颜色值的alpha的混合啦

//			movdq2q		mm4, xmm3	// TTT 测试显示值

			movdqu		xmm4, xmm0
			movdqu		xmm5, xmm1

			psubusw		xmm4, xmm1	// Source-Overlay,饱和减
			psubusw		xmm5, xmm0	// Overlay-Source,饱和减

			pmullw		xmm4, xmm3	// Alpha * (Source-Overlay)
			pmullw		xmm5, xmm3	// Alpha * (Overlay-Source)

			psrlw		xmm4, 8		// 除以256,now mm4 get the result,(Source-Overlay)<0 部分
			psrlw		xmm5, 8		// 除以256,now mm5 get the result,(Overlay-Source)>0 部分


			paddusw		xmm0, xmm5	// 饱和加到原图象D=Alpha*(O-S)+S,(Source-Overlay)<0 部分
			psubusw		xmm0, xmm4	// 饱和加到原图象D=S-Alpha*(S-O),(Overlay-Source)>0 部分
			packuswb	xmm0, xmm0	// 紧缩到低32bit

			movdq2q		mm0, xmm0	// 保存结果
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
