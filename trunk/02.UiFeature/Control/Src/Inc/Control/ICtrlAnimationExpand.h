
#pragma once
#include "..\ICtrlInterface.h"
#include "..\CDrawingBoard.h"

// 添加控件，步骤1：编写一个控件名称宏。注意，控件名称不能相同
#define CTRL_NAME_ANIMATION_EXPAND					("AnimationExpand")

class ICtrlAnimationExpand : public ICtrlInterface
{
public:
	// 开始动画
	virtual void BeginAnimation() = 0;
	// 取得用于绘制背景的图片DC
	virtual CDrawingBoard* GetAnimationBackgroudMemDc() = 0;
};
