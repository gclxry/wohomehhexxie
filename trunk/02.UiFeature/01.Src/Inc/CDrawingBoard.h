
#pragma once
#include <Windows.h>

class IUiFeatureKernel;
class CDrawingBoard
{
public:
    CDrawingBoard();
    virtual ~CDrawingBoard();

	// ������
	// nWidth�����
	// nHeight���߶�
	// nDefaultColor��Ĭ�������ɫֵ
	// bReCreate��ÿ�ζ����´��������ܿ�Ⱥ͸߶��Ƿ����仯
	// bNoCreateInit��û�����´�����������Ƿ�ʹ��Ĭ����ɫֵ��ʼ���������ݿռ�
	// ����ֵ���壺�Ƿ񴴽���һ���µ��ڴ�DC
	bool Create(int nWidth, int nHeight, DWORD nDefaultColor = 0, bool bReCreate = false, bool bNoCreateInit = false);
	void Delete();
	HBITMAP& GetBmpHandle();
	HDC& GetSafeHdc();
	// ���� BGRA ˳���Ų���32λλͼ��Ϣ
	BYTE* GetBits();
	SIZE GetDcSize();

	// ����һ���ڴ�DC��¡
	bool Clone(CDrawingBoard& FromBoard, IUiFeatureKernel* pUiKernel);

	// ���Ƶ�����һ���ڴ�DC��
	bool AlphaBlendTo(CDrawingBoard& ToBoard, RECT ToRct, RECT FromRct, IUiFeatureKernel* pUiKernel, int nAlpha = 255);
	bool AlphaBlendTo(HDC hDc, RECT ToRct, RECT FromRct, IUiFeatureKernel* pUiKernel, int nAlpha = 255);

	// ��һ��DC���и���
	bool StretchBltFrom(CDrawingBoard& FromBoard, RECT FromRct, RECT ToRct);
	bool StretchBltFrom(HDC hDc, RECT FromRct, RECT ToRct);

	// ���Ƶ�����һ���ڴ�DC��
	bool BitBltTo(CDrawingBoard& ToBoard, RECT ToRct, RECT FromRct);
	bool BitBltTo(HDC hDc, RECT ToRct, RECT FromRct);

	// ��һ��DC���и���
	bool BitBltFrom(CDrawingBoard& FromBoard, RECT FromRct, RECT ToRct);
	bool BitBltFrom(HDC hDc, RECT FromRct, RECT ToRct);

protected:
	HBITMAP m_hBmp;
	HBITMAP m_hOldBmp;
	HDC m_hDC;
	BYTE* m_pBits;
	SIZE m_DcSize;
};
