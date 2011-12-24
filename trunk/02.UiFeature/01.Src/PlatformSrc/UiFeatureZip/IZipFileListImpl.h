
#pragma once
#include "..\..\Inc\IZipFileList.h"

class IZipFileListImpl : public IZipFileList
{
public:
	IZipFileListImpl();
	virtual ~IZipFileListImpl();

	static IZipFileListImpl* GetInstance();

	virtual void RemoveFile(FILE_ITEM *pRemove);

//// 读取zip文件 //////////////////////////////////////////////////////////////////////
	// 读取zip文件
	virtual bool ReadZipFile(const char *pZipFilePath);
	// 取得解压缩文件后的文件列表
	virtual ZIP_FILE_MAP *GetUnZipFileMap();
	virtual FILE_ITEM *FindUnZipFile(char *pFileName);	

//// 创建zip文件 //////////////////////////////////////////////////////////////////////
	// 初始化zip文件，pSrcFileDir：需要压缩的源文件目录
	virtual bool InitWriteZip(char *pSrcFileDir, char *pSaveZipFile);
	// 写入一个文件，pFilePath：必须是相对于InitWriteZip函数的pSrcFileDir路径的相对路径
	virtual bool WriteToZip(char *pFilePath);
	virtual bool EndWriteZip();

//////////////////////////////////////////////////////////////////////////
	// 测试函数
	virtual void TestWriteUnZipFile(char *pszOutDir);

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
