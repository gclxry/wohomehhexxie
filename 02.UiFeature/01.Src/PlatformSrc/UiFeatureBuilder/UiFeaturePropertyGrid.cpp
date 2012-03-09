
#include "StdAfx.h"
#include "UiFeaturePropertyGrid.h"

CUiFeaturePropertyGrid::~CUiFeaturePropertyGrid()
{
}

CUiFeaturePropertyGrid::CUiFeaturePropertyGrid(const CString& strGroupName, DWORD_PTR dwData, BOOL bIsValueList)
: CMFCPropertyGridProperty(strGroupName, dwData, bIsValueList)
{
}

// Simple property
CUiFeaturePropertyGrid::CUiFeaturePropertyGrid(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr, DWORD_PTR dwData,
											   LPCTSTR lpszEditMask, LPCTSTR lpszEditTemplate, LPCTSTR lpszValidChars)
											   : CMFCPropertyGridProperty(strName, varValue, lpszDescr, dwData,
											   lpszEditMask, lpszEditTemplate, lpszValidChars)
{
}

void CUiFeaturePropertyGrid::EnableBuilderCtrl(bool bEnable)
{
	this->Enable((bEnable == true));
}
