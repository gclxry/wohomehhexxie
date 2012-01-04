
#pragma once
#include <Windows.h>

class CDrawingImage
{
public:
    CDrawingImage(void);
    virtual ~CDrawingImage(void);

	// ������nWidth�����ȡ�nHeight���߶ȡ�nDefaultColor��Ĭ�������ɫֵ��bReCreate��ÿ�ζ����´��������ܿ��Ⱥ͸߶��Ƿ����仯
	// bNoCreateInit��û�����´�����������Ƿ�ʹ��Ĭ����ɫֵ��ʼ���������ݿռ�
	void Create(int nWidth, int nHeight, DWORD nDefaultColor = 0, bool bReCreate = false, bool bNoCreateInit = false);
	void Delete();
	HBITMAP& GetBmpHandle();
	HDC& GetSafeHdc();
	BYTE* GetBits();
	SIZE GetDcSize();

private:
	HBITMAP m_hBmp;
	HDC m_hDC;
	BYTE* m_pBits;
	SIZE m_DcSize;
};