
#pragma once
#include "GlobalDef.h"

// ���໯��������
enum PWND_TYPE
{
	// �Ի���
	PWT_WND		= 1,
	// �˵�
	PWT_MENU,
	// �����б�����ʾѡ���
	PWT_DROP_WND,
};

class CWindowBase
{
public:
	CWindowBase(void);
	virtual ~CWindowBase(void);

	// ������Ϣ����
	virtual LRESULT WndProc(UINT message, WPARAM wParam, LPARAM lParam) = 0;

	// ���ô��ھ��
	void SetSafeHandle(HWND hWnd);
	// ȡ�ô��ھ��
	HWND GetSafeHandle();

	// �õ�������Ļ����
	CRect GetWindowRect();
	// �õ��ͻ������꣬[0,0]����ϵ
	CRect GetClientRect();
	// ���ݴ��ڵĳ��ȺͿ�ȣ��������Ƶ���Ļ����
	void CenterWindow(int cx = 0, int cy = 0);

	// ���ô��ڱ�������
	void SetWindowText(CString strText);

	// ���ö�ʱ��
	int SetTimer(UINT uElapse);
	// ȡ����ʱ��
	void KillTimer(int nId);

protected:
	static HINSTANCE ms_hInstance;

	// �����ھ��
	HWND m_hParent;
	// ��������
	DWORD m_dwWndStyle;
	// ���ھ��
	HWND m_hWnd;
	// ��������
	PWND_TYPE m_PuppetWndType;
	// ��������
	CString m_strWindowClass;
	// ���ڱ�������
	CString m_strWindowText;
	// ��ʱ��ID��
	int m_nTimerId;
};
