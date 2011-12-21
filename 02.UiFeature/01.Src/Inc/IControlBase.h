
#pragma once
#include "IPropertyControl.h"
#include "..\..\Inc\CMemoryDC.h"

class IWindowBase;

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
};
// ��������CONTROL_REG::strCtrlName��
typedef map<string, CONTROL_REG*>	CONTROL_REG_MAP;


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
class IControlBase;
typedef vector<IControlBase*>			CHILD_CTRLS_VEC;

class IControlBase
{
public:
	// ���Ƶ�ǰ�ؼ�������Ϊ������/���ؼ����ڴ�DC
	virtual void OnPaintControl(CMemoryDC &WndMemDc) = 0;

	// �ػ�ؼ�
	virtual void RedrawControl(bool bDrawImmediately = true) = 0;
	// �ػ�ؼ�������ػ涯����ʱ���е���
	virtual void RedrawControlInAnimationTimer() = 0;
	// �����ӿؼ��������Ի�
	virtual void SetChildCtrlToRedraw() = 0;
	// ���ÿؼ����´λ��Ƶ�ʱ���Ƿ���Ҫ�����ػ�
	virtual void SetNeedRedraw(bool bNeedRedraw) = 0;
	// ȡ���ӿؼ��б�
	virtual CHILD_CTRLS_VEC* GetChildCtrlsVec() = 0;
	// ȡ�ÿؼ��Ļ������ԣ����������Կؼ���չ��˽������
	virtual IPropertyControl* GetControlBaseProp() = 0;

	// ����Ƿ�Hover
	virtual void SetMouseHover(bool bHover) = 0;
	virtual bool IsMousehover() = 0;

//////////////////////////////////////////////////////////////////////////
// �����õĿ�������
	// ���ø��ؼ�
	virtual void SetParentControl(IControlBase* pParentCtrl) = 0;
	// ȡ�ø��ؼ���ָ�룬���ΪNULL��˵�����ؼ��ǶԻ���
	virtual IControlBase* GetParentControl() = 0;

//////////////////////////////////////////////////////////////////////////
// �Ի������
	// ���ŶԻ���
	virtual void SetOwnerWindow(IWindowBase* pWindowsBase) = 0;
	virtual IWindowBase* GetOwnerWindow() = 0;

//////////////////////////////////////////////////////////////////////////
// �ؼ���Ϣ����
	virtual void OnControlMessage(CONTROL_MSG nMsgId, WPARAM wParam, LPARAM lParam) = 0;
	// ��ʼ���ؼ�
	virtual void OnCreate() = 0;
	// �ؼ���ʼ�����
	virtual void OnFinalCreate() = 0;
	// Builderˢ������
	virtual void OnRefreshProp() = 0;
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
	virtual void OnMouseDrag(POINT pt) = 0;
	// ����Ҽ����
	virtual void OnRButtonDown(POINT pt) = 0;
	// �ƶ������ÿؼ�λ��
	virtual void OnSize() = 0;
	// ���ƿؼ�
	virtual void OnPaint() = 0;
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
	virtual void OnChar(WPARAM wParam, LPARAM lParam) = 0;
	// ���ܵ�Ĭ�ϻس�����ִ�пؼ�����
	virtual void OnEnterRun() = 0;
};

