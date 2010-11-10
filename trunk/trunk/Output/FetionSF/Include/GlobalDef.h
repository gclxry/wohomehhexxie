
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


// ·����󳤶�
#define FS_MAX_PATH								(1024 * 4)

// ��ȫɾ���ڴ�
#define SAVE_DELETE(pMem)						{if((pMem) != NULL) delete (pMem); (pMem) = NULL;}
#define SAVE_DELETE_LIST(pMem)					{if((pMem) != NULL) delete [](pMem); (pMem) = NULL;}

// ��ȫɾ�����
#define IS_SAVE_HANDLE(hHandle)					(((hHandle) != NULL) && ((hHandle) != INVALID_HANDLE_VALUE))
#define SAVE_CLOSE_HANDLE(hHandle)				{if(IS_SAVE_HANDLE(hHandle)) ::CloseHandle(hHandle); (hHandle) = NULL;}


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
