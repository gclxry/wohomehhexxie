#pragma once
#include "afxpropertygridctrl.h"
#include "..\..\Inc\IFeatureObject.h"
#include "ImageBasePropEditDlg.h"

class CPropetryDialogGridProperty : public CMFCPropertyGridProperty
{
public:
	CPropetryDialogGridProperty(const CString& strName, const COleVariant& varValueconst, CString& strInfo);
	virtual ~CPropetryDialogGridProperty();

	void SetShowDialogType(OBJECT_TYPE_ID ObjType);

protected:
	virtual BOOL HasButton() const { return TRUE; }
	virtual void OnClickButton(CPoint point);
	void ImageBaseDialog();

private:
	OBJECT_TYPE_ID m_ObjType;
	CImageBasePropEditDlg m_ImageBaseDlg;
};
