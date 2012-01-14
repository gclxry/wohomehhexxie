
#pragma once

// zip文件中的文件类型
enum ZIP_FILE_TYPE
{
	ZFT_NORMAL		= 0,
	ZFT_IMAGE
};

// 压缩文件列表
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
