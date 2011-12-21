//////////////////////////////////////////////////////////////////////////
// ComboBox的下拉按钮

#pragma once
#include "BfButton.h"

class CBfDropDownButton : public CBfButton
{
public:
	CBfDropDownButton(void);
	virtual ~CBfDropDownButton(void);

protected:
	virtual void OnPaint();
	virtual void OnMouseHover(CPoint point);
	virtual void OnMouseLeave(CPoint point);

private:
	void Normal_Sj();
	void DrawMouseMove();
};
