
#pragma once
#include "featurebaselist.h"

struct CURSOR_SHOW_INFO 
{
	bool bSysDefaule;
	int nCursorId;
};

class CMouseStyleList : public CFeatureBaseList
{
public:
	CMouseStyleList();
	virtual ~CMouseStyleList();

	void InitMouseStyleList();

protected:
	virtual void OnSelectItem();

private:
	CImageList m_CursorImageList;
};
