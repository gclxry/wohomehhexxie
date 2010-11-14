
#include "UiMethod.h"

CString CUiMethod::GetAppPath()
{
	CString strPath = _T("");
	TCHAR szBuffer[FS_MAX_PATH];
	if (::GetModuleFileName(NULL, szBuffer, FS_MAX_PATH))
	{
		strPath = szBuffer;
		while (strPath.GetAt(strPath.GetLength() - 1) != '\\' && strPath.GetLength() > 0)
		{
			strPath.Delete(strPath.GetLength() - 1, 1);
		}
	}

	return strPath;
}

Rect CUiMethod::CRect2Rect(CRect &InRect)
{
	Rect RetRect;
	RetRect.X = InRect.left;
	RetRect.Y = InRect.top;
	RetRect.Width = InRect.Width();
	RetRect.Height = InRect.Height();

	return RetRect;
}

RectF CUiMethod::CRect2RectF(CRect &InRect)
{
	RectF RetRect;
	RetRect.X = (REAL)InRect.left;
	RetRect.Y = (REAL)InRect.top;
	RetRect.Width = (REAL)InRect.Width();
	RetRect.Height = (REAL)InRect.Height();

	return RetRect;
}

CRect CUiMethod::RectF2CRect(RectF &Rf)
{
	CRect RetRect(0, 0, 0, 0);
	RetRect.left = (LONG)Rf.X;
	RetRect.top = (LONG)Rf.Y;
	RetRect.right = RetRect.left + (LONG)Rf.Width;
	RetRect.bottom = RetRect.top + (LONG)Rf.Height;

	return RetRect;
}

PointF CUiMethod::CPoint2PointF(CPoint &point)
{
	PointF ptF((REAL)point.x, (REAL)point.y);
	return ptF;
}

void CUiMethod::SafeColor(int &nColor)
{
	if (nColor > 255)
		nColor = 255;
	
	if (nColor < 0)
		nColor = 0;
}

HBITMAP WINAPI CUiMethod::GetScreenBitmap(CRect &GetRect) 
{ 
	HDC hDC = NULL, hMemDC = NULL;
	HBITMAP hNewBitmap = NULL;

	if ((hDC = ::GetDC(NULL)) != NULL)
	{ 
		if ((hMemDC = ::CreateCompatibleDC(hDC)) != NULL)
		{ 
			if ((hNewBitmap = ::CreateCompatibleBitmap(hDC, GetRect.Width(), GetRect.Height())) != NULL)
			{
				HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hMemDC, hNewBitmap);
				::BitBlt(hMemDC, 0, 0, GetRect.Width(), GetRect.Height(),
					hDC, GetRect.left, GetRect.top, SRCCOPY);

				::SelectObject(hMemDC, (HGDIOBJ)hOldBitmap);
			}
			::DeleteDC(hMemDC);
		}
		::ReleaseDC(NULL, hDC);
	}
	return hNewBitmap;
}

void CUiMethod::ClientToScreen(HWND hWnd, CRect &ClientRect)
{
	POINT Pt;
	int nW = 0, nH = 0;

	Pt.x = ClientRect.left;
	Pt.y = ClientRect.top;
	nW = ClientRect.Width();
	nH = ClientRect.Height();

	::ClientToScreen(hWnd, &Pt);
	ClientRect.left = Pt.x;
	ClientRect.top = Pt.y;
	ClientRect.right = ClientRect.left + nW;
	ClientRect.bottom = ClientRect.top + nH;
}

void CUiMethod::ScreenToClient(HWND hWnd, CRect &ScreenRect)
{
	POINT Pt;
	int nW = 0, nH = 0;

	Pt.x = ScreenRect.left;
	Pt.y = ScreenRect.top;
	nW = ScreenRect.Width();
	nH = ScreenRect.Height();

	::ScreenToClient(hWnd, &Pt);
	ScreenRect.left = Pt.x;
	ScreenRect.top = Pt.y;
	ScreenRect.right = ScreenRect.left + nW;
	ScreenRect.bottom = ScreenRect.top + nH;
}

// 创建圆角矩形区域
// 调用例子：
//	TextureBrush brush(pDrawImage);
//	GraphicsPath * pPath = MakeRoundRect(Point(DstRect1.X, DstRect1.Y),
//		Point(DstRect.X + DstRect.Width, DstRect.Y + DstRect.Height), 30);
//	pDoGrap->FillPath(&brush, pPath);
//	delete pPath;
GraphicsPath* CUiMethod::MakeRoundRect(Point topLeft, Point bottomRight, INT percentageRounded)
{
	assert(percentageRounded >= 1 && percentageRounded <= 100);

	INT left  = min(topLeft.X, bottomRight.X);
	INT right = max(topLeft.X, bottomRight.X);

	INT top    = min(topLeft.Y, bottomRight.Y);
	INT bottom = max(topLeft.Y, bottomRight.Y);

	INT offsetX = (right-left)*percentageRounded/100;
	INT offsetY = (bottom-top)*percentageRounded/100;

	GraphicsPath pt;
	GraphicsPath * path = pt.Clone();

	path->AddArc(right-offsetX, top, offsetX, offsetY, 270, 90);
	path->AddArc(right-offsetX, bottom-offsetY, offsetX, offsetY, 0, 90);
	path->AddArc(left, bottom - offsetY, offsetX, offsetY, 90, 90);
	path->AddArc(left, top, offsetX, offsetY, 180, 90);
	path->AddLine(left + offsetX, top, right - offsetX/2, top);

	return path;
}   
