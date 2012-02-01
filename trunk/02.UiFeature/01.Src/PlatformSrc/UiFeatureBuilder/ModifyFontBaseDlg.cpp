// ModifyFontBaseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UiFeatureBuilder.h"
#include "ModifyFontBaseDlg.h"


// CModifyFontBaseDlg dialog

IMPLEMENT_DYNAMIC(CModifyFontBaseDlg, CDialog)

CModifyFontBaseDlg::CModifyFontBaseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModifyFontBaseDlg::IDD, pParent)
{

}

CModifyFontBaseDlg::~CModifyFontBaseDlg()
{
}

void CModifyFontBaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CModifyFontBaseDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CModifyFontBaseDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CModifyFontBaseDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CModifyFontBaseDlg message handlers

void CModifyFontBaseDlg::OnBnClickedCancel()
{
	OnBnClickedOk();
}

void CModifyFontBaseDlg::OnBnClickedOk()
{
	OnOK();
}
