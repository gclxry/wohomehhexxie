
#pragma once
#include "..\..\Inc\IPropertyControl.h"
#include "..\..\Inc\IPropertyGroup.h"
#include "..\..\Inc\IPropertySkinManager.h"

class IPropertyControlImpl : public IPropertyControl
{
public:
	IPropertyControlImpl(void);
	virtual ~IPropertyControlImpl(void);

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
	// 2. ��xml�ļ����ؼ�����
	virtual bool ReadPropFromControlsXml(const char* pszControlId);
	// 3. ����Builder��ʾ�õ�����
	virtual bool CreateBuilderShowPropList();

protected:
//	// 1.1 �������ؼ��д�������
//	virtual bool CreateDedicationProp() = 0;
	// ����һ������
	IPropertyBase* CreateProperty(IPropertyGroup *pPropGroup, PROP_TYPE propType, UINT nPropId, char *pPropName, char *pPropInfo);

private:

private:
	// �洢Builder�ɼ������������б�
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
