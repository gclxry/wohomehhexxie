
#pragma once
#include "featurebaselist.h"
#include "..\..\Inc\IPropertyBase.h"
#include "..\..\Inc\IPropertyCursor.h"
#include "..\..\Inc\IPropertyCursorBase.h"


class CMouseStyleList : public CFeatureBaseList
{
public:
	CMouseStyleList();
	virtual ~CMouseStyleList();

	void InitMouseStyleList(IPropertyCursor* pParentCursorProp, ONE_RESOURCE_PROP_MAP* pCursorBaseMap);

protected:
	virtual COLORREF OnGetCellBkColor(int nRow, int nColum);
	virtual void OnSelectItem();
	void AddCursorInfo(IPropertyCursorBase* pCursorBaseProp, int nNo);

private:
	IPropertyCursor* m_pParentCursorProp;
	CImageList m_CursorImageList;
	ONE_RESOURCE_PROP_MAP* m_pCursorBaseMap;
};
