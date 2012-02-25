
#include "StdAfx.h"
#include "FontBaseNameList.h"
#include "resource.h"
#include "UiFeatureBuilder.h"
#include "ModifyFontBaseDlg.h"
#include "..\..\Inc\UiFeatureDefs.h"

CFontBaseNameList::CFontBaseNameList()
{
	m_pFontBaseMap = NULL;
	m_pParentFontProp = NULL;
	m_pOwnerDlg = NULL;
	m_pSkinMgr = NULL;
	m_pUiKernel = NULL;
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
	if (m_pParentFontProp == NULL || m_pOwnerDlg == NULL)
		return;

	if (m_nSelectItem <= 0)
	{
		// û��ѡ��
		m_pParentFontProp->SetFontBaseProp(NULL);
		m_pParentFontProp->SetRelevancyPropName(NULL);
		m_pOwnerDlg->UpdateCurrentFontBaseProp(NULL);
	}
	else
	{
		IPropertyFontBase* pFontBaseProp = (IPropertyFontBase*)(this->GetItemData(m_nSelectItem));
		m_pParentFontProp->SetFontBaseProp(pFontBaseProp);
		m_pParentFontProp->SetRelevancyPropName((char*)pFontBaseProp->GetObjectName());
		m_pOwnerDlg->UpdateCurrentFontBaseProp(pFontBaseProp);
	}
}

void CFontBaseNameList::InitFontBaseNameList(CModifyFontBaseDlg* pDlg, IUiFeatureKernel* pUiKernel, IPropertyFont* pParentCursorProp, ONE_RESOURCE_PROP_MAP* pFontBaseMap)
{
	if (pFontBaseMap == NULL || pDlg == NULL || pUiKernel == NULL)
		return;

	m_pUiKernel = pUiKernel;
	m_pSkinMgr = m_pUiKernel->GetSkinManager();
	m_pOwnerDlg = pDlg;
	m_pParentFontProp = pParentCursorProp;

	USES_CONVERSION;
	this->DeleteAllItems();
	m_pFontBaseMap = pFontBaseMap;

	this->SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	this->ModifyStyle(0, LVS_SINGLESEL | LVS_SHOWSELALWAYS);
	this->InsertColumn(0, _T("#"), LVCFMT_LEFT, 30);
	this->InsertColumn(1, _T("����"), LVCFMT_LEFT, 100);

	this->InsertItem(0, _T("#"));
	this->SetItemText(0, 1, _T("��������FONT����Ϊ��Ŷ"));
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

void CFontBaseNameList::NewFontBase(CString strName)
{
	if (strName.GetLength() <= 0 || m_pUiKernel == NULL || m_pSkinMgr == NULL)
		return;

	IPropertyFontBase* pNewFontBase = dynamic_cast<IPropertyFontBase*>(m_pSkinMgr->CreateEmptyBaseProp(OTID_FONT_BASE));
	if (pNewFontBase == NULL)
		return;

	int nCtns = this->GetItemCount();
	CString strNo(_T(""));
	strNo.Format(_T("%d"), nCtns);

	this->InsertItem(nCtns, strNo);
	this->SetItemText(nCtns, 1, strName);
	this->SetItemData(nCtns, (DWORD_PTR)pNewFontBase);
	this->SetItemState(nCtns, LVIS_SELECTED, LVIS_SELECTED);
	m_pOwnerDlg->UpdateCurrentFontBaseProp(pNewFontBase);
}