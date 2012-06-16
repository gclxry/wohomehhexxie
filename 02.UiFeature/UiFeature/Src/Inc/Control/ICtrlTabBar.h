
#pragma once
#include "..\ICtrlInterface.h"

// ��ӿؼ�������1����дһ���ؼ����ƺꡣע�⣬�ؼ����Ʋ�����ͬ
#define CTRL_NAME_TAB_BAR						("TabBar")

// �ؼ��򴰿ڷ��͵���Ϣ
enum CTRL_MSG_TABBAR
{
	// Button��ϢBase������Ϣֵ���������ͣ�ֻ����Ϊ��Ϣֵ��Base
	CM_TABBAR_BASE	= 0x10015000,
	// Up��Ϣ
	CM_TABBAR_UP
};

class ICtrlTabBar : public ICtrlInterface
{
public:
	// ���õ�ǰѡ����
	virtual void SetCheck(int nBtnNum) = 0;
	// ȡ��ָ����ľ���λ�ã��������������
	virtual RECT GetButtonWindowRect(int nBtnNum) = 0;
};
