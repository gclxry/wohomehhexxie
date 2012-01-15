// ImageBaseView.cpp : implementation file
//

#include "stdafx.h"
#include "UiFeatureBuilder.h"
#include "ImageBaseView.h"


// CImageBaseView dialog

IMPLEMENT_DYNAMIC(CImageBaseView, CDialogViewBase)

CImageBaseView::CImageBaseView(CWnd* pParent) : CDialogViewBase(pParent)
{

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
