
#include "StdAfx.h"
#include "MmxBase.h"

CMmxBase::CMmxBase()
{
}

CMmxBase::~CMmxBase()
{
}

// 设置符合BITMAP内存数据的矩形
void CMmxBase::SetCoverRect(__in SIZE DstSize, __inout RECT &SetRect)
{
	if (SetRect.left < 0)
		SetRect.left = 0;

	if (SetRect.top < 0)
		SetRect.top = 0;

	if (SetRect.right > DstSize.cx)
		SetRect.right = DstSize.cx;

	if (SetRect.bottom > DstSize.cy)
		SetRect.bottom = DstSize.cy;

	// 翻转矩形
	int nHeight = SetRect.bottom - SetRect.top;
	int nTop = DstSize.cy - SetRect.top - nHeight;

	SetRect.top = nTop;
	SetRect.bottom = SetRect.top + nHeight;
}

// 设置内存指定区域的Alpha值
void CMmxBase::BGRA32_CoverAlpha(__inout BYTE *pbyDst, __in SIZE DstSize, __in RECT SetRect, __in BYTE byComA, __in BYTE bySetA)
{
	if (pbyDst == NULL || DstSize.cx <= 0 || DstSize.cy <= 0 || SetRect.right <= SetRect.left || SetRect.bottom <= SetRect.top)
		return;

	SetCoverRect(DstSize, SetRect);

	int nLoops = SetRect.right - SetRect.left;
	int nLine = SetRect.top;
	int nLineEnd = SetRect.bottom;

	__asm
	{
		// edx：保存用于比较alpha的值
		movzx	edx, byte ptr [byComA]
		jmp		CURRENT_LINE_SET_BEING

	LINE_SET_BEING:
		add		dword ptr [nLine], 1

	CURRENT_LINE_SET_BEING:
		mov		ecx, dword ptr [nLineEnd]
		cmp		dword ptr [nLine], ecx
		jge		RECT_SET_END

		// 设置一行像素
		__asm
		{
			// 计算每一行开始的像素地址，存入 eax
			// C语言计算公式：BYTE *pbyLineDst = pbyDst + (DstSize.cx * nLine * 4) + (SetRect.left * 4);
			mov		eax, dword ptr [DstSize]
			imul	eax, dword ptr [nLine]
			mov		ecx, dword ptr [pbyDst]
			lea		ebx, [ecx+eax*4]
			mov		ecx, dword ptr [SetRect]
			lea		eax, [ebx+ecx*4]

			// eax：当前需要操作的像素的内存地址
			// ebx：一行像素的操作个数的计数器
			// edx：保存用于比较的数据

			// 初始化每一行的循环
			mov		ebx, 0
			jmp		CURRENT_LINE_PIX_BEGIN

			// 下一个像素的开始
		NEXT_LINE_PIX_BEGIN:
			add		ebx, 1

			// 当前一行的每一个循环的开始
		CURRENT_LINE_PIX_BEGIN:
			cmp		ebx, dword ptr [nLoops]
			jge		LINE_SET_END

			__asm
			{
				// 设置单个像素
				movzx	ecx, byte ptr [eax+3]
				cmp		ecx, edx
				jne		PIX_SET_END

				mov		cl, byte ptr [bySetA]
				mov		byte ptr [eax+3], cl

			PIX_SET_END:
				add		eax, 4
			}
			jmp		NEXT_LINE_PIX_BEGIN
		LINE_SET_END:
		}
		jmp		LINE_SET_BEING
	RECT_SET_END:
	}
}
