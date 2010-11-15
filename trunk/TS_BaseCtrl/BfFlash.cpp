
#include "BfFlash.h"


CBfFlash::CBfFlash(void)
{
	m_hDllHandle = NULL;
	m_bIsInit = false;

	m_fpInitPlayWnd = NULL;
	m_fpUnInit = NULL;
	m_fpPlayFlash = NULL;
	m_fpMovePlayWindow = NULL;
	m_fpOnTimerPlay = NULL;
	m_fpOnPaint = NULL;
	m_fpOnActivateApp = NULL;
}

CBfFlash::~CBfFlash(void)
{
}

bool CBfFlash::IsReady()
{
	return (CDirectUiWindow::IsReady() && m_bIsInit && m_hDllHandle != NULL
		&& m_fpInitPlayWnd != NULL && m_fpUnInit != NULL && m_fpPlayFlash != NULL
		&& m_fpMovePlayWindow != NULL && m_fpOnTimerPlay != NULL && m_fpOnPaint != NULL
		&& m_fpOnActivateApp != NULL);
}

bool CBfFlash::CreateWnd(CDirectUiDlg *pParentDlg, CDirectUiManager *pUiManager, CDirectUiWindowMsgCtrl *pMsgCtrl,
							 CRect WndRect, int nWndId, WND_TYPE WndType, int nImageId, CString strImagePath, IMAGE_TYPE nImageType)
{
	bool bRet = CDirectUiWindow::CreateWnd(pParentDlg, pUiManager, pMsgCtrl, WndRect, nWndId, WndType, nImageId, strImagePath, nImageType);

	if (bRet)
	{
		CString strDllPath = CUiMethod::GetAppPath() + _T("FlashShowDll.dll");

		m_hDllHandle = LoadLibrary(strDllPath);
		if (m_hDllHandle != NULL)
		{
			m_fpInitPlayWnd = (pInitPlayWnd)GetProcAddress(m_hDllHandle, "InitPlayWnd");
			m_fpUnInit = (pUnInit)GetProcAddress(m_hDllHandle, "UnInit");
			m_fpPlayFlash = (pPlayFlash)GetProcAddress(m_hDllHandle, "PlayFlash");
			m_fpMovePlayWindow = (pMovePlayWindow)GetProcAddress(m_hDllHandle, "MovePlayWindow");
			m_fpOnTimerPlay = (pOnTimerPlay)GetProcAddress(m_hDllHandle, "OnTimerPlay");
			m_fpOnPaint = (pOnPaint)GetProcAddress(m_hDllHandle, "OnPaint");
			m_fpOnActivateApp = (pOnActivateApp)GetProcAddress(m_hDllHandle, "OnActivateApp");

			m_bIsInit = m_fpInitPlayWnd(this, m_hParent);
		}
	}

	return IsReady();
}

void CBfFlash::PlayFlash(CString strFlashPath)
{
	if (!strFlashPath.IsEmpty() && IsReady())
	{
		m_strFlashPath = strFlashPath;

#ifdef UNICODE
		USES_CONVERSION;
		m_fpPlayFlash(this, W2A(m_strFlashPath));
#else
		m_fpPlayFlash(this, m_strFlashPath);
#endif
	}
}

void CBfFlash::OnDestroy()
{
	CDirectUiWindow::OnDestroy();

	if (IsReady())
		m_fpUnInit(this);
}

void CBfFlash::MoveWindow(CRect ToRect, HDWP hWinPoslnfo)
{
	CDirectUiWindow::MoveWindow(ToRect, hWinPoslnfo);

	if (IsReady())
		m_fpMovePlayWindow(this, m_WndRect);
}

void CBfFlash::OnTimer(int nTimerId)
{
	if (IsReady())
		m_fpOnTimerPlay(this, m_hParent, nTimerId);
}

void CBfFlash::OnPaint()
{
	if (IsReady())
		m_fpOnPaint(this, m_hMemoryDC, m_WndRect);
}

void CBfFlash::OnActivateApp(WPARAM wParam, LPARAM lParam)
{
	if (IsReady() && BOOL(wParam))
		m_fpOnActivateApp(this, m_hParent);
}
