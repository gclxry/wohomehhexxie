
#include "StdAfx.h"
#include "MmxRender.h"

CMmxRender::CMmxRender(void)
{
}

CMmxRender::~CMmxRender(void)
{
}

// 使用32位带透明值颜色值填充一段位图数据
void CMmxRender::RGBA32_FillBitmapBuffer(DWORD *pBmpData, CSize BmpSize, BYTE byA, BYTE byR, BYTE byG, BYTE byB)
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

	// 一次运算2个像素
	int nLoopsCtns = (BmpSize.cx * BmpSize.cy) / 2;

	__asm
	{
		emms							// MMX状态清零
		mov		edi, pBmpData			// 目标寄存器
		mov		ecx, nLoopsCtns			// 循环次数
LOOP_S:
		movq	mm0, [dwColorList]		// 将需要复制的64位数据拷贝MMX寄存器中
		movq	[edi], mm0				// 将64位数据拷贝从MMX寄存器中拷贝到目标内存中
		add		edi, 8					// 操作8字节之后的数据
		dec		ecx						// 计数器减1
		jnz		LOOP_S
		emms							// 恢复FP为正常状态
	}

	int nLast = (BmpSize.cx * BmpSize.cy) % 2;
	if (nLast > 0)
		pBmpData[BmpSize.cx * BmpSize.cy - 1] = dwColor;
}

/*
// 使用32位带透明值颜色值填充一段位图数据
void CMmxRender::RGBA32_FillBitmapBuffer(DWORD *pBmpData, CSize BmpSize, BYTE byA, BYTE byR, BYTE byG, BYTE byB)
{
	if (pBmpData == NULL || BmpSize.cx == 0 || BmpSize.cy == 0)
		return;

	byR = (BYTE)((float)byR * ((float)byA / 255.0));
	byG = (BYTE)((float)byG * ((float)byA / 255.0));
	byB = (BYTE)((float)byB * ((float)byA / 255.0));

	// 64位色块数据
	DWORD dwColor = BGRA_MARK(byB, byG, byR, byA);
	DWORD dwColorList[2] = {dwColor, dwColor};

	// 一次运算2个像素
	int nLoopsCtns = (BmpSize.cx * BmpSize.cy) / 2;

	__asm
	{
		emms							// MMX状态清零
		mov		edi, pBmpData			// 目标寄存器
		mov		ecx, nLoopsCtns			// 循环次数

LOOP_S:
		movq	mm0, [dwColorList]		// 将需要复制的64位数据拷贝MMX寄存器中
		movq	[edi], mm0				// 将64位数据拷贝从MMX寄存器中拷贝到目标内存中
		add		edi, 8					// 操作8字节之后的数据

		dec		ecx						// 计数器减1
		jnz		LOOP_S
		emms							// 恢复FP为正常状态

	}
}
*/
