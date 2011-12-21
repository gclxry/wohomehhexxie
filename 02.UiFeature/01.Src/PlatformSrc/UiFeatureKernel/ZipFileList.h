
#pragma once

//////////////////////////////////////////////////////////////////////////
// Ƥ���ļ��ļ��ṹ
// ||��4�ֽڡ��ļ�����----����2�ֽڡ������ļ����Ƴ���----�ļ�����----��4�ֽڡ�ԭ�ļ����ݳ���----��4�ֽڡ�ѹ�����ļ����ݳ���----ѹ���ļ����ݣ�||
//////////////////////////////////////////////////////////////////////////

// ѹ���ļ��б�
struct FILE_ITEM 
{
	string strFileName;
	DWORD dwSrcFileLen;
	DWORD dwZipDatalen;
	BYTE *pFileData;
};
// KEY:strFileName
typedef map<string, FILE_ITEM*>		ZIP_FILE_MAP;

// ����Ҫѹ�����ļ���׺��
typedef vector<string>				NO_COMPRESS_FILE_VEC;

class CZipFileList
{
public:
	CZipFileList();
	virtual ~CZipFileList();

//// ��ȡzip�ļ� //////////////////////////////////////////////////////////////////////
	// ��ȡzip�ļ�
	bool ReadZipFile(const char *pZipFilePath);
	// ȡ�ý�ѹ���ļ�����ļ��б�
	ZIP_FILE_MAP *GetUnZipFileMap();
	FILE_ITEM *FindUnZipFile(char *pFileName);	

//// ����zip�ļ� //////////////////////////////////////////////////////////////////////
	// ��ʼ��zip�ļ���pSrcFileDir����Ҫѹ����Դ�ļ�Ŀ¼
	bool InitWriteZip(char *pSrcFileDir, char *pSaveZipFile);
	// д��һ���ļ���pFilePath�������������InitWriteZip������pSrcFileDir·�������·��
	bool WriteToZip(char *pFilePath);
	bool EndWriteZip();

//////////////////////////////////////////////////////////////////////////
	// ���Ժ���
	void TestWriteUnZipFile(char *pszOutDir);

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
