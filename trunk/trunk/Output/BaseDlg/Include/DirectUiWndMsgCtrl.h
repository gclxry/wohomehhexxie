
#pragma once

struct DWM_INFO
{
	WPARAM wParam;
	LPARAM lParam;
};

class CDirectUiWndMsgCtrl
{
public:
	CDirectUiWndMsgCtrl(void) {};
	~CDirectUiWndMsgCtrl(void) {};

	virtual bool OnDirectUiWndMsgProc(int nMsgId, DWM_INFO &MsgInfo) = 0;
};


//////////////////////////////////////////////////////////////////////////
// 窗口消息定义
// 系统按钮命令
#define DWM_SYS_CMD_MIN									(1)
#define DWM_SYS_CMD_MAX_RES								(2)
#define DWM_SYS_CMD_CLOSE								(3)

// 鼠标按下
#define DWM_LBUTTONDOWN									(1)
// 鼠标抬起
#define DWM_LBUTTONUP									(2)
// 鼠标双击
#define DWM_LBUTTONDBLCLK								(3)
// 鼠标进入窗口
#define DWM_MOUSEHOVER									(4)
// 鼠标划出窗口
#define DWM_MOUSELEAVE									(5)
