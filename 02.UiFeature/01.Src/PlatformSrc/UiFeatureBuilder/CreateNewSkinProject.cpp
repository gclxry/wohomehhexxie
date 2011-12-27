// CreateNewSkinProject.cpp : implementation file
//

#include "stdafx.h"
#include "UiFeatureBuilder.h"
#include "CreateNewSkinProject.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\ICommonFun.h"


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
	USES_CONVERSION;
	m_strSkinDir = _T("");	
	m_strSkinName = _T("");

	this->GetDlgItemText(IDE_DIR, m_strSkinDir);
	if (m_strSkinDir.GetLength() <= 0)
	{
		AfxMessageBox(_T("��ѡ�񹤳��ļ�����·����"), MB_OK | MB_ICONERROR);
		this->GetDlgItem(IDE_DIR)->SetFocus();
		return;
	}

	this->GetDlgItemText(IDE_NAME, m_strSkinName);
	if (m_strSkinName.GetLength() <= 0)
	{
		AfxMessageBox(_T("������Ƥ���������ƣ�"), MB_OK | MB_ICONERROR);
		this->GetDlgItem(IDE_NAME)->SetFocus();
		return;
	}

	CString strToFile("");
	strToFile.Format(_T("%s%s%s%s"), m_strSkinDir, _T("\\"), m_strSkinName, _T(NAME_SKIN_PROJ_EX_NAME));

	string strPath = PathHelper(NAME_UFP_TEMPLATE);

	if (!::CopyFileA(strPath.c_str(), W2A(strToFile), TRUE))
	{
		CString strInfo(_T(""));
		strInfo.Format(_T("����Ƥ������ʧ�ܣ�ԭ���п����ǣ�\n1.��װĿ¼�²����ڡ�%s���ļ�\n2.Ŀ���ļ��Ѿ�����\n3.Ŀ���ļ��в���д"), NAME_UFP_TEMPLATE);
		AfxMessageBox(strInfo, MB_OK | MB_ICONERROR);
		return;
	}

	OnOK();
}

void CCreateNewSkinProject::GetNewProjectPath(CString &strDir, CString &strName)
{
	strDir = m_strSkinDir;
	strName = m_strSkinName;
}
