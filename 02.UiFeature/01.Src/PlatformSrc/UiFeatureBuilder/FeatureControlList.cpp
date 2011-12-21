#include "StdAfx.h"
#include "FeatureControlList.h"

CFeatureControlList::CFeatureControlList(void)
{
}

CFeatureControlList::~CFeatureControlList(void)
{
}

COLORREF CFeatureControlList::OnGetCellBkColor(int nRow, int nColum)
{
	return(nRow % 2) == 0 ? RGB(253, 241, 249) : RGB(196, 238, 254);
}
