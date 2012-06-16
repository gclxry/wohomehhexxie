
#include "StdAfx.h"
#include "SearchPanel.h"
#include "ICtrlSearchBarImpl.h"
#include "..\..\Inc\ICommonFun.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\Control\ICtrlEdit.h"

CSearchPanel::CSearchPanel()
{
	m_pSearchBar = NULL;
	m_bIsShow = false;
}

CSearchPanel::~CSearchPanel()
{
}

bool CSearchPanel::CreateFeatureWindow(char* pszKernelDllPath, char* pszSkinPath, char *pszSkinWndName, HWND hParent, RECT WndRect, int nShow, int nStyle, LPARAM lParam, bool bNewUiThread)
{
	return false;
}

bool CSearchPanel::CreatePanel(ICtrlSearchBarImpl *pSearchBar, IUiFeatureKernel* pUiKernel, char *pszSkinWndName, HWND hParent, RECT WndRect, int nShow, int nStyle, LPARAM lParam, bool bNewUiThread)
{
	m_pSearchBar = pSearchBar;
	return CUiFeatureWindow::CreateFeatureWindowByKernel(pUiKernel, pszSkinWndName, hParent, WndRect, nShow, nStyle, lParam, bNewUiThread);
}

void CSearchPanel::OnSetFocus()
{
	if (NULL != m_pSearchBar)
		m_pSearchBar->SetEditFocus();
}

void CSearchPanel::OnKillFocus()
{
	if (NULL != m_pSearchBar)
	{
	//	m_pSearchBar->SetEditFocus();
	}
}

void CSearchPanel::ShowPanel(bool bIsShow)
{
	if (m_pSearchBar == NULL || m_pSearchBar->GetOwnerWindow() == NULL || m_bIsShow == bIsShow)
		return;

	m_bIsShow = bIsShow;
	if (bIsShow)
	{
		RECT ctrlRct = m_pSearchBar->GetWindowRect();
		RectClientToScreen(m_pSearchBar->GetOwnerWindow()->GetSafeHandle(), ctrlRct);

		RECT wndRct = this->GetWindowRect();
		int nH = RECT_HEIGHT(wndRct);
		wndRct.top = ctrlRct.bottom + 25;
		wndRct.bottom = wndRct.top + nH;

		this->MoveWindow(wndRct);

		this->ShowWindow(SW_SHOW);
		m_pSearchBar->SetEditFocus();
	}
	else
	{
		this->ShowWindow(SW_HIDE);
	}
}

// 控件发送给窗口的消息接口
LRESULT CSearchPanel::OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam)
{
	if (m_bIsShow && CM_EDIT_FUNCTION_KEY_DOWN == nMsgId && m_pWindowBase != NULL && m_pSearchBar != NULL && m_pSearchBar->GetShowListName() != NULL)
	{
		IControlBase * pListCtrl = m_pWindowBase->GetControl((char*)m_pSearchBar->GetShowListName());
		if (pListCtrl != NULL)
			pListCtrl->OnCtrlNotify(WM_KEYDOWN, wParam, lParam);
	}

	return 0;
}
