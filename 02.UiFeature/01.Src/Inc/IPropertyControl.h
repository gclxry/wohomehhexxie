//////////////////////////////////////////////////////////////////////////
// һ���ؼ�������

#pragma once
#include "IFeatureObject.h"

class IControlBase;
class IPropertySkinManager;

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

class IPropertyControl : public IFeatureObject
{
public:
	// ���ø����ؼ�
	virtual void SetControlBase(IControlBase *pCtrl) = 0;
	virtual IControlBase* GetControlBase() = 0;
	virtual void SetPropertySkinManager(IPropertySkinManager *pMgr) = 0;

	// �ؼ���ʾλ�úʹ�С�����λ��������ڸ��ŵĴ��ڵ�
	virtual void SetCtrlInWindowRect(RECT CtrlWndRct) = 0;
	virtual RECT GetCtrlInWindowRect() = 0;
	// �ؼ���ʾλ�úʹ�С�����λ��������ڸ��ؼ���
	virtual RECT GetCtrlInControlRect() = 0;
	// ȡ�ÿؼ��Ĵ�С
	virtual RECT GetCtrlRect() = 0;

	// �ؼ����ƣ�Ψһʶ�𴰿ڵı�־
	virtual void SetName(char *pCtrlName) = 0;
	virtual const char* GetName() = 0;

	// �Ƿ���������Ϣ
	virtual void SetReceiveMouseMessage(bool bIsReceive) = 0;
	virtual bool GetReceiveMouseMessage() = 0;

	// ����ڸ��ؼ��Ĳ�����Ϣ
	virtual void SetLayout(CONTROL_LAYOUT_INFO &cliLayoutInfo) = 0;
	virtual CONTROL_LAYOUT_INFO GetLayout() = 0;

	// �ɼ�����
	virtual void SetVisible(bool bVisible) = 0;
	virtual bool IsVisible() = 0;

	// ��������
	virtual void SetEnable(bool bEnable) = 0;
	virtual bool IsEnable() = 0;

	// �϶��ؼ�����
	virtual void SetDragControl(bool bDrag) = 0;
	virtual bool GetDragControl() = 0;

//////////////////////////////////////////////////////////////////////////
	// ����3��������������ʾ�����ã�ִ��˳�����ϵ���
	// 1. �����յ������б�
	virtual bool CreateEmptyPropList() = 0;
	// 2.��Builder���´���һ���ؼ�����Ҫ��ʼ�����Ե�PropId
	virtual bool InitObjectIdByBuilder(const char* pszBaseId) = 0;
	// 2. ��xml�ļ��ж�ȡ�ؼ�����ʱ������Ҫ��ʼ�����Ե�PropId��PropId��Դ��xml�ļ�
	virtual bool ReadPropFromControlsXml(const char* pszControlId) = 0;
	// 3. ����Builder��ʾ�õ�����
	virtual bool CreateBuilderShowPropList() = 0;
};
