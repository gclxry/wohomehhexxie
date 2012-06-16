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
	// 控件发送给窗口的消息接口
	virtual LRESULT OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam);
	// 本窗口的消息处理函数
	virtual LRESULT WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam);
	// WM_CREATE：对话框初始化	
	virtual void OnCreate();

	virtual void OnKeyDown(int nVirtKey, int nFlag);


private:
	DWORD m_dwMainThreadId;
	ICtrlPanel* m_pAnimationPanel_1;
	ICtrlPanel* m_pAnimationPanel_11;
	ICtrlPanel* m_pAnimationPanel_GIFShow2;
	ICtrlPanel* m_pAnimationPanel_GIFShow3;
};
