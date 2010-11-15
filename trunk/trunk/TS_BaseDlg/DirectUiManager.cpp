
#include "DirectUiManager.h"

CDirectUiManager::CDirectUiManager(void)
{
	m_pDoGrap = NULL;
	m_hMemoryDC = NULL;
	m_hParent = NULL;
	m_pParentDlg = NULL;
	m_DcRect.SetRectEmpty();
	m_nTrueWndCtns = 0;
}

CDirectUiManager::~CDirectUiManager(void)
{
}

//-----------------------------------------------------------------------------
// 描述: 初始化GDI引擎
//-----------------------------------------------------------------------------
bool CDirectUiManager::InitManager(CDirectUiDlg *pParentDlg)
{
	if (pParentDlg != NULL)
	{
		m_pParentDlg = pParentDlg;
		m_hParent = m_pParentDlg->GetSafeHandle();
	}

	return IS_SAVE_HANDLE(m_hParent);
}

// 删除所有窗口
void CDirectUiManager::ClearAllDirectUiWindow()
{
	m_WndList.ClearAll();
}

void CDirectUiManager::ClearDirectUiWindow(CDirectUiWindow *pWnd)
{
	if (pWnd != NULL)
		m_WndList.DeleteSpWndObj(pWnd);
}

bool CDirectUiManager::IsReady()
{
	return IS_SAVE_HANDLE(m_hParent);
}

void CDirectUiManager::OnPaint(HDC hMemoryDC, CRect &DrawRect)
{
	Graphics DoGrap(hMemoryDC);

	m_pDoGrap = &DoGrap;
	m_hMemoryDC = hMemoryDC;
	m_DcRect = DrawRect;
	
	for (WndObj *pWndObj = m_WndList.TopObj(); pWndObj != NULL; pWndObj = m_WndList.NextObj(pWndObj))
	{
		if (pWndObj->pWnd != NULL)
			((CDirectUiWindow*)(pWndObj->pWnd))->OnPaintProc(m_pDoGrap, m_hMemoryDC);
	}
}

bool CDirectUiManager::OnMouseMove(UINT nFlags, CPoint point)
{
	bool bRet = false;

	for (WndObj *pWndObj = m_WndList.TopObj(); pWndObj != NULL; pWndObj = m_WndList.NextObj(pWndObj))
	{
		if (pWndObj->pWnd != NULL)
			((CDirectUiWindow*)(pWndObj->pWnd))->OnMouseMoveProc(nFlags, point);
	}

	return bRet;
}

void CDirectUiManager::OnTimer(int nTimerId)
{
	for (WndObj *pWndObj = m_WndList.TopObj(); pWndObj != NULL; pWndObj = m_WndList.NextObj(pWndObj))
	{
		if (pWndObj->pWnd != NULL)
			((CDirectUiWindow*)(pWndObj->pWnd))->OnTimer(nTimerId);
	}
}

void CDirectUiManager::OnActivateApp(WPARAM wParam, LPARAM lParam)
{
	for (WndObj *pWndObj = m_WndList.TopObj(); pWndObj != NULL; pWndObj = m_WndList.NextObj(pWndObj))
	{
		if (pWndObj->pWnd != NULL)
			((CDirectUiWindow*)(pWndObj->pWnd))->OnActivateApp(wParam, lParam);
	}
}

void CDirectUiManager::OnDestroy()
{
	for (WndObj *pWndObj = m_WndList.TopObj(); pWndObj != NULL; pWndObj = m_WndList.NextObj(pWndObj))
	{
		if (pWndObj->pWnd != NULL)
			((CDirectUiWindow*)(pWndObj->pWnd))->OnDestroy();
	}

	CDirectUiWindow::UnloadDirectUiWindow();
}

bool CDirectUiManager::OnLButtonDown(UINT nFlags, CPoint point)
{
	bool bRet = false;

	for (WndObj *pWndObj = m_WndList.TopObj(); pWndObj != NULL; pWndObj = m_WndList.NextObj(pWndObj))
	{
		CDirectUiWindow *pWnd = (CDirectUiWindow *)(pWndObj->pWnd);
		if (pWnd != NULL)
		{
			if (pWnd->OnLButtonDownProc(nFlags, point))
				break;
		}
	}

	return bRet;
}

bool CDirectUiManager::OnLButtonUp(UINT nFlags, CPoint point)
{
	bool bRet = false;

	for (WndObj *pWndObj = m_WndList.TopObj(); pWndObj != NULL; pWndObj = m_WndList.NextObj(pWndObj))
	{
		CDirectUiWindow *pWnd = (CDirectUiWindow *)(pWndObj->pWnd);
		if (pWnd != NULL)
		{
			if (pWnd->OnLButtonUpProc(nFlags, point))
				break;
		}
	}
	CDirectUiWindow::SetLButtonUp();

	return bRet;
}

bool CDirectUiManager::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	bool bRet = false;

	for (WndObj *pWndObj = m_WndList.TopObj(); pWndObj != NULL; pWndObj = m_WndList.NextObj(pWndObj))
	{
		CDirectUiWindow *pWnd = (CDirectUiWindow *)(pWndObj->pWnd);
		if (pWnd != NULL)
		{
			if (pWnd->OnLButtonDblClkProc(nFlags, point))
				break;
		}
	}

	return bRet;
}
