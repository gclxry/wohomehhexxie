
#pragma once

#include <atltypes.h>

// 32λARGB��ɫֵ����
#define BGRA_MARK(b,g,r,a)          (((BYTE)(b)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(r))<<16)|(((DWORD)(BYTE)(a))<<24))

// �������� alpha �ں��㷨
// byR = (BYTE)((float)byR * ((float)byA / 255.0));
// byG = (BYTE)((float)byG * ((float)byA / 255.0));
// byB = (BYTE)((float)byB * ((float)byA / 255.0));

// ����һ����ɫֵ��alpha���
#define PIXEL_ONE_COLOR_ALPHA_SET(byRGB_One,byA,MovOffset)	\
	__asm \
	{ \
		__asm	movzx		eax, byRGB_One \
		__asm	movzx		edx, byA \
		__asm	imul		eax, edx \
		__asm	cdq \
		__asm	mov			ecx, 00FFH \
		__asm	idiv		ecx \
		__asm	mov			[esi+MovOffset], al \
	}

// ����RGBAֵ������alpha��ϵ�ֵ
#define PIXEL_ALPHA_SET(byA,byR,byG,byB,dwReturn)	\
	DWORD *pdwColor = &dwReturn; \
	__asm \
	{ \
		__asm	mov		ebx, pdwColor \
		__asm	mov		esi, ebx \
		PIXEL_ONE_COLOR_ALPHA_SET(byB,byA,0) \
		PIXEL_ONE_COLOR_ALPHA_SET(byG,byA,1) \
		PIXEL_ONE_COLOR_ALPHA_SET(byR,byA,2) \
		__asm	movzx	ebx, byA \
		__asm	mov		[esi+3], bl \
	}


class CMmxBase
{
public:
	CMmxBase(void);
	~CMmxBase(void);

	// ʹ��32λ��͸��ֵ��ɫֵ���һ��λͼ����
	virtual void ARGB32_FillBitmapBuffer(DWORD *pBmpData, CSize BmpSize, BYTE byA, BYTE byR, BYTE byG, BYTE byB) {};

	// ����AlphaΪָ��ֵ
	virtual void ARGB32_CoverAlpha(DWORD *pBmpData, CSize BmpSize, BYTE byA) {};
};





// �������ظ��ǵ� alpha �ں��㷨
// dst = ((ovr - dst) * ovr.alpha) / 256 + dst
// Dst.Red = Src.Red * Src.alpha + (1-Src.alpha) * Dst.Red ;
// Dst.Green = Src.Green * Src.alpha + (1-Src.alpha) * Dst.Green;
// Dst.Blue = Src.Blue * Src.alpha + (1-Src.alpha) * Dst.Blue ;
// Dst.Alpha = 1 - (1 - Src.Alpha1) * ( 1 - Dst.Alpha)


// ����һ����ɫֵ��alpha���
#define TW0_PIXEL_ALPHA_SET(byRGB_One,byA,MovOffset)	\
	__asm \
	{ \
		__asm	movzx		eax, byRGB_One \
		__asm	imul		eax, byA \
		__asm	shr			eax, 8 \
		__asm	push		eax \
		__asm	mov			edx, ebx \
		__asm	movzx		eax, [esi+MovOffset] \
		__asm	imul		edx, eax \
		__asm	shr			edx, 8 \
		__asm	pop         eax \
		__asm	add			eax, edx \
		__asm	mov			[esi+MovOffset], al \
	}

#define TW0_PIXEL_ONE_COLOR_ALPHA_SET
