
#pragma once
#include "CDrawingBoard.h"
#include "IFeatureObject.h"
#include "IUiEngine.h"
#include "IPropertySkinManager.h"
#include "IPropertyString.h"
#include "IPropertyGroup.h"
#include "IPropertyBool.h"
#include "IPropertyInt.h"
#include "IPropertyColor.h"
#include "IPropertyComboBox.h"
#include "IPropertyCursor.h"
#include "IPropertyFont.h"
#include "IPropertyImage.h"
#include "CDrawingBoard.h"

class IWindowBase;
class IWindowBaseImpl;
class IUiFeatureKernelImpl;
class IPropertyControl;
class IControlBase;

// �ؼ�������Ϣ�ӿ�
class IControlMessage
{
public:
	virtual LRESULT OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam) = 0;
};

// Builder ר�ã���ʾ�ؼ��ı߿��8������
struct FANGKUAI_8
{
	// �������궼�ǻ���View�ľ�������
	RECT EntityRct;
	RECT LeftTop;
	RECT LeftMid;
	RECT LeftBottom;
	RECT MidTop;
	RECT MidBottom;
	RECT RightTop;
	RECT RightMid;
	RECT RightBottom;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ǰ�ؼ�����ڸ��ؼ��Ĳ�������

// �̶���С�����ϽǶ�λ
#define TN_CL_G_LEFT_TOP				"���ϽǶ�λ"
// �̶���С�����½Ƕ�λ
#define TN_CL_G_LEFT_BOTTOM				"���½Ƕ�λ"
// �̶���С�����ϽǶ�λ
#define TN_CL_G_RIGHT_TOP				"���ϽǶ�λ"
// �̶���С�����½Ƕ�λ
#define TN_CL_G_RIGHT_BOTTOM			"���½Ƕ�λ"
// ����䶯��С���������
#define TN_CL_L_LEFT					"�������"
// ����䶯��С�������Ҳ�
#define TN_CL_L_RIGHT					"�����Ҳ�"
// ����䶯��С�������Ϸ�
#define TN_CL_L_TOP						"�����Ϸ�"
// ����䶯��С�������·�
#define TN_CL_L_BOTTOM					"�����·�"
// ����䶯��С������ȫ��
#define TN_CL_L_ALL						"����ȫ��"
// ����䶯��С������
#define TN_CL_L_MIDDLE					"����"
// ����䶯��С���û��Զ���λ��
#define TN_CL_L_USER_DEF				"�û��Զ���λ��"

enum CONTROL_LAYOUT
{
	// �̶���С�����ϽǶ�λ
	CL_G_LEFT_TOP		= 0,
	// �̶���С�����½Ƕ�λ
	CL_G_LEFT_BOTTOM	= 1,
	// �̶���С�����ϽǶ�λ
	CL_G_RIGHT_TOP		= 2,
	// �̶���С�����½Ƕ�λ
	CL_G_RIGHT_BOTTOM	= 3,
	// ����䶯��С���������
	CL_L_LEFT			= 4,
	// ����䶯��С�������Ҳ�
	CL_L_RIGHT			= 5,
	// ����䶯��С�������Ϸ�
	CL_L_TOP			= 6,
	// ����䶯��С�������·�
	CL_L_BOTTOM			= 7,
	// ����䶯��С������ȫ��
	CL_L_ALL			= 8,
	// ����䶯��С������
	CL_L_MIDDLE			= 9,
	// ����䶯��С���û��Զ���λ��
	CL_L_USER_DEF		= 10,
};
// ��ǰ�ؼ�����ڸ��ؼ��Ĳ�����Ϣ
struct CONTROL_LAYOUT_INFO
{
	// ��������
	CONTROL_LAYOUT clType;
	// �ؼ���
	int nWidth;
	// �ؼ���
	int nHeight;
	// ���븸�ؼ�������
	int nLeftSpace;
	// ���븸�ؼ��Ҳ����
	int nRightSpace;
	// ���븸�ؼ��Ϸ�����
	int nTopSpace;
	// ���븸�ؼ��·�����
	int nBottomSpace;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// һ���ؼ������ṩ��ע����Ϣ�������Ϣ��ע�ᵽUiFeatureBuilder�ṩBuilder��ʾ��
// Ҳ���ṩ��UiFeatureKernel���в�ѯ
struct CONTROL_REG
{
	// ������DLL����
	string	strDllName;
	// �ؼ����ڵĿؼ�������
	string	strCtrlGroupName;
	// �ؼ�����
	string	strCtrlName;
	// �ؼ�˵��
	string strControlInfo;
};
// ��������CONTROL_REG::strCtrlName��
typedef map<string, CONTROL_REG>	CONTROL_REG_MAP;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �ӿؼ��б�
typedef vector<IControlBase*>			CHILD_CTRLS_VEC;

class IControlBase : public IFeatureObject
{
	friend class IWindowBaseImpl;
	friend class IUiFeatureKernelImpl;

public:
	IControlBase();
	virtual ~IControlBase();

	// �õ���Builder����ʾ������8�������λ��
	virtual FANGKUAI_8* BD_GetFangKuai8Rect();

	// �Ƿ�������Builder�����ı�ؼ���С��λ��
	void SetLockControl(bool bLock);
	bool GetLockControl();

	// ȡ�ø��ؼ���ָ�룬���ΪNULL��˵�����ؼ��ǶԻ���
	IControlBase* GetParentControl();
	IWindowBase* GetOwnerWindow();

	// ȡ���ӿؼ��б�
	CHILD_CTRLS_VEC* GetChildControlsVec();
	// ȡ���ӿؼ��������б�Layout.xml �еĲ���
	PROP_CONTROL_VEC* GetChildPropControlVec();

	// �ػ�ؼ�
	virtual void RedrawControl(bool bDrawImmediately = false);

	// �ؼ���ʾλ�úʹ�С�����λ��������ڸ��ŵĴ��ڵģ�����ı䲼����Ϣ
	virtual void SetWindowRect(RECT CtrlInWndRct);
	virtual RECT GetWindowRect();
	virtual RECT GetClientRect();
	// �ؼ���ʾλ�úʹ�С������ݲ�����Ϣ�����޸��ӿؼ���λ��
	virtual void SetWindowRectLayoutWithChild(RECT CtrlInWndRct);

	// �ɼ�����
	virtual void SetVisible(bool bVisible, bool bSetChild = true);
	virtual bool IsVisible();

	// ��������
	virtual void SetEnable(bool bEnable, bool bSetChild = true);
	virtual bool IsEnable();

	// ���ƿؼ���ָ����DC��
	virtual void PrintTo(CDrawingBoard &DstBoard, RECT ToRct, int nAlpha = 255);

	// ȡ�ø����ڵľ��
	HWND GetOwnerWindowHwnd();

	const char * PP_GetControlObjectName();

	// �Ƿ���������Ϣ
	void SetReceiveMouseMessage(bool bIsReceive);
	bool GetReceiveMouseMessage();

	CONTROL_LAYOUT_INFO GetLayout();

	// ����Ƿ�Hover
	bool IsMousehover();

	IPropertyGroup* PP_GetControlPropetryGroup();
	IPropertyControl *PP_GetControlPropetry();

	// �����Ը������ݵ���Ա����
	void PropetyValueToMemberValue();
	// �����ؼ�������ɺ��ٻ��Ƶ����ؼ��ϵ�alphaֵ��Ĭ��255
	void SetControlAlpha(int nCtrlAlpha = 255);
	int GetControlAlpha();

	// ȡ�û��ƿؼ����ڴ�DC
	CDrawingBoard* GetMemoryDc();

//////////////////////////////////////////////////////////////////////////
	// ���к������������ؼ�������ҵ��ʱ��ԭ���ϲ��������
	// �ƶ��ؼ�����ı䲼����Ϣ��������CtrlInWndRct�ؼ�λ�ڴ��ڵ�λ��
	void ResetWindowRect(RECT CtrlInWndRct);

	// ��������Ϣ
	virtual void OnVScroll(UINT nSBCode, UINT nPos, IControlBase* pScrollBar) = 0;
	virtual void OnHScroll(UINT nSBCode, UINT nPos, IControlBase* pScrollBar) = 0;

	// �ؼ���Ҫ�����һЩ�Զ������Ϣ����Ϣ�����ϻ��ɶԻ�����������ؼ�����
	virtual void OnCtrlNotify(int nMsgId, WPARAM wParam, LPARAM lParam) = 0;

protected:
	// �����ӿؼ��������Ի�
	void SetChildCtrlToRedraw();
	// ���ÿؼ����´λ��Ƶ�ʱ���Ƿ���Ҫ�����ػ�
	void SetNeedRedraw(bool bNeedRedraw);

protected:
	// �����ؼ����ڴ���һ������
	IPropertyBase* CreatePropetry(IPropertyGroup* pPropGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo);
	// �����ؼ����ڴ��������Լ��Ŀؼ�����
	// bNeedSetDftProp��trueʱ˵����Builder���ã��´���һ���ؼ�����Ҫ��ʼ�����Եĸ���Ĭ��ֵ
	// false��˵������Ƥ�����Ѿ���ʼ����ϣ����Դ�����ϵ�ʱ�򣬴�xml�ж�ȡ������ֵ�Ѿ���ֵ����ˣ������ٳ�ʼ��������xml�е�ֵ�ᱻ���
	virtual bool CreateControlPropetry(bool bNeedSetDftProp) = 0;
	// ���ƿؼ��Ķ����������Ҫ����ˢ�½��棬����true�����򷵻�false
	// �˺����ɶ�ʱ��������ÿ100���봥��һ��
	virtual bool OnDrawAnimation() = 0;
	// ��ʱ��
	virtual void OnTimer(UINT nTimerId) = 0;
	// ��ʼ���ؼ�
	virtual void OnCreate() = 0;
	// �ؼ���ʼ�����
	virtual void OnFinalCreate() = 0;
	// ���ٿؼ�
	virtual void OnDestroy() = 0;
	// ���ƿؼ�
	virtual void OnPaint(CDrawingBoard &DrawBoard) = 0;
	// Builderˢ������
	virtual void OnBuilderRefreshProp() = 0;
	// ������
	virtual void OnMouseEnter(POINT pt) = 0;
	// ����Ƴ�
	virtual void OnMouseLeave() = 0;
	// ����ƶ�
	virtual void OnMouseMove(POINT pt) = 0;
	// ���������
	virtual void OnLButtonDown(POINT pt) = 0;
	// ������̧��
	virtual void OnLButtonUp(POINT pt) = 0;
	// ������˫��
	virtual void OnLButtonDbClick(POINT pt) = 0;
	// ����ڿؼ��ڲ��϶��ؼ�
	virtual void OnMouseDragging(POINT pt) = 0;
	// ����Ҽ����
	virtual void OnRButtonDown(POINT pt) = 0;
	// �ƶ������ÿؼ�λ��
	virtual void OnSize() = 0;
	// �ƶ����ڿ�ʼ
	virtual void OnEnterSizeMove() = 0;
	// �ƶ����ڽ���
	virtual void OnExitSizeMove() = 0;
	// �ؼ�ȡ�ý��㣬ͨ��Tab����ת������ؼ�
	virtual void OnSetFocus() = 0;
	// �ؼ�ʧȥ����
	virtual void OnKillFocus() = 0;
	// ���ܵ�Ĭ�ϻس�����ִ�пؼ�����
	virtual void OnDefaultEnterCtrl() = 0;
	// �ؼ�ȡ�ü���������Ϣ
	virtual void OnChar(WPARAM wParam, LPARAM lParam) = 0;
	// ��������
	virtual void OnKeyDown(WPARAM wParam, LPARAM lParam) = 0;
	virtual void OnKeyUp(WPARAM wParam, LPARAM lParam) = 0;
	// ��������Ϣ
	virtual void OnMouseWheel(WPARAM wParam, LPARAM lParam) = 0;

	// ���ں�ע��һ����Ҫȡ������Ϣ
	void RegisterControlMessage(int nMsgId);
	void UnRegisterControlMessage(int nMsgId);
	// ������Ϣ:Send��ʽ
	LRESULT SendMessage(UINT nMsgId, WPARAM wParam, LPARAM lParam);
	// ������Ϣ:Post��ʽ
	bool PostMessage(UINT nMsgId, WPARAM wParam, LPARAM lParam);

private:
	// �����ؼ�����
	void CreateCtrlAllPropetry(bool bNeedSetDftProp);
	IPropertyBase* CreateCtrlOnePropetry(IPropertyGroup* pGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo);

	// ��ʼ����builder�е�����
	bool InitControlPropetry(IPropertyControl *pCtrlProp, bool bNeedSetDftProp);
	void SetPropertySkinManager(IPropertySkinManager *pMgr);
	// �����δ����һ���ؼ�
	void AppendChildContrl(IControlBase *pCtrl);

	void SetUiEngine(IUiEngine *pUiEngine);
	// ���ø��ؼ�
	void SetParentControl(IControlBase* pParentCtrl);
	// ���ŶԻ���
	void SetOwnerWindow(IWindowBase* pWindowsBase);

	// ����Ƿ�Hover
	void SetMouseHover(bool bHover);

	// �˺����ɴ��ڵ��ã����Ƶ�ǰ�ؼ�������Ϊ������/���ؼ����ڴ�DC
	virtual void OnPaintControl(CDrawingBoard &WndMemDc, RECT ActiveDrawRct);

	// �ӳ�Ա�����������ݵ�����
	void MemberValueToPropetyValue();
	// ���¼����ӿؼ���λ�úʹ�С
	void ResetChildPropetyValueToMemberValue(IControlBase* pParentCtrl);
	// �ؼ���ʾλ�úʹ�С������ݲ�����Ϣ�����޸��ӿؼ���λ��
	void SetChildWindowPostion(CHILD_CTRLS_VEC* pVec);

protected:
	// �����ؼ����ڴ�DC
	CDrawingBoard m_CtrlMemDc;
	// ���ŵĴ���
	IWindowBase* m_pWindowBase;
	// ���ؼ�
	IControlBase* m_pParentCtrl;
	// ��ͼ����
	IUiEngine *m_pUiEngine;
	// �ӿؼ��б�
	CHILD_CTRLS_VEC m_ChildCtrlsVec;
	// �����ؼ�������ɺ��ٻ��Ƶ����ؼ��ϵ�alphaֵ
	int m_nCtrlAlpha;

	// �Ƿ����ػ�ؼ�
	bool m_bNeedRedraw;
	// ���Hover״̬
	bool m_bMouseHover;
	// �ؼ�λ�ã����λ��������ڴ��ڵ�λ��
	RECT m_RectInWindow;

	// Ƥ����������
	IPropertySkinManager *m_pSkinPropMgr;
	// ��¼��xml�е�����
	IPropertyControl *m_pXmlPropCtrl;

	// Group:base
	IPropertyGroup* m_pPropGroupBase;
	// base-��������
	IPropertyString *m_pPropBase_TypeName;
	// base-objectid
	IPropertyString *m_pPropBase_ObjectId;
	// base-name
	IPropertyString *m_pPropBase_Name;
	// base-lock
	IPropertyBool *m_pPropBase_Lock;
	// base-visible
	IPropertyBool *m_pPropBase_Visible;
	// base-ReceiveMouseMessage
	IPropertyBool *m_pPropBase_RcvMouseMsg;
	// base-enable
	IPropertyBool *m_pPropBase_Enable;
	// base-taborder
	IPropertyInt *m_pPropBase_TabOrder;
	// base-defaultenterctrl
	IPropertyBool *m_pPropBase_DefaultEnterCtrl;
	// base-layout
	IPropertyGroup *m_pPropBase_LayoutGroup;
	// layout-width
	IPropertyInt *m_pPropBase_Layout_Width;
	// layout-height
	IPropertyInt *m_pPropBase_Layout_Height;

	// layout-
	IPropertyComboBox *m_pPropBase_Layout_Layout;
	// layout-leftspace
	IPropertyInt *m_pPropBase_Layout_LeftSpace;
	// layout-rightspace
	IPropertyInt *m_pPropBase_Layout_RightSpace;
	// layout-topspace
	IPropertyInt *m_pPropBase_Layout_TopSpace;
	// layout-bottomspace
	IPropertyInt *m_pPropBase_Layout_BottomSpace;

	// Group:CtrlDefs
	IPropertyGroup* m_pPropGroupCtrlDefs;
	
private:
	// Builder ר�ã���ʾ�ؼ��ı߿��8������
	FANGKUAI_8 m_BD_FangKuai8;
};
