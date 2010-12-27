//////////////////////////////////////////////////////////////////////////
// DirectUi ���ڵĻ���

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

	// ��������
	virtual bool CreateWnd(CDirectUiDlg *pParentDlg, CDirectUiManager *pUiManager, CDirectUiWindowMsgCtrl *pMsgCtrl,
		CRect WndRect, int nWndId, WND_TYPE WndType, int nImageId = 0, CString strImagePath = _T(""), IMAGE_TYPE nImageType = IT_BMP);
	// �ƶ�����
	virtual void MoveWindow(CRect ToRect, HDWP hWinPoslnfo);
	// ���ô�����ʾ����
	virtual void SetVisable(bool bIsVisable, bool bRedraw = true);
	// ȡ�õ�ǰ���ڵ�λ��
	CRect GetWindowRect() { return m_WndRect; };
	// ȡ�ô�������
	WND_TYPE GetWindowType() { return m_WndType; };
	// ȡ�ô��ڵ�ǰ��ʾ����λ�ã���ֻ��һ������
	CRect GetWndTextRect();
	// ���ô��ڱ�����ɫ
	void SetWindowColor(const Color &BkColor) { m_BkColor = BkColor; };
	// ���ô���������Ϣ
	void SetTextFont(CString strFontName, int nFontHeight, FontStyle FStyle, Color nColor, StringFormat *pFormat = NULL);
	// ���ô���������ʾ����
	void SetTextRect(CRect TextRect);
	// ���ô�������
	void SetWindowText(CString strText) { m_WndTextInfo.strText = strText; };
	// ���ô���������ɫ
	void SetWindowTextColor(Color nColor) { m_WndTextInfo.TextColor = nColor; };
	// ���ô�����Ϣ
	void SetWindowMsg(LPARAM lParam) { m_MsgInfo.lParam = lParam; };
	// ����HOT����
	void SetHotWnd(bool bIsHot);
	// ȡ�ñ���ͼƬ
	CResImage *GetResImage() { return &m_BkgndImage; };
	// �������������ڴ���������
	void SetCenterText();
	// ���ñ���ͼƬ
	bool SetBkgndImage(int nImageId = 0, CString strImagePath = _T(""), IMAGE_TYPE nImageType = IT_BMP);

	// �����Ƿ��������ĳһ����Ϣ
	void SetAllowMsg(DWORD dwMsg, bool bIsAllow);
	// ȡ�ô���ID
	int GetWindowId() { return m_nWndId; };
	// ɾ������ͼƬ
	void DeleteBkgndImage();

	// �ػش���
	virtual void RedrawWindow(UINT flags = RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);

	// �����Ƿ���ʾ
	bool IsVisable() { return (m_dwWndAttr & DWP_VISABLE) != 0; };

protected:
	// �����Ƿ�ΪGIF����
	bool IsGifWnd() { return (m_WndType == DWT_GIF_STATIC); };
	// �����Ƿ����
	bool IsEnable() { return ((m_dwWndAttr & DWP_ENABLE) != 0); };
	// �����Ƿ�ΪHOT����
	bool IsHotWnd() { return (m_dwWndAttr & DWP_HOT_WND) != 0; };
	// �����Ƿ�����
	bool IsDestroy() { return (m_dwWndAttr & DWP_DESTROY) != 0; };
	// ����Ƿ�ͣ�ڵ�ǰ����
	bool IsMouseHover() { return (m_dwWndAttr & DWP_MOUSEHOVER) != 0; };
	// ����Ƿ��ڵ�ǰ���ڰ���
	bool IsMouseDown() { return (m_dwWndAttr & DWP_MOUSEDOWN) != 0; };
	// �����Ƿ�ȡ�ý���
	bool IsInFocus() { return (m_dwWndAttr & DWP_FOCUS) != 0; };
	// �����Ƿ�����˴��������ƶ���Ϣѭ��
	bool IsEnterSize() { return (m_dwWndAttr & DWP_ENTERSIZEMOVE) != 0; };
	// �����Ƿ�������갴����Ϣ
	bool AllowMouseDownMsg() { return (m_dwWndAttr & DWP_MSG_MOUSEDOWN) != 0; };
	// �����Ƿ��������˫����Ϣ
	bool AllowMouseDClickMsg() { return (m_dwWndAttr & DWP_MSG_MOUSEDCLICK) != 0; };
	// �����Ƿ���������ƶ���Ϣ
	bool AllowMouseMoveMsg() { return (m_dwWndAttr & DWP_MSG_MOUSEMOUSE) != 0; };
	// �����Ƿ�������л�ͼ����
	bool AllowPaintMsg() { return (m_dwWndAttr & DWP_MSG_PAINT) != 0; };

	virtual void OnPaintProc(Graphics *pDoGrap, HDC hMemoryDC);
	virtual bool OnLButtonDownProc(UINT nFlags, CPoint point);
	virtual bool OnLButtonUpProc(UINT nFlags, CPoint point);
	virtual bool OnLButtonDblClkProc(UINT nFlags, CPoint point);
	virtual bool OnMouseMoveProc(UINT nFlags, CPoint point);
	virtual void OnLoseFocusProc();
	virtual void OnSetFocusProc();
	// �˳����촰����Ϣѭ��
	virtual void OnExitSizeProc(WPARAM wParam, LPARAM lParam);
	// �������촰����Ϣѭ��
	virtual void OnEnterSizeProc(WPARAM wParam, LPARAM lParam);

protected:
/// �������Ӵ��ڿ��Լ̳д������Ϣ ///////////////////////////////////////////////////////////////////////
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

	// �����Ʊ��������򣬽������ڴӲü�����ɾ��
	void NotDrawWindow();

private:
	// �������Ƿ���
	static bool ms_bIsWndLButtonDown;
	// ���������µĴ���
	static CDirectUiWindow* ms_pLButtonDownWnd;
	// ����ID����4��ʼ��1-3Ϊϵͳ��ťID
	static int ms_nDefaultWndId;
	// ȡ�ý���Ĵ���
	static CDirectUiWindow* ms_pFocusWnd;

	static void UnloadDirectUiWindow()
	{
		ms_bIsWndLButtonDown = false;
		ms_pLButtonDownWnd = NULL;
		ms_nDefaultWndId = 4;
		ms_pFocusWnd = NULL;
	};

protected:
	// ��ͼ�õ�GDI+
	Graphics *m_pDoGrap;
	// ��ͼ�õ�GDI
	HDC m_hMemoryDC;
	// ��������
	DWORD m_dwWndAttr;
	// ʵ��ĸ�����
	HWND m_hParent;
	CDirectUiDlg *m_pParentDlg;
	// ��Ϣ������
	CDirectUiWindowMsgCtrl *m_pMsgCtrl;
	// �����ͼ����
	CDirectUiManager *m_pUiManager;
	// ����λ��
	CRect m_WndRect;
	// ����ID
	int m_nWndId;
	// ��������
	WND_TYPE m_WndType;
	// ���ڱ�����ɫ
	Color m_BkColor;
	// ���ڱ�����ͼƬ
	CResImage m_BkgndImage;
	// �������ֵ�����
	WND_TEXT m_WndTextInfo;
	// ���ڷ��͵���Ϣ��Ϣ
	DWM_INFO m_MsgInfo;
};
