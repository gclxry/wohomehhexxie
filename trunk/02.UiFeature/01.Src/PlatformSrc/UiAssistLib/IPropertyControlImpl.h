
#pragma once
#include "..\..\Inc\IPropertyControl.h"

class IPropertyControlImpl : public IPropertyControl
{
public:
	IPropertyControlImpl(void);
	virtual ~IPropertyControlImpl(void);

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
private:
	// �Ƿ�ɼ�
	bool m_bVisible;
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
