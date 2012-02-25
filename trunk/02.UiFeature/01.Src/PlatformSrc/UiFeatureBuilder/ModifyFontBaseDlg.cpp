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
	m_pCurFontBaseProp = NULL;
	m_pUiKernel = NULL;
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
	if (pUiKernel == NULL)
		return;

	m_pUiKernel = pUiKernel;
	m_pParentFontProp = pParentFontProp;
	if (pUiKernel == NULL || pUiKernel->GetSkinManager() == NULL)
		return;

	m_pFontBaseMap = pUiKernel->GetSkinManager()->GetOneResourcePropMap(PROP_TYPE_FONT_BASE_NAME, true);
	if (m_pFontBaseMap == NULL)
		return;
}

BOOL CModifyFontBaseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_FontBaseNameList.InitFontBaseNameList(this, m_pUiKernel, m_pParentFontProp, m_pFontBaseMap);

	if (m_pParentFontProp != NULL)
		SetCurrentFontBaseProp(m_pParentFontProp->GetFontBaseProp());

	return TRUE;
}

void CModifyFontBaseDlg::SetCurrentFontBaseProp(IPropertyFontBase* pCurFontBaseProp)
{
	m_pCurFontBaseProp = pCurFontBaseProp;
}

void CModifyFontBaseDlg::OnBnClickedNewFontBase()
{
	if (m_pFontBaseMap == NULL)
		return;

	m_ModifyFontDlg.SetWindowInfomation(_T("新建字体属性名称"));
	m_ModifyFontDlg.DoModal();

	CString strName(_T(""));
	m_ModifyFontDlg.GetPropBaseName(strName);
	m_FontBaseNameList.NewFontBase(strName);
}

void CModifyFontBaseDlg::OnBnClickedDeleteFontBase()
{
	if (m_pFontBaseMap == NULL || m_pCurFontBaseProp == NULL)
		return;
}

void CModifyFontBaseDlg::OnBnClickedEditFontBase()
{
	if (m_pFontBaseMap == NULL || m_pCurFontBaseProp == NULL)
		return;
}

void CModifyFontBaseDlg::OnBnClickedSelectFont()
{
	if (m_pFontBaseMap == NULL || m_pCurFontBaseProp == NULL)
		return;
}

void CModifyFontBaseDlg::OnBnClickedSelectTextColor()
{
	if (m_pFontBaseMap == NULL || m_pCurFontBaseProp == NULL)
		return;
}
