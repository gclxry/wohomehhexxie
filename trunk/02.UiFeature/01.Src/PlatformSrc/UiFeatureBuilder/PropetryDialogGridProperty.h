#pragma once
#include "afxpropertygridctrl.h"

class CPropetryDialogGridProperty : public CMFCPropertyGridProperty
{
public:
	CPropetryDialogGridProperty(const CString& strName, const COleVariant& varValueconst, CString& strInfo);
	virtual ~CPropetryDialogGridProperty();

protected:
	virtual BOOL HasButton() const { return TRUE; }
	virtual void OnClickButton(CPoint point);
};
