// ModifyImageBaseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UiFeatureBuilder.h"
#include "ModifyImageBaseDlg.h"


// CModifyImageBaseDlg dialog

IMPLEMENT_DYNAMIC(CModifyImageBaseDlg, CDialog)

CModifyImageBaseDlg::CModifyImageBaseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModifyImageBaseDlg::IDD, pParent)
	, m_strImageBaseName(_T(""))
{
	m_bIsCreate = true;
}

CModifyImageBaseDlg::~CModifyImageBaseDlg()
{
}

void CModifyImageBaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strImageBaseName);
}


BEGIN_MESSAGE_MAP(CModifyImageBaseDlg, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CModifyImageBaseDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CModifyImageBaseDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CModifyImageBaseDlg message handlers

void CModifyImageBaseDlg::OnBnClickedCancel()
{
	OnCancel();
}

void CModifyImageBaseDlg::IsCreateImageBase(bool bIsCreate)
{
	m_bIsCreate = bIsCreate;
}

BOOL CModifyImageBaseDlg::OnInitDialog()
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

void CModifyImageBaseDlg::GetImageBaseName(CString &strName)
{
	strName = m_strImageBaseName;
}

void CModifyImageBaseDlg::OnBnClickedOk()
{
	this->UpdateData(TRUE);
	OnOK();
}
