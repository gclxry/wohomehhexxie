
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
	virtual void BD_DrawWindowView(CDrawingBoard &ViewMemDc) = 0;
	// �õ���Builder����ʾ������8�������λ��
	virtual FANGKUAI_8* BD_GetFangKuai8Rect() = 0;
	// ȡ�õ�ǰ����λ�õĿؼ�
	virtual IControlBase *BD_GetMouseInControl(POINT pt) = 0;
	// ȡ�õ�ǰ����Ŀؼ�
	virtual IControlBase *BD_GetFocusControl() = 0;
	// ���õ�ǰ����Ŀؼ�
	virtual void BD_SetFocusControl(IControlBase* pControl) = 0;
	// ���ÿؼ��ڱ༭ģʽ�µ�λ�úʹ�С
	virtual void BD_SetControlRect(IControlBase* pControl, RECT RctInView) = 0;
	// ��ʼ�����пؼ���Builder�е���ʾλ��
	virtual void BD_SetAllCtrlRectInView() = 0;
	// ����ָ���ؼ���Builder�е���ʾλ��
	virtual void BD_SetControlRectInView(CHILD_CTRLS_VEC *pChildCtrlsVec) = 0;
	virtual void BD_OnTimer(UINT nTimerId, HWND hView) = 0;
	// ���¼����ӿؼ���λ�úʹ�С
	virtual void ResetChildCtrlPostion(CHILD_CTRLS_VEC* pChildVec, bool bMemToProp = false) = 0;
	// �Ƿ�Ϊ���ģʽ
	virtual bool IsDesignMode() = 0;
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

	// ���ݿؼ�������Ϣ���ÿؼ���λ��
	virtual void SetControlWindowPostion(IControlBase* pCtrl, RECT ParentRctInWnd) = 0;
//////////////////////////////////////////////////////////////////////////
	// ȡ�ô��ڿؼ�ָ��
	virtual IControlBase* GetControl(char *pszCtrlName) = 0;
	// �����δ����һ���ؼ�
	virtual void AppendChildContrl(IControlBase *pCtrl) = 0;
	// ȡ���ӿؼ��б�
	virtual CHILD_CTRLS_VEC* GetChildControlsVec() = 0;
	// ȡ���ӿؼ��������б�Layout.xml �еĲ���
	virtual PROP_CONTROL_VEC* GetChildPropControlVec() = 0;

	virtual void InvalidateRect(RECT *lpRect) = 0;
	virtual void UpdateWindow() = 0;
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
	virtual IPropertyGroup *PP_GetWindowPropetryGroup() = 0;
	virtual IPropertyWindow *PP_GetWindowPropetry() = 0;

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

	// ȡ�ô������������ԵĴ��ڴ�С
	virtual SIZE PP_GetWindowPropSize() = 0;

};
