
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

class CZipFileList
{
public:
	CZipFileList();
	virtual ~CZipFileList();

//// 读取zip文件 //////////////////////////////////////////////////////////////////////
	// 读取zip文件
	bool ReadZipFile(const char *pZipFilePath);
	// 取得解压缩文件后的文件列表
	ZIP_FILE_MAP *GetUnZipFileMap();
	FILE_ITEM *FindUnZipFile(char *pFileName);	

//// 创建zip文件 //////////////////////////////////////////////////////////////////////
	// 初始化zip文件，pSrcFileDir：需要压缩的源文件目录
	bool InitWriteZip(char *pSrcFileDir, char *pSaveZipFile);
	// 写入一个文件，pFilePath：必须是相对于InitWriteZip函数的pSrcFileDir路径的相对路径
	bool WriteToZip(char *pFilePath);
	bool EndWriteZip();

//////////////////////////////////////////////////////////////////////////
	// 测试函数
	void TestWriteUnZipFile(char *pszOutDir);

private:
	void Clear();
	// 通过扩展名来判断文件是否需要加密
	bool CheckFileNeedCompress(char *pFileName);

private:
	ZIP_FILE_MAP m_ZipFileMap;
	NO_COMPRESS_FILE_VEC m_NoCompressFileVec;

//////////////////////////////////////////////////////////////////////////
	// 写入zip用
	string m_strSrcFileDir;
	string m_strSaveZipFile;
};
