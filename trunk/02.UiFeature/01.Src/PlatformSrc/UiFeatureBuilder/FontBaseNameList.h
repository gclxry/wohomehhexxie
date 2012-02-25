
#pragma once
#include "featurebaselist.h"
#include "..\..\Inc\IPropertyBase.h"
#include "..\..\Inc\IPropertyFont.h"
#include "..\..\Inc\IPropertyFontBase.h"

class CFontBaseNameList : public CFeatureBaseList
{
public:
	CFontBaseNameList();
	virtual ~CFontBaseNameList();

	void InitFontBaseNameList(IPropertyFont* pParentCursorProp, ONE_RESOURCE_PROP_MAP* pFontBaseMap);

protected:
	virtual COLORREF OnGetCellBkColor(int nRow, int nColum);
	virtual void OnSelectItem();

private:
	IPropertyFont* m_pParentFontProp;
	ONE_RESOURCE_PROP_MAP* m_pFontBaseMap;
};
