
#pragma once
#include "..\ICtrlInterface.h"

// 添加控件，步骤1：编写一个控件名称宏。注意，控件名称不能相同
#define CTRL_NAME_BASE_PANEL						("Panel")

class ICtrlPanel : public ICtrlInterface
{
public:
	// 开始动画
	virtual void BeginAnimation() = 0;
};
