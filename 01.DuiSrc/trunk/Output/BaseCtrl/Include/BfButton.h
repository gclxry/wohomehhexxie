
#pragma once

#include "BaseCtrlDefs.h"

class CBfButton : public CDirectUiWindow
{
public:
	CBfButton(void);
	virtual ~CBfButton(void);

protected:
	virtual void OnLButtonDown(CPoint point);
	virtual void OnLButtonUp(CPoint point);
	virtual void OnMouseHover(CPoint point);
	virtual void OnMouseLeave(CPoint point);
	virtual void OnLoseFocus();
	virtual void OnPaint();
};
