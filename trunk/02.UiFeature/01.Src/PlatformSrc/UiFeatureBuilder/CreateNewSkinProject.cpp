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

}

CCreateNewSkinProject::~CCreateNewSkinProject()
{
}

void CCreateNewSkinProject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCreateNewSkinProject, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CCreateNewSkinProject::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CCreateNewSkinProject::OnBnClickedOk)
END_MESSAGE_MAP()


// CCreateNewSkinProject message handlers

void CCreateNewSkinProject::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void CCreateNewSkinProject::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}
