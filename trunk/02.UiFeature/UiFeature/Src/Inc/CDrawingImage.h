
#pragma once
#include "CDrawingBoard.h"

class CDrawingImage : public CDrawingBoard
{
public:
    CDrawingImage();
    virtual ~CDrawingImage();

	// 从一段内存中创建
	void CreateByMem(BYTE *pImgFileMem, int nLen);
	// 从文件中创建
	void CreateByFile(const char *pszFilePath);
	// 直接保存为一个指定格式的文件
	bool SaveBoardToFile(const char *pszSavePath);

private:
	bool GetImageCLSID(const WCHAR* format, CLSID* pCLSID);
};
