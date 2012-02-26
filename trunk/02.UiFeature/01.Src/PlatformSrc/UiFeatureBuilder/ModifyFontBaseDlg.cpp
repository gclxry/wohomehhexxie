// ModifyFontBaseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UiFeatureBuilder.h"
#include "ModifyFontBaseDlg.h"


// CModifyFontBaseDlg dialog

IMPLEMENT_DYNAMIC(CModifyFontBaseDlg, CDialog)

CModifyFontBaseDlg::CModifyFontBaseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModifyFontBaseDlg::IDD, pParent)
	, m_nXianshiMode(0)
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
	DDX_Control(pDX, IDC_VAligning_COM, m_VAligningCombo);
	DDX_Control(pDX, IDC_HAligning_COMBO, m_HAligningCombo);
	DDX_Radio(pDX, IDR_DANHANG_BU_POINT, m_nXianshiMode);
	DDX_Control(pDX, IDC_SHADOW_EFFECT, m_EffectShadow);
	DDX_Control(pDX, IDC_OBSCURE_EFFECT, m_EffectObscure);
	DDX_Control(pDX, IDS_FONT_PROVIEW_STRTIC, m_FontProViewStatic);
	DDX_Control(pDX, IDC_PICTURE_TEXT, m_PictureTextCheckBox);
}


BEGIN_MESSAGE_MAP(CModifyFontBaseDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CModifyFontBaseDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CModifyFontBaseDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDB_SELECT_FONT, &CModifyFontBaseDlg::OnBnClickedSelectFont)
	ON_BN_CLICKED(IDB_SELECT_TEXT_COLOR, &CModifyFontBaseDlg::OnBnClickedSelectTextColor)
	ON_BN_CLICKED(IDB_NEW_FONT_BASE, &CModifyFontBaseDlg::OnBnClickedNewFontBase)
	ON_BN_CLICKED(IDB_DELETE_FONT_BASE, &CModifyFontBaseDlg::OnBnClickedDeleteFontBase)
	ON_BN_CLICKED(IDB_EDIT_FONT_BASE, &CModifyFontBaseDlg::OnBnClickedEditFontBase)
	ON_CBN_SELCHANGE(IDC_VAligning_COM, &CModifyFontBaseDlg::OnCbnSelchangeValigningCombo)
	ON_CBN_SELCHANGE(IDC_HAligning_COMBO, &CModifyFontBaseDlg::OnCbnSelchangeHaligningCombo)
	ON_BN_CLICKED(IDR_DANHANG_BU_POINT, &CModifyFontBaseDlg::OnBnClickedDanhangBuPoint)
	ON_BN_CLICKED(IDR_DANHANG_XIANSHI_POINT, &CModifyFontBaseDlg::OnBnClickedDanhangXianshiPoint)
	ON_BN_CLICKED(IDR_ZHEHANG_XIANSHI, &CModifyFontBaseDlg::OnBnClickedZhehangXianshi)
	ON_BN_CLICKED(IDC_SHADOW_EFFECT, &CModifyFontBaseDlg::OnBnClickedShadowEffect)
	ON_BN_CLICKED(IDC_OBSCURE_EFFECT, &CModifyFontBaseDlg::OnBnClickedObscureEffect)
	ON_BN_CLICKED(IDC_PICTURE_TEXT, &CModifyFontBaseDlg::OnBnClickedPictureText)
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

	m_VAligningCombo.InsertString(0, _T("垂直靠上"));
	m_VAligningCombo.InsertString(1, _T("垂直居中"));
	m_VAligningCombo.InsertString(2, _T("垂直靠下"));
	m_VAligningCombo.SetCurSel(0);

	m_HAligningCombo.InsertString(0, _T("水平靠左"));
	m_HAligningCombo.InsertString(1, _T("水平居中"));
	m_HAligningCombo.InsertString(2, _T("水平靠右"));
	m_HAligningCombo.SetCurSel(0);

	m_nXianshiMode = (int)FSM_ONE_ROW_NO_POINT;

	m_FontBaseNameList.InitFontBaseNameList(this, m_pUiKernel, m_pParentFontProp, m_pFontBaseMap);

	if (m_pParentFontProp != NULL)
		UpdateCurrentFontBaseProp(m_pParentFontProp->GetFontBaseProp());
	else
		UpdateCurrentFontBaseProp(NULL);

	this->UpdateData(FALSE);
	return TRUE;
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

void CModifyFontBaseDlg::UpdateCurrentFontBaseProp(IPropertyFontBase* pCurFontBaseProp)
{
	USES_CONVERSION;
	m_pCurFontBaseProp = pCurFontBaseProp;
	if (m_pCurFontBaseProp != NULL && m_pCurFontBaseProp->GetFontProp() != NULL)
	{
		FONT_PROP* pFontProp = m_pCurFontBaseProp->GetFontProp();
		CString strFontInfo(_T(""));
		strFontInfo.Format(_T("%s，%d"), A2W(pFontProp->Font.lfFaceName), pFontProp->Font.lfHeight);
		this->GetDlgItem(IDE_FONT_INFO_EDIT)->SetWindowText(strFontInfo);

		m_VAligningCombo.SetCurSel((int)pFontProp->VAligning);
		m_HAligningCombo.SetCurSel((int)pFontProp->HAligning);
		m_nXianshiMode = (int)pFontProp->ShowMode;

		bool bSet = m_pCurFontBaseProp->GetEffectState(FE_SHADOW);
		m_EffectShadow.SetCheck(bSet ? 1 : 0);

		bSet = m_pCurFontBaseProp->GetEffectState(FE_OBSCURE);
		m_EffectObscure.SetCheck(bSet ? 1 : 0);

		m_PictureTextCheckBox.SetCheck(pFontProp->bIsPicText ? 1 : 0);
	}
	else
	{
		this->GetDlgItem(IDE_FONT_INFO_EDIT)->SetWindowText(_T(""));
		m_VAligningCombo.SetCurSel(0);
		m_HAligningCombo.SetCurSel(0);
		m_nXianshiMode = (int)FSM_ONE_ROW_NO_POINT;
		m_EffectShadow.SetCheck(0);
		m_EffectObscure.SetCheck(0);
		m_PictureTextCheckBox.SetCheck(0);
	}

	this->UpdateData(FALSE);
	m_FontProViewStatic.RedrawView(m_pCurFontBaseProp);
}

void CModifyFontBaseDlg::OnCbnSelchangeValigningCombo()
{
	if (m_pCurFontBaseProp == NULL || m_pCurFontBaseProp->GetFontProp() == NULL)
		return;

	FONT_PROP* pFontProp = m_pCurFontBaseProp->GetFontProp();
	pFontProp->VAligning = (FONT_ALIGNING)m_VAligningCombo.GetCurSel();
	m_FontProViewStatic.RedrawView(m_pCurFontBaseProp);
}

void CModifyFontBaseDlg::OnCbnSelchangeHaligningCombo()
{
	if (m_pCurFontBaseProp == NULL || m_pCurFontBaseProp->GetFontProp() == NULL)
		return;

	FONT_PROP* pFontProp = m_pCurFontBaseProp->GetFontProp();
	pFontProp->HAligning = (FONT_ALIGNING)m_HAligningCombo.GetCurSel();
	m_FontProViewStatic.RedrawView(m_pCurFontBaseProp);
}

void CModifyFontBaseDlg::OnBnClickedDanhangBuPoint()
{
	OnBnClickedZhehangXianshi();
}

void CModifyFontBaseDlg::OnBnClickedDanhangXianshiPoint()
{
	OnBnClickedZhehangXianshi();
}

void CModifyFontBaseDlg::OnBnClickedZhehangXianshi()
{
	this->UpdateData(TRUE);
	if (m_pCurFontBaseProp == NULL || m_pCurFontBaseProp->GetFontProp() == NULL)
		return;

	FONT_PROP* pFontProp = m_pCurFontBaseProp->GetFontProp();
	pFontProp->ShowMode = (FONT_SHOW_MODE)m_nXianshiMode;
	m_FontProViewStatic.RedrawView(m_pCurFontBaseProp);
}

void CModifyFontBaseDlg::OnBnClickedShadowEffect()
{
	if (m_pCurFontBaseProp == NULL || m_pCurFontBaseProp->GetFontProp() == NULL)
		return;

	int nCheck = m_EffectShadow.GetCheck();
	m_pCurFontBaseProp->SetEffect(FE_SHADOW, (nCheck == 1));
	m_FontProViewStatic.RedrawView(m_pCurFontBaseProp);
}

void CModifyFontBaseDlg::OnBnClickedObscureEffect()
{
	if (m_pCurFontBaseProp == NULL || m_pCurFontBaseProp->GetFontProp() == NULL)
		return;

	int nCheck = m_EffectShadow.GetCheck();
	m_pCurFontBaseProp->SetEffect(FE_OBSCURE, (nCheck == 1));
	m_FontProViewStatic.RedrawView(m_pCurFontBaseProp);
}

void CModifyFontBaseDlg::OnBnClickedSelectFont()
{
	USES_CONVERSION;
	if (m_pFontBaseMap == NULL || m_pCurFontBaseProp == NULL || m_pCurFontBaseProp->GetFontProp() == NULL)
		return;

	FONT_PROP* pFontProp = m_pCurFontBaseProp->GetFontProp();

	LOGFONTW wFont;
	LOGFONT_W_A(wFont, pFontProp->Font, false);

	CFontDialog FontDlg(&wFont);
	if (FontDlg.DoModal() == IDOK)
	{
		FontDlg.GetCurrentFont(&wFont);
		LOGFONT_W_A(wFont, pFontProp->Font, true);

		CString strFontInfo(_T(""));
		strFontInfo.Format(_T("%s，%d"), A2W(pFontProp->Font.lfFaceName), pFontProp->Font.lfHeight);
		this->GetDlgItem(IDE_FONT_INFO_EDIT)->SetWindowText(strFontInfo);

		m_FontProViewStatic.RedrawView(m_pCurFontBaseProp);
	}
}

void CModifyFontBaseDlg::LOGFONT_W_A(LOGFONTW& wFont, LOGFONTA &aFont, bool bW2A)
{
	USES_CONVERSION;
	if (bW2A)
	{
		aFont.lfCharSet = wFont.lfCharSet;
		aFont.lfClipPrecision = wFont.lfClipPrecision;
		aFont.lfEscapement = wFont.lfEscapement;
		strcpy_s(aFont.lfFaceName, 32, W2A(wFont.lfFaceName));
		aFont.lfHeight = wFont.lfHeight;
		aFont.lfItalic = wFont.lfItalic;
		aFont.lfOrientation = wFont.lfOrientation;
		aFont.lfOutPrecision = wFont.lfOutPrecision;
		aFont.lfPitchAndFamily = wFont.lfPitchAndFamily;
		aFont.lfQuality = wFont.lfQuality;
		aFont.lfStrikeOut = wFont.lfStrikeOut;
		aFont.lfUnderline = wFont.lfUnderline;
		aFont.lfWeight = wFont.lfWeight;
		aFont.lfWidth = wFont.lfWidth;		
	}
	else
	{
		wFont.lfCharSet = aFont.lfCharSet;
		wFont.lfClipPrecision = aFont.lfClipPrecision;
		wFont.lfEscapement = aFont.lfEscapement;
		wcscpy_s(wFont.lfFaceName, 32, A2W(aFont.lfFaceName));
		wFont.lfHeight = aFont.lfHeight;
		wFont.lfItalic = aFont.lfItalic;
		wFont.lfOrientation = aFont.lfOrientation;
		wFont.lfOutPrecision = aFont.lfOutPrecision;
		wFont.lfPitchAndFamily = aFont.lfPitchAndFamily;
		wFont.lfQuality = aFont.lfQuality;
		wFont.lfStrikeOut = aFont.lfStrikeOut;
		wFont.lfUnderline = aFont.lfUnderline;
		wFont.lfWeight = aFont.lfWeight;
		wFont.lfWidth = aFont.lfWidth;	
	}
}

void CModifyFontBaseDlg::OnBnClickedSelectTextColor()
{
	if (m_pFontBaseMap == NULL || m_pCurFontBaseProp == NULL || m_pCurFontBaseProp->GetFontProp() == NULL)
		return;

	FONT_PROP* pFontProp = m_pCurFontBaseProp->GetFontProp();
	CMFCColorDialog ColorDlg(pFontProp->FontColor, 0, this);
	if (ColorDlg.DoModal() == IDOK)
	{
		pFontProp->FontColor = ColorDlg.GetColor();
		m_FontProViewStatic.RedrawView(m_pCurFontBaseProp);
	}
}

void CModifyFontBaseDlg::OnBnClickedPictureText()
{
	if (m_pCurFontBaseProp == NULL || m_pCurFontBaseProp->GetFontProp() == NULL)
		return;

	int nCheck = m_PictureTextCheckBox.GetCheck();
	FONT_PROP* pFontProp = m_pCurFontBaseProp->GetFontProp();
	pFontProp->bIsPicText = (nCheck == 1);
	m_FontProViewStatic.RedrawView(m_pCurFontBaseProp);
}
