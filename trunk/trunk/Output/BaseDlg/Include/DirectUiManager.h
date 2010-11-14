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

	// ȡ��ʵ���Ӵ��ڵĸ���
	int GetTrueWndCtns() { return m_nTrueWndCtns; };

	// ɾ�����д���
	void ClearAllDirectUiWindow();
	// ɾ��ָ������
	void ClearDirectUiWindow(CDirectUiWindow *pWnd);

protected:
	virtual bool IsReady();

	void DrawNormalBkgnd();
	void DrawNormalBkgndLine();

	void DrawFetionBkgnd();
	void DrawFetionBkgndLine();

protected:
	// ��ͼ�õ�GID+
	Graphics *m_pDoGrap;
	// ��ͼ�õ�GDI
	HDC m_hMemoryDC;
	HWND m_hParent;
	CDirectUiBaseDlg *m_pParentDlg;
	// ��ͼDC�Ĵ�С
	CRect m_DcRect;

	// �����Ӵ��ڵ��б�
	CWndList m_WndList;
	// ʵ���Ӵ��ڵĸ���
	int m_nTrueWndCtns;
};
