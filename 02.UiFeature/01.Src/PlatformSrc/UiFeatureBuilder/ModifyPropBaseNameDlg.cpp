// ModifyImageBaseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UiFeatureBuilder.h"
#include "ModifyPropBaseNameDlg.h"


// CModifyPropBaseNameDlg dialog

IMPLEMENT_DYNAMIC(CModifyPropBaseNameDlg, CDialog)

CModifyPropBaseNameDlg::CModifyPropBaseNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModifyPropBaseNameDlg::IDD, pParent)
	, m_strImageBaseName(_T(""))
{
	m_bIsCreate = true;
}

CModifyPropBaseNameDlg::~CModifyPropBaseNameDlg()
{
}

void CModifyPropBaseNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strImageBaseName);
}


BEGIN_MESSAGE_MAP(CModifyPropBaseNameDlg, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CModifyPropBaseNameDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CModifyPropBaseNameDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CModifyPropBaseNameDlg message handlers

void CModifyPropBaseNameDlg::OnBnClickedCancel()
{
	OnCancel();
}

void CModifyPropBaseNameDlg::IsCreate(bool bIsCreate)
{
	m_bIsCreate = bIsCreate;
}

BOOL CModifyPropBaseNameDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_strImageBaseName = _T("");
	if (m_bIsCreate)
	{
		this->SetWindowText(_T("新建图片属性名称"));
	}
	else
	{
		this->SetWindowText(_T("修改图片属性名称"));
	}

	return TRUE;
}

void CModifyPropBaseNameDlg::GetPropBaseName(CString &strName)
{
	strName = m_strImageBaseName;
}

void CModifyPropBaseNameDlg::OnBnClickedOk()
{
	this->UpdateData(TRUE);
	OnOK();
}
