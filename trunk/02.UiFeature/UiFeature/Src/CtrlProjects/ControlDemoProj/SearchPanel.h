
#pragma once
#include "..\..\Inc\CUiFeatureWindow.h"

class ICtrlSearchBarImpl;
class CSearchPanel : public CUiFeatureWindow
{
public:
	CSearchPanel();
	virtual ~CSearchPanel();

	virtual void ShowPanel(bool bIsShow);

	// 控件发送给窗口的消息接口
	virtual LRESULT OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam);

	virtual bool CreateFeatureWindow(char* pszKernelDllPath, char* pszSkinPath, char *pszSkinWndName, HWND hParent, RECT WndRect, int nShow, int nStyle = WS_OVERLAPPED | WS_THICKFRAME, LPARAM lParam = NULL, bool bNewUiThread = true);

	// 创建一个窗口，参数：
	// IUiFeatureKernel* pUiKernel：Kernel指针
	// char *pszWndName：*.ufd皮肤文件中对话框的名字
	// HWND hParent：父窗口
	// RECT WndRect：窗口显示位置，坐标为屏幕位置
	// int nShow：显示模式，如：SW_SHOW、SW_HIDE
	// LPARAM lParam：创建窗口时传入的参数，可以通过 GetCreateWindowParam 函数取得
	virtual bool CreatePanel(ICtrlSearchBarImpl *pSearchBar, IUiFeatureKernel* pUiKernel, char *pszSkinWndName, HWND hParent, RECT WndRect, int nShow, int nStyle = WS_OVERLAPPED | WS_THICKFRAME, LPARAM lParam = NULL, bool bNewUiThread = false);

	virtual void OnSetFocus();
	virtual void OnKillFocus();

private:
	bool m_bIsShow;
	ICtrlSearchBarImpl* m_pSearchBar;
};
