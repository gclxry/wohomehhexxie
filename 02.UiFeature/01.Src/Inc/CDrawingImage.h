
#pragma once
#include "CDrawingBoard.h"

class CDrawingImage : public CDrawingBoard
{
public:
    CDrawingImage();
    virtual ~CDrawingImage();

	// ��һ���ڴ��д���
	void CreateByMem(BYTE *pImgFileMem, int nLen);
	// ���ļ��ڴ��д���
	void CreateByFile(const char *pszFilePath);
};
