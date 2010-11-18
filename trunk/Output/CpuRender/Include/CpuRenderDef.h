
#pragma once

#include "FetionSF.h"
#include <assert.h>
#include <atlbase.h>
#include <atltypes.h>
#include <atlstr.h>
#include <math.h>
#include <vector>
#include <list>

using namespace std;

// 定义图片的四个顶点（四角坐标）
#define DEF_VERTEX(varName,x,y,z)\
	AK3D_VERTEX varName;\
	varName.xDest=x;\
	varName.yDest=y;\
	varName.zDest=z;

#define DEF_UV(varName,u,v)\
	float varName[2];\
	varName[0]=u;\
	varName[1]=v;


// 椭圆轨迹类型
enum ELLIPSE_GET_TYPE
{
	// 左半部椭圆轨迹
	EGT_LEFT	= 1,
	// 右半部椭圆轨迹
	EGT_RIGHT	= 2,
	// 上半部椭圆轨迹
	EGT_TOP		= 3,
	// 下半部椭圆轨迹
	EGT_DOWN	= 4,
};

typedef std::vector<CPoint> POINT_VET;
typedef std::list<CPoint> POINT_LIST;
