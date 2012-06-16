
#pragma once
#include "..\ICtrlInterface.h"

// ��ӿؼ�������1����дһ���ؼ����ƺꡣע�⣬�ؼ����Ʋ�����ͬ
#define CTRL_NAME_BUTTON						("Button")

// �����ؼ��򴰿ڷ��͵���Ϣ
enum CTRL_MSG_BUTTON
{
	// Button��ϢBase������Ϣֵ���������ͣ�ֻ����Ϊ�ؼ���Ϣֵ��Base
	CM_BUTTON_BASE	= 0x10002000,
	// Button Down��Ϣ
	CM_BUTTON_DOWN,
	// Button Up��Ϣ
	CM_BUTTON_UP,
	// ���� Button 
	CM_BUTTON_ENTER,
	// �뿪 Button
	CM_BUTTON_LEAVE,
	// Button �Ҽ�������Ϣ
	CM_BUTTON_R_BTN_DOWN
};

class ICtrlButton : public ICtrlInterface
{
public:
	// ����Button����
	virtual	void SetButtonText(const char* pszText) = 0;
	// ��ȡButton����
	virtual	const char* GetButtonText() = 0;

	// check button ģʽ��
	virtual void SetCheck(bool bIsCheck, bool bRedraw) = 0;
	virtual bool IsCheck() = 0;
	virtual IControlBase* GetCheckPanel() = 0;
};
