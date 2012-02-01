// ModifyMouseStyleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UiFeatureBuilder.h"
#include "ModifyMouseStyleDlg.h"


// CModifyMouseStyleDlg dialog

IMPLEMENT_DYNAMIC(CModifyMouseStyleDlg, CDialog)

CModifyMouseStyleDlg::CModifyMouseStyleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModifyMouseStyleDlg::IDD, pParent)
{

}

CModifyMouseStyleDlg::~CModifyMouseStyleDlg()
{
}

void CModifyMouseStyleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CModifyMouseStyleDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CModifyMouseStyleDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CModifyMouseStyleDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CModifyMouseStyleDlg message handlers

void CModifyMouseStyleDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CModifyMouseStyleDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}
