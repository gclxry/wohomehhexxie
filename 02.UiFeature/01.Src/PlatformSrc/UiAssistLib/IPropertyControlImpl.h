
#pragma once
#include "..\..\Inc\IPropertyControl.h"

class IPropertyControlImpl : public IPropertyControl
{
public:
	IPropertyControlImpl(void);
	virtual ~IPropertyControlImpl(void);

	// 控件显示位置和大小，这个位置是相对于附着的窗口的
	virtual void SetCtrlInWindowRect(RECT CtrlWndRct);
	virtual RECT GetCtrlInWindowRect();
	// 控件显示位置和大小，这个位置是相对于父控件的
	virtual RECT GetCtrlInControlRect();
	// 取得控件的大小
	virtual RECT GetCtrlRect();

	// 是否接受鼠标消息
	virtual void SetReceiveMouseMessage(bool bIsReceive);
	virtual bool GetReceiveMouseMessage();

	// 可见属性
	virtual void SetVisible(bool bVisible);
	virtual bool IsVisible();

	// 相对于父控件的布局信息
	virtual void SetLayout(CONTROL_LAYOUT_INFO &cliLayoutInfo);
	virtual CONTROL_LAYOUT_INFO GetLayout();

	// 控件名称，唯一识别窗口的标志
	virtual void SetName(char *pCtrlName);
	virtual const char* GetName();

	// 拖动控件属性
	virtual void SetDragControl(bool bDrag);
	virtual bool GetDragControl();
private:
	// 是否可见
	bool m_bVisible;
	// 是否接受鼠标消息
	bool m_bIsReceiveMouseMsg;
	// 控件位置，这个位置是相对于窗口的位置
	RECT m_RectInWindow;
	// 控件位置，这个位置是相对于父控件的位置
	RECT m_RectInParentCtrl;
	// 控件布局信息
	CONTROL_LAYOUT_INFO m_LayoutInfo;
	// 控件名称
	string m_strCtrlName;
	// 拖动控件
	bool m_bDragCtrl;
};
