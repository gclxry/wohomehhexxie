
#pragma once
#include "DialogViewBase.h"
#include "..\..\Inc\IPropertyImageBase.h"
#include "..\..\Inc\IZipFile.h"
#include "..\..\Inc\IUiFeatureKernel.h"
#include "..\..\Inc\IControlBase.h"
#include "..\..\Inc\UiFeatureDefs.h"


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

	IPropertyImageBase m_DrawFangKuai;
	FANGKUAI_8 m_FangKuai8;

	bool m_bIsLButtonDown;
	CPoint m_LBtnDownPos;
	CPoint m_LBtnUpPos;
	CPoint m_MouseMovePos;

	// 光标
	int m_nViewCursor;
	SIZE_CTRL_TYPE m_nMoveFangKuai8Type;
	bool m_bMoveInCtrlFangKuai8;
private:
	// 设置光标
	void SetViewCursor(int nCursor);
	SIZE_CTRL_TYPE OnMouseMove_FangKuai8(CPoint point, bool bIsWnd);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};
