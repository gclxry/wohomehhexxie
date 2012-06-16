
#pragma once
#include "CDrawingBoard.h"

class CDrawingImage : public CDrawingBoard
{
public:
    CDrawingImage();
    virtual ~CDrawingImage();

	// ��һ���ڴ��д���
	void CreateByMem(BYTE *pImgFileMem, int nLen);
	// ���ļ��д���
	void CreateByFile(const char *pszFilePath);
	// ֱ�ӱ���Ϊһ��ָ����ʽ���ļ�
	bool SaveBoardToFile(const char *pszSavePath);

private:
	bool GetImageCLSID(const WCHAR* format, CLSID* pCLSID);
};
