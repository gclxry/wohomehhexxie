
#pragma once
#include "CDrawingBoard.h"

class CDrawingImage : public CDrawingBoard
{
public:
    CDrawingImage();
    virtual ~CDrawingImage();

	// 从一段内存中创建
	void CreateByMem(BYTE *pImgFileMem, int nLen);
	// 从文件内存中创建
	void CreateByFile(const char *pszFilePath);
};
