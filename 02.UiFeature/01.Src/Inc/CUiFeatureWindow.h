// ˵����UiFeature�ĸ����ܻ����Ի���

#pragma once
#include <Windows.h>
#include "IWindowBase.h"
#include "IControlBase.h"
#include "IUiFeatureKernel.h"
#include "CWin32Window.h"

class CUiFeatureWindow : public CWin32Window, public IControlMessage
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
	bool CreateFeatureWindow(char* pszKernelDllPath, char* pszSkinPath, char *pszSkinWndName, HWND hParent, RECT WndRect, int nShow, int nStyle = WS_OVERLAPPED | WS_THICKFRAME, LPARAM lParam = NULL, bool bNewUiThread = true);
	// �����ڵ���Ϣ������
	virtual LRESULT WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam);
	// ȡ��
	IWindowBase* GetUiFeatureWindow();
	// ���ô��ڱ�������
	void SetWindowText(char* pstrWndText);
	// ��ʼ���Ի������
	virtual void OnInitWindowEnd(int nErrorCode);

	// �ؼ����͸����ڵ���Ϣ�ӿ�
	virtual LRESULT OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam);

	virtual bool CreateWindowWithNewThread(HWND hParent, RECT WndRect, char *pszWndText, int nShow, int nStyle = WS_OVERLAPPED | WS_THICKFRAME, LPARAM lParam = NULL);
	virtual bool CreateWindowWithoutThread(HWND hParent, RECT WndRect, char *pszWndText, int nShow, int nStyle = WS_OVERLAPPED | WS_THICKFRAME, LPARAM lParam = NULL);

protected:
	virtual bool InitInstance();

protected:
	HMODULE m_hKernelDll;
	IUiFeatureKernel *m_pUiFeatureKernel;
	// UiFeature����ĶԻ�����Դָ��
	IWindowBase* m_pWindowBase;
	string m_strKernelDllPath;
	string m_strSkinPath;
	string m_strSkinWndName;
};
