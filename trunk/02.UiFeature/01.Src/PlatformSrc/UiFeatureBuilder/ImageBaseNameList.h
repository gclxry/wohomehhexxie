#pragma once
#include "featurebaselist.h"
#include "..\..\Inc\IPropertyImage.h"
#include "..\..\Inc\IPropertyImageBase.h"
#include "..\..\Inc\IUiFeatureKernel.h"
#include "..\..\Inc\IPropertySkinManager.h"

class CImageBasePropEditDlg;
class CLocalImageList;
class CImageBaseNameList : public CFeatureBaseList
{
public:
	CImageBaseNameList(void);
	~CImageBaseNameList(void);

	bool CreateImageBaseProp(CString strName);
	IPropertyImageBase * GetSelectImageBase();
	void InitImageBaseShow(IUiFeatureKernel* pUiKernel, IPropertyImage* pParentImgProp);
	void Init(CImageBasePropEditDlg *pImgBaseDlg, CLocalImageList* pLocalImg);

protected:
	virtual void OnSelectItem();

private:
	IUiFeatureKernel* m_pUiKernel;
	CImageBasePropEditDlg *m_pImgBaseDlg;
	CLocalImageList* m_pLocalImgList;
	IPropertyImage* m_pParentImgProp;
	IPropertyImageBase* m_pSelectImgBaseProp;
};
