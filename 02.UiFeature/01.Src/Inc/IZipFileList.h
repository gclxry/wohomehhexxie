
#pragma once

//////////////////////////////////////////////////////////////////////////
// 皮肤文件文件结构
// ||【4字节】文件个数----（【2字节】单个文件名称长度----文件名称----【4字节】原文件内容长度----【4字节】压缩后文件内容长度----压缩文件内容）||
//////////////////////////////////////////////////////////////////////////

// 压缩文件列表
struct FILE_ITEM 
{
	string strFileName;
	DWORD dwSrcFileLen;
	DWORD dwZipDatalen;
	BYTE *pFileData;
};
// KEY:strFileName
typedef map<string, FILE_ITEM*>		ZIP_FILE_MAP;

// 不需要压缩的文件后缀名
typedef vector<string>				NO_COMPRESS_FILE_VEC;

class IZipFileList
{
public:

//// 读取zip文件 //////////////////////////////////////////////////////////////////////
	// 读取zip文件
	virtual bool ReadZipFile(const char *pZipFilePath) = 0;
	// 取得解压缩文件后的文件列表
	virtual ZIP_FILE_MAP *GetUnZipFileMap() = 0;
	virtual FILE_ITEM *FindUnZipFile(char *pFileName) = 0;

//// 创建zip文件 //////////////////////////////////////////////////////////////////////
	// 初始化zip文件，pSrcFileDir：需要压缩的源文件目录
	virtual bool InitWriteZip(char *pSrcFileDir, char *pSaveZipFile) = 0;
	// 写入一个文件，pFilePath：必须是相对于InitWriteZip函数的pSrcFileDir路径的相对路径
	virtual bool WriteToZip(char *pFilePath) = 0;
	virtual bool EndWriteZip() = 0;

//////////////////////////////////////////////////////////////////////////
	// 测试函数
	virtual void TestWriteUnZipFile(char *pszOutDir) = 0;
};

///////////////////////////////////////////////////////////////////////////

IZipFileList *GetZipFileInterface();
typedef IZipFileList* (*GETZIPFILEINTERFACE)();
