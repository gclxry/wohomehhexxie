
#pragma once
#include "CDrawingImage.h"

// zip�ļ��е��ļ�����
enum ZIP_FILE_TYPE
{
	ZFT_NORMAL		= 0,
	ZFT_IMAGE
};

// ѹ���ļ��б�
struct ZIP_FILE 
{
	char strFileName[MAX_PATH + 1];
	BYTE byFileType;
	DWORD dwSrcFileLen;
	DWORD dwZipDatalen;
	BYTE *pFileData;
	CDrawingImage DrawImg;
};
// KEY:strFileName
typedef map<string, ZIP_FILE*>		ZIP_FILE_MAP;
