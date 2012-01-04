
#pragma once
#include <Windows.h>

class CDrawingImage
{
public:
    CDrawingImage(void);
    virtual ~CDrawingImage(void);

	// ��һ���ڴ��д���
	void CreateByMem(BYTE *pImgFileMem, int nLen);
	// ���ļ��ڴ��д���
	void CreateByFile(const char *pszFilePath);

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
