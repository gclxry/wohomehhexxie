
#pragma once

//////////////////////////////////////////////////////////////////////////
// Ƥ���ļ��ļ��ṹ
// ||��4�ֽڡ��ļ�����----����2�ֽڡ������ļ����Ƴ���----�ļ�����----��4�ֽڡ�ԭ�ļ����ݳ���----��4�ֽڡ�ѹ�����ļ����ݳ���----ѹ���ļ����ݣ�||
//////////////////////////////////////////////////////////////////////////

// ѹ���ļ��б�
struct ZIP_FILE 
{
	string strFileName;
	DWORD dwSrcFileLen;
	DWORD dwZipDatalen;
	BYTE *pFileData;
};
// KEY:strFileName
typedef map<string, ZIP_FILE*>		ZIP_FILE_MAP;

// ����Ҫѹ�����ļ���׺��
typedef vector<string>				NO_COMPRESS_FILE_VEC;

class IZipFileList
{
public:
	virtual void RemoveFile(ZIP_FILE *pRemove) = 0;

//// ��ȡzip�ļ� //////////////////////////////////////////////////////////////////////
	// ��ȡzip�ļ�
	virtual bool ReadZipFile(const char *pZipFilePath) = 0;
	// ȡ�ý�ѹ���ļ�����ļ��б�
	virtual ZIP_FILE_MAP *GetUnZipFileMap() = 0;
	virtual ZIP_FILE *FindUnZipFile(char *pFileName) = 0;

//// ����zip�ļ� //////////////////////////////////////////////////////////////////////
	// ��ʼ��zip�ļ���pSrcFileDir����Ҫѹ����Դ�ļ�Ŀ¼
	virtual bool WriteZipInit(char *pSrcFileDir, char *pSaveZipFile) = 0;
	// д��һ���ļ���pFilePath�������������WriteZipInit������pSrcFileDir·�������·��
	virtual bool WriteZipAppendFile(char *pFilePath) = 0;
	// д��һ��buffer��pFilePath�������������WriteZipInit������pSrcFileDir·�������·��
	virtual bool WriteZipAppendBuffer(char *pFilePath, BYTE *pBuffer, int nBufferLen) = 0;
	virtual bool WriteZipEnd() = 0;

//////////////////////////////////////////////////////////////////////////
	// ���Ժ���
	virtual void TestWriteUnZipFile(char *pszOutDir) = 0;
};

///////////////////////////////////////////////////////////////////////////

IZipFileList *GetZipFileInterface();
typedef IZipFileList* (*GETZIPFILEINTERFACE)();
