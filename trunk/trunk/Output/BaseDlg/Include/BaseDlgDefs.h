
#pragma once
#include "FetionSF.h"

// 下拉三角形的大小
#define DROP_SJ_H								(4)
#define DROP_SJ_W								(7)

#define MSG_TITLE								_T("奇幻科技")

// 窗口类型
enum WND_TYPE
{
	// Bar，会包含多个子窗口
	DWT_BAR_NORMAL	= 0x00000100,
	// Tool bar
	DWT_BAR_TOOL_BAR,
	// 标题栏
	DWT_BAR_CAPTION,
	// ComboBox的选择按钮
	DWT_BAR_COMBO_SELECT_BUTTON,
	// 按钮
	DWT_BUTTON		= 0x00000200,
	// 下拉按钮
	DWT_COMBO_BOX_DROPDOWN_BUTTON,
	// 渐变按钮
	DWT_GRADIENT_BUTTON,
	// 渐变下拉按钮
	DWT_DROPDOWN_GRADIENT_BUTTON,
	// 静态文本框
	DWT_STATIC		= 0x00000400,
	// GIF显示窗口
	DWT_GIF_STATIC,
	// 超链接按钮
	DWT_LINK_STATIC,
	// 鼠标滑过按钮
	DWT_MOUSEMOVE_STATIC,
	// 编辑框
	DWT_EDIT		= 0x00000800,
	// 富文本框
	DWT_RICH_EDIT,
	// CheckBox
	DWT_CHECK_BOX	= 0x00001000,
	// ComboBox
	DWT_COMBO_BOX	= 0x00002000,
	// Flash
	DWT_FLASH		= 0x00004000,
};

/// 窗口属性列表 ///////////////////////////////////////////////////////////////////////
// 是否可见
const DWORD DWP_VISABLE							= 0x00000001;
// 是否禁用
const DWORD DWP_ENABLE							= 0x00000002;
// 是否为默认窗口
const DWORD DWP_DEFAULTWND						= 0x00000004;
// 是否取得焦点
const DWORD DWP_FOCUS							= 0x00000008;
// 窗口是否销毁
const DWORD DWP_DESTROY							= 0x00000010;
// 窗口是否进入了窗口拉伸移动消息循环
const DWORD DWP_ENTERSIZEMOVE					= 0x00000020;
// 鼠标是否进入窗口
const DWORD DWP_MOUSEHOVER						= 0x00000040;
// 鼠标是否按下
const DWORD DWP_MOUSEDOWN						= 0x00000080;
// 是否发送鼠标按下消息
const DWORD DWP_MSG_MOUSEDOWN					= 0x00000100;
// 是否发送鼠标双击消息
const DWORD DWP_MSG_MOUSEDCLICK					= 0x00000200;
// 是否发送鼠标移动消息
const DWORD DWP_MSG_MOUSEMOUSE					= 0x00000400;
// 是否发送绘图消息
const DWORD DWP_MSG_PAINT						= 0x00000800;
// HOT 窗口，主要用于按钮，如toolbar的按钮被按下后的状态
const DWORD DWP_HOT_WND							= 0x00001000;


//////////////////////////////////////////////////////////////////////////

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
