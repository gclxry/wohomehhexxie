
#include "UiMethod.h"

CRect GetWndRect(HWND hWnd)
{
	CRect WndRect(0, 0, 0, 0);
	if (IS_SAVE_HANDLE(hWnd))
	{
		::GetWindowRect(hWnd, &WndRect);
		int nW = WndRect.Width();
		int nH = WndRect.Height();

		WndRect.SetRectEmpty();
		WndRect.right = nW;
		WndRect.bottom = nH;
	}

	return WndRect;
}

CString GetAppPath()
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

Rect CRect2Rect(CRect &InRect)
{
	Rect RetRect;
	RetRect.X = InRect.left;
	RetRect.Y = InRect.top;
	RetRect.Width = InRect.Width();
	RetRect.Height = InRect.Height();

	return RetRect;
}

RectF CRect2RectF(CRect &InRect)
{
	RectF RetRect;
	RetRect.X = (REAL)InRect.left;
	RetRect.Y = (REAL)InRect.top;
	RetRect.Width = (REAL)InRect.Width();
	RetRect.Height = (REAL)InRect.Height();

	return RetRect;
}

CRect RectF2CRect(RectF &Rf)
{
	CRect RetRect(0, 0, 0, 0);
	RetRect.left = (LONG)Rf.X;
	RetRect.top = (LONG)Rf.Y;
	RetRect.right = RetRect.left + (LONG)Rf.Width;
	RetRect.bottom = RetRect.top + (LONG)Rf.Height;

	return RetRect;
}

PointF CPoint2PointF(CPoint &point)
{
	PointF ptF((REAL)point.x, (REAL)point.y);
	return ptF;
}

CRect CenterWnd(int cx, int cy)
{
	// 设置默认大小
	CRect WorkArea(0, 0, 0, 0), CenterRect(0, 0, 0, 0);
	::SystemParametersInfo(SPI_GETWORKAREA, 0, &WorkArea, 0);

	CenterRect.left = (WorkArea.Width() - cx) / 2;
	CenterRect.right = CenterRect.left + cx;
	CenterRect.top = (WorkArea.Height() - cy) / 2;
	CenterRect.bottom = CenterRect.top + cy;

	return CenterRect;
}

void SafeColor(int &nColor)
{
	if (nColor > 255)
		nColor = 255;
	
	if (nColor < 0)
		nColor = 0;
}

HBITMAP WINAPI GetScreenBitmap(CRect &GetRect) 
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

void ClientToScreen(HWND hWnd, CRect &ClientRect)
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

void ScreenToClient(HWND hWnd, CRect &ScreenRect)
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
GraphicsPath* MakeRoundRect(Point topLeft, Point bottomRight, INT percentageRounded)
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


void EllipsePoints(int nX, int nY, CPoint &MidPoint, ELLIPSE_GET_TYPE egtType,
				   POINT_LIST &LeftUpList, POINT_LIST &LeftDownList,
				   POINT_LIST &RightUpList, POINT_LIST &RightDownList)
{
	// 左上侧
	CPoint LeftUp(MidPoint.x - nX, MidPoint.y - nY);
	// 左下侧
	CPoint LeftDown(MidPoint.x - nX, MidPoint.y + nY);
	// 右上侧
	CPoint RightUp(MidPoint.x + nX, MidPoint.y - nY);
	// 右下侧
	CPoint RightDown(MidPoint.x + nX, MidPoint.y + nY);

	LeftUpList.push_front(LeftUp);
	RightUpList.push_back(RightUp);
	RightDownList.push_front(RightDown);
	LeftDownList.push_back(LeftDown);
}

void EllipseToList(POINT_LIST &ListFrom, POINT_VET &VetTo)
{
	for (POINT_LIST::iterator pItem = ListFrom.begin(); pItem != ListFrom.end(); pItem++)
	{
		CPoint pt = *pItem;
		VetTo.push_back(pt);
	}
};

/*---------------------------中点算法生成椭圆---------------------------------*/
// MidPoint ： 椭圆中点
// dbRx ： 椭圆横方向半截
// dbRy ： 椭圆纵方向半截
// egtType ： 取得那条边的弧线
// PointList ： 输出的点阵
void EllipseMidPoint(CPoint &MidPoint, double dbRx, double dbRy, ELLIPSE_GET_TYPE egtType, POINT_VET &PointList)
{
	POINT_LIST LeftUpList;
	POINT_LIST LeftDownList;
	POINT_LIST RightUpList;
	POINT_LIST RightDownList;

	PointList.clear();
	LeftUpList.clear();
	LeftDownList.clear();
	RightUpList.clear();
	RightDownList.clear();

	double dbX = 0.0, dbY = 0.0, dbD = 0.0, dbXp = 0.0, dbYp = 0.0, dbSquareX = 0.0, dbSquareY = 0.0;
	dbSquareX = dbRx * dbRx;
	dbSquareY = dbRy * dbRy;
	dbXp = (int)(0.5 + (double)dbSquareX / sqrt((double)(dbSquareX + dbSquareY)));
	dbYp = (int)(0.5 + (double)dbSquareY / sqrt((double)(dbSquareX + dbSquareY)));
	dbX = 0.0;
	dbY = dbRy;
	dbD = 4 * (dbSquareY - dbSquareX * dbRy) + dbSquareX;
	EllipsePoints((int)dbX, (int)dbY, MidPoint, egtType,
		LeftUpList, LeftDownList, RightUpList, RightDownList);
	while (dbX <= dbXp)
	{
		if (dbD <= 0.0)
		{
			dbD += 4 * dbSquareY * (2 * dbX + 3);
		}
		else
		{
			dbD += 4 * dbSquareY * (2 * dbX + 3) - 8 * dbSquareX * (dbY - 1);
			dbY--;
		}

		dbX++;
		EllipsePoints((int)dbX, (int)dbY, MidPoint, egtType,
			LeftUpList, LeftDownList, RightUpList, RightDownList);
	}

	dbX = dbRx;
	dbY = 0;
	dbD = 4 * (dbSquareX - dbRx * dbSquareY) + dbSquareY;
	EllipsePoints((int)dbX, (int)dbY, MidPoint, egtType,
		LeftUpList, LeftDownList, RightUpList, RightDownList);
	while (dbY < dbYp)
	{
		if (dbD <= 0.0)
		{
			dbD += 4 * dbSquareX * (2 * dbY + 3);
		}
		else
		{
			dbD += 4 * dbSquareX * (2 * dbY + 3) - 8 * dbSquareY * (dbX - 1);
			dbX--;
		}
		dbY++;
		EllipsePoints((int)dbX, (int)dbY, MidPoint, egtType,
			LeftUpList, LeftDownList, RightUpList, RightDownList);
	}

	if (egtType == EGT_TOP)
	{
		EllipseToList(LeftUpList, PointList);
		EllipseToList(RightUpList, PointList);
	}
	else if (egtType == EGT_RIGHT)
	{
		EllipseToList(RightUpList, PointList);
		EllipseToList(RightDownList, PointList);
	}
	else if (egtType == EGT_DOWN)
	{
		EllipseToList(RightDownList, PointList);
		EllipseToList(LeftDownList, PointList);
	}
	else if (egtType == EGT_LEFT)
	{
		EllipseToList(LeftDownList, PointList);
		EllipseToList(LeftUpList, PointList);
	}
}
