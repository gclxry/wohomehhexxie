#include "StdAfx.h"
#include "Win32TestWindow.h"
#include <assert.h>
#include "..\..\Inc\ICommonFun.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\CDrawingImage.h"

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

// �ؼ����͸����ڵ���Ϣ�ӿ�
LRESULT CWin32TestWindow::OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam)
{
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
	RECT WorkArea;
	INIT_RECT(WorkArea);
	::SystemParametersInfo(SPI_GETWORKAREA, 0, &WorkArea, 0);
	::MoveWindow(m_hWnd, 0, 0, RECT_WIDTH(WorkArea), RECT_HEIGHT(WorkArea), FALSE);

	m_pAnimationExpandCtrl = dynamic_cast<ICtrlAnimationExpand*>(m_pWindowBase->GetControl("TestAniExpand"));
	if (m_pAnimationExpandCtrl == NULL)
	{
		assert(false);
		return;
	}

	CDrawingImage* pDrawBoard = m_pAnimationExpandCtrl->GetAnimationBackgroudMemDc();
	if (pDrawBoard == NULL)
	{
		assert(false);
		return;
	}

	pDrawBoard->CreateByFile("F:\\03.360\\03.Infomation\\����ͼƬ\\zhuomian.bmp");

	RECT rct;
	rct.left = rct.top = 500;
	rct.right = rct.left + 60;
	rct.bottom = rct.top + 60;
	m_pAnimationExpandCtrl->SetIconPostion(rct);
	m_pAnimationExpandCtrl->SetUpMode(true);
	m_pAnimationExpandCtrl->BeginAnimation();
}