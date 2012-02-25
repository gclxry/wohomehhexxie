
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
	bool Create(int nWidth, int nHeight, DWORD nDefaultColor = 0, bool bReCreate = false, bool bNoCreateInit = false);
	void Delete();
	HBITMAP& GetBmpHandle();
	HDC& GetSafeHdc();
	BYTE* GetBits();
	SIZE GetDcSize();
	// ���Ƶ�����һ���ڴ�DC��
	bool BitBltTo(CDrawingBoard& ToBoard, RECT ToRct, RECT FromRct);
	// ���Ƶ�����һ���ڴ�DC��
	bool AlphaBlendTo(CDrawingBoard& ToBoard, RECT ToRct, RECT FromRct, IUiFeatureKernel* pUiKernel, int nAlpha = 255);

protected:
	HBITMAP m_hBmp;
	HBITMAP m_hOldBmp;
	HDC m_hDC;
	BYTE* m_pBits;
	SIZE m_DcSize;
};
