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
	virtual ~CLocalImageList(void);

	void SetSelectImagePropBase(IPropertyImageBase* pImgBase);
	void Init(IUiFeatureKernel* pUiKernel, CImageBasePropEditDlg *pImgBaseDlg, CImageBaseNameList* pImgBaseLise, CImageBaseView* pImgBaseView);
	bool OnLoadLocalImage(CString strFilePath, CString strFileName);
	bool OnDeleteLocalImage();

protected:
	virtual COLORREF OnGetCellBkColor(int nRow, int nColum);
	virtual void OnSelectItem();
	void RefreshList(ZIP_FILE* pSelZipFile);

private:
	CImageBasePropEditDlg *m_pImgBaseDlg;
	IUiFeatureKernel* m_pUiKernel;
	CImageBaseNameList* m_pImgBaseLise;
	ZIP_FILE_MAP* m_pZipFileMap;
	IPropertyImageBase* m_pSelImgBase;
	CImageBaseView* m_pImgBaseView;
	ZIP_FILE *m_pCurrentZipFile;
};
