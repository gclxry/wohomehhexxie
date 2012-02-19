
#include "StdAfx.h"
#include "MouseStyleList.h"
#include "resource.h"
#include "UiFeatureBuilder.h"

extern CUiFeatureBuilderApp theApp;

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

	CBitmap bmp;
	if (bmp.LoadBitmap(IDB_CURSOR_BITMAP))
	{
		BITMAP bmpObj;
		bmp.GetBitmap(&bmpObj);

		UINT nFlags = (ILC_MASK | ((theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4));
		m_CursorImageList.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
		m_CursorImageList.Add(&bmp, RGB(255, 0, 0));

		this->SetImageList(&m_CursorImageList, TVSIL_NORMAL);
	}
}
