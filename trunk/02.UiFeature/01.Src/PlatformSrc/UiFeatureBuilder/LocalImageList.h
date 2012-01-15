#pragma once
#include "featurebaselist.h"
#include "..\..\Inc\IUiFeatureKernel.h"

class CImageBasePropEditDlg;
class CImageBaseNameList;
class CImageBaseView;
class CLocalImageList : public CFeatureBaseList
{
public:
	CLocalImageList(void);
	~CLocalImageList(void);

	void SetSelectImagePropBase(IPropertyImageBase* pImgBase);
	void Init(IUiFeatureKernel* pUiKernel, CImageBasePropEditDlg *pImgBaseDlg, CImageBaseNameList* pImgBaseLise, CImageBaseView* pImgBaseView);
	bool OnLoadLocalImage(CString strFilePath, CString strFileName);

protected:
	virtual void OnSelectItem();
	void RefreshList(ZIP_FILE* pSelZipFile);

private:
	CImageBasePropEditDlg *m_pImgBaseDlg;
	IUiFeatureKernel* m_pUiKernel;
	CImageBaseNameList* m_pImgBaseLise;
	ZIP_FILE_MAP* m_ZipFileMap;
	IPropertyImageBase* m_pSelImgBase;
	CImageBaseView* m_pImgBaseView;
	ZIP_FILE *m_pCurrentZipFile;
};
