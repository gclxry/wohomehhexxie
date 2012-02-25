
#include "StdAfx.h"
#include "FontBaseNameList.h"
#include "resource.h"
#include "UiFeatureBuilder.h"
#include "..\..\Inc\UiFeatureDefs.h"

CFontBaseNameList::CFontBaseNameList()
{
	m_pFontBaseMap = NULL;
	m_pParentFontProp = NULL;
}

CFontBaseNameList::~CFontBaseNameList()
{
}

COLORREF CFontBaseNameList::OnGetCellBkColor(int nRow, int nColum)
{
	return(nRow % 2) == 0 ? RGB(255, 255, 255) : RGB(255, 255, 255);
}

void CFontBaseNameList::OnSelectItem()
{
	if (m_pParentFontProp == NULL)
		return;

	if (m_nSelectItem <= 0)
	{
		// 没有选择
		m_pParentFontProp->SetFontBaseProp(NULL);
		m_pParentFontProp->SetRelevancyPropName(NULL);
	}
	else
	{
		IPropertyFontBase* pFontBaseProp = (IPropertyFontBase*)(this->GetItemData(m_nSelectItem));
		m_pParentFontProp->SetFontBaseProp(pFontBaseProp);
		m_pParentFontProp->SetRelevancyPropName((char*)pFontBaseProp->GetObjectName());
	}
}

void CFontBaseNameList::InitFontBaseNameList(IPropertyFont* pParentCursorProp, ONE_RESOURCE_PROP_MAP* pFontBaseMap)
{
	m_pParentFontProp = pParentCursorProp;
	if (pFontBaseMap == NULL)
		return;

	USES_CONVERSION;
	this->DeleteAllItems();
	m_pFontBaseMap = pFontBaseMap;

	this->SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	this->ModifyStyle(0, LVS_SINGLESEL | LVS_SHOWSELALWAYS);
	this->InsertColumn(0, _T("#"), LVCFMT_LEFT, 30);
	this->InsertColumn(1, _T("名称"), LVCFMT_LEFT, 100);

	this->InsertItem(0, _T("#"));
	this->SetItemText(0, 1, _T("点我设置FONT属性为空哦"));
	this->SetItemData(0, NULL);

	int nNo = 1;
	for (ONE_RESOURCE_PROP_MAP::iterator pFontBaseItem = m_pFontBaseMap->begin();
		pFontBaseItem != m_pFontBaseMap->end(); pFontBaseItem++)
	{
		IPropertyFontBase* pFontBaseProp = dynamic_cast<IPropertyFontBase*>(pFontBaseItem->second);
		if (pFontBaseProp == NULL || pFontBaseProp->GetObjectName() == NULL || strlen(pFontBaseProp->GetObjectName()) <= 0)
			continue;

		CString strNo(_T(""));
		strNo.Format(_T("%d"), nNo);
		this->InsertItem(nNo, strNo);
		this->SetItemText(nNo, 1, A2W(pFontBaseProp->GetObjectName()));
		this->SetItemData(nNo, (DWORD_PTR)pFontBaseProp);

		if (pFontBaseProp == m_pParentFontProp->GetFontBaseProp())
			this->SetItemState(nNo, LVIS_SELECTED, LVIS_SELECTED);

		nNo++;
	}
}
