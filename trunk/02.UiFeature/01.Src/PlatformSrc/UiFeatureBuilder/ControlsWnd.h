
#pragma once
#include "FeatureControlList.h"
#include "UiFeatureControl.h"


struct CONTROL_LIST_ITEM 
{
	// ������DLL����
	string	strDllName;
	// �ؼ�����
	string	strCtrlName;
	// �ؼ���Builder��ʾ��ͼƬ����icon�ļ�����Щ�ļ������ControlsResĿ¼�£�Ϊ����ʹ��Builder�е�Ĭ�ϵ�ͼ��
	string	strControlImg;
};
// KEY: strCtrlName
typedef map<string, CONTROL_LIST_ITEM>	CONTROL_LIST_ITEM_MAP;

struct CONTROL_LIST_GROUP
{
	// �ؼ����ڵĿؼ�������
	string strCtrlGroupName;
	CONTROL_LIST_ITEM_MAP ItemMap;
};
// KEY:strCtrlGroupName
typedef map<string, CONTROL_LIST_GROUP>	CONTROL_LIST_GROUP_MAP;


class CControlsToolBar : public CMFCToolBar
{
public:
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CControlsWnd : public CDockablePane
{
// ����
public:
	CControlsWnd();
	virtual ~CControlsWnd();

	void AdjustLayout();

	// ���ÿؼ��б�
	void SetControlList(CONTROL_REG_MAP* pRegControlMap);

private:
	void SetCurrentSelectList(string strGroupName);

private:
	CComboBox m_wndObjectCombo;
	CFeatureControlList m_wndCtrlList;

	CONTROL_LIST_GROUP_MAP	m_ListGroupMap;

// ʵ��
public:

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGroupSelchangeCombo();

	DECLARE_MESSAGE_MAP()
};

