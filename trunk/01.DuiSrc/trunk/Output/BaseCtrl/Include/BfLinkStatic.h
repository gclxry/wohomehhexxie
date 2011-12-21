//////////////////////////////////////////////////////////////////////////
// 类似网页打开连接的按钮

#pragma once
#include "BfStatic.h"

class CBfLinkStatic : public CBfStatic
{
public:
	CBfLinkStatic(void);
	virtual ~CBfLinkStatic(void);

	void SetMouseActive(bool bIsActive);
	virtual void MoveWindow(const CRect &ToRect, HDWP hWinPoslnfo);
private:
	virtual void OnPaint();
	virtual void OnMouseHover(CPoint point);
	virtual void OnMouseLeave(CPoint point);
	virtual void OnLButtonUp(CPoint point);

	void CopyFontInfo(WND_TEXT &From, WND_TEXT &To);
};
