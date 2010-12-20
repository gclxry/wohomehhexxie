
#include "StdAfx.h"
#include "SseRender.h"

CSseRender::CSseRender(void)
{
}

CSseRender::~CSseRender(void)
{
}

// 使用32位带透明值颜色值填充一段位图数据
void CSseRender::RGBA32_FillBitmapBuffer(DWORD *pBmpData, CSize BmpSize, DWORD dwColor)
{
	if (pBmpData == NULL || BmpSize.cx == 0 || BmpSize.cy == 0)
		return;

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
}

void CSseRender::SolidBrush32ARGB(DWORD *pImgData, CSize ImgSize, CRect DrawRect, DWORD dwColor)
{
	if (pImgData == NULL || ImgSize.cx == 0 || ImgSize.cy == 0 || DrawRect.IsRectEmpty())
		return;

	// 64位色块数据
	DWORD dwColorList[2] = {dwColor, dwColor};

	// 一次运算2个像素
	int nLoopsCtns = (ImgSize.cx * ImgSize.cy) / 2;

	__asm
	{
		emms							// MMX状态清零

		mov		edi, pImgData			// 目标寄存器
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

// Invert image using Assembly with MMX
void InvertImageAssembly_MMX(
	BYTE* pSource, 
	BYTE* pDest, 
	int nNumberOfPixels)
{
	__int64 i = 0;
	i = ~i;                                 // 0xffffffffffffffff    

	// Two pixels are processed in one loop
	int nNumberOfLoops = nNumberOfPixels / 2;

	__asm
	{
		emms

			mov         esi, pSource            // input pointer
			mov         edi, pDest              // output pointer
			mov         ecx, nNumberOfLoops     // loop counter

start_loop:
		movq        mm0, i                  // mm0 = 0xffffffffffffffff 

			psubusb     mm0, [esi]              // Unsigned subtraction with saturation.
		// mm0 = mm0 - [esi] for each byte

		movq        [edi], mm0              // [edi] = mm0 (two pixels)

			add         esi, 8                  // increment input pointer (next 64 bits)
			add         edi, 8                  // increment output pointer (next 64 bits)

			dec         ecx
			jnz         start_loop

			emms
	}
}

int MMXAdd(BYTE *d, BYTE *s, int w, int h)
{
	int iCount = w * h;

	// we assume all data in the register is not used by others
	__asm
	{
		// Assign pointers to register
		mov			esi, [s]			// put src addr to esi reg
		mov			edi, [d]			//put dest addr to edi reg
		mov			ecx, [iCount]		//put count to ecx reg
		shr			ecx, 3				//divide count with 8 by shifting 3 bits to right

codeloop:
		movq		mm0, [esi]			//mov 8 bytes of src data to mmx reg 0
		movq		mm1, [edi]			// mov 8 bytes of dest data to mmx reg 1
		PADDUSB		mm0, mm1			// Add unsigned 8bit saturated to mmx reg 0
			movq		[edi], mm0			// dump back the added 8 bytes of data to dest memory
			add			esi, 8				// add src pointer by 8 bytes
			add			edi, 8				// add dest pointer by 8 bytes

			dec			ecx					// decrement count by 1
			jnz			codeloop			// jump to codeloop if not Zero
			emms							// Restore FPU state to normal

	}

	return 1;
}