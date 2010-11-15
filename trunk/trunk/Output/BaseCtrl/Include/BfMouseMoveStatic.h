//////////////////////////////////////////////////////////////////////////
// 类似网页打开连接的按钮

#pragma once
#include "BfStatic.h"

class CBfMouseMoveStatic : public CBfStatic
{
public:
	CBfMouseMoveStatic(void);
	virtual ~CBfMouseMoveStatic(void);

private:
	virtual void OnMouseHover(CPoint point);
	virtual void OnMouseLeave(CPoint point);
};
