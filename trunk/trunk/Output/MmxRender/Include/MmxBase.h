
// �������ظ��ǵ� alpha �ں��㷨
// dst = ((ovr - dst) * ovr.alpha) / 256 + dst
// Dst.Red = Src.Red * Src.alpha + (1-Src.alpha) * Dst.Red ;
// Dst.Green = Src.Green * Src.alpha + (1-Src.alpha) * Dst.Green;
// Dst.Blue = Src.Blue * Src.alpha + (1-Src.alpha) * Dst.Blue ;
// Dst.Alpha = 1 - (1 - Src.Alpha1) * ( 1 - Dst.Alpha)

#pragma once

#include <atltypes.h>
#include "CPUID.h"

// 32λARGB��ɫֵ����
#define BGRA_MARK(b,g,r,a)          (((BYTE)(b)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(r))<<16)|(((DWORD)(BYTE)(a))<<24))

class CMmxBase
{
public:
	CMmxBase(void);
	~CMmxBase(void);

	// �滻ָ����Alphaֵ��
	// pbyDst���ڴ�λͼ��BTIMAP����
	// DstSize���ڴ�λͼ�Ĵ�С����λ����
	// SetRect����Ҫ���õ�λͼ��λ��
	// byComA��ָ����Ҫ�滻��Alphaֵ
	// bySetA��alphaֵ
	virtual void ARGB32_CoverAlpha(__inout BYTE *pbyDst, __in CSize DstSize, __in CRect SetRect, __in BYTE byComA, __in BYTE bySetA);

protected:
	// ���÷���BITMAP�ڴ����ݵľ���
	virtual void SetCoverRect(__in CSize DstSize, __inout CRect &SetRect);

protected:
	CPUID m_CpuSupport;
};
