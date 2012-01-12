#include "StdAfx.h"
#include "ImageBaseNameList.h"
#include "ImageBasePropEditDlg.h"
#include "LocalImageList.h"

CImageBaseNameList::CImageBaseNameList(void)
{
	m_pImgBaseDlg = NULL;
	m_pLocalImgList = NULL;
}

CImageBaseNameList::~CImageBaseNameList(void)
{
}

void CImageBaseNameList::Init(CImageBasePropEditDlg *pImgBaseDlg, CLocalImageList* pLocalImg)
{
	if (pImgBaseDlg == NULL || pLocalImg == NULL)
		return;

	m_pImgBaseDlg = pImgBaseDlg;
	m_pLocalImgList = pLocalImg;

	this->DeleteAllItems();

	this->SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	this->ModifyStyle(0, LVS_SINGLESEL | LVS_SHOWSELALWAYS);
	this->InsertColumn(0, _T("#"), LVCFMT_LEFT, 50);
	this->InsertColumn(1, _T("Í¼Æ¬ÊôÐÔÃû³Æ"), LVCFMT_LEFT, 160);

	this->InsertItem(0, _T(""));
	this->SetItemText(0, 1, _T("µãÎÒä¯ÀÀÍ¼Æ¬"));
}

void CImageBaseNameList::OnSelectItem()
{
	if (m_pImgBaseDlg == NULL)
		return;

	m_pImgBaseDlg->SetImageEditEnableStyle((m_SelectItem.iItem > 1));
}
