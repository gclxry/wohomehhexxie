#include "StdAfx.h"
#include "LocalImageList.h"
#include "ImageBasePropEditDlg.h"

CLocalImageList::CLocalImageList(void)
{
}

CLocalImageList::~CLocalImageList(void)
{
}

void CLocalImageList::Init(CImageBasePropEditDlg *pImgBaseDlg)
{
	if (pImgBaseDlg == NULL)
		return;

	m_pImgBaseDlg = pImgBaseDlg;

	this->DeleteAllItems();

	this->SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	this->ModifyStyle(0, LVS_SINGLESEL | LVS_SHOWSELALWAYS);
	this->InsertColumn(0, _T("#"), LVCFMT_LEFT, 50);
	this->InsertColumn(1, _T("本地图片名称"), LVCFMT_LEFT, 160);
}

void CLocalImageList::OnSelectItem()
{
	if (m_pImgBaseDlg == NULL)
		return;

	if (m_nSelectItem <= 0)
	{
		// 没有选择
	}
	else
	{
	}
}
