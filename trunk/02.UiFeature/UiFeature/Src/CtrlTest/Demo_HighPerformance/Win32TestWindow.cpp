#include "StdAfx.h"
#include "Win32TestWindow.h"
#include <assert.h>
#include "..\..\Inc\ICommonFun.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include <Shellapi.h>
#include <windows.h>

CWin32TestWindow::CWin32TestWindow()
{
	m_pAnimationPanel_1 = NULL;
	m_pAnimationPanel_11 = NULL;
	m_dwMainThreadId = 0;
}

CWin32TestWindow::~CWin32TestWindow()
{
}

bool CWin32TestWindow::ShowWin32TestWindow(DWORD dwMainThreadId)
{
	m_dwMainThreadId = dwMainThreadId;

	string strKernelDllPath = PathHelper(NAME_KERNEL_DLL);
	string strSkinPath = PathHelper("CtrlTest_Skin\\Demo_HighPerformance\\Demo_HighPerformance.ufd");

	CRect WndRct(0, 0, 0, 0);
	return CreateFeatureWindow((char*)strKernelDllPath.c_str(), (char*)strSkinPath.c_str(), "TestWindow", NULL, WndRct, SW_SHOW, WS_OVERLAPPED | WS_THICKFRAME, NULL, false);
}

void CWin32TestWindow::OnKeyDown(int nVirtKey, int nFlag)
{
	if (nVirtKey == VK_ESCAPE)
	{
		this->CloseWindow(false);
		::PostThreadMessage(m_dwMainThreadId, WM_QUIT, 0, 0);
	}
}

// 控件发送给窗口的消息接口
LRESULT CWin32TestWindow::OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam)
{
	if (pCtrl == NULL)
		return -1;

	return 0;
}

// 本窗口的消息处理函数
LRESULT CWin32TestWindow::WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam)
{
	if (nMsgId == WM_LBUTTONUP && m_pWindowBase != NULL)
	{
		//m_pWindowBase->AppendAnimationControl(m_pAnimationPanel_1);
		m_pWindowBase->AppendAnimationControl(m_pAnimationPanel_GIFShow2);
		m_pWindowBase->AppendAnimationControl(m_pAnimationPanel_GIFShow3);
		m_pWindowBase->AppendAnimationControl(m_pAnimationPanel_11);
		m_pWindowBase->DoControlAnimation();
	}

	return CUiFeatureWindow::WndProc(nMsgId, wParam, lParam);
}

// WM_CREATE：对话框初始化	
void CWin32TestWindow::OnCreate()
{
	if (m_pWindowBase != NULL)
		m_pWindowBase->SetAnimationTimer();

	m_pAnimationPanel_1 = dynamic_cast<ICtrlPanel*>(m_pWindowBase->GetControl("P1"));
	m_pAnimationPanel_11 = dynamic_cast<ICtrlPanel*>(m_pWindowBase->GetControl("P11"));
	m_pAnimationPanel_GIFShow2 = dynamic_cast<ICtrlPanel*>(m_pWindowBase->GetControl("GIFShow2"));
	m_pAnimationPanel_GIFShow3 = dynamic_cast<ICtrlPanel*>(m_pWindowBase->GetControl("GIFShow3"));
}

void CWin32TestWindow::UnInitialized()
{
	if (m_pUiKernel != NULL)
		m_pUiKernel->UnInitialized();
}
