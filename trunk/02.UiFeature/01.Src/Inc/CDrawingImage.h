
#pragma once
#include <Windows.h>

class CDrawingImage
{
public:
    CDrawingImage(void);
    virtual ~CDrawingImage(void);

	// 从一段内存中创建
	void CreateByMem(BYTE *pImgFileMem, int nLen);
	// 从文件内存中创建
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
