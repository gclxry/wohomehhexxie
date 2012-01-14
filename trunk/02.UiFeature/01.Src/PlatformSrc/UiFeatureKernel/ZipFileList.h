
#pragma once
#include "..\..\Inc\IZipFile.h"

//////////////////////////////////////////////////////////////////////////
// Ƥ���ļ��ļ��ṹ
// ||��4�ֽڡ��ļ�����----����1�ֽڡ��ļ�����----��2�ֽڡ������ļ����Ƴ���----�ļ�����----��4�ֽڡ�ԭ�ļ����ݳ���----��4�ֽڡ�ѹ�����ļ����ݳ���----ѹ���ļ����ݣ�||
//////////////////////////////////////////////////////////////////////////

// ����Ҫѹ�����ļ���׺��
typedef vector<string>				NO_COMPRESS_FILE_VEC;

class CZipFileList : public IZipFile
{
public:
	CZipFileList();
	virtual ~CZipFileList();

	static CZipFileList* GetInstance();

	virtual void RemoveFile(ZIP_FILE *pRemove);

//// ��ȡzip�ļ� //////////////////////////////////////////////////////////////////////
	// ��ȡzip�ļ�
	virtual bool ReadZipFile(const char *pZipFilePath);
	// ȡ�ý�ѹ���ļ�����ļ��б�
	virtual ZIP_FILE_MAP *GetUnZipFileMap();
	virtual ZIP_FILE *FindUnZipFile(char *pFileName);

//// ����zip�ļ� //////////////////////////////////////////////////////////////////////
	// ��ʼ��zip�ļ���pSrcFileDir����Ҫѹ����Դ�ļ�Ŀ¼
	virtual bool WriteZipInit(char *pSrcFileDir, char *pSaveZipFile);
	// д��һ���ļ���pFileName�������������WriteZipInit������pSrcFileDir·�������·��
	virtual bool WriteZipAppendFile(char *pFileName, ZIP_FILE_TYPE ZipType);
	// д��һ��buffer��pFileName�������������WriteZipInit������pSrcFileDir·�������·��
	virtual bool WriteZipAppendBuffer(char *pFileName, BYTE *pBuffer, int nBufferLen, ZIP_FILE_TYPE ZipType);
	// ��zip�ļ�д��һ������
	virtual bool WriteZipAppendStruct(ZIP_FILE *pNormalFile);
	virtual bool WriteZipEnd(bool bEntToClear);

//////////////////////////////////////////////////////////////////////////
	// ���Ժ���������ѹ����ļ�д�뱾��һ��ָ��Ŀ¼
	virtual void TestWriteUnZipFile(char *pszOutDir);

private:
	void Clear();
	// ͨ����չ�����ж��ļ��Ƿ���Ҫ����
	bool CheckFileNeedCompress(char *pFileName);
	bool FindFileName(char *pFileName);

private:
	ZIP_FILE_MAP m_ZipFileMap;
	NO_COMPRESS_FILE_VEC m_NoCompressFileVec;

//////////////////////////////////////////////////////////////////////////
	// д��zip��
	string m_strSrcFileDir;
	string m_strSaveZipFile;
};
