#include "StdAfx.h"
#include "PropetryDialogGridProperty.h"

CPropetryDialogGridProperty::CPropetryDialogGridProperty(const CString& strName, const COleVariant& varValue, CString& strInfo) : CMFCPropertyGridProperty(strName, varValue, strInfo)
{
}

CPropetryDialogGridProperty::~CPropetryDialogGridProperty()
{
}

void CPropetryDialogGridProperty::OnClickButton(CPoint /*point*/)
{
	AfxMessageBox(_T("Show your dialog here..."));
	SetValue(_T("New value"));
}
