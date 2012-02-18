
#include "StdAfx.h"
#include "MouseStyleList.h"


CMouseStyleList::CMouseStyleList()
{
}

CMouseStyleList::~CMouseStyleList()
{
}

void CMouseStyleList::OnSelectItem()
{
}

void CMouseStyleList::InitMouseStyleList()
{
	USES_CONVERSION;
	this->DeleteAllItems();

	this->SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	this->ModifyStyle(0, LVS_SINGLESEL | LVS_SHOWSELALWAYS);
	this->InsertColumn(0, _T("#"), LVCFMT_LEFT, 50);
	this->InsertColumn(1, _T("系统"), LVCFMT_LEFT, 50);
	this->InsertColumn(2, _T("样式"), LVCFMT_LEFT, 80);
	this->InsertColumn(3, _T("说明"), LVCFMT_LEFT, 160);

	CImageList
	this->SetImageList();
}
