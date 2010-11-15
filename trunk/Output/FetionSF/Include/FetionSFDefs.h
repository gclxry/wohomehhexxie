
#pragma once

#include <Windows.h>
#include <math.h>
#include <assert.h>
#include <atlbase.h>
#include <atltypes.h>
#include <atlstr.h>
#include <process.h>

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


// 加载的图片类型
enum IMAGE_TYPE
{
	IT_NON	= 0,
	IT_BMP	= 1,
	IT_PNG	= 2,
	IT_JPG	= 3,
	IT_GIF	= 4,
};

// 窗口文字信息
class WND_TEXT 
{
public:
	WND_TEXT() :
	OutFormat(StringFormat::GenericTypographic())
	{
		strFontName = _T(""); 
		nFontHeight = 0;
		FStyle = FontStyleRegular;
		TextColor = Color(0, 0, 0);
		TextRectF.X = 0.0;
		TextRectF.Y = 0.0;
		TextRectF.Width = 0.0;
		TextRectF.Height = 0.0;
		strText = _T("");

		OutFormat.SetLineAlignment(StringAlignmentCenter);
	};
	bool IsEmpty() { return strFontName.IsEmpty(); };

	// 字体名
	CString strFontName;
	// 字体高
	int nFontHeight;
	// 字体样式
	FontStyle FStyle;
	// 字体颜色
	Color TextColor;
	// 输出格式
	StringFormat OutFormat;
	// 窗口的文字
	CString strText;
	// 窗口文字输出的位置
	RectF TextRectF;
};
