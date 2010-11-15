
#pragma once
#include "BaseCtrlDefs.h"
#include "BfWindowsWnd.h"

class CBfEdit : public CDirectUiWindow, public CBfWindowsWnd
{
public:
	CBfEdit(HINSTANCE hInstance);
	virtual ~CBfEdit(void);
	
	// ÒÆ¶¯´°¿Ú
	virtual void MoveWindow(CRect ToRect, HDWP hWinPoslnfo);

	void SetDrawFrame(bool bIsDraw) { m_bIsDrawFrame = bIsDraw; };

protected:
	virtual void OnPaint();
	virtual void OnMouseHover(CPoint point);
	virtual void OnLoseFocus();
	virtual void OnSetFocus();

	virtual LPCTSTR GetSuperClassName() const;
	virtual LPCTSTR GetWindowClassName() const;

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	bool m_bIsDrawFrame;
};
