#pragma once
#include "..\..\Inc\CUiFeatureWindow.h"
#include "..\..\Inc\Control\ICtrlButton.h"
#include "..\..\Inc\Control\ICtrlLinkLable.h"
#include "..\..\Inc\Control\ICtrlPanel.h"
#include "..\..\Inc\Control\ICtrlButton.h"

class CWin32TestWindow : public CUiFeatureWindow
{
public:
	CWin32TestWindow();
	virtual ~CWin32TestWindow();

	bool ShowWin32TestWindow(DWORD dwMainThreadId);
	void UnInitialized();

protected:
	// �ؼ����͸����ڵ���Ϣ�ӿ�
	virtual LRESULT OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam);
	// �����ڵ���Ϣ������
	virtual LRESULT WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam);
	// WM_CREATE���Ի����ʼ��	
	virtual void OnCreate();

	virtual void OnKeyDown(int nVirtKey, int nFlag);
	// WM_TIMER����ʱ��	
	virtual void OnTimer(UINT nTimerId);

private:
	void CloseTestWindow();

private:
	int m_nTimer;

	DWORD m_dwMainThreadId;
	ICtrlButton* m_pCloseButton;
	ICtrlLinkLable* m_pLinkTieba;
	ICtrlLinkLable* m_pLinkTengXun;
	ICtrlLinkLable* m_pLinkXinLang;
	ICtrlLinkLable* m_pLink360;

	ICtrlPanel* m_pAnimationPanel;
	ICtrlPanel* m_pUifeaturelogoPanel;
	ICtrlPanel* m_pWindowbkPanel;

	ICtrlButton* m_pGetDemoBtn;
};
