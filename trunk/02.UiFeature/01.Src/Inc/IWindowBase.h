
#pragma once
#include "IControlBase.h"
#include "IFeatureObject.h"
#include "IPropertyWindow.h"

class IWindowBase : public IFeatureObject
{
public:
//////////////////////////////////////////////////////////////////////////
// Builder ʹ�õĺ���
	virtual void BD_InitWindowBase(IPropertyWindow *pWindowProp, bool bSetDftProp) = 0;

//////////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////////
	// ȡ�ô��ڿؼ�ָ��
	virtual IControlBase* GetControl(char *pszCtrlName) = 0;
	// �����δ����һ���ؼ�
	virtual void AppendChildContrl(IControlBase *pCtrl) = 0;

public:
////// ���º������ⲿ���ڵ��� //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ���ⲿ���ڵ��ã���ʼ�����໯����
	virtual void PG_InitWindowBase(HWND hWnd, char *pszSkinPath, char *pszWndName) = 0;
	// ���ⲿ���ڵ��ã������ڵ���Ϣ��������bPassOn����Ϊtrue�ǣ���Ϣ��������ݴ���falseʱ��������ϣ������´�
	virtual LRESULT WindowProc(UINT nMsgId, WPARAM wParam, LPARAM lParam, bool &bPassOn) = 0;



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// �����������
	// �Ƿ�֧��ȫ���ڵ���ƶ�
	virtual void PP_SetDragWindow(bool bDrag) = 0;
	virtual bool PP_GetDragWindow() = 0;

	// �Ƿ����
	virtual void PP_SetCanFullScreen(bool bCanFull) = 0;
	virtual bool PP_IsCanFullScreen() = 0;
	virtual void PP_SetFullScreen(bool bFull) = 0;
	virtual bool PP_IsFullScreen() = 0;

	// ����Object����
	virtual void PP_SetWindowObjectName(char *pszWndName) = 0;
	virtual const char * PP_GetWindowObjectName() = 0;

	// ��������
	virtual void PP_SetWindowText(char *pszWndName) = 0;
	virtual const char * PP_GetWindowText() = 0;

	virtual IPropertyGroup *PP_GetWindowPropetryGroup() = 0;

};
