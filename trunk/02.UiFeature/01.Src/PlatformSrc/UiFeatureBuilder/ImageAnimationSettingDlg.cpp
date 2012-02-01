// ImageAnimationSettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UiFeatureBuilder.h"
#include "ImageAnimationSettingDlg.h"


// CImageAnimationSettingDlg dialog

IMPLEMENT_DYNAMIC(CImageAnimationSettingDlg, CDialog)

CImageAnimationSettingDlg::CImageAnimationSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImageAnimationSettingDlg::IDD, pParent)
	, m_nImagePlayType(0)
{
	m_pImageBase = NULL;
}

CImageAnimationSettingDlg::~CImageAnimationSettingDlg()
{
}

void CImageAnimationSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDR_IMG_ANIMATION_STATIC_IMG, m_nImagePlayType);
	DDX_Control(pDX, IDC_IMG_PLAY_SHUNXU, m_BofangTypeComboBox);
	DDX_Control(pDX, IDC_IMG_XUNHUAN_CTNS, m_LoopTypeComboBox);
}


BEGIN_MESSAGE_MAP(CImageAnimationSettingDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CImageAnimationSettingDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CImageAnimationSettingDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDR_IMG_ANIMATION_STATIC_IMG, &CImageAnimationSettingDlg::OnBnClickedImgAnimationStaticImg)
	ON_BN_CLICKED(IDR_IMG_ANIMATION_GIF, &CImageAnimationSettingDlg::OnBnClickedImgAnimationGif)
	ON_BN_CLICKED(IDR_IMG_ANIMATION_XULIE, &CImageAnimationSettingDlg::OnBnClickedImgAnimationXulie)
	ON_CBN_SELCHANGE(IDC_IMG_PLAY_SHUNXU, &CImageAnimationSettingDlg::OnCbnSelchangeImgPlayShunxu)
	ON_CBN_SELCHANGE(IDC_IMG_XUNHUAN_CTNS, &CImageAnimationSettingDlg::OnCbnSelchangeImgXunhuanCtns)
END_MESSAGE_MAP()


// CImageAnimationSettingDlg message handlers

void CImageAnimationSettingDlg::OnBnClickedOk()
{
	OnOK();
}

void CImageAnimationSettingDlg::OnBnClickedCancel()
{
	OnCancel();
}

void CImageAnimationSettingDlg::SetImageBase(IPropertyImageBase *pImageBase)
{
	if (pImageBase == NULL)
		m_pImageBase = NULL;
	else
		m_pImageBase = pImageBase->GetImageProp();
}

BOOL CImageAnimationSettingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_BofangTypeComboBox.InsertString(0, _T("正向播放"));
	m_BofangTypeComboBox.InsertString(1, _T("反向播放"));
	m_BofangTypeComboBox.SetCurSel(0);

	m_LoopTypeComboBox.InsertString(0, _T("循环一次"));
	m_LoopTypeComboBox.InsertString(1, _T("无限循环"));
	m_LoopTypeComboBox.SetCurSel(0);

	if (m_pImageBase != NULL)
	{
		m_nImagePlayType = m_pImageBase->ImgPlayType;
		m_BofangTypeComboBox.SetCurSel(m_pImageBase->ImgBoFangType);
		m_LoopTypeComboBox.SetCurSel(m_pImageBase->ImgLoopType);
	}
	this->UpdateData(FALSE);
	EnableAnimationSetting();

	return TRUE;
}

void CImageAnimationSettingDlg::OnBnClickedImgAnimationStaticImg()
{
	OnBnClickedImgAnimationXulie();
}

void CImageAnimationSettingDlg::OnBnClickedImgAnimationGif()
{
	OnBnClickedImgAnimationXulie();
}

void CImageAnimationSettingDlg::OnBnClickedImgAnimationXulie()
{
	this->UpdateData(TRUE);
	if (m_pImageBase != NULL)
		m_pImageBase->ImgPlayType = (IMAGE_PLAY_TYPE)m_nImagePlayType;

	EnableAnimationSetting();
}

void CImageAnimationSettingDlg::OnCbnSelchangeImgPlayShunxu()
{
	m_pImageBase->ImgBoFangType = (IMAGE_BOFANG_TYPE)m_BofangTypeComboBox.GetCurSel();
}

void CImageAnimationSettingDlg::OnCbnSelchangeImgXunhuanCtns()
{
	m_pImageBase->ImgLoopType = (IMAGE_LOOP_TYPE)m_LoopTypeComboBox.GetCurSel();
}

void CImageAnimationSettingDlg::EnableAnimationSetting()
{
	m_BofangTypeComboBox.EnableWindow(m_nImagePlayType != IPT_STATIC_IMG);
	m_LoopTypeComboBox.EnableWindow(m_nImagePlayType != IPT_STATIC_IMG);
}
