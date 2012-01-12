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
	m_pSelectImgBaseProp = NULL;
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
	m_pSelectImgBaseProp = NULL;
	if (m_pImgBaseDlg == NULL)
		return;

	if (m_nSelectItem >= 1)
		m_pSelectImgBaseProp = (IPropertyImageBase*)this->GetItemData(m_nSelectItem);

	m_pImgBaseDlg->SetImageEditEnableStyle((m_nSelectItem >= 1));
}

void CImageBaseNameList::InitImageBaseShow(IUiFeatureKernel* pUiKernel, IPropertyImage* pParentImgProp)
{
	m_pUiKernel = pUiKernel;
	m_pParentImgProp = pParentImgProp;
}

IPropertyImageBase* CImageBaseNameList::GetSelectImageBase()
{
	return m_pSelectImgBaseProp;
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
