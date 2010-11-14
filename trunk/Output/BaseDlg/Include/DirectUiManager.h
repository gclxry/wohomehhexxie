#pragma once

class CDirectUiManager
{
public:
	CDirectUiManager(void);
	~CDirectUiManager(void);

	virtual bool InitManager(CDirectUiBaseDlg *pParentDlg);

	virtual void OnPaint(HDC hMemoryDC, CRect &WndRect);
	virtual void OnDestroy();
	virtual bool OnMouseMove(UINT nFlags, CPoint point);
	virtual bool OnLButtonDown(UINT nFlags, CPoint point);
	virtual bool OnLButtonUp(UINT nFlags, CPoint point);
	virtual bool OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual void OnTimer(int nTimerId);
	virtual void OnActivateApp(WPARAM wParam, LPARAM lParam);

	// 取得实体子窗口的个数
	int GetTrueWndCtns() { return m_nTrueWndCtns; };

	// 删除所有窗口
	void ClearAllDirectUiWindow();
	// 删除指定窗口
	void ClearDirectUiWindow(CDirectUiWindow *pWnd);

protected:
	virtual bool IsReady();

	void DrawNormalBkgnd();
	void DrawNormalBkgndLine();

	void DrawFetionBkgnd();
	void DrawFetionBkgndLine();

protected:
	// 绘图用的GID+
	Graphics *m_pDoGrap;
	// 绘图用的GDI
	HDC m_hMemoryDC;
	HWND m_hParent;
	CDirectUiBaseDlg *m_pParentDlg;
	// 绘图DC的大小
	CRect m_DcRect;

	// 所有子窗口的列表
	CWndList m_WndList;
	// 实体子窗口的个数
	int m_nTrueWndCtns;
};
