
#pragma once
#include "CMemoryDC.h"
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

class IWindowBase;
class IWindowBaseImpl;
class IKernelWindowImpl;
class IPropertyControl;
class IControlBase;

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
	// �ؼ���Builder��ʾ��ͼƬ����icon�ļ�����Щ�ļ������ControlsResĿ¼�£�Ϊ����ʹ��Builder�е�Ĭ�ϵ�ͼ��
	string	strControlImg;
	// �ؼ�˵��
	string strControlInfo;
};
// ��������CONTROL_REG::strCtrlName��
typedef map<string, CONTROL_REG>	CONTROL_REG_MAP;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �ؼ��ܹ��յ�����Ϣ
enum CONTROL_MSG
{
	// ��ʼ���ؼ�
	CM_Create	= 1,
	// �ؼ���ʼ�����
	CM_FinalCreate,
	// Builderˢ������
	CM_BuilderRefreshProp,
	// ������
	CM_MouseEnter,
	// ����Ƴ�
	CM_MouseLeave,
	// ����ƶ�
	CM_MouseMove,
	// ���������
	CM_LButtonDown,
	// ������̧��
	CM_LButtonUp,
	// ������˫��
	CM_LButtonDbClick,
	// ����Ҽ����
	CM_RButtonDown,
	// �ƶ������ÿؼ�λ��
	CM_Size,
	// ���ƿؼ�
	CM_Paint,
	// �ƶ����ڿ�ʼ
	CM_EnterSizeMove,
	// �ƶ����ڽ���
	CM_ExitSizeMove,
	// ���ٿؼ�
	CM_Destroy,
	// �ؼ�ȡ�ý��㣬ͨ��Tab����ת������ؼ�
	CM_SetFocus,
	// �ؼ�ʧȥ����
	CM_KillFocus,
	// �ؼ�ȡ�ü���������Ϣ
	CM_Char,
	// ���ܵ�Ĭ�ϻس�����Ϣ
	CM_DefaultEnterCtrl
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �ӿؼ��б�
typedef vector<IControlBase*>			CHILD_CTRLS_VEC;

class IControlBase : public IFeatureObject
{
	friend class IWindowBaseImpl;
	friend class IKernelWindowImpl;
public:
	IControlBase();
	virtual ~IControlBase();


protected:
	// �����ؼ����ڴ���һ������
	IPropertyBase* CreatePropetry(OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo);

	// �����ؼ����ڴ��������Լ��Ŀؼ�����
	virtual bool CreateControlPropetry() = 0;
	// �����ؼ��������Ϣ
	virtual void OnNotification(int nMsgId, WPARAM wParam, LPARAM lParam) = 0;

//////////////////////////////////////////////////////////////////////////
	// �ؼ���Ϣ����
	// ��ʼ���ؼ�
	virtual void OnCreate() = 0;
	// �ؼ���ʼ�����
	virtual void OnFinalCreate() = 0;
	// Builderˢ������
	virtual void OnBuilderRefreshProp() = 0;
	// ������
	virtual void OnMouseEnter(POINT pt);
	// ����Ƴ�
	virtual void OnMouseLeave() = 0;
	// ����ƶ�
	virtual void OnMouseMove(POINT pt);
	// ���������
	virtual void OnLButtonDown(POINT pt);
	// ������̧��
	virtual void OnLButtonUp(POINT pt);
	// ������˫��
	virtual void OnLButtonDbClick(POINT pt);
	// ����϶��ؼ�
	virtual void OnMouseDrag(POINT pt);
	// ����Ҽ����
	virtual void OnRButtonDown(POINT pt);
	// �ƶ������ÿؼ�λ��
	virtual void OnSize() = 0;
	// ���ƿؼ�
	virtual void OnPaint();
	// �ƶ����ڿ�ʼ
	virtual void OnEnterSizeMove() = 0;
	// �ƶ����ڽ���
	virtual void OnExitSizeMove() = 0;
	// ���ٿؼ�
	virtual void OnDestroy() = 0;
	// �ؼ�ȡ�ý��㣬ͨ��Tab����ת������ؼ�
	virtual void OnSetFocus() = 0;
	// �ؼ�ʧȥ����
	virtual void OnKillFocus() = 0;
	// �ؼ�ȡ�ü���������Ϣ
	virtual void OnChar(WPARAM wParam, LPARAM lParam);
	// ���ܵ�Ĭ�ϻس�����ִ�пؼ�����
	virtual void OnDefaultEnterCtrl() = 0;

	

private:
	// �����ؼ�����
	void CreateCtrlAllPropetry();
	IPropertyBase* CreateCtrlOnePropetry(IPropertyGroup* pGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo);

	// ��ʼ����builder�е�����
	bool BD_InitControlBase(IPropertyControl *pCtrlProp);
	void SetPropertySkinManager(IPropertySkinManager *pMgr);
	// �����δ����һ���ؼ�
	void AppendChildContrl(IControlBase *pCtrl);

	virtual void OnCtrlMessage(int nMsgId, WPARAM wParam, LPARAM lParam);

protected:
	// �����ؼ����ڴ�DC
	CMemoryDC m_CtrlMemDc;
	// ���ŵĴ���
	IWindowBase* m_pOwnerWindowBase;
	// ���ؼ�
	IControlBase* m_pParentCtrl;
	// ��ͼ����
	IUiEngine *m_pUiEngine;
	// �ӿؼ��б�
	CHILD_CTRLS_VEC m_ChildCtrlsVec;

	// �Ƿ����ػ�ؼ�
	bool m_bNeedRedraw;
	// ���Hover״̬
	bool m_bMouseHover;
	// �ؼ�λ�ã����λ��������ڴ��ڵ�λ��
	RECT m_RectInWindow;
	// �ؼ�λ�ã����λ��������ڸ��ؼ���λ��
	RECT m_RectInParentCtrl;
	// �ؼ�������Ϣ
	CONTROL_LAYOUT_INFO m_LayoutInfo;

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
	// base-visible
	IPropertyBool *m_pPropBase_Visible;
	// base-ReceiveMouseMessage
	IPropertyBool *m_pPropBase_RcvMouseMsg;
	// base-enable
	IPropertyBool *m_pPropBase_Enable;
	// base-dragInCtrl
	IPropertyBool *m_pPropBase_DragInCtrl;
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

	// layout-leftspace
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
	
protected:
	// ���Ƶ�ǰ�ؼ�������Ϊ������/���ؼ����ڴ�DC
	virtual void OnPaintControl(CMemoryDC &WndMemDc);

	// �ػ�ؼ�
	virtual void RedrawControl(bool bDrawImmediately = true);
	// �ػ�ؼ�������ػ涯����ʱ���е���
	virtual void RedrawControlInAnimationTimer();
	// �����ӿؼ��������Ի�
	virtual void SetChildCtrlToRedraw();
	// ���ÿؼ����´λ��Ƶ�ʱ���Ƿ���Ҫ�����ػ�
	virtual void SetNeedRedraw(bool bNeedRedraw);
	// ȡ���ӿؼ��б�
	virtual CHILD_CTRLS_VEC* GetChildCtrlsVec();

	// ����Ƿ�Hover
	virtual void SetMouseHover(bool bHover);
	virtual bool IsMousehover();


//////////////////////////////////////////////////////////////////////////
// �����õĿ�������
	// ���ø��ؼ�
	virtual void SetParentControl(IControlBase* pParentCtrl);
	// ȡ�ø��ؼ���ָ�룬���ΪNULL��˵�����ؼ��ǶԻ���
	virtual IControlBase* GetParentControl();

//////////////////////////////////////////////////////////////////////////
// �Ի������
	// ���ŶԻ���
	virtual void SetOwnerWindow(IWindowBase* pWindowsBase);
	virtual IWindowBase* GetOwnerWindow();

protected:

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// �������
public:

	// �ؼ���ʾλ�úʹ�С�����λ��������ڸ��ŵĴ��ڵ�
	virtual void SetCtrlInWindowRect(RECT CtrlWndRct);
	virtual RECT GetCtrlInWindowRect();
	// �ؼ���ʾλ�úʹ�С�����λ��������ڸ��ؼ���
	virtual RECT GetCtrlInControlRect();
	// ȡ�ÿؼ��Ĵ�С
	virtual RECT GetCtrlRect();

	// �Ƿ���������Ϣ
	virtual void SetReceiveMouseMessage(bool bIsReceive);
	virtual bool GetReceiveMouseMessage();

	// �ɼ�����
	virtual void SetVisible(bool bVisible);
	virtual bool IsVisible();

	// ����ڸ��ؼ��Ĳ�����Ϣ
	virtual void SetLayout(CONTROL_LAYOUT_INFO &cliLayoutInfo);
	virtual CONTROL_LAYOUT_INFO GetLayout();

	// �϶��ؼ�����
	virtual void SetDragControl(bool bDrag);
	virtual bool GetDragControl();

	// ��������
	virtual void SetEnable(bool bEnable);
	virtual bool IsEnable();

	//////////////////////////////////////////////////////////////////////////
	// ����3��������������ʾ�����ã�ִ��˳�����ϵ���
	// 1. �����յ������б�
	virtual bool CreateEmptyPropList();
	// 2. ��xml�ļ��ж�ȡ�ؼ�����ʱ������Ҫ��ʼ�����Ե�PropId��PropId��Դ��xml�ļ�
	virtual bool ReadPropFromControlsXml(const char* pszControlId);
	// 2.��Builder���´���һ���ؼ�����Ҫ��ʼ�����Ե�PropId
	virtual bool InitObjectIdByBuilder(const char* pszBaseId);
	// 3. ����Builder��ʾ�õ�����
	virtual bool CreateBuilderShowPropList();

protected:
	//	// 1.1 �������ؼ��д�������
	//	virtual bool CreateDedicationProp() = 0;
	// ����һ������
	IPropertyBase* CreateProperty(IPropertyGroup *pPropGroup, OBJECT_TYPE_ID propType, char *pPropName, char *pPropInfo);

	void InitControlPropetry();
	// 2.��Builder���´���һ���ؼ�����Ҫ��ʼ�����Ե�PropId
	void InitControlPropObjectId(GROUP_PROP_VEC *pPropList);

};
