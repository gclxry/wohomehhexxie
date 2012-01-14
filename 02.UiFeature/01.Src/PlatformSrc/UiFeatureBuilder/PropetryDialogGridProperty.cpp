#include "StdAfx.h"
#include "PropetryDialogGridProperty.h"
#include "ImageBasePropEditDlg.h"
#include "PropertyViewCtrl.h"
#include "MainFrm.h"

CPropetryDialogGridProperty::CPropetryDialogGridProperty(const CString& strName, const COleVariant& varValue, CString& strInfo) : CMFCPropertyGridProperty(strName, varValue, strInfo)
{
	m_ObjType = OTID_NONE;
	m_pUiKernel = NULL;
	m_pPropViewList = NULL;
}

CPropetryDialogGridProperty::~CPropetryDialogGridProperty()
{
}

void CPropetryDialogGridProperty::InitDialogPropetry(CPropertyViewCtrl *pPropView, IUiFeatureKernel* pUiKernel, OBJECT_TYPE_ID ObjType)
{
	m_pPropViewList = pPropView;
	m_ObjType = ObjType;
	m_pUiKernel = pUiKernel;
	AllowEdit(FALSE);
}

void CPropetryDialogGridProperty::OnClickButton(CPoint /*point*/)
{
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	if (pMain != NULL)
		pMain->SetPropetryChange();

	if (m_ObjType == OTID_IMAGE_BASE)
	{
		ImageBaseDialog();
		m_pPropViewList->RefreshAllData();
		return;
	}

	SetValue(_T(""));
	AfxMessageBox(_T("错误的属性类型"));
}

void CPropetryDialogGridProperty::ImageBaseDialog()
{
	USES_CONVERSION;
	IPropertyBase *pPropBase = (IPropertyBase*)this->GetData();
	IPropertyImage* pParentImgProp = dynamic_cast<IPropertyImage*>(pPropBase);
	if (pParentImgProp == NULL)
		return;

	CImageBasePropEditDlg ImageBaseDlg;
	ImageBaseDlg.InitImageBaseShow(m_pUiKernel, pParentImgProp);
	if (ImageBaseDlg.DoModal() != IDOK)
		return;

	int nSelectItem = -1;
	IPropertyImageBase *pImgBase = ImageBaseDlg.GetSelectImageBase(nSelectItem);
	if (pImgBase == NULL)
	{
		if (nSelectItem == 0)
		{
			pParentImgProp->SetImageBaseProp(NULL);
			pParentImgProp->SetRelevancyPropName(NULL);
			COleVariant varValue(_T(""));
			SetValue(varValue);
		}
		return;
	}

	COleVariant varValue(A2W(pParentImgProp->GetRelevancyPropName()));
	SetValue(varValue);
}
