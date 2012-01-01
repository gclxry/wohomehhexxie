// 一个控件必须实现的所有接口

#pragma once
#include "IControlBase.h"

class ICtrlInterface : public IControlBase
{
public:
	ICtrlInterface();
	virtual ~ICtrlInterface();

};
