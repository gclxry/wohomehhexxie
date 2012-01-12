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
	if (pImgBaseDlg == NULL || pLocalImg == NULL || m_pUiKernel == NULL || m_pUiKernel->GetSkinManager() == NULL)
		return;

	m_pImgBaseDlg = pImgBaseDlg;
	m_pLocalImgList = pLocalImg;

	this->DeleteAllItems();

	this->SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	this->ModifyStyle(0, LVS_SINGLESEL | LVS_SHOWSELALWAYS);
	this->InsertColumn(0, _T("#"), LVCFMT_LEFT, 50);
	this->InsertColumn(1, _T("图片属性名称"), LVCFMT_LEFT, 160);

	LoadImageBaseProp();
}

void CImageBaseNameList::LoadImageBaseProp()
{
	USES_CONVERSION;
	if (m_pUiKernel == NULL || m_pUiKernel->GetSkinManager() == NULL)
		return;
	
	ONE_RESOURCE_PROP_MAP* pMap = m_pUiKernel->GetSkinManager()->GetOneResourcePropMap("imagebase");
	if (pMap == NULL)
		return;

	this->DeleteAllItems();
	this->InsertItem(0, _T(""));
	this->SetItemText(0, 1, _T("点我浏览图片"));

	int nNo = 1;
	bool bFind = false;
	for (ONE_RESOURCE_PROP_MAP::iterator pImage = pMap->begin(); pImage != pMap->end(); pImage++, nNo++)
	{
		IPropertyBase* pPropBase = pImage->second;
		IPropertyImageBase* pImageProp = dynamic_cast<IPropertyImageBase*>(pPropBase);
		if (pImageProp == NULL)
			continue;

		CString strNo(_T(""));
		strNo.Format(_T("%d"), nNo);
		this->InsertItem(nNo, strNo);
		this->SetItemText(nNo, 1, A2W(pImageProp->GetObjectName()));
		this->SetItemData(nNo, (DWORD_PTR)pImageProp);

		if (m_pParentImgProp != NULL && m_pParentImgProp->GetRelevancyPropName() != NULL && !bFind)
		{
			if (lstrcmpiA(m_pParentImgProp->GetRelevancyPropName(), pImageProp->GetObjectName()) == 0)
			{
				bFind = true;
				this->SetItemState(nNo, LVIS_SELECTED, LVIS_SELECTED);
				m_pImgBaseDlg->SetImageEditEnableStyle(true);
			}
		}
	}
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

bool CImageBaseNameList::OnModifyImageBaseProp(CString strName)
{
	USES_CONVERSION;
	if (m_pUiKernel == NULL || m_pUiKernel->GetSkinManager() == NULL || strName.GetLength() <= 0 || m_pSelectImgBaseProp == NULL)
		return false;

	if (!m_pUiKernel->GetSkinManager()->BD_ModifyPropetryName(dynamic_cast<IPropertyBase*>(m_pSelectImgBaseProp), W2A(strName)))
		return false;

	this->SetItemText(m_nSelectItem, 1, strName);
	return true;
}

bool CImageBaseNameList::OnCreateImageBaseProp(CString strName)
{
	USES_CONVERSION;
	if (m_pUiKernel == NULL || m_pUiKernel->GetSkinManager() == NULL || strName.GetLength() <= 0)
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

void CImageBaseNameList::OnDeleteImageBaseProp()
{
	bool bDelete = false;
	int nCtns = this->GetItemCount();
	for (int i = 1; i < nCtns; )
	{
		BOOL bCheck = this->GetCheck(i);
		if (bCheck)
		{
			bDelete = true;
			// 选中，删除
			IPropertyImageBase *pImgBaseProp = (IPropertyImageBase *)this->GetItemData(i);
			m_pUiKernel->GetSkinManager()->BD_DeletePropetry(dynamic_cast<IPropertyBase*>(pImgBaseProp));

			this->DeleteItem(i);
			nCtns = this->GetItemCount();
			if (nCtns <= 1)
				return;

			i = 1;
		}
		else
		{
			i++;
		}
	}

	nCtns = this->GetItemCount();
	if (nCtns >= 1)
		this->SetCheck(0, FALSE);

	if (!bDelete)
		AfxMessageBox(_T("请先勾选属性列表中复选框，选择需要删除的图片属性，再进行删除操作！"), MB_OK | MB_ICONWARNING);
}

void CImageBaseNameList::OnSelectItem()
{
	m_pSelectImgBaseProp = NULL;
	if (m_pImgBaseDlg == NULL)
		return;

	if (m_nSelectItem >= 1)
		m_pSelectImgBaseProp = (IPropertyImageBase*)this->GetItemData(m_nSelectItem);

	IMAGE_BASE_PROP* pImgProp = m_pSelectImgBaseProp->GetImageProp();
	if (pImgProp == NULL)
	{
		m_pImgBaseDlg->SetImageEditEnableStyle((m_nSelectItem >= 1));
		return;
	}

	if (m_pSelectImgBaseProp == NULL)
	{
		m_pImgBaseDlg->m_nShowAreaLeft = 0;
		m_pImgBaseDlg->m_nShowAreaTop = 0;
		m_pImgBaseDlg->m_nShowAreaBottom = 0;
		m_pImgBaseDlg->m_nShowAreaRight = 0;
		m_pImgBaseDlg->m_nJggLeft = 0;
		m_pImgBaseDlg->m_nJggTop = 0;
		m_pImgBaseDlg->m_nJggRight = 0;
		m_pImgBaseDlg->m_nJggBottom = 0;
		m_pImgBaseDlg->m_nSelelShowImgType = 0;
	}
	else
	{
		m_pImgBaseDlg->m_nShowAreaLeft = pImgProp->RectInImage.left;
		m_pImgBaseDlg->m_nShowAreaTop = pImgProp->RectInImage.top;
		m_pImgBaseDlg->m_nShowAreaBottom = pImgProp->RectInImage.bottom;
		m_pImgBaseDlg->m_nShowAreaRight = pImgProp->RectInImage.right;
		m_pImgBaseDlg->m_nJggLeft = pImgProp->jggInfo.left;
		m_pImgBaseDlg->m_nJggTop = pImgProp->jggInfo.top;
		m_pImgBaseDlg->m_nJggRight = pImgProp->jggInfo.right;
		m_pImgBaseDlg->m_nJggBottom = pImgProp->jggInfo.bottom;
		m_pImgBaseDlg->m_nSelelShowImgType = pImgProp->ImgShowType;
	}

	m_pImgBaseDlg->UpdateData(FALSE);
	m_pImgBaseDlg->SetImageEditEnableStyle((m_nSelectItem >= 1));
}
