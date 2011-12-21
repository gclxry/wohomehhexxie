
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

// ����ͼƬ���ĸ����㣨�Ľ����꣩
#define DEF_VERTEX(varName,x,y,z)\
	AK3D_VERTEX varName;\
	varName.xDest=x;\
	varName.yDest=y;\
	varName.zDest=z;

#define DEF_UV(varName,u,v)\
	float varName[2];\
	varName[0]=u;\
	varName[1]=v;


// ��Բ�켣����
enum ELLIPSE_GET_TYPE
{
	// ��벿��Բ�켣
	EGT_LEFT	= 1,
	// �Ұ벿��Բ�켣
	EGT_RIGHT	= 2,
	// �ϰ벿��Բ�켣
	EGT_TOP		= 3,
	// �°벿��Բ�켣
	EGT_DOWN	= 4,
};

typedef std::vector<CPoint> POINT_VET;
typedef std::list<CPoint> POINT_LIST;
