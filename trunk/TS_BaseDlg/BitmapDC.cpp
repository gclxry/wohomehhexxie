
                        /*¨q¡Ð¨r©©~ ¡è¡¡ ¨q¡Ð¨r ¨q¡Ð¨r
                        ¨q¡Ð¨q¡Ð¨r¨q¡Ð¨r¡«¨q¡Ð¨r¦á¦á,¡¡¦á¦á
                        ,¦á¦á¦á¦á,''¦á~~ ,''~¦á¦á¡¡ ,''


                                  ("`-''-/").___..--''"`-._
                                   `6_ 6  )   `-.  (     ).`-.__.`)
                                   (_Y_.)'  ._   )  `._ `. ``-..-'
                                 _..`--'_..-_/  /--'_.' ,'
                                (il),-'   (li),'  ((!.-'*/


#include "BitmapDC.h"

CBitmapDC::CBitmapDC()
{
    m_pBits = NULL;
    m_hBmp = NULL;
	m_hDC = NULL;
	m_DcSize.cx = m_DcSize.cy = 0;
}

CBitmapDC::~CBitmapDC()
{
   Delete();
}

CSize CBitmapDC::GetDcSize()
{
	return m_DcSize;
}

HDC CBitmapDC::GetSafeHdc()
{
	return m_hDC;
}

HBITMAP CBitmapDC::GetBmpHandle()
{
	return m_hBmp;
}

DWORD* CBitmapDC::GetBits()
{
	return (DWORD*)m_pBits;
}

void CBitmapDC::Create(int nWidth, int nHeight)
{
	if (nWidth <= 0 || nHeight<= 0)
		return;

	if (nWidth != m_DcSize.cx || nHeight != m_DcSize.cy)
	{
		Delete();
		
		m_DcSize.cx = nWidth;
		m_DcSize.cy = nHeight;

		BITMAPINFOHEADER bih;
		memset(&bih, 0, sizeof(BITMAPINFOHEADER));
		bih.biSize = sizeof(BITMAPINFOHEADER);
		bih.biHeight = nHeight;
		bih.biWidth = nWidth;
		//bih.biWidth = ((((int)nWidth * 8) + 31) & ~31) >> 3;
		bih.biPlanes = 1;
		bih.biBitCount = 32;
		bih.biCompression = BI_RGB;

		m_hDC = CreateCompatibleDC(NULL);
		if (m_hDC != NULL)
		{
			m_hBmp	= ::CreateDIBSection(GetSafeHdc(), (BITMAPINFO*)&bih,
				DIB_RGB_COLORS, (void**)(&m_pBits), NULL, 0);

			if (m_hBmp != NULL && m_pBits != NULL)
				SelectObject(m_hDC, m_hBmp);
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
		if (m_pBits != NULL)
			memset(m_pBits, 0, m_DcSize.cx * m_DcSize.cy * 4);
	}
}

void CBitmapDC::Delete()
{
	if (m_hBmp != NULL)
	{
		DeleteObject(m_hBmp);
		m_hBmp = NULL;
	}

	if (m_hDC != NULL)
	{
		DeleteDC(m_hDC);
		m_hDC = NULL;
	}

	m_pBits = NULL;
	m_DcSize.cx = m_DcSize.cy = 0;
}
