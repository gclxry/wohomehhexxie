
#pragma once
#include "ICtrlInterface.h"

class ICtrlBasePanel : public ICtrlInterface
{
public:
	ICtrlBasePanel();
	virtual ~ICtrlBasePanel();

protected:
	// �����ؼ����ڴ��������Լ��Ŀؼ�����
	virtual bool CreateControlPropetry();
	// ��ʼ���ؼ�
	virtual void OnCreate();
	// �ؼ���ʼ�����
	virtual void OnFinalCreate();
	// ���ٿؼ�
	virtual void OnDestroy();
};
