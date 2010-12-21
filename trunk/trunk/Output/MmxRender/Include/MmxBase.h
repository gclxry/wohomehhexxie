
#pragma once

#include <atltypes.h>

// 32λARGB��ɫֵ����
#define BGRA_MARK(b,g,r,a)          (((BYTE)(b)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(r))<<16)|(((DWORD)(BYTE)(a))<<24))

// ����һ����ɫֵ��alpha���
#define PIXEL_ONE_COLOR_ALPHA_SET(byRGB_One,byA,MovOffset)	\
	__asm \
	{ \
		__asm	movzx       eax, byRGB_One \
		__asm	movzx       edx, byA \
		__asm	imul        eax, edx \
		__asm	cdq \
		__asm	mov         ecx, 00FFh \
		__asm	idiv        ecx \
		__asm	mov         [esi+MovOffset], al \
	}

// ����RGBAֵ������alpha��ϵ�ֵ
#define PIXEL_ALPHA_SET(byA,byR,byG,byB,dwReturn)	\
	DWORD *pdwColor = &dwReturn; \
	__asm \
	{ \
		__asm	mov			ebx, pdwColor \
		__asm	mov			esi, ebx \
		PIXEL_ONE_COLOR_ALPHA_SET(byB,byA,0) \
		PIXEL_ONE_COLOR_ALPHA_SET(byG,byA,1) \
		PIXEL_ONE_COLOR_ALPHA_SET(byR,byA,2) \
		__asm	movzx		ebx, byA \
		__asm	mov         [esi+3], bl \
	}


class CMmxBase
{
public:
	CMmxBase(void);
	~CMmxBase(void);

	// ʹ��32λ��͸��ֵ��ɫֵ���һ��λͼ����
	virtual void RGBA32_FillBitmapBuffer(DWORD *pBmpData, CSize BmpSize, BYTE byA, BYTE byR, BYTE byG, BYTE byB) {};
};
