#include "StdAfx.h"
#include "PropetryDialogGridProperty.h"
#include "ImageBasePropEditDlg.h"

CPropetryDialogGridProperty::CPropetryDialogGridProperty(const CString& strName, const COleVariant& varValue, CString& strInfo) : CMFCPropertyGridProperty(strName, varValue, strInfo)
{
	m_ObjType = OTID_NONE;
	m_pUiKernel = NULL;
}

CPropetryDialogGridProperty::~CPropetryDialogGridProperty()
{
}

void CPropetryDialogGridProperty::InitDialogPropetry(IUiFeatureKernel* pUiKernel, OBJECT_TYPE_ID ObjType)
{
	m_ObjType = ObjType;
	m_pUiKernel = pUiKernel;
}

void CPropetryDialogGridProperty::OnClickButton(CPoint /*point*/)
{
	if (m_ObjType == OTID_IMAGE_BASE)
	{
		ImageBaseDialog();
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

	IPropertyImageBase *pImgBase = ImageBaseDlg.GetSelectImageBase();
	if (pImgBase == NULL)
		return;

	pParentImgProp->SetImageBaseProp(pImgBase);
	pParentImgProp->SetRelevancyPropName((char*)pImgBase->GetObjectName());
	COleVariant varValue(A2W(pParentImgProp->GetRelevancyPropName()));
	SetValue(varValue);
}
