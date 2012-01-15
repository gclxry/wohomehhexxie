
#pragma once
#include "DialogViewBase.h"
#include "..\..\Inc\IPropertyImageBase.h"
#include "..\..\Inc\IZipFile.h"
#include "..\..\Inc\IUiFeatureKernel.h"


// CImageBaseView dialog

class CImageBaseView : public CDialogViewBase
{
	DECLARE_DYNAMIC(CImageBaseView)

public:
	CImageBaseView(CWnd* pParent = NULL);   // standard constructor
	virtual ~CImageBaseView();

	void SetCurrentShowImage(IUiFeatureKernel *pUiKernel, IPropertyImageBase *pImgBase, ZIP_FILE *pZipFile);

protected:
	virtual void OnSize_SetViewSize(int cx, int cy);
	virtual void OnDraw();

private:
	IPropertyImageBase *m_pCurShowImgBase;
	ZIP_FILE *m_pCurZipFile;

	IPropertyImageBase m_ZipFileImgBase;
	IUiFeatureKernel *m_pUiKernel;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
