
#include "stdafx.h"

#include "ControlsWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "UiFeatureBuilder.h"

// 显示控件名称的列
#define CONTROL_NAME_COLUMN					(1)

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

CControlsWnd::CControlsWnd()
{

}

CControlsWnd::~CControlsWnd()
{
}

BEGIN_MESSAGE_MAP(CControlsWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(ID_VIEW_CONTROLSWND_COMBO, &CControlsWnd::OnGroupSelchangeCombo)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar 消息处理程序

void CControlsWnd::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
		return;

	CRect rectClient,rectCombo;
	GetClientRect(rectClient);

	m_wndObjectCombo.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), 200, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndObjectCombo.GetWindowRect(&rectCombo);

//////////////////////////////////////////////////////////////////////////
	m_wndCtrlList.SetWindowPos(NULL, rectClient.left, rectClient.top + rectCombo.Height(), rectClient.Width(), rectClient.Height() - rectCombo.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
}

int CControlsWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 创建组合:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndObjectCombo.Create(dwViewStyle, rectDummy, this, ID_VIEW_CONTROLSWND_COMBO))
	{
		TRACE0("未能创建控件分组下拉框 \n");
		return -1;      // 未能创建
	}
	m_wndObjectCombo.SetFont(CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT)));

//////////////////////////////////////////////////////////////////////////
	if (!m_wndCtrlList.Create(WS_CHILD | WS_VISIBLE, rectDummy, this, ID_VIEW_CONTROLSWND_LIST))
	{
		TRACE0("未能创建控件列表 \n");
		return -1;      // 未能创建
	}
	m_wndCtrlList.SetFont(CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT)));

	// 设置显示模式：report
	m_wndCtrlList.SetView(1);

	m_wndCtrlList.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_wndCtrlList.ModifyStyle(0, LVS_SINGLESEL | LVS_SHOWSELALWAYS);

	m_wndCtrlList.InsertColumn(0, _T("#"), LVCFMT_LEFT, 30);
	m_wndCtrlList.InsertColumn(CONTROL_NAME_COLUMN, _T("控件名称"), LVCFMT_LEFT, 80);
	m_wndCtrlList.InsertColumn(CONTROL_NAME_COLUMN + 1, _T("控件说明"), LVCFMT_LEFT, 160);

	AdjustLayout();
	return 0;
}

void CControlsWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

// 设置控件列表
void CControlsWnd::SetControlList(CONTROL_REG_MAP* pRegControlMap)
{
	USES_CONVERSION;
	if (pRegControlMap == NULL)
		return;

	for (CONTROL_REG_MAP::iterator pCtrlItem = pRegControlMap->begin(); pCtrlItem != pRegControlMap->end(); pCtrlItem++)
	{
		CONTROL_REG RegCtrl = pCtrlItem->second;

		CONTROL_LIST_GROUP_MAP::iterator pGroup = m_ListGroupMap.find(RegCtrl.strCtrlGroupName);
		if (pGroup == m_ListGroupMap.end())
		{
			// 新组别
			CONTROL_LIST_GROUP Group;
			Group.ItemMap.clear();
			Group.strCtrlGroupName = RegCtrl.strCtrlGroupName;
			m_ListGroupMap.insert(pair<string, CONTROL_LIST_GROUP>(RegCtrl.strCtrlGroupName, Group));

			pGroup = m_ListGroupMap.find(RegCtrl.strCtrlGroupName);
			if (pGroup == m_ListGroupMap.end())
				continue;

			m_wndObjectCombo.AddString(A2W(RegCtrl.strCtrlGroupName.c_str()));
		}

		CONTROL_LIST_GROUP &Group = pGroup->second;
		CONTROL_REG_MAP::iterator pItem = Group.ItemMap.find(RegCtrl.strCtrlName);
		if (pItem != Group.ItemMap.end())
			continue;

		Group.ItemMap.insert(pair<string, CONTROL_REG>(RegCtrl.strCtrlName, RegCtrl));
	}

	CONTROL_LIST_GROUP_MAP::iterator pGroup = m_ListGroupMap.begin();
	if (pGroup != m_ListGroupMap.end())
	{
		m_wndObjectCombo.SetCurSel(0);
		CONTROL_LIST_GROUP &Group = pGroup->second;
		SetCurrentSelectList(Group.strCtrlGroupName);
	}
}

void CControlsWnd::SetCurrentSelectList(string strGroupName)
{
	USES_CONVERSION;

	m_wndCtrlList.DeleteAllItems();
	if (strGroupName.size() <= 0 || m_ListGroupMap.size() <= 0)
		return;

	CONTROL_LIST_GROUP_MAP::iterator pGroup = m_ListGroupMap.find(strGroupName);
	if (pGroup == m_ListGroupMap.end())
		return;

	int nCtns = 0;
	CONTROL_LIST_GROUP &Group = pGroup->second;
	for (CONTROL_REG_MAP::iterator pCtrlItem = Group.ItemMap.begin(); pCtrlItem != Group.ItemMap.end(); pCtrlItem++)
	{
		CONTROL_REG& Item = pCtrlItem->second;

		CString strNo;
		strNo.Format(_T("%d"), nCtns + 1);
		m_wndCtrlList.InsertItem(nCtns, strNo);
		m_wndCtrlList.SetItemText(nCtns, CONTROL_NAME_COLUMN, A2W(Item.strCtrlName.c_str()));
		m_wndCtrlList.SetItemText(nCtns, CONTROL_NAME_COLUMN + 1, A2W(Item.strControlInfo.c_str()));
		nCtns++;
	}
}

void CControlsWnd::OnGroupSelchangeCombo()
{
	USES_CONVERSION;

	CString strGroup(_T(""));
	int nSel = m_wndObjectCombo.GetCurSel();
	m_wndObjectCombo.GetLBText(nSel, strGroup);

	string strNewGroup(W2A(strGroup));
	SetCurrentSelectList(strNewGroup);
}
