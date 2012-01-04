
#include "stdafx.h"
#include "..\..\Inc\CDrawingImage.h"
#include "..\..\Inc\UiFeatureDefs.h"

CDrawingImage::CDrawingImage(void)
{
    m_pBits = NULL;
    m_hBmp = NULL;
	m_hDC = NULL;
	m_DcSize.cx = m_DcSize.cy = 0;
}

CDrawingImage::~CDrawingImage(void)
{
   Delete();
}

SIZE CDrawingImage::GetDcSize()
{
	return m_DcSize;
}

HDC& CDrawingImage::GetSafeHdc()
{
	return m_hDC;
}

HBITMAP& CDrawingImage::GetBmpHandle()
{
	return m_hBmp;
}

BYTE* CDrawingImage::GetBits()
{
	return m_pBits;
}

void CDrawingImage::Delete()
{
	if (m_hBmp != NULL)
	{
		::DeleteObject(m_hBmp);
		m_hBmp = NULL;
	}

	if (m_hDC != NULL)
	{
		::DeleteDC(m_hDC);
		m_hDC = NULL;
	}

	m_pBits = NULL;
	m_DcSize.cx = m_DcSize.cy = 0;
}

// 从一段内存中创建
void CDrawingImage::CreateByMem(BYTE *pImgFileMem, int nLen)
{
	if (pImgFileMem == NULL || nLen <= 0)
		return;

}

// 从文件内存中创建
void CDrawingImage::CreateByFile(const char *pszFilePath)
{
	if (pszFilePath == NULL || strlen(pszFilePath) <= 0)
		return;

	WIN32_FILE_ATTRIBUTE_DATA FileAttr;
	if (!::GetFileAttributesExA(pszFilePath, GetFileExInfoStandard, &FileAttr))
		return;

	FILE *pFile = NULL;
	fopen_s(&pFile, pszFilePath, "rb");
	if (pFile == NULL)
		return;

	BYTE *pReadBuf = new BYTE[FileAttr.nFileSizeLow];
	if (pReadBuf == NULL)
	{
		fclose(pFile);
		return;
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
			SAFE_DELETE(pReadBuf);
			fclose(pFile);
			return;
		}
	}

	if (nReadCtns != (int)FileAttr.nFileSizeLow)
	{
		SAFE_DELETE(pReadBuf);
		fclose(pFile);
		return;
	}



	SAFE_DELETE(pReadBuf);
}
