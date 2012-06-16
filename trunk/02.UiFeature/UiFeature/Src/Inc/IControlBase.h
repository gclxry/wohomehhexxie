
#pragma once
#include "CDrawingImage.h"
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
#include "CTList.h"


class IWindowBase;
class IWindowBaseImpl;
class IUiFeatureKernelImpl;
class IPropertyControl;
class IControlBase;
class IControlManager;


// �ؼ�������Ϣ�������Ϣ�ᷢ�����ڻ��ߴ������ĸ��ؼ���
enum CTRL_MSG_BASE
{
	CMB_BASE = 0x000F0000,
	// �ؼ�������ʼ
	CMB_ANIMATION_BEGIN,
	// �ؼ���������
	CMB_ANIMATION_END,
	// �������쳣
	CMB_ANIMATION_ERROR
};


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
// �̶���С�����Ͼ���
#define TN_CL_G_TOP_MIDDLE				"�̶���С�����Ͼ���"
// �̶���С�����¾���
#define TN_CL_G_BOTTOM_MIDDLE			"�̶���С�����¾���"
// �̶���С���������
#define TN_CL_G_LEFT_MIDDLE				"�̶���С���������"
// �̶���С�����Ҿ���
#define TN_CL_G_RIGHT_MIDDLE			"�̶���С�����Ҿ���"
// �̶���С������
#define TN_CL_G_MID_MIDDLE				"�̶���С������"

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
	// �̶���С�����Ͼ���
	CL_G_TOP_MIDDLE		= 11,
	// �̶���С�����¾���
	CL_G_BOTTOM_MIDDLE	= 12,
	// �̶���С���������
	CL_G_LEFT_MIDDLE	= 13,
	// �̶���С�����Ҿ���
	CL_G_RIGHT_MIDDLE	= 14,
	// �̶���С������
	CL_G_MID_MIDDLE		= 15,
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
class CONTROL_REG : public ListObj
{
public:
	CONTROL_REG();
	~CONTROL_REG();

	IControlManager* pCtrlMgr;
	// ������DLL����
	char strDllName[MAX_PATH + 1];
	// �ؼ����ڵĿؼ�������
	char strCtrlGroupName[MAX_PATH + 1];
	// �ؼ�����
	char strCtrlName[MAX_PATH + 1];
	// �ؼ�˵��
	char strControlInfo[MAX_PATH + 1];
};
// �ڲ���� CONTROL_REG*
typedef CTList CONTROL_REG_TLIST;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �ӿؼ��б�
// typedef vector<IControlBase*>			CHILD_CTRLS_VEC;
// IControlBase* �б�
typedef CTList			CHILD_CTRLS_VEC;

class IControlBase : public IFeatureObject, public ListObj
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

	// �ؼ���ʾλ�úʹ�С�����λ��������ڸ��ŵĴ��ڵ�
	// bRememberToProp:false ����ı䲼����Ϣ
	// bRememberToProp:true ��ı䲼����Ϣ
	virtual void SetWindowRect(RECT CtrlInWndRct, bool bRememberToProp = false);
	virtual RECT GetWindowRect();
	virtual RECT GetClientRect();
	// �ƶ��ؼ����Ὣ���յ�λ����Ϣ��Ϊ������Ϣ
	// ������CtrlInWndRct�ؼ�λ�ڴ��ڵ�λ��
	// bSetChild���Ƿ�ݹ������ӿؼ�
	void SetWindowRectLayoutWithChild(RECT CtrlInWndRct, bool bSetChild = true);

	// �ɼ�����
	virtual void SetVisible(bool bVisible, bool bSetChild = false);
	virtual bool IsVisible();

	// ��������
	virtual void SetEnable(bool bEnable, bool bSetChild = false);
	virtual bool IsEnable();

	// ���ƿؼ���ָ����DC��
	void PrintTo(CDrawingBoard &DstBoard, RECT ToRct);
	// ����ǰ�ؼ��������ӿؼ�������ӡ��һ���ڴ�DC��
	// bPrintWhenInvisible������ؼ�visiable����Ϊfalse�Ƿ�Ҳ��ӡ
	bool PrintToCoverChild(CDrawingBoard &DstBoard, bool bPrintWhenInvisible);

	// �жϲ����еĿؼ��Ƿ�����Լ�
	bool CompareControl(IControlBase* pCtrl);

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

	// �����ؼ�������ɺ��ٻ��Ƶ����ؼ��ϵ�alphaֵ
	void PP_SetControlDrawAlpha(int nCtrlAlpha);
	int PP_GetControlDrawAlpha();

	// �Ƿ�ʹ�� AlphaBlend ����ֱ�ӽ��ؼ����Ƶ�������
	void PP_SetControlAlphaBlendDraw(bool bIsAlphaBlendDraw);
	bool PP_GetControlAlphaBlendDraw();

	// �Ƿ�Ϊ�޻��ƿؼ�
	void PP_SetNoDrawControl(bool bIsNoDrawCtrl);
	bool PP_GetNoDrawControl();

	// ���ö�������
	void PP_SetCtrlAnimationType(DWORD animEffect);
	DWORD PP_GetCtrlAnimationType();

	// ����/ȡ�÷��Ϳؼ���Ϣ��Ŀ��
	void SetControlMessage(IControlMessage* pCtrlMsg);
	IControlMessage* GetControlMessage();

	// ȡ�û��ƿؼ����ڴ�DC
	CDrawingBoard* GetMemoryDc();
	// �����Ը������ݵ���Ա����
	void PropetyValueToMemberValue(bool bCallRefresh, IPropertyBase* pPropBase);

//////////////////////////////////////////////////////////////////////////
	// ��������Ϣ
	virtual void OnVScroll(UINT nSBCode, UINT nPos, IControlBase* pScrollBar) = 0;
	virtual void OnHScroll(UINT nSBCode, UINT nPos, IControlBase* pScrollBar) = 0;
	// ��������Ϣ
	virtual void OnMouseWheel(WPARAM wParam, LPARAM lParam) = 0;

	// �ؼ���Ҫ�����һЩ�Զ������Ϣ����Ϣ�����ϻ��ɶԻ�����������ؼ�����
	virtual void OnCtrlNotify(int nMsgId, WPARAM wParam, LPARAM lParam) = 0;

	// �����ؼ����ڴ���һ������
	IPropertyBase* CreatePropetry(IPropertyGroup* pPropGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo);

	// ��һ���ؼ������������ӿؼ���ʱ��ϵͳ�ᷢ�ʹ���������ӿؼ�����Ϣ
	void CreateSubControl(bool bIsCreate);
	// ���ø��ؼ�
	void SetParentControl(IControlBase* pParentCtrl);
	// ���ÿؼ��Ĳ��ַ�ʽ
	void SetControlLayoutType(CONTROL_LAYOUT CtrlLayout);
	// ���������ڵ�dll
	void SetControlDllManager(IControlManager* pOwnerCtrlDllMgr);
	IControlManager* GetControlDllManager();

	// �Ƿ�ʹ����ʱ�ڴ����
	bool PP_IsUseTempDrawMem();

protected:
	// �����ӿؼ��������Ի�
	void SetChildCtrlToRedraw();

	// �����ؼ����ڴ��������Լ��Ŀؼ�����
	// bIsNewCtrl��trueʱ˵����Builder���ã��´���һ���ؼ�����Ҫ��ʼ�����Եĸ���Ĭ��ֵ
	// false��˵������Ƥ�����Ѿ���ʼ����ϣ����Դ�����ϵ�ʱ�򣬴�xml�ж�ȡ������ֵ�Ѿ���ֵ����ˣ������ٳ�ʼ��������xml�е�ֵ�ᱻ���
	virtual bool CreateControlPropetry(bool bIsNewCtrl) = 0;
	// ���ƿؼ��Ķ����������Ҫ����ˢ�½��棬����true�����򷵻�false
	// �˺����ɶ�ʱ��������ÿ100���봥��һ��
	virtual bool OnDrawAnimation() = 0;
	// ��ʱ��
	virtual void OnTimer(UINT nTimerId) = 0;
	// ��ʼ���ؼ�
	virtual void OnCreate() = 0;
	// �ؼ���ʼ�����
	virtual void OnFinalCreate() = 0;
	// ��һ���ؼ������������ӿؼ���ʱ��ϵͳ�ᷢ�ʹ���������ӿؼ�����Ϣ
	virtual void OnCreateSubControl(bool bIsCreate) = 0;
	// �����Ի�������Ի����ϵĿؼ�����ʼ�����
	virtual void OnWindowFinalCreate() = 0;
	// �����Ի��򼴽��ر�
	virtual void OnWindowClose() = 0;
	// Builderˢ�����ԣ��˺�����ֻҪ���¼��ؿؼ����Լ���
	virtual void OnBuilderRefreshProp(IPropertyBase* pPropBase) = 0;
	// ���ٿؼ�
	virtual void OnDestroy() = 0;
	// ���ƿؼ�
	virtual void OnPaint(CDrawingBoard &DrawBoard) = 0;
	// ������
	virtual void OnMouseEnter(POINT pt) = 0;
	// ����Ƴ�
	virtual void OnMouseLeave(POINT pt) = 0;
	// ����ƶ�
	virtual void OnMouseMove(POINT pt) = 0;
	// ���������
	virtual void OnLButtonDown(POINT pt) = 0;
	// ������̧��
	virtual void OnLButtonUp(POINT pt) = 0;
	// ������˫��
	virtual void OnLButtonDbClick(POINT pt) = 0;
	// ����ڿؼ��ڲ��϶�
	virtual void OnMouseDragging(POINT pt) = 0;
	// ����϶�����������̧����ꡣpDragCtrl����ק��Դ�ؼ�
	virtual void OnDragStop(IControlBase* pDragCtrl, POINT pt, WPARAM wParam, LPARAM lParam) = 0;
	// ȡ�ÿؼ�֮����ק�����ݲ������ڴ����� OnDragStop ��Ϣ��ᱻ����
	virtual void OnGetDragParam(WPARAM& wParam, LPARAM& lParam) = 0;
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
	// ����Ƿ������˿ؼ�ָ����RGN����Ĭ�Ϸ���true�������ؼ�����RGN����
	virtual bool OnCheckMouseInRgn(POINT pt) = 0;
	// ���ÿؼ����
	virtual IPropertyCursor* OnSetCursor(POINT pt) = 0;
	// �յ���Ҫ��ջ��ƻ������Ϣ
	virtual void OnClearDrawMemoryDc() = 0;

//////////////////////////////////////////////////////////////////////////
	// �û��Զ���ǿ������ʼ
	virtual void OnUserDefHighAnimationBegin() = 0;
	// �û��Զ���ǿ�������ƽӿڣ�hWndDc���ؼ����ڵĴ���DC
	virtual void OnUserDefHighAnimationDraw(HDC hWndDc) = 0;
	// �û��Զ���ǿ��������
	virtual void OnUserDefHighAnimationEnd() = 0;
//////////////////////////////////////////////////////////////////////////

	// ���ں�ע��һ����Ҫȡ������Ϣ
	void RegisterControlMessage(int nMsgId);
	void UnRegisterControlMessage(int nMsgId);
	// ������Ϣ:Send��ʽ
	LRESULT SendMessage(UINT nMsgId, WPARAM wParam, LPARAM lParam);
	// ������Ϣ:Post��ʽ
	bool PostMessage(UINT nMsgId, WPARAM wParam, LPARAM lParam);
	// ���Ŷ�����Ϣ
	void OnCtrlAnimation(WPARAM wParam, LPARAM lParam);
	// ׼���ؼ�����
	bool ControlAnimationReady();

private:
	// �����ؼ�����
	void CreateCtrlAllPropetry(bool bIsNewCtrl);
	IPropertyBase* CreateCtrlOnePropetry(IPropertyGroup* pGroup, OBJECT_TYPE_ID propType, const char* pszPropName, const char *pszPropInfo);

	// ��ʼ����builder�е�����
	bool InitControlPropetry(IPropertyControl *pCtrlProp, bool bIsNewCtrl);
	void SetPropertySkinManager(IPropertySkinManager *pMgr);
	// �����δ����һ���ؼ�
	void AppendChildContrl(IControlBase *pCtrl);

	void SetUiEngine(IUiEngine *pUiEngine);
	// ���ŶԻ���
	void SetOwnerWindow(IWindowBase* pWindowsBase);

	// ����Ƿ�Hover
	void SetMouseHover(bool bHover);

	// �˺����ɴ��ڵ��ã����Ƶ�ǰ�ؼ�������Ϊ������/���ؼ����ڴ�DC
	virtual void OnPaintControl(CDrawingBoard &WndMemDc, RECT ActiveDrawRct);

	// �ӳ�Ա�����������ݵ�����
	void MemberValueToPropetyValue();
	// ���¼����ӿؼ���λ�úʹ�С
	void ResetChildPropetyValueToMemberValue(IControlBase* pParentCtrl, bool bCallRefresh, IPropertyBase* pPropBase);
	// �ؼ���ʾλ�úʹ�С������ݲ�����Ϣ�����޸��ӿؼ���λ��
	void SetChildControlLayoutPostion(CHILD_CTRLS_VEC* pVec);
	// �ݹ��ӡ�ӿؼ���һ���ڴ�DC��
	bool ChildPrint(CHILD_CTRLS_VEC *pChildCtrlsVec, CDrawingBoard& DstBoard, POINT offsetPt, bool bPrintWhenInvisible);

	// ������Ե��������ĸ��ؼ�����Ϣ
	void ClearPropertyOwner();
	// ��ջ��ƻ���
	void ClearDrawMemoryDc();

protected:
	// ������Ϣ��Ŀ��
	IControlMessage* m_pSendMsgCtrl;

	// �ӿؼ��б�
	CHILD_CTRLS_VEC m_ChildCtrlsVec;

	// �Ƿ����ػ�ؼ�
	bool m_bNeedRedraw;
	// ���Hover״̬
	bool m_bMouseHover;
	// �ؼ�λ�ã����λ��������ڴ��ڵ�λ��
	RECT m_RectInWindow;

	// �����ؼ����ڴ�DC
	CDrawingImage m_CtrlMemDc;
	// �����ڴ�DC
	CDrawingImage m_CtrlAnimationMemDc;
	// �����Ƿ�ʼ
	bool m_bIsCtrlAnimationBegin;

	// ���ŵĴ���
	IWindowBase* m_pWindowBase;
	// ���ؼ�
	IControlBase* m_pParentCtrl;
	// ��ͼ����
	IUiEngine *m_pUiEngine;

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

	// base-Draw
	IPropertyGroup *m_pPropBase_DrawGroup;
	// base-Draw-NoDrawControl
	IPropertyBool *m_pPropBase_NoDrawCtrl;
	// base-Draw-AlphaBlendDraw
	IPropertyBool *m_pPropBase_Draw_AlphaBlendDraw;
	// base-Draw-DrawAlpha
	IPropertyInt *m_pPropBase_Draw_DrawAlpha;
	// base-Draw-TempDrawMem
	IPropertyBool *m_pPropBase_Draw_TempDrawMem;

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

	// base-Animation
	IPropertyGroup *m_pPropBase_AnimationGroup;
	// Animation-AnimationType
	IPropertyComboBox *m_pPropBase_AnimationType;
	// Animation-FrameTimeSpin
	IPropertyInt *m_pPropBase_Animation_FrameTime;
	// Animation-Front
	IPropertyComboBox *m_pPropBase_Animation_Direction;

	// Group:CtrlDefs
	IPropertyGroup* m_pPropGroupCtrlDefs;

private:
	// Builder ר�ã���ʾ�ؼ��ı߿��8������
	FANGKUAI_8 m_BD_FangKuai8;
	IControlManager* m_pOwnerCtrlDllMgr;
};
