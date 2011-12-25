
#pragma once
#include "..\..\Inc\IControlBase.h"
#include "..\..\Inc\IPropertyWindowManager.h"

class IWindowBase
{
public:
	// ���ھ�����ʾ
	virtual void CenterWindow() = 0;
	// ȡ�ô��ھ��
	virtual HWND GetSafeHandle() = 0;
	// �õ�������Ļ����
	virtual RECT GetWindowRect() = 0;
	// �õ��ͻ������꣬[0,0]����ϵ
	virtual RECT GetClientRect() = 0;
	// �ػ�ؼ�
	virtual void RedrawControl(IControlBase* pCtrl, bool bDrawImmediately = true) = 0;
	// ��������
	virtual IPropertyWindowManager* GetWindowProp() = 0;
	// ȡ�ô��ڿؼ�ָ��
	virtual IControlBase* GetControl(char *pszCtrlName) = 0;


public:
////// ���º������ⲿ���ڵ��� //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���ⲿ���ڵ��ã���ʼ�����໯����
	virtual void InitWindowBase(HWND hWnd, char *pszSkinPath, char *pszWndName) = 0;
	// ���ⲿ���ڵ��ã������ڵ���Ϣ��������bPassOn����Ϊtrue�ǣ���Ϣ��������ݴ���falseʱ��������ϣ������´�
	virtual LRESULT WindowProc(UINT nMsgId, WPARAM wParam, LPARAM lParam, bool &bPassOn) = 0;
};
