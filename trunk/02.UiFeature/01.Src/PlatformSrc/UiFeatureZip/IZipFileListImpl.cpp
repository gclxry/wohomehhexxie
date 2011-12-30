
#include "stdafx.h"
#include "IZipFileListImpl.h"
#include ".\zip\inc\zlib.h"
#include "..\..\Inc\UiFeatureDefs.h"

#pragma comment(lib, "./zip/lib/zlib.lib")
#pragma comment(lib, "./zip/lib/Unzip.lib")

IZipFileList *GetZipFileInterface()
{
	return IZipFileListImpl::GetInstance();
}

IZipFileListImpl* IZipFileListImpl::GetInstance()
{
	static IZipFileListImpl _ZipFileListInstance;
	return &_ZipFileListInstance;
}

IZipFileListImpl::IZipFileListImpl()
{
	m_ZipFileMap.clear();
	m_NoCompressFileVec.clear();
	m_NoCompressFileVec.push_back(".jpg");
	m_NoCompressFileVec.push_back(".jpeg");
	m_NoCompressFileVec.push_back(".PNG");
	m_NoCompressFileVec.push_back(".gif");
}

IZipFileListImpl::~IZipFileListImpl()
{
	Clear();
}

void IZipFileListImpl::Clear()
{
	for (ZIP_FILE_MAP::iterator pZipItem = m_ZipFileMap.begin(); pZipItem != m_ZipFileMap.end(); pZipItem++)
	{
		ZIP_FILE* pZip = pZipItem->second;
		if (pZip != NULL)
		{
			SAFE_DELETE(pZip->pFileData);
			SAFE_DELETE(pZip);
		}
	}
	m_ZipFileMap.clear();
}

void IZipFileListImpl::RemoveFile(ZIP_FILE *pRemove)
{
	if (m_ZipFileMap.size() <= 0 || pRemove == NULL)
		return;

	for (ZIP_FILE_MAP::iterator pZipItem = m_ZipFileMap.begin(); pZipItem != m_ZipFileMap.end(); pZipItem++)
	{
		ZIP_FILE* pZip = pZipItem->second;
		if (pZip == pRemove)
		{
			SAFE_DELETE(pZip->pFileData);
			SAFE_DELETE(pZip);
			m_ZipFileMap.erase(pZipItem);
			break;
		}
	}

	if (m_ZipFileMap.size() <= 0)
		m_ZipFileMap.clear();
}

// 初始化zip文件，pSrcFileDir：需要压缩的源文件目录
bool IZipFileListImpl::WriteZipInit(char *pSrcFileDir, char *pSaveZipFile)
{
	Clear();
	if (pSrcFileDir == NULL || pSaveZipFile == NULL || strlen(pSrcFileDir) <= 0 || strlen(pSaveZipFile) <= 0)
		return false;

	m_strSrcFileDir = pSrcFileDir;
	m_strSaveZipFile = pSaveZipFile;

	char pEnd = m_strSrcFileDir[m_strSrcFileDir.size() - 1];
	if (pEnd != '\\')
		m_strSrcFileDir += "\\";

	return true;
}

// 写入一段buffer
bool IZipFileListImpl::WriteZipAppendBuffer(char *pFilePath, BYTE *pBuffer, int nBufferLen)
{
	if (pFilePath == NULL || strlen(pFilePath) <= 0 || pBuffer == NULL)
		return false;

	if (nBufferLen <= 0)
		return true;

	ZIP_FILE *pFileItem = new ZIP_FILE;
	if (pFileItem == NULL)
		return false;

	pFileItem->strFileName = pFilePath;
	pFileItem->dwSrcFileLen = nBufferLen;
	pFileItem->dwZipDatalen = 0;
	pFileItem->pFileData = NULL;

	if (CheckFileNeedCompress(pFilePath))
	{
		uLong ulComLen = compressBound(nBufferLen);
		if (ulComLen <= 0)
		{
			SAFE_DELETE(pFileItem);
			return false;
		}

		pFileItem->dwZipDatalen = ulComLen;
		pFileItem->pFileData = new BYTE[ulComLen];
		if (pFileItem->pFileData == NULL)
		{
			SAFE_DELETE(pFileItem);
			return false;
		}

		if (compress(pFileItem->pFileData, &(pFileItem->dwZipDatalen), pBuffer, nBufferLen) != Z_OK)
		{
			SAFE_DELETE(pFileItem->pFileData);
			SAFE_DELETE(pFileItem);
			return false;
		}
	}
	else
	{
		pFileItem->dwZipDatalen = nBufferLen;
		pFileItem->pFileData = new BYTE[nBufferLen];
		if (pFileItem->pFileData == NULL)
		{
			SAFE_DELETE(pFileItem);
			return false;
		}

		memcpy(pFileItem->pFileData, pBuffer, nBufferLen);
	}

	m_ZipFileMap.insert(pair<string, ZIP_FILE*>(pFileItem->strFileName, pFileItem));
	return true;
}

// 写入一个文件，pFilePath：必须是相对于WriteZipInit函数的pSrcFileDir路径的相对路径
bool IZipFileListImpl::WriteZipAppendFile(char *pFilePath)
{
	if (pFilePath == NULL || strlen(pFilePath) <= 0 || m_strSrcFileDir.size() <= 0 || m_strSaveZipFile.size() <= 0)
		return false;

	string strPath = m_strSrcFileDir;
	strPath += pFilePath;

	WIN32_FILE_ATTRIBUTE_DATA FileAttr;
	if (!::GetFileAttributesExA(strPath.c_str(), GetFileExInfoStandard, &FileAttr))
		return false;

	FILE *pFile = NULL;
	fopen_s(&pFile, strPath.c_str(), "rb");
	if (pFile == NULL)
		return false;

	BYTE *pReadBuf = new BYTE[FileAttr.nFileSizeLow];
	if (pReadBuf == NULL)
	{
		fclose(pFile);
		return false;
	}

	int nReadCtns = 0;
	while(nReadCtns < (int)FileAttr.nFileSizeLow)
	{
		BYTE *pRead = pReadBuf + nReadCtns;
		int nNeedRead = FileAttr.nFileSizeLow - nReadCtns;

		int nRead = fread_s(pRead, nNeedRead, 1, nNeedRead, pFile);
		nReadCtns += nRead;

		if (errno != 0)
		{
			fclose(pFile);
			return false;
		}
	}

	if (nReadCtns != (int)FileAttr.nFileSizeLow)
	{
		fclose(pFile);
		return false;
	}

	ZIP_FILE *pFileItem = new ZIP_FILE;
	if (pFileItem == NULL)
	{
		fclose(pFile);
		SAFE_DELETE(pReadBuf);
		return false;
	}

	pFileItem->strFileName = pFilePath;
	pFileItem->dwSrcFileLen = FileAttr.nFileSizeLow;
	pFileItem->dwZipDatalen = 0;
	pFileItem->pFileData = NULL;
	if (CheckFileNeedCompress(pFilePath))
	{
		uLong ulComLen = compressBound(nReadCtns);
		if (ulComLen <= 0)
		{
			fclose(pFile);
			SAFE_DELETE(pReadBuf);
			SAFE_DELETE(pFileItem);
			return false;
		}

		pFileItem->dwZipDatalen = ulComLen;
		pFileItem->pFileData = new BYTE[ulComLen];
		if (pFileItem->pFileData == NULL)
		{
			fclose(pFile);
			SAFE_DELETE(pReadBuf);
			SAFE_DELETE(pFileItem);
			return false;
		}

		if (compress(pFileItem->pFileData, &(pFileItem->dwZipDatalen), pReadBuf, nReadCtns) != Z_OK)
		{
			fclose(pFile);
			SAFE_DELETE(pReadBuf);
			SAFE_DELETE(pFileItem->pFileData);
			SAFE_DELETE(pFileItem);
			return false;
		}
		SAFE_DELETE(pReadBuf);
	}
	else
	{
		pFileItem->dwZipDatalen = FileAttr.nFileSizeLow;
		pFileItem->pFileData = pReadBuf;
	}

	m_ZipFileMap.insert(pair<string, ZIP_FILE*>(pFileItem->strFileName, pFileItem));

	fclose(pFile);
	return true;
}

bool IZipFileListImpl::WriteZipEnd()
{
	if (m_ZipFileMap.size() <= 0)
		return false;

	FILE *pFile = NULL;
	fopen_s(&pFile, m_strSaveZipFile.c_str(), "wb");
	if (pFile == NULL)
		return false;

	// 写入总文件个数
	DWORD dwFileCtns = m_ZipFileMap.size();
	int nWriteLen = fwrite(&dwFileCtns, 1, sizeof(DWORD), pFile);
	if (nWriteLen != sizeof(DWORD))
	{
		fclose(pFile);
		return false;
	}

	// 写入单个文件
	for (ZIP_FILE_MAP::iterator pZipItem = m_ZipFileMap.begin(); pZipItem != m_ZipFileMap.end(); pZipItem++)
	{
		ZIP_FILE* pZip = pZipItem->second;
		if (pZip == NULL || pZip->pFileData == NULL || pZip->dwSrcFileLen <= 0 || pZip->dwZipDatalen <= 0 || pZip->strFileName.size() <= 0)
			continue;

		// 文件名称长度
		SHORT sNameLen = pZip->strFileName.size();
		nWriteLen = fwrite(&sNameLen, 1, sizeof(SHORT), pFile);
		if (nWriteLen != sizeof(SHORT))
		{
			fclose(pFile);
			return false;
		}

		// 文件名
		nWriteLen = fwrite(pZip->strFileName.c_str(), 1, sNameLen, pFile);
		if (nWriteLen != sNameLen)
		{
			fclose(pFile);
			return false;
		}

		// 原文件内容长度
		nWriteLen = fwrite(&(pZip->dwSrcFileLen), 1, sizeof(DWORD), pFile);
		if (nWriteLen != sizeof(DWORD))
		{
			fclose(pFile);
			return false;
		}

		// 压缩后文件内容长度
		nWriteLen = fwrite(&(pZip->dwZipDatalen), 1, sizeof(DWORD), pFile);
		if (nWriteLen != sizeof(DWORD))
		{
			fclose(pFile);
			return false;
		}

		// 文件内容
		nWriteLen = 0;
		while (nWriteLen < (int)(pZip->dwZipDatalen))
		{
			BYTE *pWrite = pZip->pFileData + nWriteLen;
			int nNeedWrite = pZip->dwZipDatalen - nWriteLen;
			int nWrite = fwrite(pWrite, 1, nNeedWrite, pFile);
			nWriteLen += nWrite;

			if (errno != 0)
			{
				fclose(pFile);
				return false;
			}
		}

		if (nWriteLen != (int)pZip->dwZipDatalen)
		{
			fclose(pFile);
			return false;
		}
	}

	fclose(pFile);
	return true;
}

//////////////////////////////////////////////////////////////////////////
// 读取zip文件
bool IZipFileListImpl::ReadZipFile(const char *pZipFilePath)
{
	Clear();
	if (pZipFilePath == NULL || strlen(pZipFilePath) <= 0)
		return false;

	FILE *pFile = NULL;
	fopen_s(&pFile, pZipFilePath, "rb");
	if (pFile == NULL)
		return false;

	DWORD nFileCtns = 0;
	int nReadLen = fread_s(&nFileCtns, sizeof(DWORD), 1, sizeof(DWORD), pFile);
	if (nReadLen != sizeof(DWORD))
	{
		fclose(pFile);
		return false;
	}

	for (int i = 0; i < (int)nFileCtns; i++)
	{
		SHORT sNameLen = 0;
		nReadLen = fread_s(&sNameLen, sizeof(SHORT), 1, sizeof(SHORT), pFile);
		if (nReadLen != sizeof(SHORT))
		{
			fclose(pFile);
			return false;
		}

		char szName[MAX_PATH + 1];
		memset(szName, 0, MAX_PATH + 1);
		nReadLen = fread_s(szName, MAX_PATH, 1, sNameLen, pFile);
		if (nReadLen != sNameLen)
		{
			fclose(pFile);
			return false;
		}

		DWORD dwSrcFileLen = 0;
		int nReadLen = fread_s(&dwSrcFileLen, sizeof(DWORD), 1, sizeof(DWORD), pFile);
		if (nReadLen != sizeof(DWORD))
		{
			fclose(pFile);
			return false;
		}

		DWORD dwZipDataLen = 0;
		nReadLen = fread_s(&dwZipDataLen, sizeof(DWORD), 1, sizeof(DWORD), pFile);
		if (nReadLen != sizeof(DWORD))
		{
			fclose(pFile);
			return false;
		}

		BYTE *pZipData = new BYTE[dwZipDataLen];
		if (pZipData == NULL)
		{
			fclose(pFile);
			return false;
		}
		nReadLen = 0;
		while(nReadLen < (int)dwZipDataLen)
		{
			BYTE *pRead = pZipData + nReadLen;
			int nNeedRead = dwZipDataLen - nReadLen;

			int nRead = fread_s(pRead, nNeedRead, 1, nNeedRead, pFile);
			nReadLen += nRead;

			if (errno != 0)
			{
				SAFE_DELETE(pZipData);
				fclose(pFile);
				return false;
			}
		}

		if (nReadLen != (int)dwZipDataLen)
		{
			SAFE_DELETE(pZipData);
			fclose(pFile);
			return false;
		}

		// 解压缩
		ZIP_FILE* pZipItem = new ZIP_FILE;
		if (pZipItem == NULL)
		{
			SAFE_DELETE(pZipData);
			fclose(pFile);
			return false;
		}

		pZipItem->strFileName = szName;
		pZipItem->dwSrcFileLen = dwSrcFileLen;
		pZipItem->dwZipDatalen = dwZipDataLen;
		pZipItem->pFileData = NULL;
		if (CheckFileNeedCompress(szName))
		{
			pZipItem->pFileData = new BYTE[dwSrcFileLen];
			if (pZipItem->pFileData == NULL)
			{
				SAFE_DELETE(pZipItem);
				SAFE_DELETE(pZipData);
				fclose(pFile);
				return false;
			}

			if (uncompress(pZipItem->pFileData, &(pZipItem->dwSrcFileLen), pZipData, pZipItem->dwZipDatalen) != Z_OK)
			{
				SAFE_DELETE(pZipItem->pFileData);
				SAFE_DELETE(pZipItem);
				SAFE_DELETE(pZipData);
				fclose(pFile);
				return false;
			}
			SAFE_DELETE(pZipData);
		}
		else
		{
			pZipItem->pFileData = pZipData;
		}

		m_ZipFileMap.insert(pair<string, ZIP_FILE*>(pZipItem->strFileName, pZipItem));
	}

	fclose(pFile);
	return true;
}

// 取得解压缩文件后的文件列表
ZIP_FILE_MAP* IZipFileListImpl::GetUnZipFileMap()
{
	return &m_ZipFileMap;
}

ZIP_FILE* IZipFileListImpl::FindUnZipFile(char *pFileName)
{
	if (pFileName == NULL || strlen(pFileName) <= 0)
		return NULL;

	string strName = pFileName;
	ZIP_FILE_MAP::iterator pZipItem = m_ZipFileMap.find(strName);
	if (pZipItem == m_ZipFileMap.end())
		return NULL;

	return (pZipItem->second);
}

void IZipFileListImpl::TestWriteUnZipFile(char *pszOutDir)
{
	if (pszOutDir == NULL || strlen(pszOutDir) <= 0)
		return;

	string strOutDir = pszOutDir;
	char pEnd = strOutDir[strOutDir.size() - 1];
	if (pEnd != '\\')
		strOutDir += "\\";

	for (ZIP_FILE_MAP::iterator pZipItem = m_ZipFileMap.begin(); pZipItem != m_ZipFileMap.end(); pZipItem++)
	{
		ZIP_FILE* pZip = pZipItem->second;
		if (pZip == NULL || pZip->pFileData == NULL || pZip->dwSrcFileLen <= 0 || pZip->dwZipDatalen <= 0 || pZip->strFileName.size() <= 0)
			continue;

		string strPath = strOutDir + pZip->strFileName;

		FILE *pFile = NULL;
		fopen_s(&pFile, strPath.c_str(), "wb");
		if (pFile == NULL)
			continue;

		// 文件内容
		int nWriteLen = 0;
		while (nWriteLen < (int)(pZip->dwSrcFileLen))
		{
			BYTE *pWrite = pZip->pFileData + nWriteLen;
			int nNeedWrite = pZip->dwSrcFileLen - nWriteLen;
			int nWrite = fwrite(pWrite, 1, nNeedWrite, pFile);
			nWriteLen += nWrite;

			if (errno != 0)
				break;
		}

		fclose(pFile);
	}
}

// 通过扩展名来判断文件是否需要加密
bool IZipFileListImpl::CheckFileNeedCompress(char *pFileName)
{
	if (pFileName == NULL)
		return false;

	char *pComBegin = NULL;
	int nCom = strlen(pFileName) - 1;
	while (nCom >= 0)
	{
		if (pFileName[nCom] == '.')
		{
			pComBegin = pFileName + nCom;
			break;
		}
		nCom--;
	}

	if (pComBegin == NULL)
		return false;

	for (NO_COMPRESS_FILE_VEC::iterator pExItem = m_NoCompressFileVec.begin(); pExItem != m_NoCompressFileVec.end(); pExItem++)
	{
		string strExName = *pExItem;
		if (lstrcmpiA(pComBegin, strExName.c_str()) == 0)
			return false;
	}

	return true;
}
