#include "StdAfx.h"
#include "Win32TestWindow.h"
#include <assert.h>
#include "..\..\Inc\ICommonFun.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\CDrawingBoard.h"

CWin32TestWindow::CWin32TestWindow()
{
	m_dwMainThreadId = 0;
	m_pAnimationExpandCtrl = NULL;
}

CWin32TestWindow::~CWin32TestWindow()
{
}

bool CWin32TestWindow::ShowWin32TestWindow(DWORD dwMainThreadId)
{
	m_dwMainThreadId = dwMainThreadId;

	string strKernelDllPath = PathHelper(NAME_KERNEL_DLL);
	string strSkinPath = PathHelper("TestSkin\\ICtrlAnimationExpand.ufd");

	CRect WndRct(0, 0, 0, 0);
	return CreateFeatureWindow((char*)strKernelDllPath.c_str(), (char*)strSkinPath.c_str(), "TestWindow", NULL, WndRct, SW_SHOW, NULL);
}

void CWin32TestWindow::OnKeyDown(int nVirtKey, int nFlag)
{
	if (nVirtKey == VK_ESCAPE)
	{
		this->CloseSelf();
		::PostThreadMessage(m_dwMainThreadId, WM_QUIT, 0, 0);
	}
}

// 控件发送给窗口的消息接口
LRESULT CWin32TestWindow::OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

// 本窗口的消息处理函数
LRESULT CWin32TestWindow::WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam)
{
	return CUiFeatureWindow::WndProc(nMsgId, wParam, lParam);
}

// WM_CREATE：对话框初始化	
void CWin32TestWindow::OnCreate()
{
	m_pAnimationExpandCtrl = dynamic_cast<ICtrlAnimationExpand*>(m_pWindowBase->GetControl("TestAniExpand"));
	if (m_pAnimationExpandCtrl == NULL)
	{
		assert(false);
		return;
	}

	CDrawingBoard* pDrawBoard = m_pAnimationExpandCtrl->GetAnimationBackgroudMemDc();
	if (pDrawBoard == NULL)
	{
		assert(false);
		return;
	}

}
