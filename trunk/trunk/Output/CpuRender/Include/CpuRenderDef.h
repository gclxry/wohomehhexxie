
#pragma once

#include <assert.h>
#include <atlbase.h>
#include <atltypes.h>
#include <atlstr.h>
#include <math.h>
#include <vector>
#include <list>

using namespace std;

#define DEF_VERTEX(varName,x,y,z)\
	AK3D_VERTEX varName;\
	varName.xDest=x;\
	varName.yDest=y;\
	varName.zDest=z;

#define DEF_UV(varName,u,v)\
	float varName[2];\
	varName[0]=u;\
	varName[1]=v;


// Õ÷‘≤πÏº£¿‡–Õ
enum ELLIPSE_GET_TYPE
{
	// ◊Û∞Î≤øÕ÷‘≤πÏº£
	EGT_LEFT	= 1,
	// ”“∞Î≤øÕ÷‘≤πÏº£
	EGT_RIGHT	= 2,
	// …œ∞Î≤øÕ÷‘≤πÏº£
	EGT_TOP		= 3,
	// œ¬∞Î≤øÕ÷‘≤πÏº£
	EGT_DOWN	= 4,
};

typedef std::vector<CPoint> POINT_VET;
typedef std::list<CPoint> POINT_LIST;
