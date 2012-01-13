
#include "stdafx.h"
#include <iostream>
#include <atlcomcli.h>
#include "..\..\Inc\CDrawingImage.h"
#include "..\..\Inc\UiFeatureDefs.h"

CDrawingImage::CDrawingImage(void)
{
	CoInitialize(NULL);
}

CDrawingImage::~CDrawingImage(void)
{
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
	while (nReadCtns < (int)FileAttr.nFileSizeLow)
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

	CreateByMem(pReadBuf, nReadCtns);

	SAFE_DELETE(pReadBuf);
	fclose(pFile);
}

// 从一段内存中创建
void CDrawingImage::CreateByMem(BYTE *pImgFileMem, int nLen)
{
	if (pImgFileMem == NULL || nLen <= 0)
		return;

	Delete();
	CComPtr<IStream> ImgStream;
	if (::CreateStreamOnHGlobal(NULL, TRUE, &ImgStream) != S_OK)
		return;

	ImgStream->Write(pImgFileMem, nLen, NULL);
	Bitmap* pBitmap = Gdiplus::Bitmap::FromStream(ImgStream);
	if (pBitmap == NULL)
		return;

	Create(pBitmap->GetWidth(), pBitmap->GetHeight(), 0, false, true);
	if (IS_SAFE_HANDLE(m_hDC))
	{
		Graphics DoGrap(m_hDC);
		DoGrap.DrawImage(pBitmap, 0, 0);
	}

	SAFE_DELETE(pBitmap);
	ImgStream.Release();
}
