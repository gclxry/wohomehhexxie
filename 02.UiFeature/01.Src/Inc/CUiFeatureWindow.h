// ˵����UiFeature�ĸ����ܻ����Ի���

#pragma once
#include <Windows.h>
#include "IWindowBase.h"
#include "IControlBase.h"
#include "IUiFeatureKernel.h"

class CUiFeatureWindow : public IControlMessage
{
public:
	CUiFeatureWindow();
	virtual ~CUiFeatureWindow();

	// ����һ�����ڣ�������
	// char* pszDllDir��UiFeatureKernel.dll��ȫ·��
	// char* pszSkinPath��*.ufdƤ���ļ���ȫ·��
	// char *pszWndName��*.ufdƤ���ļ��жԻ��������
	// HWND hParent��������
	// RECT WndRect��������ʾλ�ã�����Ϊ��Ļλ��
	// int nShow����ʾģʽ���磺SW_SHOW��SW_HIDE
	// LPARAM lParam����������ʱ����Ĳ���������ͨ�� GetCreateWindowParam ����ȡ��
	bool CreateFeatureWindow(char* pszKernelDllPath, char* pszSkinPath, char *pszSkinWndName, HWND hParent, RECT WndRect, int nShow, LPARAM lParam);

	// �ؼ����͸����ڵ���Ϣ�ӿ�
	virtual LRESULT OnCtrlMessage(IControlBase* pCtrl, WPARAM wParam, LPARAM lParam);
	// �����ڵ���Ϣ������
	virtual LRESULT WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam);

	// ȡ�ô��ھ��
	HWND GetSafeHandle();
	// �õ�������Ļ����
	RECT GetWindowRect();
	// �õ��ͻ������꣬[0,0]����ϵ
	RECT GetClientRect();
	// ȡ��
	IWindowBase* GetUiFeatureWindow();
	// ȡ�ô��ڱ�������
	const char* GetWindowText();
	// ���ô��ڱ�������
	void SetWindowText(char* pstrWndText);
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
	// ���ٴ��ڣ�ͬʱ���ٴ����̣߳�������������ڴ˴�������̵߳���
	// ����ڱ����ڵ��߳��е��ã�����������
	void CloseWindow();
	// �����ڲ���Ҫ�رմ��ڣ����ô˺���
	void CloseSelf();
	// ���ô���֧��͸��ģʽ
	void SetWindowTransparence(bool bIsTrans);
	// ȡ�ô����Ի���Ĳ���
	LPARAM GetCreateWindowParam();
	// ȡ�ô�����ָ�����ƵĿؼ�
	IControlBase* GetCtrlObject(char* pstrCtrlName);
	// �����Ƿ�����
	bool IsWindowEnd();
	// �����߳��Ƿ�����
	bool IsWindowThreadEnd();
	// ��ʼ���Ի������
	virtual void OnInitWindowError(int nErrorCode);
	// ��ʼ���Ի���ɹ�
	virtual void OnInitWindowSuccess();

protected:
	// ����Windows��Ϣ���������أ�����Ҫ���ø����ԭ���� /////////////////////////////////////////////////////
	// �����Ҫ���ص���Ϣ�����������к����У�����ϵ��ؿ�����Ա //////////////////////////////////////////////
	virtual void OnKeyDown(int nVirtKey, int nFlag);
	// ϵͳ��Ϣ������true˵������Ҫ���ظ�ϵͳ�������ã�ֱ�ӷ���
	virtual bool OnSysCommand(WPARAM wParam, LPARAM lParam);
	// WM_CREATE���Ի����ʼ��	
	virtual void OnCreate();
	// �Ի����ʼ����ϵ���
	virtual void OnCreateEnd();
	// WM_TIMER����ʱ��	
	virtual void OnTimer(UINT nTimerId);
	// WM_DESTROY�����ٴ���
	virtual void OnDestroy();
	virtual void OnKillFocus();
	virtual void OnSetFocus();
	// ����MFC��PreTranslateMessage��������ص���true�����ټ��������ɷ���Ϣ
	virtual bool PreTranslateMessage(MSG msg);

private:
	// ���ô����Ի���Ĳ���
	void SetCreateWindowParam(LPARAM lParam);
	// ����һ����ͨ���ڣ�û�о����ں˹���
	bool CreateWin32Window(HWND hParent, RECT WndRect, char *pszWndText, int nShow, LPARAM lParam);
	// Win32 �Ի���ע�ᴴ������
	ATOM RegisterClass();
	bool InitInstance();

//////////////////////////////////////////////////////////////////////////
	// ���º���ԭ���ϲ������ⲿ������ã�ֻ�ṩ���ڲ�ʹ��
public:
	// ���ô��ھ��
	void SetSafeHandle(HWND hWnd);
	void _BeginWindowThread();
	void _PostEndThread();
	void WaitWindowThreadEnd();

protected:
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

//////////////////////////////////////////////////////////////////////////
	HMODULE m_hKernelDll;
	IUiFeatureKernel *m_pUiFeatureKernel;
	// UiFeature����ĶԻ�����Դָ��
	IWindowBase* m_pWindowBase;
	string m_strKernelDllPath;
	string m_strSkinPath;
	string m_strSkinWndName;
};
