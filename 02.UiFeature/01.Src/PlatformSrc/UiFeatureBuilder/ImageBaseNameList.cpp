#include "StdAfx.h"
#include "ImageBaseNameList.h"
#include "ImageBasePropEditDlg.h"
#include "LocalImageList.h"
#include "..\..\Inc\ICommonFun.h"

CImageBaseNameList::CImageBaseNameList(void)
{
	m_pImgBaseDlg = NULL;
	m_pLocalImgList = NULL;
	m_pParentImgProp = NULL;
	m_pUiKernel = NULL;
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

	m_pImgBaseDlg->SetImageEditEnableStyle((m_SelectItem.iItem >= 1));
}

void CImageBaseNameList::InitImageBaseShow(IUiFeatureKernel* pUiKernel, IPropertyImage* pParentImgProp)
{
	m_pUiKernel = pUiKernel;
	m_pParentImgProp = pParentImgProp;
}

IPropertyImageBase* CImageBaseNameList::GetSelectImageBase()
{
	if (m_SelectItem.iItem <= 0)
		return NULL;

	return (IPropertyImageBase*)m_SelectItem.lParam;
}

bool CImageBaseNameList::CreateImageBaseProp(CString strName)
{
	USES_CONVERSION;
	if (m_pUiKernel == NULL || m_pUiKernel->GetSkinManager() == NULL)
		return false;

	IPropertyBase* pPropBase = m_pUiKernel->GetSkinManager()->CreateEmptyBaseProp(OTID_IMAGE_BASE);
	if (pPropBase == NULL)
		return false;

	IPropertyImageBase * pNewImgBase = dynamic_cast<IPropertyImageBase*>(pPropBase);
	if (pNewImgBase == NULL)
		return false;
	pNewImgBase->SetObjectName(W2A(strName));

	int nCtns = this->GetItemCount();
	CString strNo(_T(""));
	strNo.Format(_T("%d"), nCtns);
	this->InsertItem(nCtns, strNo);
	this->SetItemText(nCtns, 1, strName);
	this->SetItemData(nCtns, (DWORD_PTR)pNewImgBase);

	return true;
}
