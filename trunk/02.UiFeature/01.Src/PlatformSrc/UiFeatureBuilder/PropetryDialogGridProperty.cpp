#include "StdAfx.h"
#include "PropetryDialogGridProperty.h"

CPropetryDialogGridProperty::CPropetryDialogGridProperty(const CString& strName, const COleVariant& varValue, CString& strInfo) : CMFCPropertyGridProperty(strName, varValue, strInfo)
{
	m_ObjType = OTID_NONE;
}

CPropetryDialogGridProperty::~CPropetryDialogGridProperty()
{
}

void CPropetryDialogGridProperty::SetShowDialogType(OBJECT_TYPE_ID ObjType)
{
	m_ObjType = ObjType;
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
	if (m_ImageBaseDlg.DoModal() != IDOK)
		return;


}