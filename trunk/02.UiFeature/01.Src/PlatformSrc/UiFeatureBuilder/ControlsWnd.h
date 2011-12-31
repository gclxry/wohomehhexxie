
#pragma once
#include "FeatureControlList.h"
#include "UiFeatureControl.h"
#include "..\..\Inc\IControlBase.h"

struct CONTROL_LIST_GROUP
{
	// 控件所在的控件组名称
	string strCtrlGroupName;
	CONTROL_REG_MAP ItemMap;
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
// 构造
public:
	CControlsWnd();
	virtual ~CControlsWnd();

	void AdjustLayout();

	// 设置控件列表
	void SetControlList(CONTROL_REG_MAP* pRegControlMap);

private:
	void SetCurrentSelectList(string strGroupName);

private:
	CComboBox m_wndObjectCombo;
	CFeatureControlList m_wndCtrlList;

	CONTROL_LIST_GROUP_MAP	m_ListGroupMap;

// 实现
public:

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGroupSelchangeCombo();

	DECLARE_MESSAGE_MAP()
};

