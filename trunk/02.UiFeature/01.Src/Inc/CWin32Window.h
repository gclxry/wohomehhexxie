// ˵����Win32�Ļ����Ի���

#pragma once
#include <Windows.h>

#define FEATURE_CLASS_NAME						"Win32Window"

class CWin32Window
{
public:
	CWin32Window();
	virtual ~CWin32Window();

	// ����һ�����ڣ�������
	// HWND hParent��������
	// RECT WndRect��������ʾλ�ã�����Ϊ��Ļλ��
	// char *pszWndText�����ڱ���
	// int nShow����ʾģʽ���磺SW_SHOW��SW_HIDE
	// LPARAM lParam����������ʱ����Ĳ���������ͨ�� GetCreateWindowParam ����ȡ��
	virtual bool CreateWindowWithNewThread(HWND hParent, RECT WndRect, char *pszWndText, int nShow, LPARAM lParam);
	virtual bool CreateWindowWithoutThread(HWND hParent, RECT WndRect, char *pszWndText, int nShow, LPARAM lParam);

	// �����ڵ���Ϣ������
	virtual LRESULT WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam);

	// ȡ�ô��ڱ�������
	const char* GetWindowText();
	// ���ô��ڱ�������
	void SetWindowText(char* pstrWndText);
	// ȡ�ô��ھ��
	HWND GetSafeHandle();
	// �õ�������Ļ����
	RECT GetWindowRect();
	// �õ��ͻ������꣬[0,0]����ϵ
	RECT GetClientRect();
	// ͬAPI�� IsWindow
	bool IsWindow();
	// �������Ƶ���Ļ����
	void CenterWindow();
	// ���ö�ʱ��
	void SetTimer(int nId, UINT uElapse);
	// ȡ����ʱ��
	void KillTimer(int nId);
	// ���öԻ���λ��
	void MoveWindow(RECT MoveRect, BOOL bRepaint = TRUE);
	// ��ʾ/���ش��ڣ�����ΪSW_SHOW֮��
	void ShowWindow(int nShow);
	// �����ػ�����
	void InvalidateRect(RECT *pInvRect);
	// ���´��ڣ��������л���
	void UpdateWindow();
	// �����ػ洰��
	void RedrawWindow(RECT *pDrawRect = NULL);
	// ������Ϣ:Send��ʽ
	LRESULT SendMessage(UINT nMsgId, WPARAM wParam, LPARAM lParam);
	// ������Ϣ:Post��ʽ
	bool PostMessage(UINT nMsgId, WPARAM wParam, LPARAM lParam);
	// ���ô���֧��͸��ģʽ
	void SetWindowTransparence(bool bIsTrans);
	// ȡ�ô����Ի���Ĳ���
	LPARAM GetCreateWindowParam();
	// �����Ƿ�����
	bool IsWindowEnd();
	// �����߳��Ƿ�����
	bool IsWindowThreadEnd();
	// ���ٴ��ڣ�true���ȴ�������ɣ�false�����ȴ��������
	// ����ڱ����ڵ��߳��е��ã�true����������
	void CloseWindow(bool bIsWaitEnd = true);

	// ȡ�����湤�������С
	RECT GetWorkAreaRect();

protected:
	// ����Windows��Ϣ���������أ�����Ҫ���ø����ԭ���� /////////////////////////////////////////////////////
	// �����Ҫ���ص���Ϣ�����������к����У�����ϵ��ؿ�����Ա //////////////////////////////////////////////
	virtual void OnKeyDown(int nVirtKey, int nFlag);
	// ϵͳ��Ϣ������true˵������Ҫ���ظ�ϵͳ�������ã�ֱ�ӷ���
	virtual bool OnSysCommand(WPARAM wParam, LPARAM lParam);
	virtual void OnCreate();
	// WM_TIMER����ʱ��	
	virtual void OnTimer(UINT nTimerId);
	// WM_DESTROY�����ٴ���
	virtual void OnDestroy();
	virtual void OnKillFocus();
	virtual void OnSetFocus();
	virtual void OnSize(UINT nType, int cx, int cy);
	// ����MFC��PreTranslateMessage��������ص���true�����ټ��������ɷ���Ϣ
	virtual bool PreTranslateMessage(MSG msg);

	// ���ô����Ի���Ĳ���
	void SetCreateWindowParam(LPARAM lParam);

	// Win32 �Ի���ע�ᴴ������
	ATOM RegisterClass();
	virtual bool InitInstance();

	// �������������������ڰ�ť
	void HideInTaskbar();
//////////////////////////////////////////////////////////////////////////
	// ���º���ԭ���ϲ������ⲿ������ã�ֻ�ṩ���ڲ�ʹ��

public:
	// ���ô��ھ��
	void SetSafeHandle(HWND hWnd);
	void _BeginWindowThread();
	void _PostEndThread();
	void WaitWindowThreadEnd();

protected:
	bool m_bIsCreateWithThread;
	// ���ھ��
	HWND m_hWnd;
	// ���ڱ�������
	string m_strWndText;
	// �����ھ��
	HWND m_hParentWnd;
	// �����Ի���Ĳ������������ͨ��������������
	LPARAM m_lParam;

	HANDLE m_hCreateWaitEvent;
	HANDLE m_hUiThread;
	DWORD m_dwUiThreadId;
	RECT m_rctCreate;
	int m_nCreateShow;
};
