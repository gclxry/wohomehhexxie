#pragma once
#include "DirectUiWindow.h"
#include "WndList.h"

class CDirectUiManager
{
public:
	CDirectUiManager(void);
	~CDirectUiManager(void);

	virtual bool InitManager(CDirectUiDlg *pParentDlg);

	virtual void OnPaintRgn(CRect &WndRect, Graphics *pGraphics);
	virtual void OnPaint(HDC hMemoryDC, CRect &DrawRect);
	virtual bool OnMouseMove(UINT nFlags, CPoint point);
	virtual void OnTimer(int nTimerId);
	virtual void OnActivateApp(WPARAM wParam, LPARAM lParam);
	virtual bool OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnDestroy();
	virtual bool OnLButtonUp(UINT nFlags, CPoint point);
	virtual bool OnLButtonDblClk(UINT nFlags, CPoint point);

	// ȡ��ʵ���Ӵ��ڵĸ���
	int GetTrueWndCtns() { return m_nTrueWndCtns; };

	// ɾ�����д���
	void ClearAllDirectUiWindow();
	// ɾ��ָ������
	void ClearDirectUiWindow(CDirectUiWindow *pWnd);

protected:
	virtual bool IsReady();

protected:
	// ��ͼ�õ�GID+
	Graphics *m_pDoGrap;
	// ��ͼ�õ�GDI
	HDC m_hMemoryDC;
	HWND m_hParent;
	CDirectUiDlg *m_pParentDlg;
	// ��ͼDC�Ĵ�С
	CRect m_DcRect;

	// �����Ӵ��ڵ��б�
	CWndList m_WndList;
	// ʵ���Ӵ��ڵĸ���
	int m_nTrueWndCtns;
};
