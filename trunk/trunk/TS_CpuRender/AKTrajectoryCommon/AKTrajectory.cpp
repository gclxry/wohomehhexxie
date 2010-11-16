
#include "stdafx.h"
#include "AKTrajectory.h"

void CAKTrajectory::EllipsePoints(int nX, int nY, CPoint &MidPoint,
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

void CAKTrajectory::EllipseToList(POINT_LIST &ListFrom, POINT_VET &VetTo)
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
// egtType ： 取得哪条边的弧线
// PointList ： 输出的点阵
void CAKTrajectory::EllipseMidPoint(CPoint &MidPoint, double dbRx, double dbRy, ELLIPSE_GET_TYPE egtType, POINT_VET &PointList)
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
	EllipsePoints((int)dbX, (int)dbY, MidPoint,
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
		EllipsePoints((int)dbX, (int)dbY, MidPoint,
			LeftUpList, LeftDownList, RightUpList, RightDownList);
	}

	dbX = dbRx;
	dbY = 0;
	dbD = 4 * (dbSquareX - dbRx * dbSquareY) + dbSquareY;
	EllipsePoints((int)dbX, (int)dbY, MidPoint,
		LeftUpList, LeftDownList, RightUpList, RightDownList) ;
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
		EllipsePoints((int)dbX, (int)dbY, MidPoint,
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
