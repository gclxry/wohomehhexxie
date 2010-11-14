
#pragma once
#include "CpuRenderDef.h"

class CAKTrajectory
{
public:
	CAKTrajectory();
	virtual ~CAKTrajectory();

	// 取得椭圆轨迹数据
	static void EllipseMidPoint(CPoint &MidPoint, double dbRx, double dbRy, ELLIPSE_GET_TYPE egtType, POINT_VET &PointList);

private:
	static void EllipseToList(POINT_LIST &ListFrom, POINT_VET &VetTo);
	static void EllipsePoints(int nX, int nY, CPoint &MidPoint,
		POINT_LIST &LeftUpList, POINT_LIST &LeftDownList, POINT_LIST &RightUpList, POINT_LIST &RightDownList);
};
