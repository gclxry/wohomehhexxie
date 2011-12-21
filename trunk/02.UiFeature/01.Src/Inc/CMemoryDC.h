
#pragma once
#include <Windows.h>

class CMemoryDC
{
public:
    CMemoryDC(void);
    virtual ~CMemoryDC(void);

	// 参数：宽度、高度、默认填充颜色值、每次都重新创建、不重新创建的情况下是否使用默认颜色值填充
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
