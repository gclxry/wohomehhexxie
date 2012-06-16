#include "StdAfx.h"
#include "Win32TestWindow.h"
#include <assert.h>
#include "..\..\Inc\ICommonFun.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\CA2W_W2A.h"
#include <Shellapi.h>
#include <windows.h>

CWin32TestWindow::CWin32TestWindow()
{
	m_dwMainThreadId = 0;
	m_pCloseButton = NULL;
	m_pLinkTieba = NULL;
	m_pLinkTengXun = NULL;
	m_pLinkXinLang = NULL;
	m_pLink360 = NULL;

	m_pAnimationPanel = NULL;
	m_pUifeaturelogoPanel = NULL;
	m_pWindowbkPanel = NULL;

	m_pGetDemoBtn = NULL;
	m_nWndAnimationId = 1;
}

CWin32TestWindow::~CWin32TestWindow()
{
}

bool CWin32TestWindow::ShowWin32TestWindow(DWORD dwMainThreadId)
{
	m_dwMainThreadId = dwMainThreadId;

	string strKernelDllPath = PathHelper(NAME_KERNEL_DLL);
	string strSkinPath = PathHelper("CtrlTest_Skin\\Demo_WindowAnimation\\Demo_WindowAnimation.ufd");

	CRect WndRct(0, 0, 0, 0);
	return CreateFeatureWindow((char*)strKernelDllPath.c_str(), (char*)strSkinPath.c_str(), "MainWindow", NULL, WndRct, SW_SHOW, WS_OVERLAPPED | WS_THICKFRAME, NULL, false);
}

void CWin32TestWindow::OnKeyDown(int nVirtKey, int nFlag)
{
	if (nVirtKey == VK_ESCAPE)
		CloseTestWindow();
}

// 控件发送给窗口的消息接口
LRESULT CWin32TestWindow::OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam)
{
	CUiFeatureWindow::OnCtrlMessage(pCtrl, nMsgId, wParam, lParam);

	USES_CONVERSION_F;
	if (m_pCloseButton->CompareControl(pCtrl) && nMsgId == CM_BUTTON_UP)
	{
		CloseTestWindow();
	}
	else if (nMsgId == CM_LINK_LABLE_UP)
	{
		ICtrlLinkLable* pLinkCtrl = dynamic_cast<ICtrlLinkLable*>(pCtrl);
		if (pLinkCtrl == NULL)
			return -1;

		char* pszUrl = (char*)wParam;
		if (pszUrl == NULL || strlen(pszUrl) <= 0)
			return -1;

		HINSTANCE hOpen = ::ShellExecute(NULL, _T("open"), A2W_F(pszUrl), NULL, NULL, SW_SHOWNORMAL);
		if (hOpen == NULL)
			return -1;
	}
	else if (nMsgId == CM_BUTTON_UP && m_pGetDemoBtn->CompareControl(pCtrl))
	{
		SetWindowAnimation();
	}

	return 0;
}

void CWin32TestWindow::CloseTestWindow()
{
	this->CloseWindow(false);
	::PostThreadMessage(m_dwMainThreadId, WM_QUIT, 0, 0);
}

// 本窗口的消息处理函数
LRESULT CWin32TestWindow::WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam)
{
	if (UM_WINDOWS == nMsgId && UWM_ANIMATION_THREAD_END == wParam)
	{
		// 窗口接受到动画线程结束的消息
		SetWindowAnimation();
	}

	return CUiFeatureWindow::WndProc(nMsgId, wParam, lParam);
}

// WM_CREATE：对话框初始化	
void CWin32TestWindow::OnCreate()
{
	if (m_pWindowBase == NULL)
		return;

	m_pCloseButton = dynamic_cast<ICtrlButton*>(m_pWindowBase->GetControl("closebtn"));
	m_pLinkTieba = dynamic_cast<ICtrlLinkLable*>(m_pWindowBase->GetControl("link.tieba"));
	m_pLinkTengXun = dynamic_cast<ICtrlLinkLable*>(m_pWindowBase->GetControl("link.tengxun"));
	m_pLinkXinLang = dynamic_cast<ICtrlLinkLable*>(m_pWindowBase->GetControl("link.xinlang"));
	m_pLink360 = dynamic_cast<ICtrlLinkLable*>(m_pWindowBase->GetControl("link.down360"));

	m_pAnimationPanel = dynamic_cast<ICtrlPanel*>(m_pWindowBase->GetControl("AnimationPanel"));
	m_pUifeaturelogoPanel = dynamic_cast<ICtrlPanel*>(m_pWindowBase->GetControl("uifeaturelogo"));
	m_pWindowbkPanel = dynamic_cast<ICtrlPanel*>(m_pWindowBase->GetControl("windowbk"));

	m_pGetDemoBtn = dynamic_cast<ICtrlButton*>(m_pWindowBase->GetControl("GetDemoBtn"));

	if (m_pCloseButton == NULL || m_pLinkTieba == NULL || m_pLinkTengXun == NULL || m_pLinkXinLang == NULL ||
		m_pAnimationPanel == NULL || m_pUifeaturelogoPanel == NULL || m_pWindowbkPanel == NULL ||
		m_pLink360 == NULL || m_pGetDemoBtn == NULL)
	{
		assert(false);
		return;
	}
}

void CWin32TestWindow::UnInitialized()
{
	if (m_pUiKernel != NULL)
		m_pUiKernel->UnInitialized();
}

void CWin32TestWindow::SetWindowAnimation()
{
	if (m_pWindowbkPanel == NULL || m_pWindowBase == NULL)
		return;

	if (m_nWndAnimationId > 72)
	{
		m_nWndAnimationId = 1;
		::MessageBox(m_hWnd, _T("亲！已经为您播放了72个动画！"), _T("亲，动画完了："), MB_OK);
		return;
	}

	m_nWndAnimationId++;

	// 设置控件动画类型
	m_pWindowbkPanel->PP_SetCtrlAnimationType(m_nWndAnimationId);

	// 向窗口加入动画元素
	m_pWindowBase->AppendAnimationControl(m_pWindowbkPanel);

	// 开始动画
	m_pWindowBase->DoControlAnimation();
}
