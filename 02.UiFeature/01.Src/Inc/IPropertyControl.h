//////////////////////////////////////////////////////////////////////////
// 一个控件的属性

#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 当前控件相对于父控件的布局类型
enum CONTROL_LAYOUT
{
	// 固定大小：左上角定位
	CL_G_LEFT_TOP		= 0,
	// 固定大小：左下角定位
	CL_G_LEFT_BOTTOM	= 1,
	// 固定大小：右上角定位
	CL_G_RIGHT_TOP		= 2,
	// 固定大小：右下角定位
	CL_G_RIGHT_BOTTOM	= 3,
	// 拉伸变动大小：撑满左侧
	CL_L_LEFT			= 4,
	// 拉伸变动大小：撑满右侧
	CL_L_RIGHT			= 5,
	// 拉伸变动大小：撑满上方
	CL_L_TOP			= 6,
	// 拉伸变动大小：撑满下方
	CL_L_BOTTOM			= 7,
	// 拉伸变动大小：撑满全部
	CL_L_ALL			= 8,
	// 拉伸变动大小：居中
	CL_L_MIDDLE			= 9,
};
// 当前控件相对于父控件的布局信息
struct CONTROL_LAYOUT_INFO
{
	// 布局类型
	CONTROL_LAYOUT clType;
	// 控件宽
	int nWidth;
	// 控件高
	int nHeight;
	// 距离父控件左侧距离
	int nLeftSpace;
	// 距离父控件右侧距离
	int nRightSpace;
	// 距离父控件上方距离
	int nTopSpace;
	// 距离父控件下方距离
	int nBottomSpace;
};

class IPropertyControl
{
public:

	// 控件显示位置和大小，这个位置是相对于附着的窗口的
	virtual void SetCtrlInWindowRect(RECT CtrlWndRct) = 0;
	virtual RECT GetCtrlInWindowRect() = 0;
	// 控件显示位置和大小，这个位置是相对于父控件的
	virtual RECT GetCtrlInControlRect() = 0;
	// 取得控件的大小
	virtual RECT GetCtrlRect() = 0;

	// 控件名称，唯一识别窗口的标志
	virtual void SetName(char *pCtrlName) = 0;
	virtual const char* GetName() = 0;

	// 是否接受鼠标消息
	virtual void SetReceiveMouseMessage(bool bIsReceive) = 0;
	virtual bool GetReceiveMouseMessage() = 0;

	// 相对于父控件的布局信息
	virtual void SetLayout(CONTROL_LAYOUT_INFO &cliLayoutInfo) = 0;
	virtual CONTROL_LAYOUT_INFO GetLayout() = 0;

	// 可见属性
	virtual void SetVisible(bool bVisible) = 0;
	virtual bool IsVisible() = 0;

	// 拖动控件属性
	virtual void SetDragControl(bool bDrag) = 0;
	virtual bool GetDragControl() = 0;

};
