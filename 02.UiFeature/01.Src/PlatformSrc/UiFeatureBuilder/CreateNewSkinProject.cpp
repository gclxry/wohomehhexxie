// CreateNewSkinProject.cpp : implementation file
//

#include "stdafx.h"
#include "UiFeatureBuilder.h"
#include "CreateNewSkinProject.h"


// CCreateNewSkinProject dialog

IMPLEMENT_DYNAMIC(CCreateNewSkinProject, CDialog)

CCreateNewSkinProject::CCreateNewSkinProject(CWnd* pParent /*=NULL*/)
	: CDialog(CCreateNewSkinProject::IDD, pParent)
{
	m_strSkinDir = _T("");
	m_strSkinName = _T("");
}

CCreateNewSkinProject::~CCreateNewSkinProject()
{
}

void CCreateNewSkinProject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDE_DIR, m_BrowseFolderEdit);
}


BEGIN_MESSAGE_MAP(CCreateNewSkinProject, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CCreateNewSkinProject::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CCreateNewSkinProject::OnBnClickedOk)
END_MESSAGE_MAP()


// CCreateNewSkinProject message handlers

BOOL CCreateNewSkinProject::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	m_BrowseFolderEdit.EnableFolderBrowseButton();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CCreateNewSkinProject::OnBnClickedCancel()
{
	m_strSkinDir = _T("");
	m_strSkinName = _T("");

	OnCancel();
}

void CCreateNewSkinProject::OnBnClickedOk()
{
	m_strSkinDir = _T("");
	m_strSkinName = _T("");

	this->GetDlgItemText(IDE_DIR, m_strSkinDir);
	if (m_strSkinDir.GetLength() <= 0)
	{
		AfxMessageBox(_T("请选择工程文件保存路径！"), MB_OK | MB_ICONERROR);
		this->GetDlgItem(IDE_DIR)->SetFocus();
		return;
	}

	this->GetDlgItemText(IDE_NAME, m_strSkinName);
	if (m_strSkinName.GetLength() <= 0)
	{
		AfxMessageBox(_T("请输入皮肤工程名称！"), MB_OK | MB_ICONERROR);
		this->GetDlgItem(IDE_NAME)->SetFocus();
		return;
	}

	OnOK();
}

void CCreateNewSkinProject::GetNewProjectPath(CString &strDir, CString &strName)
{
	strDir = m_strSkinDir;
	strName = m_strSkinName;
}
