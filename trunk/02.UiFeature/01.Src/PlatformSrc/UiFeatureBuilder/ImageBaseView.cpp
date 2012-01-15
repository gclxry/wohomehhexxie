// ImageBaseView.cpp : implementation file
//

#include "stdafx.h"
#include "UiFeatureBuilder.h"
#include "ImageBaseView.h"
#include "..\..\Inc\UiFeatureDefs.h"


#define FRAME_ADD_SIZE					(10)

// CImageBaseView dialog

IMPLEMENT_DYNAMIC(CImageBaseView, CDialogViewBase)

CImageBaseView::CImageBaseView(CWnd* pParent) : CDialogViewBase(pParent)
{
	m_pCurShowImgBase = NULL;
	m_pCurZipFile = NULL;
	m_pUiKernel = NULL;
}

CImageBaseView::~CImageBaseView()
{
}

void CImageBaseView::DoDataExchange(CDataExchange* pDX)
{
	CDialogViewBase::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CImageBaseView, CDialogViewBase)
END_MESSAGE_MAP()


// CImageBaseView message handlers

void CImageBaseView::SetCurrentShowImage(IUiFeatureKernel *pUiKernel, IPropertyImageBase *pImgBase, ZIP_FILE *pZipFile)
{
	m_pUiKernel = pUiKernel;
	m_ZipFileImgBase.SetUiKernel(m_pUiKernel);

	m_pCurShowImgBase = pImgBase;
	m_pCurZipFile = pZipFile;
	m_ZipFileImgBase.SetZipFile(m_pCurZipFile, true);

	CRect WndRct;
	WndRct.SetRectEmpty();
	this->GetClientRect(&WndRct);
	SetScrollBarSize(WndRct.Width(), WndRct.Height());
	this->RedrawWindow();
}

void CImageBaseView::OnSize_SetViewSize(int cx, int cy)
{
	m_rcViewSize = m_rcDlgSize;
	if (m_pCurZipFile == NULL)
		return;

	CDrawingImage* pImgMemDc = m_ZipFileImgBase.GetMemDc();
	if (pImgMemDc == NULL || pImgMemDc->GetSafeHdc() == NULL)
		return;

	if (m_rcViewSize.Width() < pImgMemDc->GetDcSize().cx)
		m_rcViewSize.right = pImgMemDc->GetDcSize().cx;

	if (m_rcViewSize.Height() < pImgMemDc->GetDcSize().cy)
		m_rcViewSize.bottom = pImgMemDc->GetDcSize().cy;

	m_rcViewSize.right += FRAME_ADD_SIZE;
	m_rcViewSize.bottom += FRAME_ADD_SIZE;
}

void CImageBaseView::OnDraw()
{
	if (m_pCurZipFile == NULL)
		return;

	// 先绘制图片
	CDrawingImage* pImgMemDc = m_ZipFileImgBase.GetMemDc();
	if (pImgMemDc == NULL)
		return;

	RECT DstRct;
	INIT_RECT(DstRct);
	DstRct.right = pImgMemDc->GetDcSize().cx;
	DstRct.bottom = pImgMemDc->GetDcSize().cy;
	m_ZipFileImgBase.DrawImage(m_MemDc, DstRct);

	// 再绘制选择方框
	if (m_pCurShowImgBase == NULL)
		return;
}
