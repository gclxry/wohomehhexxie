
#pragma once
#include "BaseCtrlDefs.h"

using namespace std;
typedef map<UINT, CString*> MENU_TEXT_LIST;

class CBfPopupMenu : public CWindowBase
{
	friend class CBfBaseDlg;
public:
	CBfPopupMenu(void);
	virtual ~CBfPopupMenu(void);

	HMENU GetSafeMenuHandle() { return m_hMenu; };

	bool Create();
	bool AppendMenu(UINT uFlags, UINT uIDNewItem, LPCWSTR lpNewItem);
	void TrackPopupMenu(HWND hParent, int x, int y);
	void Destroy();

	void SetMenuWndHookInfo(HWND hWnd, WNDPROC pOldWndProc);
	virtual LRESULT WndProc(UINT message, WPARAM wParam, LPARAM lParam);

protected:
	static void OnMeasureItem(MEASUREITEMSTRUCT *lpMis);
	static void OnDrawItem(DRAWITEMSTRUCT * lpDrawSta);
	static void DrawItem(DRAWITEMSTRUCT *lpDrawSta, HDC hMemoryDC);

protected:
	LRESULT OnNcCalcSize(WPARAM wParam, LPARAM lParam);
	LRESULT OnWindowPosChanging(WPARAM wParam, LPARAM lParam);
	LRESULT OnNcPaint(HWND hWnd, WPARAM wParam, LPARAM lParam);
	LRESULT OnPrintClient(HWND hWnd, WPARAM wParam, LPARAM lParam);
	void OnNcPaintDraw(HWND hWnd, HDC hMemoryDC);
	void PrintClientDraw(HWND hWnd, HDC hMemoryDC, LPARAM lParam);
	LRESULT OnDrawSelect(HWND hWnd, WPARAM wParam, LPARAM lParam);

protected:
	HMENU m_hMenu;
	MENU_TEXT_LIST m_MenuTextList;
	WNDPROC m_pOldWndProc;
	int m_nSelIndex;
};
