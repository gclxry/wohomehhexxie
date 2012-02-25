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
	m_pParentFontProp = NULL;
	m_pFontBaseMap = NULL;
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
	ON_BN_CLICKED(IDB_SELECT_FONT, &CModifyFontBaseDlg::OnBnClickedSelectFont)
	ON_BN_CLICKED(IDB_SELECT_TEXT_COLOR, &CModifyFontBaseDlg::OnBnClickedSelectTextColor)
	ON_BN_CLICKED(IDB_NEW_FONT_BASE, &CModifyFontBaseDlg::OnBnClickedNewFontBase)
	ON_BN_CLICKED(IDB_DELETE_FONT_BASE, &CModifyFontBaseDlg::OnBnClickedDeleteFontBase)
	ON_BN_CLICKED(IDB_EDIT_FONT_BASE, &CModifyFontBaseDlg::OnBnClickedEditFontBase)
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

void CModifyFontBaseDlg::InitFontBaseShow(IUiFeatureKernel* pUiKernel, IPropertyFont* pParentFontProp)
{
	m_pParentFontProp = pParentFontProp;
	if (pUiKernel == NULL || pUiKernel->GetSkinManager() == NULL)
		return;

	m_pFontBaseMap = pUiKernel->GetSkinManager()->GetOneResourcePropMap(PROP_TYPE_FONT_BASE_NAME);
	if (m_pFontBaseMap == NULL)
		return;	
}

BOOL CModifyFontBaseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_FontBaseNameList.InitFontBaseNameList(m_pParentFontProp, m_pFontBaseMap);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CModifyFontBaseDlg::OnBnClickedSelectFont()
{
	// TODO: Add your control notification handler code here
}

void CModifyFontBaseDlg::OnBnClickedSelectTextColor()
{
	// TODO: Add your control notification handler code here
}

void CModifyFontBaseDlg::OnBnClickedNewFontBase()
{
	// TODO: Add your control notification handler code here
}

void CModifyFontBaseDlg::OnBnClickedDeleteFontBase()
{
	// TODO: Add your control notification handler code here
}

void CModifyFontBaseDlg::OnBnClickedEditFontBase()
{
	// TODO: Add your control notification handler code here
}
