
#pragma once
#include <Windows.h>

class CMemoryDC
{
public:
    CMemoryDC(void);
    virtual ~CMemoryDC(void);

	// ��������ȡ��߶ȡ�Ĭ�������ɫֵ��ÿ�ζ����´����������´�����������Ƿ�ʹ��Ĭ����ɫֵ���
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
