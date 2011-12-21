//////////////////////////////////////////////////////////////////////////
// DirectUi 窗口的基类

#pragma once
#include "BaseDlgDefs.h"
#include "DirectUiDlg.h"
#include "DirectUiWindowMsgCtrl.h"
#include "ResImage.h"

class CDirectUiManager;

class CDirectUiWindow
{
	friend class CDirectUiManager;

public:
	CDirectUiWindow(void);
	virtual ~CDirectUiWindow(void);

	static inline bool IsWndLButtonDown() { return ms_bIsWndLButtonDown; };
	static inline int GetDefaultWndId() { return ms_nDefaultWndId++; };

	// 创建窗口
	virtual bool CreateWnd(CDirectUiDlg *pParentDlg, CDirectUiManager *pUiManager, CDirectUiWindowMsgCtrl *pMsgCtrl,
		CRect WndRect, int nWndId, WND_TYPE WndType, int nImageId = 0, CString strImagePath = _T(""), IMAGE_TYPE nImageType = IT_BMP);
	// 移动窗口
	virtual void MoveWindow(CRect ToRect, HDWP hWinPoslnfo);
	// 设置窗口显示属性
	virtual void SetVisable(bool bIsVisable, bool bRedraw = true);
	// 取得当前窗口的位置
	CRect GetWindowRect() { return m_WndRect; };
	// 取得窗口类型
	WND_TYPE GetWindowType() { return m_WndType; };
	// 取得窗口当前显示文字位置，限只有一行文字
	CRect GetWndTextRect();
	// 设置窗口背景颜色
	void SetWindowColor(const Color &BkColor) { m_BkColor = BkColor; };
	// 设置窗口文字信息
	void SetTextFont(CString strFontName, int nFontHeight, FontStyle FStyle, Color nColor, StringFormat *pFormat = NULL);
	// 设置窗口文字显示区域
	void SetTextRect(CRect TextRect);
	// 设置窗口文字
	void SetWindowText(CString strText) { m_WndTextInfo.strText = strText; };
	// 设置窗口文字颜色
	void SetWindowTextColor(Color nColor) { m_WndTextInfo.TextColor = nColor; };
	// 设置窗口消息
	void SetWindowMsg(LPARAM lParam) { m_MsgInfo.lParam = lParam; };
	// 设置HOT窗口
	void SetHotWnd(bool bIsHot);
	// 取得背景图片
	CResImage *GetResImage() { return &m_BkgndImage; };
	// 设置文字现在在窗口正中央
	void SetCenterText();
	// 设置背景图片
	bool SetBkgndImage(int nImageId = 0, CString strImagePath = _T(""), IMAGE_TYPE nImageType = IT_BMP);

	// 设置是否允许接收某一类消息
	void SetAllowMsg(DWORD dwMsg, bool bIsAllow);
	// 取得窗口ID
	int GetWindowId() { return m_nWndId; };
	// 删除背景图片
	void DeleteBkgndImage();

	// 重回窗口
	virtual void RedrawWindow(UINT flags = RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);

	// 窗口是否显示
	bool IsVisable() { return (m_dwWndAttr & DWP_VISABLE) != 0; };

protected:
	// 窗口是否为GIF窗口
	bool IsGifWnd() { return (m_WndType == DWT_GIF_STATIC); };
	// 窗口是否可用
	bool IsEnable() { return ((m_dwWndAttr & DWP_ENABLE) != 0); };
	// 窗口是否为HOT窗口
	bool IsHotWnd() { return (m_dwWndAttr & DWP_HOT_WND) != 0; };
	// 窗口是否销毁
	bool IsDestroy() { return (m_dwWndAttr & DWP_DESTROY) != 0; };
	// 鼠标是否停在当前窗口
	bool IsMouseHover() { return (m_dwWndAttr & DWP_MOUSEHOVER) != 0; };
	// 鼠标是否在当前窗口按下
	bool IsMouseDown() { return (m_dwWndAttr & DWP_MOUSEDOWN) != 0; };
	// 窗口是否取得焦点
	bool IsInFocus() { return (m_dwWndAttr & DWP_FOCUS) != 0; };
	// 窗口是否进入了窗口拉伸移动消息循环
	bool IsEnterSize() { return (m_dwWndAttr & DWP_ENTERSIZEMOVE) != 0; };
	// 窗口是否允许鼠标按下消息
	bool AllowMouseDownMsg() { return (m_dwWndAttr & DWP_MSG_MOUSEDOWN) != 0; };
	// 窗口是否允许鼠标双击消息
	bool AllowMouseDClickMsg() { return (m_dwWndAttr & DWP_MSG_MOUSEDCLICK) != 0; };
	// 窗口是否允许鼠标移动消息
	bool AllowMouseMoveMsg() { return (m_dwWndAttr & DWP_MSG_MOUSEMOUSE) != 0; };
	// 窗口是否允许进行绘图操作
	bool AllowPaintMsg() { return (m_dwWndAttr & DWP_MSG_PAINT) != 0; };

	virtual void OnPaintProc(Graphics *pDoGrap, HDC hMemoryDC);
	virtual bool OnLButtonDownProc(UINT nFlags, CPoint point);
	virtual bool OnLButtonUpProc(UINT nFlags, CPoint point);
	virtual bool OnLButtonDblClkProc(UINT nFlags, CPoint point);
	virtual bool OnMouseMoveProc(UINT nFlags, CPoint point);
	virtual void OnLoseFocusProc();
	virtual void OnSetFocusProc();
	// 退出拉伸窗口消息循环
	virtual void OnExitSizeProc(WPARAM wParam, LPARAM lParam);
	// 进入拉伸窗口消息循环
	virtual void OnEnterSizeProc(WPARAM wParam, LPARAM lParam);

protected:
/// 以下是子窗口可以继承处理的消息 ///////////////////////////////////////////////////////////////////////
	virtual void OnDestroy();
	virtual void OnPaint() {};
	virtual void OnLButtonDown(CPoint point) {};
	virtual void OnLButtonUp(CPoint point) {};
	virtual void OnLButtonDblClk(CPoint point) {};
	virtual void OnMouseMove(CPoint point) {};
	virtual void OnMouseHover(CPoint point) {};
	virtual void OnMouseLeave(CPoint point) {};
	virtual void OnLoseFocus() {};
	virtual void OnSetFocus() {};
	virtual void OnExitSize() {};
	virtual void OnEnterSize() {};
	virtual void OnTimer(int nTimerId) {};
	virtual void OnActivateApp(WPARAM wParam, LPARAM lParam) {};
//////////////////////////////////////////////////////////////////////////

	virtual bool IsReady();
	virtual void SetDefaultFont();

	static inline bool IsThisWndDown(CDirectUiWindow* pWnd) { return (CDirectUiWindow::ms_pLButtonDownWnd == pWnd); };
	static inline bool IsThisWndGetFocus(CDirectUiWindow* pWnd) { return (CDirectUiWindow::ms_pFocusWnd == pWnd); };
	static inline void SetLButtonDown(CDirectUiWindow* pWnd)
	{
		if (CDirectUiWindow::ms_pFocusWnd != NULL)
			CDirectUiWindow::ms_pFocusWnd->OnLoseFocusProc();

		CDirectUiWindow::ms_bIsWndLButtonDown = true;
		CDirectUiWindow::ms_pLButtonDownWnd = pWnd;
		CDirectUiWindow::ms_pFocusWnd = pWnd;

		if (CDirectUiWindow::ms_pFocusWnd != NULL)
			CDirectUiWindow::ms_pFocusWnd->OnSetFocusProc();
	};

	static inline void SetLButtonUp()
	{
		CDirectUiWindow::ms_bIsWndLButtonDown = false;
		CDirectUiWindow::ms_pLButtonDownWnd = NULL;
	};

	// 不绘制本窗口区域，将本窗口从裁剪区中删除
	void NotDrawWindow();

private:
	// 鼠标左键是否按下
	static bool ms_bIsWndLButtonDown;
	// 鼠标左键按下的窗口
	static CDirectUiWindow* ms_pLButtonDownWnd;
	// 窗口ID，从4开始，1-3为系统按钮ID
	static int ms_nDefaultWndId;
	// 取得焦点的窗口
	static CDirectUiWindow* ms_pFocusWnd;

	static void UnloadDirectUiWindow()
	{
		ms_bIsWndLButtonDown = false;
		ms_pLButtonDownWnd = NULL;
		ms_nDefaultWndId = 4;
		ms_pFocusWnd = NULL;
	};

protected:
	// 绘图用的GDI+
	Graphics *m_pDoGrap;
	// 绘图用的GDI
	HDC m_hMemoryDC;
	// 窗口属性
	DWORD m_dwWndAttr;
	// 实体的父窗口
	HWND m_hParent;
	CDirectUiDlg *m_pParentDlg;
	// 消息处理类
	CDirectUiWindowMsgCtrl *m_pMsgCtrl;
	// 界面绘图管理
	CDirectUiManager *m_pUiManager;
	// 窗口位置
	CRect m_WndRect;
	// 窗口ID
	int m_nWndId;
	// 窗口类型
	WND_TYPE m_WndType;
	// 窗口背景颜色
	Color m_BkColor;
	// 窗口背景的图片
	CResImage m_BkgndImage;
	// 窗口文字的字体
	WND_TEXT m_WndTextInfo;
	// 窗口发送的消息信息
	DWM_INFO m_MsgInfo;
};
