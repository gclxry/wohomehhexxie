
#pragma once
#include "FetionSFDefs.h"
#include "WindowBase.h"

#pragma warning(disable:4800)


//////// DirectUiDlg �������� //////////////////////////////////////////////////////////////
// �Ƿ�����С����ť
#define BFS_HAVE_MIN_BTN								(0x00000001)
// �Ƿ�����󻯰�ť
#define BFS_HAVE_MAX_BTN								(0x00000002)
// �Ƿ�Ϊ���
#define BFS_MAX_WND										(0x00000004)
// ����Ƿ��һ�ν��봰��
#define BFS_FIRST_IN_WND								(0x00000008)
// �Ƿ�֧������߿����
#define BFS_CAN_DRAW									(0x00000010)
// ģʽ�Ի���
#define BFS_MODAL_DLG									(0x00000020)
//////////////////////////////////////////////////////////////////////////////////////////////

// ��Ϣ�������໯
LRESULT CALLBACK PuppetWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

class CDirectUiDlg : public CWindowBase
{
public:
	CDirectUiDlg(HINSTANCE hInstance, HWND hParentWnd, int nIconId);
	~CDirectUiDlg(void);

	// ��Ϣ����
	virtual LRESULT WndProc(UINT message, WPARAM wParam, LPARAM lParam);

	// ģʽ�Ի������ʵ��ʽ
	int DoModal();

	// ��ģʽ��ʾ�Ի���
	void ShowWindow();

	// �Ի����������ú��ж�
	bool IsSetBfStyle(DWORD dwStyle) { return (m_dwWndStyle & dwStyle); };
	void AddBfStyle(DWORD dwStyle) { m_dwWndStyle |= dwStyle; };
	void DeleteBfStyle(DWORD dwStyle) { m_dwWndStyle &= (~dwStyle); };

	// ���ö��ᴰ��״̬������״̬�£�����Ӧ����ƶ���Ϣ��
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
	// �û�ǿ���˳�
	bool m_bCoerceEnd;
	// ����ͼ��ID
	int m_nIconId;
	// �Ƿ񶳽ᴰ��
	bool m_bIsFreeze;
};
