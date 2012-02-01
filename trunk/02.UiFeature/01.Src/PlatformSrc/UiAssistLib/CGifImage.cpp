
#include "stdafx.h"
#include "CGifImage.h"
#include <iostream>
#include <atlcomcli.h>
#include "..\..\Inc\UiFeatureDefs.h"

CGifImage::CGifImage()
{
	m_pImg = NULL;
	m_nFrameCount = 0;
	m_pPropertyItem = NULL;
	m_nCurFrame = 0;
}

CGifImage::~CGifImage()
{
	Release();
}

int CGifImage::GetCurrentPlayFrame()
{
	return m_nCurFrame;
}

int CGifImage::SetCurrentPlayFrame(int nFrame)
{
	if (m_pImg == NULL || m_pPropertyItem == NULL)
		return -1;

	m_nCurFrame = nFrame;
	
	if (m_nCurFrame < 0)
		m_nCurFrame = 0;

	if (m_nCurFrame >= m_nFrameCount)
		m_nCurFrame = 0;

	// Guid��ֵ����ʾGIFΪ FrameDimensionTime����ʾTIFʱΪ FrameDimensionPage
	GUID Guid = FrameDimensionTime;
	// �������õ�ǰ�Ļ����֡
	m_pImg->SelectActiveFrame(&Guid, m_nCurFrame);
	return ((((long*)(m_pPropertyItem->value))[m_nCurFrame]) * 10);
}

// ��һ���ڴ��д���
bool CGifImage::CreateByMem(BYTE *pImgFileMem, int nLen)
{
	if (pImgFileMem == NULL || nLen <= 0)
		return false;

	Release();
	CComPtr<IStream> ImgStream;
	if (::CreateStreamOnHGlobal(NULL, TRUE, &ImgStream) != S_OK)
		return false;

	ImgStream->Write(pImgFileMem, nLen, NULL);
	m_pImg = Gdiplus::Bitmap::FromStream(ImgStream);
	if (m_pImg == NULL)
		return false;

	ImgStream.Release();
	Init();
	return true;
}

void CGifImage::Init()
{
	if (m_pImg != NULL)
	{
		UINT nCount = m_pImg->GetFrameDimensionsCount();
		GUID* pDimensionIDs = new GUID[nCount];

		// �õ���֡�Ķ����б�
		m_pImg->GetFrameDimensionsList(pDimensionIDs, nCount);

		//��ȡ��֡��
		m_nFrameCount = m_pImg->GetFrameCount(&pDimensionIDs[0]);

		// ����ͼ�����������Ŀ PropertyItemEquipMake.
		// ��ȡ����Ŀ�Ĵ�С.
		int nSize = m_pImg->GetPropertyItemSize(PropertyTagFrameDelay);
		if (nSize > 0)
		{
			// Ϊ������Ŀ����ռ�.
			m_pPropertyItem = (PropertyItem*)malloc(nSize);
			m_pImg->GetPropertyItem(PropertyTagFrameDelay, nSize, m_pPropertyItem);
		}
		delete pDimensionIDs;
	}
}

void CGifImage::Release()
{
	SAFE_FREE(m_pPropertyItem);

	m_pImg = NULL;
	m_nFrameCount = 0;
	m_pPropertyItem = NULL;

	SAFE_DELETE(m_pImg);
}

bool CGifImage::IsAnimatedGIF()
{
	return (m_pPropertyItem != NULL && m_nFrameCount > 1);
}

int CGifImage::GetFrameCounts()
{
	return m_nFrameCount;
}

PropertyItem* CGifImage::GetFrameParam()
{
	return m_pPropertyItem;
}

Bitmap* CGifImage::GetImage()
{
	return m_pImg;
}

SIZE CGifImage::GetImageSize()
{
	SIZE sizeImg;
	sizeImg.cx = sizeImg.cy = 0;
	if (m_pImg != NULL)
	{
		sizeImg.cx = m_pImg->GetWidth();
		sizeImg.cy = m_pImg->GetHeight();
	}

	return sizeImg;
}

// ���ļ��ڴ��д���
bool CGifImage::CreateByFile(const char *pszFilePath)
{
	if (pszFilePath == NULL || strlen(pszFilePath) <= 0)
		return false;

	WIN32_FILE_ATTRIBUTE_DATA FileAttr;
	if (!::GetFileAttributesExA(pszFilePath, GetFileExInfoStandard, &FileAttr))
		return false;

	FILE *pFile = NULL;
	fopen_s(&pFile, pszFilePath, "rb");
	if (pFile == NULL)
		return false;

	BYTE *pReadBuf = new BYTE[FileAttr.nFileSizeLow];
	if (pReadBuf == NULL)
	{
		fclose(pFile);
		return false;
	}

	int nReadCtns = 0;
	while (nReadCtns < (int)FileAttr.nFileSizeLow)
	{
		BYTE *pRead = pReadBuf + nReadCtns;
		int nNeedRead = FileAttr.nFileSizeLow - nReadCtns;

		int nRead = fread_s(pRead, nNeedRead, 1, nNeedRead, pFile);
		nReadCtns += nRead;
	}

	fclose(pFile);
	if (nReadCtns != (int)FileAttr.nFileSizeLow)
	{
		SAFE_DELETE(pReadBuf);
		return false;
	}

	bool bRet = CreateByMem(pReadBuf, nReadCtns);
	SAFE_DELETE(pReadBuf);
	return bRet;
}
