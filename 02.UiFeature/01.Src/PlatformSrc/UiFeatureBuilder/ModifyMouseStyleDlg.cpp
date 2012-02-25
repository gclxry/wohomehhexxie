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
	m_pParentCursorProp = NULL;
	m_pCursorBaseMap = NULL;
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

	m_MouseStyleList.InitMouseStyleList(m_pParentCursorProp, m_pCursorBaseMap);
	return TRUE;
}

void CModifyMouseStyleDlg::InitCursorBaseShow(IUiFeatureKernel* pUiKernel, IPropertyCursor* pParentCursorProp)
{
	m_pParentCursorProp = pParentCursorProp;
	if (pUiKernel == NULL || pUiKernel->GetSkinManager() == NULL)
		return;

	m_pCursorBaseMap = pUiKernel->GetSkinManager()->GetOneResourcePropMap(PROP_TYPE_CURSOR_BASE_NAME, true);
	if (m_pCursorBaseMap == NULL)
		return;	
}
