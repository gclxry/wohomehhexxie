
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
// ������Ϣ����
// ϵͳ��ť����
#define DWM_SYS_CMD_MIN									(1)
#define DWM_SYS_CMD_MAX_RES								(2)
#define DWM_SYS_CMD_CLOSE								(3)

// ��갴��
#define DWM_LBUTTONDOWN									(1)
// ���̧��
#define DWM_LBUTTONUP									(2)
// ���˫��
#define DWM_LBUTTONDBLCLK								(3)
// �����봰��
#define DWM_MOUSEHOVER									(4)
// ��껮������
#define DWM_MOUSELEAVE									(5)
