
#pragma once
#include "..\ICtrlInterface.h"

// 添加控件，步骤1：编写一个控件名称宏。注意，控件名称不能相同
#define CTRL_NAME_BUTTON						("Button")

// 动画控件向窗口发送的消息
enum CTRL_MSG_BUTTON
{
	// Button消息Base，此消息值不允许被发送，只是作为控件消息值的Base
	CM_BUTTON_BASE	= 0x10002000,
	// Button Down消息
	CM_BUTTON_DOWN,
	// Button Up消息
	CM_BUTTON_UP,
	// 进入 Button 
	CM_BUTTON_ENTER,
	// 离开 Button
	CM_BUTTON_LEAVE,
	// Button 右键按下消息
	CM_BUTTON_R_BTN_DOWN
};

class ICtrlButton : public ICtrlInterface
{
public:
	// 设置Button文言
	virtual	void SetButtonText(const char* pszText) = 0;
	// 获取Button文言
	virtual	const char* GetButtonText() = 0;

	// check button 模式下
	virtual void SetCheck(bool bIsCheck, bool bRedraw) = 0;
	virtual bool IsCheck() = 0;
	virtual IControlBase* GetCheckPanel() = 0;
};
