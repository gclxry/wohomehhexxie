
#pragma once
#include "FetionSFDefs.h"
#include "WindowBase.h"

#pragma warning(disable:4800)


//////// DirectUiDlg 窗口属性 //////////////////////////////////////////////////////////////
// 是否有最小化按钮
#define BFS_HAVE_MIN_BTN								(0x00000001)
// 是否有最大化按钮
#define BFS_HAVE_MAX_BTN								(0x00000002)
// 是否为最大化
#define BFS_MAX_WND										(0x00000004)
// 鼠标是否第一次进入窗口
#define BFS_FIRST_IN_WND								(0x00000008)
// 是否支持拉伸边框操作
#define BFS_CAN_DRAW									(0x00000010)
// 模式对话框
#define BFS_MODAL_DLG									(0x00000020)
//////////////////////////////////////////////////////////////////////////////////////////////

// 消息处理子类化
LRESULT CALLBACK PuppetWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

class CDirectUiDlg : public CWindowBase
{
public:
	CDirectUiDlg(HINSTANCE hInstance, HWND hParentWnd, int nIconId);
	~CDirectUiDlg(void);

	// 消息处理
	virtual LRESULT WndProc(UINT message, WPARAM wParam, LPARAM lParam);

	// 模式对话框的现实方式
	int DoModal();

	// 非模式显示对话框
	void ShowWindow();

	// 对话框属性设置和判断
	bool IsSetBfStyle(DWORD dwStyle) { return (m_dwWndStyle & dwStyle); };
	void AddBfStyle(DWORD dwStyle) { m_dwWndStyle |= dwStyle; };
	void DeleteBfStyle(DWORD dwStyle) { m_dwWndStyle &= (~dwStyle); };

	// 设置冻结窗口状态，冻结状态下，不响应鼠标移动消息。
	void SetFreezeDlg(bool bIsFreeze) { m_bIsFreeze = bIsFreeze; };

protected:
	virtual void OnPaint(HDC hPaintDc) {};
	virtual void OnDestroy() {};
	virtual void OnCreate() {};
	virtual LRESULT OnNcActive(UINT message, WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnNcCalcSize(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnKillFocus(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnEraseBkgnd(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnNcPaint(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMouseMove(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnLButtonDown(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnLButtonUp(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnLButtonDblClk(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnNcHitTest(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnEnterSizeMove(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnExitSizeMove(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMove(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnTimer(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnActivateApp(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnSizeProc(WPARAM wParam, LPARAM lParam);

	virtual void RedrawDlg();

protected:
	bool CreateDlg();
	ATOM RegisterBfoClass();
	bool InitInstance();
	void EndThisDialog();

protected:
	// 用户强制退出
	bool m_bCoerceEnd;
	// 窗口图标ID
	int m_nIconId;
	// 是否冻结窗口
	bool m_bIsFreeze;
};
