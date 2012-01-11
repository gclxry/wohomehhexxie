#pragma once
#include "featurebaselist.h"

class CImageBaseNameList : public CFeatureBaseList
{
public:
	CImageBaseNameList(void);
	~CImageBaseNameList(void);

protected:
	virtual void OnSelectItem();
};
