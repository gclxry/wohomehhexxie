//////////////////////////////////////////////////////////////////////////
// 类似MFC CStatic，静态文本窗口

#pragma once
#include "BaseCtrlDefs.h"

#define CHECK_BOX_HW						(10)

class CBfCheckBox : public CDirectUiWindow
{
public:
	CBfCheckBox(void);
	virtual ~CBfCheckBox(void);

	void SetCheck(bool bIsCheck);
	bool IsCheck() { return m_bIsCheck; };

	// 移动窗口
	virtual void MoveWindow(CRect ToRect, HDWP hWinPoslnfo);

protected:
	virtual void OnLButtonDown(CPoint point);
	virtual void OnLButtonUp(CPoint point);
	virtual void OnMouseHover(CPoint point);
	virtual void OnMouseLeave(CPoint point);
	virtual void OnPaint();

private:
	bool m_bIsCheck;
};
