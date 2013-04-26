#include "StdAfx.h"
#include "Win32TestWindow.h"
#include <assert.h>
#include "..\..\Inc\ICommonFun.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include <Shellapi.h>
#include <windows.h>

CWin32TestWindow::CWin32TestWindow()
{
	m_dwMainThreadId = 0;
	m_bCloseWindow = false;
}

CWin32TestWindow::~CWin32TestWindow()
{
}

bool CWin32TestWindow::ShowWin32TestWindow(DWORD dwMainThreadId)
{
	m_dwMainThreadId = dwMainThreadId;

	string strKernelDllPath = PathHelper(NAME_KERNEL_DLL);
	string strSkinPath = PathHelper("CtrlTest_Skin\\Demo_DialogAnimation\\Demo_DialogAnimation.ufd");

	CRect WndRct(0, 0, 0, 0);
	return CreateFeatureWindow((char*)strKernelDllPath.c_str(), (char*)strSkinPath.c_str(), "TestWindow", NULL, WndRct, SW_SHOW, WS_OVERLAPPED | WS_THICKFRAME, NULL, false);
}

void CWin32TestWindow::OnKeyDown(int nVirtKey, int nFlag)
{
	if (nVirtKey == VK_ESCAPE)
	{
//		this->CloseWindow(false);
//		::PostThreadMessage(m_dwMainThreadId, WM_QUIT, 0, 0);
		m_bCloseWindow = true;
		this->CloseWindowWithAnimation(m_pAnimationPanel);
	}
}

// �ؼ����͸����ڵ���Ϣ�ӿ�
LRESULT CWin32TestWindow::OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam)
{
	CUiFeatureWindow::OnCtrlMessage(pCtrl, nMsgId, wParam, lParam);

	// ������ж���Ϊ���Ƴ�����Ӧ�ó����ڹرնԻ���Ķ���������ϵͳ���򴰿ڷ���CMB_ANIMATION_END��Ϣ
	// ֻҪ�ж��ڶԻ������ʱ���ܵ������Ϣ���Ϳ����Ƴ�����Ӧ�ó�����
	if (m_bCloseWindow && m_pAnimationPanel != NULL && m_pAnimationPanel->CompareControl(pCtrl) && nMsgId == CMB_ANIMATION_END)
	{
		// �رնԻ��򶯻����������رմ���
		::PostThreadMessage(m_dwMainThreadId, WM_QUIT, 0, 0);
		return 0;
	}

	return 0;
}

// �����ڵ���Ϣ��������
LRESULT CWin32TestWindow::WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam)
{
	return CUiFeatureWindow::WndProc(nMsgId, wParam, lParam);
}

// WM_CREATE���Ի����ʼ��	
void CWin32TestWindow::OnCreate()
{
	m_pAnimationPanel = dynamic_cast<ICtrlPanel*>(m_pWindowBase->GetControl("AnimationPanel"));
	if (m_pAnimationPanel == NULL)
	{
		assert(false);
		return;
	}

	ShowWindowWithAnimation(m_pAnimationPanel);
}

void CWin32TestWindow::UnInitialized()
{
	if (m_pUiKernel != NULL)
		m_pUiKernel->UnInitialized();
}