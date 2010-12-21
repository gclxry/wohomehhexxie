
#include "StdAfx.h"
#include "SseRender.h"

CSseRender::CSseRender(void)
{
}

CSseRender::~CSseRender(void)
{
}

// 计算一个颜色值的alpha混合
#define PIXEL_ONE_COLOR_ALPHA_SET(byRGB_One,byA,MovOffset)	\
__asm	movzx       eax, byRGB_One \
__asm	movzx       edx, byA \
__asm	imul        eax, edx \
__asm	cdq \
__asm	mov         ecx, 255 \
__asm	idiv        ecx \
__asm	mov         [esi+MovOffset], al

// 根据一个像素的RGBA值，进行本像素的alpha混合
#define PIXEL_ALPHA_SET(byA,byR,byG,byB,dwReturn)	\
BYTE *pA = &byA; \
DWORD *pdwColor = &dwReturn; \
__asm \
{ \
	__asm	mov			ebx, pdwColor \
	__asm	mov			esi, ebx \
	PIXEL_ONE_COLOR_ALPHA_SET(byR,byA,2) \
	PIXEL_ONE_COLOR_ALPHA_SET(byG,byA,1) \
	PIXEL_ONE_COLOR_ALPHA_SET(byB,byA,0) \
	__asm	movzx		ebx, byA \
	__asm	mov         [esi+3], bl \
}



// 使用32位带透明值颜色值填充一段位图数据
void CSseRender::RGBA32_FillBitmapBuffer1(DWORD *pBmpData, CSize BmpSize, BYTE byA, BYTE byR, BYTE byG, BYTE byB)
{
	if (pBmpData == NULL || BmpSize.cx == 0 || BmpSize.cy == 0)
		return;

	DWORD dwColor;
	// 根据一个像素的RGBA值，进行本像素的alpha混合
	PIXEL_ALPHA_SET(byA,byR,byG,byB,dwColor);

	// 64位色块数据
	DWORD dwColorList[2] = {dwColor, dwColor};

	// 一次运算2个像素
	int nLoopsCtns = (BmpSize.cx * BmpSize.cy) / 2;

	__asm
	{
		emms						// MMX状态清零
		mov		edi, pBmpData		// 目标寄存器
		mov		ecx, nLoopsCtns		// 循环次数
LOOP_S:
		movq	mm0, [dwColorList]
		movq	[edi], mm0
		add		edi, 8
		dec		ecx
		jnz		LOOP_S
		emms
	}
}

// 使用32位带透明值颜色值填充一段位图数据
void CSseRender::RGBA32_FillBitmapBuffer(DWORD *pBmpData, CSize BmpSize, BYTE byA, BYTE byR, BYTE byG, BYTE byB)
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