
#pragma once
#include "ICtrlInterface.h"

class ICtrlBasePanel : public ICtrlInterface
{
public:
	ICtrlBasePanel();
	virtual ~ICtrlBasePanel();

protected:
	// 派生控件用于创建属于自己的控件属性
	virtual bool CreateControlPropetry();
	// 初始化控件
	virtual void OnCreate();
	// 控件初始化完毕
	virtual void OnFinalCreate();
	// 销毁控件
	virtual void OnDestroy();
};
