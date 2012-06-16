
#pragma once
#include "..\ICtrlInterface.h"

// 添加控件，步骤1：编写一个控件名称宏。注意，控件名称不能相同
#define CTRL_NAME_LINK_LABLE						("LinkLable")

// 动画控件向窗口发送的消息
enum CTRL_MSG_LINK_LABLE
{
	// LINK_LABLE消息Base，此消息值不允许被发送，只是作为动画消息值的Base
	CM_LINK_LABLE_BASE	= 0x10008000,
	// LINK_LABLE Down消息
	CM_LINK_LABLE_DOWN,
	// LINK_LABLE Up消息
	CM_LINK_LABLE_UP
};

class ICtrlLinkLable : public ICtrlInterface
{
public:
	// 设置Link文字
	virtual void SetLinkText(char *pText, bool bRedraw) = 0;
	// 设置Link链接地址URL
	virtual void SetLinkUrl(char *pUrl) = 0;
	// 取得Link链接地址URL
	virtual const char * GetLinkUrl() = 0;
};
