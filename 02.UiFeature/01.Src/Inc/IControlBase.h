
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

class IWindowBase;
class IWindowBaseImpl;
class IUiFeatureKernelImpl;
class IPropertyControl;
class IControlBase;

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
	friend class IUiFeatureKernelImpl;

public:
	IControlBase();
	virtual ~IControlBase();

	// �õ���Builder����ʾ������8�������λ��
	virtual FANGKUAI_8* BD_GetFangKuai8Rect();

	// ȡ�ø��ؼ���ָ�룬���ΪNULL��˵�����ؼ��ǶԻ���
	IControlBase* GetParentControl();
	IWindowBase* GetOwnerWindow();

	// ȡ���ӿؼ��б�
	CHILD_CTRLS_VEC* GetChildControlsVec();
	// ȡ���ӿؼ��������б�Layout.xml �еĲ���
	PROP_CONTROL_VEC* GetChildPropControlVec();

	// �ػ�ؼ�
	void RedrawControl(bool bDrawImmediately = true);
	// �ػ�ؼ�������ػ涯����ʱ���е���
	void RedrawControlInAnimationTimer();


	// �ؼ���ʾλ�úʹ�С�����λ��������ڸ��ŵĴ��ڵ�
	void SetCtrlInWindowRect(RECT CtrlWndRct);
	RECT GetCtrlInWindowRect();
	// �ؼ���ʾλ�úʹ�С�����λ��������ڸ��ؼ���
	RECT GetCtrlInControlRect();
	// ȡ�ÿؼ��Ĵ�С
	RECT GetCtrlRect();

	const char * PP_GetControlObjectName();

	// �Ƿ���������Ϣ
	void SetReceiveMouseMessage(bool bIsReceive);
	bool GetReceiveMouseMessage();

	// �ɼ�����
	void SetVisible(bool bVisible, bool bSetChild = true);
	bool IsVisible();

	// �϶��ؼ�����
	void SetDragInControl(bool bDrag);
	bool GetDragInControl();

	// ��������
	void SetEnable(bool bEnable, bool bSetChild = true);
	bool IsEnable();

	// ����ڸ��ؼ��Ĳ�����Ϣ
	void SetLayout(CONTROL_LAYOUT_INFO &cliLayoutInfo);
	CONTROL_LAYOUT_INFO GetLayout();

	// ����Ƿ�Hover
	bool IsMousehover();

	IPropertyGroup* PP_GetControlPropetryGroup();
	IPropertyControl *PP_GetControlPropetry();

protected:
	// �����ӿؼ��������Ի�
	void SetChildCtrlToRedraw();
	// ���ÿؼ����´λ��Ƶ�ʱ���Ƿ���Ҫ�����ػ�
	void SetNeedRedraw(bool bNeedRedraw);

protected:
	// �����ؼ����ڴ���һ������
	IPropertyBase* CreatePropetry(OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo);
	// �����ؼ����ڴ��������Լ��Ŀؼ�����
	// bNeedSetDftProp��trueʱ˵����Builder���ã��´���һ���ؼ�����Ҫ��ʼ�����Եĸ���Ĭ��ֵ
	// false��˵������Ƥ�����Ѿ���ʼ����ϣ����Դ�����ϵ�ʱ�򣬴�xml�ж�ȡ������ֵ�Ѿ���ֵ����ˣ������ٳ�ʼ��������xml�е�ֵ�ᱻ���
	virtual bool CreateControlPropetry(bool bNeedSetDftProp) = 0;
	// ��ʼ���ؼ�
	virtual void OnCreate() = 0;
	// �ؼ���ʼ�����
	virtual void OnFinalCreate() = 0;
	// ���ٿؼ�
	virtual void OnDestroy() = 0;
	// ���ƿؼ�
	virtual void OnPaint() = 0;
	// �����ؼ��������Ϣ
	virtual void OnCtrlMessage(int nMsgId, WPARAM wParam, LPARAM lParam) = 0;
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
	// ����϶��ؼ�
	virtual void OnMouseDragInCtrl(POINT pt) = 0;
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


private:
	// �����ؼ�����
	void CreateCtrlAllPropetry(bool bNeedSetDftProp);
	IPropertyBase* CreateCtrlOnePropetry(IPropertyGroup* pGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo);

	// ��ʼ����builder�е�����
	bool BD_InitControlBase(IPropertyControl *pCtrlProp, bool bNeedSetDftProp);
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
	virtual void OnPaintControl(CDrawingBoard &WndMemDc);

protected:
	// �����ؼ����ڴ�DC
	CDrawingBoard m_CtrlMemDc;
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
	
private:
	// Builder ר�ã���ʾ�ؼ��ı߿��8������
	FANGKUAI_8 m_BD_FangKuai8;

protected:

	//////////////////////////////////////////////////////////////////////////
	// ����3��������������ʾ�����ã�ִ��˳�����ϵ���
	// 1. �����յ������б�
	// 2. ��xml�ļ��ж�ȡ�ؼ�����ʱ������Ҫ��ʼ�����Ե�PropId��PropId��Դ��xml�ļ�
	virtual bool ReadPropFromControlsXml(const char* pszControlId);
	// 2.��Builder���´���һ���ؼ�����Ҫ��ʼ�����Ե�PropId
	virtual bool InitObjectIdByBuilder(const char* pszBaseId);
	// 3. ����Builder��ʾ�õ�����
	virtual bool CreateBuilderShowPropList();

protected:

	// 2.��Builder���´���һ���ؼ�����Ҫ��ʼ�����Ե�PropId
	void InitControlPropObjectId(GROUP_PROP_VEC *pPropList);

};
