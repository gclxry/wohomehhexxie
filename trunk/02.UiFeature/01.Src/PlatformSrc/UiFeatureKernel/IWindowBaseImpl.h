
#pragma once
#include "..\..\Inc\IWindowBase.h"
#include "..\..\Inc\CMemoryDC.h"
#include "..\..\Inc\IPropertyWindow.h"

class IWindowBaseImpl : public IWindowBase
{
public:
	IWindowBaseImpl();
	virtual ~IWindowBaseImpl();

	// ��ʼ��
	virtual void InitWindowBase(HWND hWnd, char *pszSkinPath, char *pszWndName);
	// ���ھ�����ʾ
	virtual void CenterWindow();
	// ȡ�ô��ھ��
	virtual HWND GetSafeHandle();
	// �õ�������Ļ����
	virtual RECT GetWindowRect();
	// �õ��ͻ������꣬[0,0]����ϵ
	virtual RECT GetClientRect();
	// �ػ�ؼ�
	virtual void RedrawControl(IControlBase* pCtrl, bool bDrawImmediately = true);
	// ��������
	virtual IPropertyWindow* GetWindowProp();
	// ȡ�ô��ڿؼ�ָ��
	virtual IControlBase* GetControl(char *pszCtrlName);

protected:
	// ���ô����͸�����ԡ����ô����Ƿ�֧�ֲַ�
	void SetLayeredWindow(bool bIsLayered);

protected:
	// �����ڵ���Ϣ��������bPassOn����Ϊtrue�ǣ���Ϣ��������ݴ���falseʱ��������ϣ������´�
	virtual LRESULT WindowProc(UINT nMsgId, WPARAM wParam, LPARAM lParam, bool &bPassOn);

	virtual void OnCreate();
	virtual void OnTimer(UINT nTimerId);
	virtual void OnKeyDown(int nVirtKey, int nFlag);
	// ϵͳ��Ϣ������TRUE˵������Ҫ���ظ����ü�������
	virtual bool OnSysCommand(int nSysCommand, int xPos, int yPos);
	virtual void OnKillFocus(WPARAM wParam, LPARAM lParam);
	virtual void OnSetFocus(WPARAM wParam, LPARAM lParam);
	virtual void OnDestroy();
	virtual void OnSize(UINT nType, int cx, int cy);
	virtual void OnSizing(UINT nSide, LPRECT lpRect);
	// WM_ENTERSIZEMOVE�������ƶ������촰�ڲ���
	virtual void OnEnterSizeMove();
	// WM_EXITSIZEMOVE���˳��ƶ������촰�ڲ���
	virtual void OnExitSizeMove();
	virtual void OnPaint(HDC hWndDc);
	// �Ի������˵����������Ҽ��˵������Ͻǲ˵��Ľػ�
	virtual void OnPopupSystemMenu(POINT pt);

	virtual void OnMouseMove(int nVirtKey, POINT pt);
	virtual void OnLButtonDown(int nVirtKey, POINT pt);
	virtual void OnLButtonUp(int nVirtKey, POINT pt);
	virtual void OnLButtonDbClick(int nVirtKey, POINT pt);
	virtual void OnRButtonDown(int nVirtKey, POINT pt);

private:
	// �ڲ����ܵ���ʼ����Ϣ����ʼ��ʼ�����ڣ�����Ƥ��
	void OnInitWindowBase();

private:
	// ѭ������ÿ���ؼ��Ļ���
	void DrawControl();
	void RedrawWindow(RECT* pDrawRct = NULL);
	// ��ʼ���Ƿ����
	bool IsInit();
	// �����ڵ����Է����仯ʱ��Ҫ֪ͨ���ڽ���ˢ��ʱ����
	void RefreshWindowStyle();
	// ȡ�õ�ǰ��������������ĸ��ؼ���
	bool CheckMouseInControl(CHILD_CTRLS_VEC *pCtrlVec, POINT pt, IControlBase **ppControl);
	// ���ô��������пؼ���λ�úʹ�С
	void SetControlPostion(CHILD_CTRLS_VEC *pCtrlVec, SIZE NewSize);
	// ���ݿؼ�������Ϣ�õ��ؼ���λ��
	void SetControlWindowPostion(IControlBase* pCtrl, RECT ParentRctInWnd);
	// ���õ�ǰ�õ�����Ŀؼ����������ΪNULL��˵����ǰû�пؼ��õ����㣬���пؼ���ʧȥ����
	void SetFocusCtrl(IControlBase *pControl);
	// ͨ���ݹ����ָ�����ƵĿؼ�
	bool GetControlByName(CHILD_CTRLS_VEC *pCtrlVec, char *pszCtrlName, IControlBase **ppCtrl);

protected:
	BLENDFUNCTION m_Blend;
	// Window����
	IPropertyWindow *m_pWndProp;
	// �����ھ��
	HWND m_hParent;
	// ���ھ��
	HWND m_hWnd;
	// �����Ի�����ڴ�DC
	CMemoryDC m_WndMemDc;
	// �ӿؼ��б�
	CHILD_CTRLS_VEC m_ChildCtrlsVec;
	// �Ƿ�Ϊlayered����
	bool m_bIsLayeredWnd;
	// �������Ƿ���
	bool m_bIsLButtonDown;
	// ���Hover�Ŀؼ�
	IControlBase* m_pMouseHoverCtrl;
	// ���������µĿؼ�
	IControlBase* m_pLButtonDownCtrl;
	// ȡ�ý���Ŀؼ�
	IControlBase* m_pFocusCtrl;
	// Ƥ��·��
	string m_strSkinPath;
	// �Ի�������
	string m_strWindowName;
};

