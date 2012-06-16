#pragma once
#include "..\..\Inc\CUiFeatureWindow.h"
#include "..\..\Inc\Control\ICtrlPanel.h"

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


private:
	DWORD m_dwMainThreadId;
	ICtrlPanel* m_pAnimationPanel_1;
	ICtrlPanel* m_pAnimationPanel_11;
	ICtrlPanel* m_pAnimationPanel_GIFShow2;
	ICtrlPanel* m_pAnimationPanel_GIFShow3;
};
