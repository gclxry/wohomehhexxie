
#pragma once
#include "..\..\Inc\CUiFeatureWindow.h"

class ICtrlSearchBarImpl;
class CSearchPanel : public CUiFeatureWindow
{
public:
	CSearchPanel();
	virtual ~CSearchPanel();

	virtual void ShowPanel(bool bIsShow);

	// �ؼ����͸����ڵ���Ϣ�ӿ�
	virtual LRESULT OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam);

	virtual bool CreateFeatureWindow(char* pszKernelDllPath, char* pszSkinPath, char *pszSkinWndName, HWND hParent, RECT WndRect, int nShow, int nStyle = WS_OVERLAPPED | WS_THICKFRAME, LPARAM lParam = NULL, bool bNewUiThread = true);

	// ����һ�����ڣ�������
	// IUiFeatureKernel* pUiKernel��Kernelָ��
	// char *pszWndName��*.ufdƤ���ļ��жԻ��������
	// HWND hParent��������
	// RECT WndRect��������ʾλ�ã�����Ϊ��Ļλ��
	// int nShow����ʾģʽ���磺SW_SHOW��SW_HIDE
	// LPARAM lParam����������ʱ����Ĳ���������ͨ�� GetCreateWindowParam ����ȡ��
	virtual bool CreatePanel(ICtrlSearchBarImpl *pSearchBar, IUiFeatureKernel* pUiKernel, char *pszSkinWndName, HWND hParent, RECT WndRect, int nShow, int nStyle = WS_OVERLAPPED | WS_THICKFRAME, LPARAM lParam = NULL, bool bNewUiThread = false);

	virtual void OnSetFocus();
	virtual void OnKillFocus();

private:
	bool m_bIsShow;
	ICtrlSearchBarImpl* m_pSearchBar;
};
