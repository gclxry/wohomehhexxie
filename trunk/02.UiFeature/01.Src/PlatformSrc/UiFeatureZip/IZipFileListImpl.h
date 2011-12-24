
#pragma once
#include "..\..\Inc\IZipFileList.h"

class IZipFileListImpl : public IZipFileList
{
public:
	IZipFileListImpl();
	virtual ~IZipFileListImpl();

	static IZipFileListImpl* GetInstance();

	virtual void RemoveFile(FILE_ITEM *pRemove);

//// ��ȡzip�ļ� //////////////////////////////////////////////////////////////////////
	// ��ȡzip�ļ�
	virtual bool ReadZipFile(const char *pZipFilePath);
	// ȡ�ý�ѹ���ļ�����ļ��б�
	virtual ZIP_FILE_MAP *GetUnZipFileMap();
	virtual FILE_ITEM *FindUnZipFile(char *pFileName);	

//// ����zip�ļ� //////////////////////////////////////////////////////////////////////
	// ��ʼ��zip�ļ���pSrcFileDir����Ҫѹ����Դ�ļ�Ŀ¼
	virtual bool InitWriteZip(char *pSrcFileDir, char *pSaveZipFile);
	// д��һ���ļ���pFilePath�������������InitWriteZip������pSrcFileDir·�������·��
	virtual bool WriteToZip(char *pFilePath);
	virtual bool EndWriteZip();

//////////////////////////////////////////////////////////////////////////
	// ���Ժ���
	virtual void TestWriteUnZipFile(char *pszOutDir);

private:
	void Clear();
	// ͨ����չ�����ж��ļ��Ƿ���Ҫ����
	bool CheckFileNeedCompress(char *pFileName);

private:
	ZIP_FILE_MAP m_ZipFileMap;
	NO_COMPRESS_FILE_VEC m_NoCompressFileVec;

//////////////////////////////////////////////////////////////////////////
	// д��zip��
	string m_strSrcFileDir;
	string m_strSaveZipFile;
};
