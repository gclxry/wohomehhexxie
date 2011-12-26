//////////////////////////////////////////////////////////////////////////
// һ���ؼ�������

#pragma once
#include "IFeatureObject.h"
#include "IPropertyBase.h"
#include "IPropertyGroup.h"
#include "IPropertySkinManager.h"

class IControlBase;
class IPropertySkinManager;
class IPropertyControlManager;

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


// �ӿؼ��б�
typedef map<string, IPropertyControlManager*>			CHILD_CTRL_PROP_MAP;

class IPropertyControlManager : public IFeatureObject
{
public:
	IPropertyControlManager(void);
	virtual ~IPropertyControlManager(void);

	// ���ؼ�����
	void SetParentPropertyControl(IPropertyControlManager *pParent);
	virtual IPropertyControlManager* GetParentPropertyControl();

	// ���ø����ؼ�
	virtual void SetControlBase(IControlBase *pCtrl);
	virtual IControlBase* GetControlBase();
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
	virtual void SetName(char *pCtrlName);
	virtual const char* GetName();

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

private:
	// 2.��Builder���´���һ���ؼ�����Ҫ��ʼ�����Ե�PropId
	void InitControlPropObjectId(GROUP_PROP_VEC *pPropList);

private:
	// �洢Builder�ɼ������������б�Ҳ���ǵ�ǰ�ؼ��������б�
	GROUP_PROP_VEC m_ControlPropList;
	// �����ؼ�
	IControlBase *m_pBaseCtrl;
	IPropertySkinManager *m_pSkinPropMgr;
	IPropertyControlManager* m_pParentPropertyControl;

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
