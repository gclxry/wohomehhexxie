
#include "stdafx.h"
#include "..\..\Inc\CDrawingBoard.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IUiFeatureKernel.h"
#include "..\..\Inc\IUiEngine.h"

CDrawingBoard::CDrawingBoard(void)
{
    m_pBits = NULL;
	m_hBmp = NULL;
	m_hOldBmp = NULL;
	m_hDC = NULL;
	m_DcSize.cx = m_DcSize.cy = 0;
}

CDrawingBoard::~CDrawingBoard(void)
{
   Delete();
}

SIZE CDrawingBoard::GetDcSize()
{
	return m_DcSize;
}

HDC& CDrawingBoard::GetSafeHdc()
{
	return m_hDC;
}

HBITMAP& CDrawingBoard::GetBmpHandle()
{
	return m_hBmp;
}

BYTE* CDrawingBoard::GetBits()
{
	return m_pBits;
}

bool CDrawingBoard::Create(int nWidth, int nHeight, DWORD nDefaultColor, bool bReCreate, bool bNoCreateInit)
{
	bool bIsCreateNew = false;
	if ((nWidth <= 0) || (nHeight<= 0))
		return bIsCreateNew;

	if (bReCreate || (nWidth != m_DcSize.cx) || (nHeight != m_DcSize.cy))
	{
		bIsCreateNew = true;
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
			{
				m_hOldBmp = (HBITMAP)::SelectObject(m_hDC, m_hBmp);
				::SetBkMode(m_hDC, TRANSPARENT);
			}
			else
			{
				Delete();
			}
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

	return bIsCreateNew;
}

void CDrawingBoard::Delete()
{
	if (m_hDC != NULL && m_hOldBmp != NULL)
		::SelectObject(m_hDC, m_hOldBmp);
	m_hOldBmp = NULL;

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

// 绘制到另外一个内存DC上
bool CDrawingBoard::BitBltTo(CDrawingBoard& ToBoard, RECT ToRct, RECT FromRct)
{
	if (!IS_SAFE_HANDLE(m_hDC) || !IS_SAFE_HANDLE(ToBoard.GetSafeHdc()))
		return false;

	return (::BitBlt(ToBoard.GetSafeHdc(), ToRct.left, ToRct.top, RECT_WIDTH(ToRct), RECT_HEIGHT(ToRct),
		m_hDC, FromRct.left, FromRct.top, SRCCOPY) == TRUE);
}

// 绘制到另外一个内存DC上
bool CDrawingBoard::AlphaBlendTo(CDrawingBoard& ToBoard, RECT ToRct, RECT FromRct, IUiFeatureKernel* pUiKernel, int nAlpha)
{
	if (!IS_SAFE_HANDLE(m_hDC) || !IS_SAFE_HANDLE(ToBoard.GetSafeHdc()) || pUiKernel == NULL || pUiKernel->GetUiEngine() == NULL)
		return false;

	return pUiKernel->GetUiEngine()->AlphaBlend(ToBoard, ToRct.left, ToRct.top, RECT_WIDTH(ToRct), RECT_HEIGHT(ToRct),
		*this, FromRct.left, FromRct.top, RECT_WIDTH(FromRct), RECT_HEIGHT(FromRct), nAlpha);
}

// 从一个DC进行复制
bool CDrawingBoard::BitBltFrom(HDC hDc, RECT FromRct, RECT ToRct)
{
	if (!IS_SAFE_HANDLE(hDc) || !IS_SAFE_HANDLE(m_hDC) || IS_RECT_EMPTY(ToRct) || IS_RECT_EMPTY(FromRct))
		return false;

	return (::BitBlt(m_hDC, ToRct.left, ToRct.top, RECT_WIDTH(ToRct), RECT_HEIGHT(ToRct),
		hDc, FromRct.left, FromRct.top, SRCCOPY) == TRUE);
}

// 从一个DC进行复制
bool CDrawingBoard::StretchBltFrom(HDC hDc, RECT FromRct, RECT ToRct)
{
	if (!IS_SAFE_HANDLE(hDc) || !IS_SAFE_HANDLE(m_hDC) || IS_RECT_EMPTY(ToRct) || IS_RECT_EMPTY(FromRct))
		return false;

	return (::StretchBlt(m_hDC, ToRct.left, ToRct.top, RECT_WIDTH(ToRct), RECT_HEIGHT(ToRct),
		hDc, FromRct.left, FromRct.top, RECT_WIDTH(FromRct), RECT_HEIGHT(FromRct), SRCCOPY) == TRUE);
}

// 从另一个内存DC克隆
bool CDrawingBoard::Clone(CDrawingBoard& FromBoard, IUiFeatureKernel* pUiKernel)
{
	if (FromBoard.GetSafeHdc() == NULL || FromBoard.GetDcSize().cx <= 0 || FromBoard.GetDcSize().cy <= 0 || pUiKernel == NULL)
		return false;

	this->Create(FromBoard.GetDcSize().cx, FromBoard.GetDcSize().cy, 0, true, false);
	if (m_hDC == NULL)
		return false;
	
	RECT fromRct = {0, 0, FromBoard.GetDcSize().cx, FromBoard.GetDcSize().cy};

	return FromBoard.AlphaBlendTo(*this, fromRct, fromRct, pUiKernel);
}
