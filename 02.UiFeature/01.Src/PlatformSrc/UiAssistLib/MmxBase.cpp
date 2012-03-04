
#include "StdAfx.h"
#include "MmxBase.h"

CMmxBase::CMmxBase()
{
}

CMmxBase::~CMmxBase()
{
}

// ���÷���BITMAP�ڴ����ݵľ���
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

	// ��ת����
	int nHeight = SetRect.bottom - SetRect.top;
	int nTop = DstSize.cy - SetRect.top - nHeight;

	SetRect.top = nTop;
	SetRect.bottom = SetRect.top + nHeight;
}

// �����ڴ�ָ�������Alphaֵ
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
		// edx���������ڱȽ�alpha��ֵ
		movzx	edx, byte ptr [byComA]
		jmp		CURRENT_LINE_SET_BEING

	LINE_SET_BEING:
		add		dword ptr [nLine], 1

	CURRENT_LINE_SET_BEING:
		mov		ecx, dword ptr [nLineEnd]
		cmp		dword ptr [nLine], ecx
		jge		RECT_SET_END

		// ����һ������
		__asm
		{
			// ����ÿһ�п�ʼ�����ص�ַ������ eax
			// C���Լ��㹫ʽ��BYTE *pbyLineDst = pbyDst + (DstSize.cx * nLine * 4) + (SetRect.left * 4);
			mov		eax, dword ptr [DstSize]
			imul	eax, dword ptr [nLine]
			mov		ecx, dword ptr [pbyDst]
			lea		ebx, [ecx+eax*4]
			mov		ecx, dword ptr [SetRect]
			lea		eax, [ebx+ecx*4]

			// eax����ǰ��Ҫ���������ص��ڴ��ַ
			// ebx��һ�����صĲ��������ļ�����
			// edx���������ڱȽϵ�����

			// ��ʼ��ÿһ�е�ѭ��
			mov		ebx, 0
			jmp		CURRENT_LINE_PIX_BEGIN

			// ��һ�����صĿ�ʼ
		NEXT_LINE_PIX_BEGIN:
			add		ebx, 1

			// ��ǰһ�е�ÿһ��ѭ���Ŀ�ʼ
		CURRENT_LINE_PIX_BEGIN:
			cmp		ebx, dword ptr [nLoops]
			jge		LINE_SET_END

			__asm
			{
				// ���õ�������
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
