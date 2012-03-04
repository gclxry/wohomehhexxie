
#pragma once

// 32λARGB��ɫֵ����
#define BGRA_MARK(b,g,r,a)          (((BYTE)(b)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(r))<<16)|(((DWORD)(BYTE)(a))<<24))

class CMmxBase
{
public:
	CMmxBase();
	virtual ~CMmxBase();

	// �滻ָ����Alphaֵ��
	// pbyDst���ڴ�λͼ��BTIMAP����
	// DstSize���ڴ�λͼ�Ĵ�С����λ����
	// SetRect����Ҫ���õ�λͼ��λ��
	// byComA��ָ����Ҫ�滻��Alphaֵ
	// bySetA��alphaֵ
	virtual void BGRA32_CoverAlpha(__inout BYTE *pbyDst, __in SIZE DstSize, __in RECT SetRect, __in BYTE byComA, __in BYTE bySetA);

protected:
	// ���÷���BITMAP�ڴ����ݵľ���
	void SetCoverRect(__in SIZE DstSize, __inout RECT &SetRect);
};
