
#pragma once
#include "CMemoryDC.h"
#include "IFeatureObject.h"
#include "IUiEngine.h"
#include "IPropertySkinManager.h"

class IWindowBase;
class IWindowBaseImpl;
class IPropertyControl;
class IControlBase;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ǰ�ؼ�����ڸ��ؼ��Ĳ�������
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
	CM_EnterRun
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �ӿؼ��б�
typedef vector<IControlBase*>			CHILD_CTRLS_VEC;

class IControlBase : public IFeatureObject
{
	friend class IWindowBaseImpl;
public:
	IControlBase();
	virtual ~IControlBase();


	
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

//////////////////////////////////////////////////////////////////////////
// �ؼ���Ϣ����
	virtual void OnControlMessage(CONTROL_MSG nMsgId, WPARAM wParam, LPARAM lParam);
	// ��ʼ���ؼ�
	virtual void OnCreate();
	// �ؼ���ʼ�����
	virtual void OnFinalCreate();
	// Builderˢ������
	virtual void OnRefreshProp();
	// ������
	virtual void OnMouseEnter(POINT pt);
	// ����Ƴ�
	virtual void OnMouseLeave();
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
	virtual void OnSize();
	// ���ƿؼ�
	virtual void OnPaint();
	// �ƶ����ڿ�ʼ
	virtual void OnEnterSizeMove();
	// �ƶ����ڽ���
	virtual void OnExitSizeMove();
	// ���ٿؼ�
	virtual void OnDestroy();
	// �ؼ�ȡ�ý��㣬ͨ��Tab����ת������ؼ�
	virtual void OnSetFocus();
	// �ؼ�ʧȥ����
	virtual void OnKillFocus();
	// �ؼ�ȡ�ü���������Ϣ
	virtual void OnChar(WPARAM wParam, LPARAM lParam);
	// ���ܵ�Ĭ�ϻس�����ִ�пؼ�����
	virtual void OnEnterRun();

protected:
	// �����ؼ����ڴ�DC
	CMemoryDC m_CtrlMemDc;
	// ���ŵĴ���
	IWindowBase* m_pParentWindowBase;
	// �ӿؼ��б�
	CHILD_CTRLS_VEC m_ChildCtrlsVec;
	// �Ƿ����ػ�ؼ�
	bool m_bNeedRedraw;
	// ��ͼ����
	IUiEngine *m_pUiEngine;
	// ���Hover״̬
	bool m_bMouseHover;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// �������
public:
	// ���ø����ؼ�
	virtual void SetPropertySkinManager(IPropertySkinManager *pMgr);

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

	// �ؼ����ƣ�Ψһʶ�𴰿ڵı�־
	virtual void PP_SetObjectName(char *pCtrlName);
	virtual const char* PP_GetObjectName();

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

	// �洢Builder�ɼ������������б�Ҳ���ǵ�ǰ�ؼ��������б�
	GROUP_PROP_VEC m_ControlPropList;
	// �����ؼ�
	IControlBase *m_pBaseCtrl;
	IPropertySkinManager *m_pSkinPropMgr;

	// �Ƿ�ɼ�
	bool m_bVisible;
	bool m_bEnable;
	// �Ƿ���������Ϣ
	bool m_bIsReceiveMouseMsg;
	// �ؼ�λ�ã����λ��������ڴ��ڵ�λ��
	RECT m_RectInWindow;
	// �ؼ�λ�ã����λ��������ڸ��ؼ���λ��
	RECT m_RectInParentCtrl;
	// �ؼ�������Ϣ
	CONTROL_LAYOUT_INFO m_LayoutInfo;
	// �ؼ�����
	string m_strCtrlName;
	// �϶��ؼ�
	bool m_bDragCtrl;
};
