
#include "stdafx.h"
#include "ResImage.h"
#include "Win32BaseDlg.h"

CResImage::CResImage(void)
{
	m_pBmp = NULL;
	m_pPngImg = NULL;
	m_GifImg.m_pImg = NULL;
	m_hMem = NULL;
	m_ImgType = IT_BMP;
	m_bIsFromRes = true;
}

CResImage::~CResImage(void)
{
	FreeResImage();
}

Image * CResImage::GetImage()
{
	if (m_ImgType == IT_BMP)
	{
		return m_pBmp;
	}
	else if (m_ImgType == IT_PNG)
	{
		return m_pPngImg;
	}
	else if (m_ImgType == IT_GIF)
	{
		return m_GifImg.m_pImg;
	}

	return NULL;
}

void CResImage::FreeResImage()
{
	if (IsReady())
	{
		m_ImgType = IT_BMP;
		SAVE_DELETE(m_pBmp);

		if (m_bIsFromRes)
		{
			if (m_hMem != NULL)
				GlobalFree(m_hMem);

			m_pPngImg = NULL;
			m_GifImg.m_pImg = NULL;
			m_GifImg.Release();
			m_hMem = NULL;
		}
		else
		{
			SAVE_DELETE(m_pPngImg);
			SAVE_DELETE(m_GifImg.m_pImg);

			m_GifImg.Release();
		}
	}
}

bool CResImage::LoadImageFromFile(CString strPath, IMAGE_TYPE nType)
{
	FreeResImage();

	m_bIsFromRes = false;
	m_ImgType = nType;
	if (m_ImgType == IT_BMP)
	{
		m_pBmp = LoadBmpImage(strPath);
	}
	else if (m_ImgType == IT_PNG)
	{
		m_pPngImg = LoadImage(strPath);
	}
	else if (m_ImgType == IT_GIF)
	{
		m_GifImg.m_pImg = LoadImage(strPath);
		m_GifImg.Init();
	}

	return ((m_pBmp != NULL) || (m_pPngImg != NULL) || (m_GifImg.m_pImg != NULL));
}

Bitmap * CResImage::LoadBmpImage(CString strPath)
{
	Bitmap * pBmp = Bitmap::FromFile(strPath);
	Status st = pBmp->GetLastStatus();
	if (st != Ok)
		SAVE_DELETE(pBmp);

	return pBmp;
}

Image* CResImage::LoadImage(CString strPath)
{
	Image * pImage = Image::FromFile(strPath);
	Status st = pImage->GetLastStatus();
	if (st != Ok)
		SAVE_DELETE(pImage);

	return pImage;
}

bool CResImage::LoadImageFromRes(UINT nID, IMAGE_TYPE nType)
{
	FreeResImage();

	m_bIsFromRes = true;
	m_ImgType = nType;
	if (m_ImgType == IT_BMP)
	{
		m_pBmp = LoadBmpImage(nID);
	}
	else if (m_ImgType == IT_PNG)
	{
		m_pPngImg = LoadImage(nID);
	}
	else if (m_ImgType == IT_GIF)
	{
		m_GifImg.m_pImg = LoadImage(nID);
		m_GifImg.Init();
	}

	return ((m_pBmp != NULL) || (m_pPngImg != NULL) || (m_GifImg.m_pImg != NULL));
}

Bitmap * CResImage::LoadBmpImage(UINT nBmpId)
{
	Bitmap * pBmp = Bitmap::FromResource(CWin32BaseDlg::m_hInstance, MAKEINTRESOURCE(nBmpId));
	Status st = pBmp->GetLastStatus();
	if (st != Ok)
		SAVE_DELETE(pBmp);

	return pBmp;
}

Image* CResImage::LoadImage(UINT nID)
{
	Image* pImg = NULL;
	HINSTANCE hInst = CWin32BaseDlg::m_hInstance;
	HRSRC hRsrc = NULL;

	if (m_ImgType == IT_PNG)
	{
		hRsrc = ::FindResource(hInst, MAKEINTRESOURCE(nID), _T("PNG"));
	}
	else if (m_ImgType == IT_GIF)
	{
		hRsrc = ::FindResource(hInst, MAKEINTRESOURCE(nID), _T("GIF"));
	}
	else
	{
		return pImg;
	}

	if (hRsrc != NULL)
	{
		// load resource into memory
		DWORD dwLen = SizeofResource(hInst, hRsrc);
		if (dwLen > 0)
		{
			BYTE* lpRsrc = (BYTE*)LoadResource(hInst, hRsrc);
			if (lpRsrc != NULL)
			{
				// Allocate global memory on which to create stream
				m_hMem = GlobalAlloc(GMEM_FIXED, dwLen);
				if (m_hMem != NULL)
				{
					BYTE* pMem = (BYTE*)GlobalLock(m_hMem);
					memcpy(pMem, lpRsrc, dwLen);
					IStream* pStm = NULL;
					CreateStreamOnHGlobal(m_hMem, FALSE, &pStm);
					if (pStm != NULL)
					{
						// load from stream
						pImg = Image::FromStream(pStm);

						// free/release
						pStm->Release();
						FreeResource(lpRsrc);
					}
					GlobalUnlock(m_hMem);
				}
			}
		}
	}

	return pImg;
}

bool CResImage::IsReady()
{
	if (m_bIsFromRes)
		return ((m_pPngImg != NULL && m_hMem != NULL) || m_pBmp != NULL || (m_GifImg.m_pImg != NULL && m_hMem != NULL));
	else
		return ((m_pBmp != NULL) || (m_pPngImg != NULL) || (m_GifImg.m_pImg != NULL));
}

CGifImage *CResImage::GetGifImage()
{
	CGifImage *pGif = NULL;
	if (IsReady() && m_ImgType == IT_GIF && m_GifImg.m_pImg != NULL)
	{
		pGif = &m_GifImg;
	}

	return pGif;
}
