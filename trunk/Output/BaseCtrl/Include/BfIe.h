
#pragma once
#include "BaseCtrlDefs.h"
#include "BfWindowsWnd.h"

class CBfIe : public CDirectUiWindow, public CBfWindowsWnd
{
public:
	CBfIe(HINSTANCE hInstance);
	virtual ~CBfIe(void);
	
	// ÒÆ¶¯´°¿Ú
	virtual void MoveWindow(CRect ToRect, HDWP hWinPoslnfo);

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
