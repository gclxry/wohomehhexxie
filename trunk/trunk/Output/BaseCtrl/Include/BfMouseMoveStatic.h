//////////////////////////////////////////////////////////////////////////
// ������ҳ�����ӵİ�ť

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
