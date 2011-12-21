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
	virtual void OnPaint(HDC hMemoryDC, CRect &DrawRect, HDC hParentPaintDc = NULL);
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

	// ȡ��ʵ�ʴ��ڵĻ�ͼDC
	HDC GetParentPaintDc() { return m_hPaintDc; };

protected:
	virtual bool IsReady();

protected:
	// ʵ�ʵĴ��ڵ�DC
	HDC m_hPaintDc;
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
