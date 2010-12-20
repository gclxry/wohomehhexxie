
#include "StdAfx.h"
#include "SseRender.h"

CSseRender::CSseRender(void)
{
}

CSseRender::~CSseRender(void)
{
}

// ʹ��32λ��͸��ֵ��ɫֵ���һ��λͼ����
void CSseRender::RGBA32_FillBitmapBuffer(DWORD *pBmpData, CSize BmpSize, DWORD dwColor)
{
	if (pBmpData == NULL || BmpSize.cx == 0 || BmpSize.cy == 0)
		return;

	// 64λɫ������
	DWORD dwColorList[2] = {dwColor, dwColor};

	// һ������2������
	int nLoopsCtns = (BmpSize.cx * BmpSize.cy) / 2;

	__asm
	{
		emms							// MMX״̬����
		mov		edi, pBmpData			// Ŀ��Ĵ���
		mov		ecx, nLoopsCtns			// ѭ������

LOOP_S:
		movq	mm0, [dwColorList]		// ����Ҫ���Ƶ�64λ���ݿ���MMX�Ĵ�����
		movq	[edi], mm0				// ��64λ���ݿ�����MMX�Ĵ����п�����Ŀ���ڴ���
		add		edi, 8					// ����8�ֽ�֮�������

		dec		ecx						// ��������1
		jnz		LOOP_S
		emms							// �ָ�FPΪ����״̬
	}
}

void CSseRender::SolidBrush32ARGB(DWORD *pImgData, CSize ImgSize, CRect DrawRect, DWORD dwColor)
{
	if (pImgData == NULL || ImgSize.cx == 0 || ImgSize.cy == 0 || DrawRect.IsRectEmpty())
		return;

	// 64λɫ������
	DWORD dwColorList[2] = {dwColor, dwColor};

	// һ������2������
	int nLoopsCtns = (ImgSize.cx * ImgSize.cy) / 2;

	__asm
	{
		emms							// MMX״̬����

		mov		edi, pImgData			// Ŀ��Ĵ���
		mov		ecx, nLoopsCtns			// ѭ������

LOOP_S:
		movq	mm0, [dwColorList]		// ����Ҫ���Ƶ�64λ���ݿ���MMX�Ĵ�����
		movq	[edi], mm0				// ��64λ���ݿ�����MMX�Ĵ����п�����Ŀ���ڴ���
		add		edi, 8					// ����8�ֽ�֮�������

		dec		ecx						// ��������1
		jnz		LOOP_S
		emms							// �ָ�FPΪ����״̬
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