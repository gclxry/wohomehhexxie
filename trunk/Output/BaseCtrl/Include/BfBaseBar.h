#pragma once

#include "BaseCtrlDefs.h"
#include "ResImage.h"

class CBfBaseBar : public CDirectUiWindow
{
public:
	CBfBaseBar(void);
	~CBfBaseBar(void);

	// 初始化 bar 的各个属性，以及bar中的子窗口
	virtual bool InitBar() = 0;

protected:
	virtual void OnLButtonDown(CPoint point);
};
