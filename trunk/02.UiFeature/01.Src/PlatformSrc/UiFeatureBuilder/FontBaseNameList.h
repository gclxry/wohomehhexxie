
#pragma once
#include "featurebaselist.h"
#include "..\..\Inc\IPropertyBase.h"
#include "..\..\Inc\IPropertyFont.h"
#include "..\..\Inc\IPropertyFontBase.h"
#include "..\..\Inc\IUiFeatureKernel.h"

class CModifyFontBaseDlg;
class CFontBaseNameList : public CFeatureBaseList
{
public:
	CFontBaseNameList();
	virtual ~CFontBaseNameList();

	void InitFontBaseNameList(CModifyFontBaseDlg* pDlg, IUiFeatureKernel* pUiKernel, IPropertyFont* pParentCursorProp, ONE_RESOURCE_PROP_MAP* pFontBaseMap);
	void NewFontBase(CString strName);
	void DeleteCurrentFontBase();

protected:
	virtual COLORREF OnGetCellBkColor(int nRow, int nColum);
	virtual void OnSelectItem();

private:
	IPropertySkinManager* m_pSkinMgr;
	IUiFeatureKernel* m_pUiKernel;
	CModifyFontBaseDlg* m_pOwnerDlg;
	IPropertyFont* m_pParentFontProp;
	ONE_RESOURCE_PROP_MAP* m_pFontBaseMap;
};
