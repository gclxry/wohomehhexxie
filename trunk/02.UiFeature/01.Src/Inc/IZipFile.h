
#pragma once

// zip�ļ��е��ļ�����
enum ZIP_FILE_TYPE
{
	ZFT_NORMAL		= 0,
	ZFT_IMAGE
};

// ѹ���ļ��б�
struct ZIP_FILE 
{
	string strFileName;
	BYTE byFileType;
	DWORD dwSrcFileLen;
	DWORD dwZipDatalen;
	BYTE *pFileData;
};
// KEY:strFileName
typedef map<string, ZIP_FILE*>		ZIP_FILE_MAP;


class IZipFile
{
public:
};
