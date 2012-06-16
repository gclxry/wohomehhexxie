
#pragma once
#include "..\ICtrlInterface.h"

// 添加控件，步骤1：编写一个控件名称宏。注意，控件名称不能相同
#define CTRL_NAME_TAB_BAR						("TabBar")

// 控件向窗口发送的消息
enum CTRL_MSG_TABBAR
{
	// Button消息Base，此消息值不允许被发送，只是作为消息值的Base
	CM_TABBAR_BASE	= 0x10015000,
	// Up消息
	CM_TABBAR_UP
};

class ICtrlTabBar : public ICtrlInterface
{
public:
	// 设置当前选中项
	virtual void SetCheck(int nBtnNum) = 0;
	// 取得指定项的矩形位置，相对于整个窗口
	virtual RECT GetButtonWindowRect(int nBtnNum) = 0;
};
