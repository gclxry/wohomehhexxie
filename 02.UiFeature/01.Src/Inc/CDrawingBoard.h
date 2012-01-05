
#pragma once
#include <Windows.h>

class CDrawingBoard
{
public:
    CDrawingBoard();
    virtual ~CDrawingBoard();

	// 参数：nWidth：宽度、nHeight：高度、nDefaultColor：默认填充颜色值、bReCreate：每次都重新创建，不管宽度和高度是否发生变化
	// bNoCreateInit：没有重新创建的情况下是否使用默认颜色值初始化整个数据空间
	void Create(int nWidth, int nHeight, DWORD nDefaultColor = 0, bool bReCreate = false, bool bNoCreateInit = false);
	void Delete();
	HBITMAP& GetBmpHandle();
	HDC& GetSafeHdc();
	BYTE* GetBits();
	SIZE GetDcSize();

protected:
	HBITMAP m_hBmp;
	HDC m_hDC;
	BYTE* m_pBits;
	SIZE m_DcSize;
};
