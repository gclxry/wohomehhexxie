
#pragma once
#include "..\ICtrlInterface.h"

// ��ӿؼ�������1����дһ���ؼ����ƺꡣע�⣬�ؼ����Ʋ�����ͬ
#define CTRL_NAME_LINK_LABLE						("LinkLable")

// �����ؼ��򴰿ڷ��͵���Ϣ
enum CTRL_MSG_LINK_LABLE
{
	// LINK_LABLE��ϢBase������Ϣֵ���������ͣ�ֻ����Ϊ������Ϣֵ��Base
	CM_LINK_LABLE_BASE	= 0x10008000,
	// LINK_LABLE Down��Ϣ
	CM_LINK_LABLE_DOWN,
	// LINK_LABLE Up��Ϣ
	CM_LINK_LABLE_UP
};

class ICtrlLinkLable : public ICtrlInterface
{
public:
	// ����Link����
	virtual void SetLinkText(char *pText, bool bRedraw) = 0;
	// ����Link���ӵ�ַURL
	virtual void SetLinkUrl(char *pUrl) = 0;
	// ȡ��Link���ӵ�ַURL
	virtual const char * GetLinkUrl() = 0;
};
