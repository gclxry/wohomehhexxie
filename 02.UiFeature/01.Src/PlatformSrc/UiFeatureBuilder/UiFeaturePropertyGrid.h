
#pragma once
#include "afxpropertygridctrl.h"
#include "..\..\Inc\IPropertyBuilderCtrl.h"

class CUiFeaturePropertyGrid : public CMFCPropertyGridProperty, public IPropertyBuilderCtrl
{
public:
	virtual ~CUiFeaturePropertyGrid();

	CUiFeaturePropertyGrid(const CString& strGroupName, DWORD_PTR dwData = 0, BOOL bIsValueList = FALSE);

	// Simple property
	CUiFeaturePropertyGrid(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0,
		LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL, LPCTSTR lpszValidChars = NULL);

	virtual void EnableBuilderCtrl(bool bEnable);
};
