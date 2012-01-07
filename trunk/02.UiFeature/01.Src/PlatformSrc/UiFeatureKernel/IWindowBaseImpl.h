
#pragma once
#include "..\..\Inc\IWindowBase.h"
#include "..\..\Inc\CDrawingBoard.h"
#include "..\..\Inc\IPropertyGroup.h"
#include "..\..\Inc\IPropertyString.h"
#include "..\..\Inc\IPropertyBool.h"
#include "..\..\Inc\IPropertyInt.h"
#include "..\..\Inc\IPropertyImage.h"
#include "..\..\Inc\IPropertySkinManager.h"

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

//////////////////////////////////////////////////////////////////////////
	// ����Ƥ����ʹ�õĺ�����ʼ��
	virtual void PG_InitWindowBase(HWND hWnd, char *pszSkinPath, char *pszWndName);

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

//////////////////////////////////////////////////////////////////////////
	// ȡ�ô��ڿؼ�ָ��
	virtual IControlBase* GetControl(char *pszCtrlName);
	// �����δ����һ���ؼ�
	virtual void AppendChildContrl(IControlBase *pCtrl);
	// ȡ���ӿؼ��б�
	virtual CHILD_CTRLS_VEC* GetChildControlsVec();
	// ȡ���ӿؼ��������б�Layout.xml �еĲ���
	virtual PROP_CONTROL_VEC* GetChildPropControlVec();

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
	// 001.�ڲ����ܵ���ʼ����Ϣ����ʼ��ʼ�����ڣ�����Ƥ��
	void OnInitWindowBase();
	bool IsInit();

	// ��Builder�л����õı߿�ɫ��
	void BD_NewFrameImage();
	void BD_NewFrameImageBase(IPropertyImageBase *pImgBase, string strImgPath);

private:
	// ѭ������ÿ���ؼ��Ļ���
	void DrawControl();
	void RedrawWindow(RECT* pDrawRct = NULL);
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
	// Ƥ��·��
	string m_strSkinPath;
	// Ƥ����object����
	string m_strWindowObjectName;
	// Builder ר�ã���ʾ�ؼ��ı߿��8������
	FANGKUAI_8 m_BD_FangKuai8;

	// ��Builder�л����õı߿�ɫ��
	IPropertyImage m_BuilderWndFrameImage;
	IPropertyImageBase m_BuilderWndFrameImageBase;
	IPropertyImage m_BuilderCtrlFrameImage;
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
	IPropertyBase* CreateCtrlOnePropetry(IPropertyGroup* pGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo);
	// �ͷ��ӿؼ��б�
	void ReleaseChildVec(CHILD_CTRLS_VEC *pChildCtrlsVec);
	// ���ƴ��ںͱ�ѡ�еĿؼ��ı߿��8������
	void BD_DrawSelectRect(CDrawingBoard &MemDc, RECT DrawRct, bool bIsWndFrame);

private:
	IUiEngine *m_pUiEngine;
	IPropertySkinManager* m_pSkinPropMgr;

	bool m_bIsFullScreen;

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
	// base-sysbase-��С�ߴ�
	// base-sysbase-���ߴ�
	// Group-size
	IPropertyGroup* m_pPropGroupSize;
	// size-width
	IPropertyInt *m_pPropSize_Width;
	// size-height
	IPropertyInt *m_pPropSize_Height;
	// Group-drag(��ק����)
	IPropertyGroup* m_pPropGroupDrag;
	// drag-enable
	IPropertyBool *m_pPropDrag_Enable;
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
