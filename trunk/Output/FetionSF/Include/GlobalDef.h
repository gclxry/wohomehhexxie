
#pragma once

#include <Windows.h>
#include <math.h>
#include <assert.h>
#include <atlbase.h>
#include <atltypes.h>
#include <atlstr.h>

#include <vector>
#include <list>
using namespace std;

#include "gdiplus.h"
using namespace Gdiplus;


// 路径最大长度
#define FS_MAX_PATH								(1024 * 4)

// 安全删除内存
#define SAVE_DELETE(pMem)						{if((pMem) != NULL) delete (pMem); (pMem) = NULL;}
#define SAVE_DELETE_LIST(pMem)					{if((pMem) != NULL) delete [](pMem); (pMem) = NULL;}

// 安全删除句柄
#define IS_SAVE_HANDLE(hHandle)					(((hHandle) != NULL) && ((hHandle) != INVALID_HANDLE_VALUE))
#define SAVE_CLOSE_HANDLE(hHandle)				{if(IS_SAVE_HANDLE(hHandle)) ::CloseHandle(hHandle); (hHandle) = NULL;}


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
