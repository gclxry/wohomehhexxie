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
	DDX_Control(pDX, IDL_MOUSE_SYTLE_LIST, m_MouseStyleList);
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

BOOL CModifyMouseStyleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	m_MouseStyleList.InitMouseStyleList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
