
#include "stdafx.h"
#include "..\..\Inc\CMemoryDC.h"

CMemoryDC::CMemoryDC(void)
{
    m_pBits = NULL;
    m_hBmp = NULL;
	m_hDC = NULL;
	m_DcSize.cx = m_DcSize.cy = 0;
}

CMemoryDC::~CMemoryDC(void)
{
   Delete();
}

SIZE CMemoryDC::GetDcSize()
{
	return m_DcSize;
}

HDC& CMemoryDC::GetSafeHdc()
{
	return m_hDC;
}

HBITMAP& CMemoryDC::GetBmpHandle()
{
	return m_hBmp;
}

BYTE* CMemoryDC::GetBits()
{
	return m_pBits;
}

void CMemoryDC::Create(int nWidth, int nHeight, DWORD nDefaultColor, bool bReCreate, bool bNoCreateInit)
{
	if ((nWidth <= 0) || (nHeight<= 0))
		return;

	if (bReCreate || (nWidth != m_DcSize.cx) || (nHeight != m_DcSize.cy))
	{
		Delete();
		
		m_DcSize.cx = nWidth;
		m_DcSize.cy = nHeight;

		BITMAPINFOHEADER bih;
		memset(&bih, 0, sizeof(BITMAPINFOHEADER));
		bih.biSize = sizeof(BITMAPINFOHEADER);
		bih.biHeight = nHeight;
		bih.biWidth = nWidth;
		bih.biPlanes = 1;
		bih.biBitCount = 32;
		bih.biCompression = BI_RGB;

		m_hDC = ::CreateCompatibleDC(NULL);
		if (m_hDC != NULL)
		{
			m_hBmp = ::CreateDIBSection(GetSafeHdc(), (BITMAPINFO*)&bih,
				DIB_RGB_COLORS, (void**)(&m_pBits), NULL, 0);

			if (m_hBmp != NULL && m_pBits != NULL)
				::SelectObject(m_hDC, m_hBmp);
			else
				Delete();
		}
		else
		{
			Delete();
		}
	}
	else
	{
		if (m_pBits != NULL && bNoCreateInit)
			memset(m_pBits, nDefaultColor, m_DcSize.cx * m_DcSize.cy * 4);
	}
}

void CMemoryDC::Delete()
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
