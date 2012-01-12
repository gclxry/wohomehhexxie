#pragma once
#include "featurebaselist.h"

class CImageBasePropEditDlg;
class CLocalImageList;
class CImageBaseNameList : public CFeatureBaseList
{
public:
	CImageBaseNameList(void);
	~CImageBaseNameList(void);

	void Init(CImageBasePropEditDlg *pImgBaseDlg, CLocalImageList* pLocalImg);

protected:
	virtual void OnSelectItem();

private:
	CImageBasePropEditDlg *m_pImgBaseDlg;
	CLocalImageList* m_pLocalImgList;
};
