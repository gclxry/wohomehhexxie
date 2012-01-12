#pragma once
#include "featurebaselist.h"

class CImageBasePropEditDlg;
class CLocalImageList : public CFeatureBaseList
{
public:
	CLocalImageList(void);
	~CLocalImageList(void);

	void Init(CImageBasePropEditDlg *pImgBaseDlg);

protected:
	virtual void OnSelectItem();

private:
	CImageBasePropEditDlg *m_pImgBaseDlg;
};
