
#pragma once
#include "..\..\Inc\IWindowBase.h"
#include "..\..\Inc\CDrawingBoard.h"
#include "..\..\Inc\IPropertyGroup.h"
#include "..\..\Inc\IPropertyString.h"
#include "..\..\Inc\IPropertyBool.h"
#include "..\..\Inc\IPropertyInt.h"
#include "..\..\Inc\IPropertyImage.h"
#include "..\..\Inc\IPropertySkinManager.h"
#include "..\..\Inc\CHighAccuracyTimer.h"
#include "WindowResize.h"

class IWindowBaseImpl : public IWindowBase
{
public:
	IWindowBaseImpl();
	virtual ~IWindowBaseImpl();

//////////////////////////////////////////////////////////////////////////
	// Builder ʹ�õĺ���
	virtual void BD_InitWindowBase(IPropertyWindow *pWindowProp, bool bSetDftProp);
	virtual void BD_DrawWindowView(CDrawingBoard &ViewMemDc);
	// �õ���Builder����ʾ������8�������λ��
	virtual FANGKUAI_8* BD_GetFangKuai8Rect();
	// ȡ�õ�ǰ����λ�õĿؼ�
	virtual IControlBase *BD_GetMouseInControl(POINT pt);
	// ȡ�õ�ǰ����Ŀؼ�
	virtual IControlBase *BD_GetFocusControl();
	// ���õ�ǰ����Ŀؼ�
	virtual void BD_SetFocusControl(IControlBase* pControl);
	// ���ÿؼ��ڱ༭ģʽ�µ�λ�úʹ�С
	virtual void BD_SetControlRect(IControlBase* pControl, RECT RctInView);
	// ��ʼ�����пؼ���Builder�е���ʾλ��
	virtual void BD_SetAllCtrlRectInView();
	// ����ָ���ؼ���Builder�е���ʾλ��
	virtual void BD_SetControlRectInView(CHILD_CTRLS_VEC *pChildCtrlsVec);
	// ���¼����ӿؼ���λ�úʹ�С��������bMemToProp �Ƿ��¼�������У�BuilderʱΪtrue
	virtual void ResetChildCtrlPostion(CHILD_CTRLS_VEC* pChildVec, bool bMemToProp = false);
	// �Ƿ�Ϊ���ģʽ
	virtual bool IsDesignMode();

//////////////////////////////////////////////////////////////////////////
	// ����Ƥ����ʹ�õĺ�����ʼ��
	virtual void PG_InitWindowBase(HWND hWnd, char *pszSkinPath, char *pszWndName);
	virtual IUiFeatureKernel* GetUiKernel();

	// ���ھ�����ʾ
	virtual void CenterWindow();
	// ȡ�ô��ھ��
	virtual HWND GetSafeHandle();
	// �õ�������Ļ����
	virtual RECT GetWindowRect();
	// �õ��ͻ������꣬[0,0]����ϵ
	virtual RECT GetClientRect();

	// ���ݿؼ�������Ϣ���ÿؼ���λ��
	void SetControlWindowPostion(IControlBase* pCtrl, RECT ParentRctInWnd);
//////////////////////////////////////////////////////////////////////////
	// ȡ�ô��ڿؼ�ָ��
	virtual IControlBase* GetControl(char *pszCtrlName);
	// �����δ����һ���ؼ�
	virtual void AppendChildContrl(IControlBase *pCtrl);
	// ȡ���ӿؼ��б�
	virtual CHILD_CTRLS_VEC* GetChildControlsVec();
	// ȡ���ӿؼ��������б�Layout.xml �еĲ���
	virtual PROP_CONTROL_VEC* GetChildPropControlVec();

	// ����������ͨ�ö�����ʱ��
	virtual void SetAnimationTimer();
	// ������ͨ��ʱ��
	virtual int SetTimer(DWORD uElapse);
	virtual void KillTimer(int nId);
	// ���ø߾��ȶ�ʱ��
	virtual int SetHighAccuracyTimer(DWORD uElapse);
	virtual void KillHighAccuracyTimer(int nId);

	void InvalidateRect(RECT *lpRect);
	void UpdateWindow();
	// �����ػ洰��
	virtual void RedrawWindow(RECT *pDrawRect = NULL);

	// ��ʾ�Զ�����
	void SetWindowCursor(int nCursor);

protected:
	// �����ڵ���Ϣ��������bPassOn����Ϊtrue�ǣ���Ϣ��������ݴ���falseʱ��������ϣ������´�
	virtual LRESULT WindowProc(UINT nMsgId, WPARAM wParam, LPARAM lParam, bool &bPassOn);

	virtual void OnCreate();
	virtual void BD_OnTimer(UINT nTimerId, HWND hView);
	virtual void OnTimer(UINT nTimerId);
	virtual void OnKeyDown(int nVirtKey, int nFlag);
	// ϵͳ��Ϣ������true˵������Ҫ���ظ����ü�������
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
	virtual void OnPaint(HDC hWndDc, RECT *pLayeredRect = NULL);
	// �Ի������˵����������Ҽ��˵������Ͻǲ˵��Ľػ�
	virtual void OnPopupSystemMenu(POINT pt);
	// ���������ʽ������true��ʾ�������Զ����������ƣ�falseΪ��Ҫʹ��ϵͳĬ�ϵ�����
	virtual bool OnSetCursor(HWND hWnd, int nHitTest, int nMsgId);
	virtual LRESULT OnNcHitTest(int nX, int nY);
	// ���ڳߴ����ֵ��Сֵ����
	virtual bool OnGetMinMaxInfo(MINMAXINFO *pMinMaxInfo);

	virtual void OnMouseMove(int nVirtKey, POINT pt);
	virtual void OnLButtonDown(int nVirtKey, POINT pt);
	virtual void OnLButtonUp(int nVirtKey, POINT pt);
	virtual void OnLButtonDbClick(int nVirtKey, POINT pt);
	virtual void OnRButtonDown(int nVirtKey, POINT pt);

private:
	// �ڲ����ܵ���ʼ����Ϣ����ʼ��ʼ�����ڣ�����Ƥ��
	void OnInitWindowBase();
	// ��ʼ���Ի��򡢼��ش���Ƥ����ɣ��ڷֲ㴰��ģʽ�£���ʼ�����ں���ʾ����
	void OnInitWindowBaseEnd();
	bool IsInit();
	// �����ؼ�
	bool CreateChildCtrlVec(IControlBase *pParentCtrl, PROP_CONTROL_VEC* pPropCtrlVec, CHILD_CTRLS_VEC* pCtrlVec);

	// ��Builder�л����õı߿�ɫ��
	void BD_NewFrameImage();
	void BD_NewFrameImageBase(IPropertyImageBase *pImgBase, string strImgPath);
	bool BD_CheckMouseInControl(CHILD_CTRLS_VEC *pCtrlVec, POINT pt, IControlBase** ppControl);

	// ����Դ��ڵ�����������õ���Կؼ����������
	POINT GetCtrlMouseOffset(POINT WndPt, IControlBase* pCtrl);
private:
	// ѭ������ÿ���ؼ��Ļ���
	void DrawControl();
	// �����ڵ����Է����仯ʱ��Ҫ֪ͨ���ڽ���ˢ��ʱ����
	void RefreshWindowStyle();
	// ȡ�õ�ǰ��������������ĸ��ؼ���
	bool CheckMouseInControl(CHILD_CTRLS_VEC *pCtrlVec, POINT pt, IControlBase **ppControl);
	// ���ô��������пؼ���λ�úʹ�С
	void SetControlPostion(CHILD_CTRLS_VEC *pCtrlVec, SIZE NewSize);
	// ���õ�ǰ�õ�����Ŀؼ����������ΪNULL��˵����ǰû�пؼ��õ����㣬���пؼ���ʧȥ����
	void SetFocusCtrl(IControlBase *pControl);
	// ͨ���ݹ����ָ�����ƵĿؼ�
	bool GetControlByName(CHILD_CTRLS_VEC *pCtrlVec, char *pszCtrlName, IControlBase **ppCtrl);
	// �ڷֲ㴰��ģʽ�����촰�ڴ�С
	void ResizeInLayeredWindow(RECT NewWndRect);
	// ���ݴ��ڻ������ԣ����ô��ڻ�����ʽ
	void SetWindowStyleByProp();
	// ���ô���֧��͸��ģʽ
	void SetWindowTransparence(bool bIsTrans);
	// �������������������ڰ�ť
	void HideInTaskbar();

protected:
	// �߽��ȶ�ʱ��
	CHighAccuracyTimer m_HighTimer;
	// �Ƿ�Ϊ���ģʽ
	bool m_bIsDesignMode;
	// Ƥ��·��
	string m_strSkinPath;
	// Ƥ����object����
	string m_strWindowObjectName;
	// Builder ר�ã���ʾ�ؼ��ı߿��8������
	FANGKUAI_8 m_BD_FangKuai8;

	// ��Builder�л����õı߿�ɫ��
	IPropertyImageBase m_BuilderWndFrameImageBase;
	IPropertyImageBase m_BuilderCtrlFrameImageBase;

	BLENDFUNCTION m_Blend;
	// �����ھ��
	HWND m_hParent;
	// ���ھ��
	HWND m_hWnd;
	// �����Ի�����ڴ�DC
	CDrawingBoard m_WndMemDc;
	// �������Ƿ���
	bool m_bIsLButtonDown;
	// ���Hover�Ŀؼ�
	IControlBase* m_pMouseHoverCtrl;
	// ���������µĿؼ�
	IControlBase* m_pLButtonDownCtrl;
	// ȡ�ý���Ŀؼ�
	IControlBase* m_pFocusCtrl;
	// �ӿؼ��б�
	CHILD_CTRLS_VEC m_ChildCtrlsVec;
	// Builder��View���ڵľ��
	HWND m_hBuilderView;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ��������
public:
	// ��xml�е��������õ�manager��
	virtual IPropertyGroup *PP_GetWindowPropetryGroup();
	virtual IPropertyWindow *PP_GetWindowPropetry();

	virtual void PP_SetWindowPropetry(IPropertyWindow *pWndPropInXml, bool bSetDftProp);

	// �Ƿ�֧��ȫ���ڵ���ƶ�
	virtual void PP_SetDragWindow(bool bDrag);
	virtual bool PP_GetDragWindow();

	// �Ƿ����
	virtual void PP_SetCanFullScreen(bool bCanFull);
	virtual bool PP_IsCanFullScreen();
	virtual void PP_SetFullScreen(bool bFull);
	virtual bool PP_IsFullScreen();

	// ���ô����͸�����ԡ����ô����Ƿ�֧�ֲַ�
	virtual void PP_SetLayeredWindow(bool bIsLayered);
	virtual bool PP_GetLayeredWindow();

	// ����Object����
	virtual void PP_SetWindowObjectName(char *pszWndName);
	virtual const char * PP_GetWindowObjectName();

	// ��������
	virtual void PP_SetWindowText(char *pszWndName);
	virtual const char * PP_GetWindowText();

	// ȡ�ô������������ԵĴ��ڴ�С
	virtual SIZE PP_GetWindowPropSize();

private:
	// �����յ����Զ���
	void CreateWindowPropetry(bool bSetDftProp);
	IPropertyBase* CreateWindowOnePropetry(IPropertyGroup* pGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo);
	// �ͷ��ӿؼ��б�
	void ReleaseChildVec(CHILD_CTRLS_VEC *pChildCtrlsVec);
	// ���ƴ��ںͱ�ѡ�еĿؼ��ı߿��8������
	void BD_DrawSelectRect(CDrawingBoard &MemDc, FANGKUAI_8 &FangKuai8, bool bIsWndFrame);

private:
	IUiFeatureKernel *m_pUiKernel;
	IUiEngine *m_pUiEngine;
	IPropertySkinManager* m_pSkinPropMgr;
	// �������촰�ڲ�������
	CWindowResize m_WndResize;

	bool m_bIsFullScreen;
	// ��ǰ�����ʽ��
	int m_nCurMouseStyle;

	// ��xml�ж��벢��Ҫд��xml�е����Դ��������б�
	IPropertyWindow *m_pXmlPropWindow;

	// Group:base
	IPropertyGroup* m_pPropGroupBase;
	// base-��������
	IPropertyString *m_pPropBase_TypeName;
	// base-objectid
	IPropertyString *m_pPropBase_ObjectId;
	// base-name
	IPropertyString *m_pPropBase_Name;
	// base-windowtitle
	IPropertyString *m_pPropBase_WindowText;
	// base-visible
	IPropertyBool *m_pPropBase_Visible;
	// base-����������ʾ��ť
	IPropertyBool *m_pPropBase_ShowInTaskbar;
	// base-֧�ֲַ㴰��
	IPropertyBool *m_pPropBase_Layered;
	// base-topmost
	IPropertyBool *m_pPropBase_TopMost;
	// base-sysbase
	IPropertyGroup* m_pPropGroupSysBase;
	// base-sysbase-���
	IPropertyBool *m_pPropSysBase_CanFullScreen;
	// base-sysbase-��С��
	IPropertyBool *m_pPropSysBase_CanMiniSize;

	// Group-size
	IPropertyGroup* m_pPropGroupWindowSize;
	// size-width
	IPropertyInt *m_pPropSize_WindowWidth;
	// size-height
	IPropertyInt *m_pPropSize_WindowHeight;

	// Group-drag(��ק����)
	IPropertyGroup* m_pPropGroupDrag;
	// drag-enable
	IPropertyBool *m_pPropDrag_Enable;

	// Group-Size(���ڵĴ�С)
	IPropertyGroup* m_pPropGroupSize;
	// Size-enable
	IPropertyBool *m_pPropSize_Enable;
	// Size-MaxWidth
	IPropertyInt *m_pPropSize_MaxWidth;
	// Size-MaxHeight
	IPropertyInt *m_pPropSize_MaxHeight;
	// Size-MinWidth
	IPropertyInt *m_pPropSize_MinWidth;
	// Size-MinHeight
	IPropertyInt *m_pPropSize_MinHeight;

	// Group-stretching(���촰��)
	IPropertyGroup* m_pPropGroupStretching;
	// stretching-enable
	IPropertyBool *m_pPropStretching_Enable;
	// stretching-leftspace
	IPropertyInt *m_pPropStretching_LeftSpace;
	// stretching-rightspace
	IPropertyInt *m_pPropStretching_RightSpace;
	// stretching-topspace
	IPropertyInt *m_pPropStretching_TopSpace;
	// stretching-bottomspace
	IPropertyInt *m_pPropStretching_BottomSpace;
	// Group-WindowRgn
	IPropertyGroup* m_pPropGroupWindowRgn;
};
