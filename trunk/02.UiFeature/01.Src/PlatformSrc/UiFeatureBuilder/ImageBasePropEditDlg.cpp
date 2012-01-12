// ImageBasePropEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UiFeatureBuilder.h"
#include "ImageBasePropEditDlg.h"
#include "..\..\Inc\UiFeatureDefs.h"


// CImageBasePropEditDlg dialog

IMPLEMENT_DYNAMIC(CImageBasePropEditDlg, CDialog)

CImageBasePropEditDlg::CImageBasePropEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImageBasePropEditDlg::IDD, pParent)
	, m_nShowAreaTop(0)
	, m_nShowAreaLeft(0)
	, m_nShowAreaBottom(0)
	, m_nShowAreaRight(0)
	, m_nJggLeft(0)
	, m_nJggTop(0)
	, m_nJggRight(0)
	, m_nJggBottom(0)
	, m_nSelelShowImgType(0)
{
	m_pImageView = NULL;
	m_pUiKernel = NULL;
	m_pParentImgProp = NULL;
}

CImageBasePropEditDlg::~CImageBasePropEditDlg()
{
	SAFE_DELETE(m_pImageView);
}

void CImageBasePropEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDS_FRAME_1, m_Static_1);
	DDX_Control(pDX, IDS_FRAME_2, m_Static_2);
	DDX_Control(pDX, IDS_FRAME_3, m_Static_3);
	DDX_Control(pDX, IDOK, m_OkBtn);
	DDX_Control(pDX, IDL_IMAGEBASE_NAME_LIST, m_ImageBaseList);
	DDX_Control(pDX, IDL_LOCAL_IMAGE_LIST, m_LocalImageList);
	DDX_Text(pDX, IDE_SHOW_AREA_TOP, m_nShowAreaTop);
	DDX_Text(pDX, IDE_SHOW_AREA_LEFT, m_nShowAreaLeft);
	DDX_Text(pDX, IDE_SHOW_AREA_BOTTOM, m_nShowAreaBottom);
	DDX_Text(pDX, IDE_SHOW_AREA_RIGHT, m_nShowAreaRight);
	DDX_Text(pDX, IDE_JJG_LEFT, m_nJggLeft);
	DDX_Text(pDX, IDE_JJG_TOP, m_nJggTop);
	DDX_Text(pDX, IDE_JJG_RIGHT, m_nJggRight);
	DDX_Text(pDX, IDE_JJG_BOTTOM, m_nJggBottom);
	DDX_Control(pDX, IDC_XIANSHIBILI_COMBO, m_ShowBiLi_Combo);
	DDX_Radio(pDX, IDR_PINGPU, m_nSelelShowImgType);
}


BEGIN_MESSAGE_MAP(CImageBasePropEditDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CImageBasePropEditDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDB_NEW_IMAGEBASE, &CImageBasePropEditDlg::OnBnClickedNewImagebase)
	ON_BN_CLICKED(IDB_DELETE_IMAGEBASE, &CImageBasePropEditDlg::OnBnClickedDeleteImagebase)
	ON_BN_CLICKED(IDB_EDIT_IMAGEBASE, &CImageBasePropEditDlg::OnBnClickedEditImagebase)
	ON_BN_CLICKED(IDCANCEL, &CImageBasePropEditDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDB_GET_LOCAL_IMAGE, &CImageBasePropEditDlg::OnBnClickedGetLocalImage)
	ON_BN_CLICKED(IDB_DELETE_LOCAL_IMAGE, &CImageBasePropEditDlg::OnBnClickedDeleteLocalImage)
	ON_BN_CLICKED(IDR_PINGPU, &CImageBasePropEditDlg::OnBnClickedPingpu)
	ON_BN_CLICKED(IDR_QUANLASHEN, &CImageBasePropEditDlg::OnBnClickedQuanlashen)
	ON_BN_CLICKED(IDR_JJG, &CImageBasePropEditDlg::OnBnClickedJjg)
	ON_NOTIFY(UDN_DELTAPOS, IDS_SHOW_AREA_LEFT, &CImageBasePropEditDlg::OnDeltaposShowAreaLeft)
	ON_NOTIFY(UDN_DELTAPOS, IDS_SHOW_AREA_TOP, &CImageBasePropEditDlg::OnDeltaposShowAreaTop)
	ON_NOTIFY(UDN_DELTAPOS, IDS_SHOW_AREA_RIGHT, &CImageBasePropEditDlg::OnDeltaposShowAreaRight)
	ON_NOTIFY(UDN_DELTAPOS, IDS_SHOW_AREA_BOTTOM, &CImageBasePropEditDlg::OnDeltaposShowAreaBottom)
	ON_NOTIFY(UDN_DELTAPOS, IDS_JJG_LEFT, &CImageBasePropEditDlg::OnDeltaposJjgLeft)
	ON_NOTIFY(UDN_DELTAPOS, IDS_JJG_TOP, &CImageBasePropEditDlg::OnDeltaposJjgTop)
	ON_NOTIFY(UDN_DELTAPOS, IDS_JJG_BOTTOM, &CImageBasePropEditDlg::OnDeltaposJjgBottom)
	ON_NOTIFY(UDN_DELTAPOS, IDS_JJG_RIGHT, &CImageBasePropEditDlg::OnDeltaposJjgRight)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()


// CImageBasePropEditDlg message handlers

void CImageBasePropEditDlg::SetChildPos()
{
	if (!::IsWindow(m_hWnd))
		return;

	CRect WndRct;
	this->GetClientRect(&WndRct);

	CRect CtrlRct(0, 0, 0, 0);
	if (::IsWindow(m_Static_1.m_hWnd))
	{
		CtrlRct.SetRectEmpty();
		CtrlRct.left = 11;
		CtrlRct.right = CtrlRct.left + 218;
		CtrlRct.top = 11;
		CtrlRct.bottom = WndRct.bottom - 11;
		m_Static_1.MoveWindow(&CtrlRct);
	}

	if (::IsWindow(m_ImageBaseList.m_hWnd))
	{
		CtrlRct.SetRectEmpty();
		CtrlRct.left = 22;
		CtrlRct.right = CtrlRct.left + 196;
		CtrlRct.top = 70;
		CtrlRct.bottom = WndRct.bottom - 22;
		m_ImageBaseList.MoveWindow(&CtrlRct);
	}

	if (::IsWindow(m_Static_2.m_hWnd))
	{
		CtrlRct.SetRectEmpty();
		CtrlRct.left = 240;
		CtrlRct.right = WndRct.right - 11;
		CtrlRct.top = 11;
		CtrlRct.bottom = WndRct.bottom - 11;
		m_Static_2.MoveWindow(&CtrlRct);
	}

	if (m_pImageView != NULL && ::IsWindow(m_pImageView->m_hWnd))
	{
		CtrlRct.SetRectEmpty();
		CtrlRct.left = 440;
		CtrlRct.right = WndRct.right - 22;
		CtrlRct.top = 50;
		CtrlRct.bottom = WndRct.bottom - 22;
		m_pImageView->MoveWindow(&CtrlRct);
	}

	if (::IsWindow(m_Static_3.m_hWnd))
	{
		CtrlRct.SetRectEmpty();
		CtrlRct.left = 251;
		CtrlRct.right = CtrlRct.left + 179;
		CtrlRct.top = 308;
		CtrlRct.bottom = WndRct.bottom - 22;
		m_Static_3.MoveWindow(&CtrlRct);
	}

	if (::IsWindow(m_LocalImageList.m_hWnd))
	{
		CtrlRct.SetRectEmpty();
		CtrlRct.left = 262;
		CtrlRct.right = CtrlRct.left + 157;
		CtrlRct.top = 359;
		CtrlRct.bottom = WndRct.bottom - 33;
		m_LocalImageList.MoveWindow(&CtrlRct);
	}

	if (::IsWindow(m_OkBtn.m_hWnd))
	{
		CtrlRct.SetRectEmpty();
		CtrlRct.right = WndRct.right - 22;
		CtrlRct.left = CtrlRct.right - 80;
		CtrlRct.top = 22;
		CtrlRct.bottom = CtrlRct.top + 22;
		m_OkBtn.MoveWindow(&CtrlRct);
	}
}

BOOL CImageBasePropEditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_pImageView = new CImageBaseView(this);
	if (m_pImageView != NULL)
	{
		CRect ViewRct(0, 0, 0, 0);
		m_pImageView->MoveWindow(ViewRct);
		m_pImageView->ShowWindow(SW_SHOW);
	}
	SetChildPos();

	SetImageEditEnableStyle(false);

	m_ShowBiLi_Combo.InsertString(0, _T("100%"));
	m_ShowBiLi_Combo.InsertString(1, _T("200%"));
	m_ShowBiLi_Combo.InsertString(2, _T("400%"));
	m_ShowBiLi_Combo.InsertString(3, _T("600%"));
	m_ShowBiLi_Combo.InsertString(4, _T("800%"));
	m_ShowBiLi_Combo.InsertString(5, _T("1000%"));
	m_ShowBiLi_Combo.SetCurSel(0);

	m_ImageBaseList.Init(this, &m_LocalImageList);
	m_LocalImageList.Init(this);

	this->UpdateData(FALSE);
	return TRUE;
}

void CImageBasePropEditDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	SetChildPos();
}

void CImageBasePropEditDlg::OnBnClickedCancel()
{
	OnCancel();
}

void CImageBasePropEditDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnGetMinMaxInfo(lpMMI);

	if (lpMMI != NULL)
	{
		lpMMI->ptMinTrackSize.x = 966;
		lpMMI->ptMinTrackSize.y = 666;
	}
}

void CImageBasePropEditDlg::OnDeltaposShowAreaLeft(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	*pResult = 0;
	if (pNMUpDown == NULL)
		return;

	SetNewDeltaposValue(m_nShowAreaLeft, pNMUpDown->iDelta);
}

void CImageBasePropEditDlg::OnDeltaposShowAreaTop(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	*pResult = 0;
	if (pNMUpDown == NULL)
		return;

	SetNewDeltaposValue(m_nShowAreaTop, pNMUpDown->iDelta);
}

void CImageBasePropEditDlg::OnDeltaposShowAreaRight(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	*pResult = 0;
	if (pNMUpDown == NULL)
		return;

	SetNewDeltaposValue(m_nShowAreaRight, pNMUpDown->iDelta);
}

void CImageBasePropEditDlg::OnDeltaposShowAreaBottom(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	*pResult = 0;
	if (pNMUpDown == NULL)
		return;

	SetNewDeltaposValue(m_nShowAreaBottom, pNMUpDown->iDelta);
}

void CImageBasePropEditDlg::OnDeltaposJjgLeft(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	*pResult = 0;
	if (pNMUpDown == NULL)
		return;

	SetNewDeltaposValue(m_nJggLeft, pNMUpDown->iDelta);
}

void CImageBasePropEditDlg::OnDeltaposJjgTop(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	*pResult = 0;
	if (pNMUpDown == NULL)
		return;

	SetNewDeltaposValue(m_nJggTop, pNMUpDown->iDelta);
}

void CImageBasePropEditDlg::OnDeltaposJjgBottom(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	*pResult = 0;
	if (pNMUpDown == NULL)
		return;

	SetNewDeltaposValue(m_nJggBottom, pNMUpDown->iDelta);
}

void CImageBasePropEditDlg::OnDeltaposJjgRight(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	*pResult = 0;
	if (pNMUpDown == NULL)
		return;

	SetNewDeltaposValue(m_nJggRight, pNMUpDown->iDelta);
}

void CImageBasePropEditDlg::SetNewDeltaposValue(int &nSetValue, int nDelta)
{
	if (nDelta == -1)
		nSetValue++;
	else
		nSetValue--;

	if (nSetValue < 0)
		nSetValue = 0;

	this->UpdateData(FALSE);
}

void CImageBasePropEditDlg::OnBnClickedPingpu()
{
	this->UpdateData(TRUE);
	SetJjgEditCtrlStyle(FALSE);
}

void CImageBasePropEditDlg::OnBnClickedQuanlashen()
{
	this->UpdateData(TRUE);
	SetJjgEditCtrlStyle(FALSE);
}

void CImageBasePropEditDlg::OnBnClickedJjg()
{
	this->UpdateData(TRUE);
	SetJjgEditCtrlStyle(TRUE);
}

void CImageBasePropEditDlg::SetJjgEditCtrlStyle(bool bEnable)
{
	if (!::IsWindow(m_hWnd))
		return;

	this->GetDlgItem(IDE_JJG_LEFT)->EnableWindow(bEnable);
	this->GetDlgItem(IDS_JJG_LEFT)->EnableWindow(bEnable);
	this->GetDlgItem(IDE_JJG_TOP)->EnableWindow(bEnable);
	this->GetDlgItem(IDS_JJG_TOP)->EnableWindow(bEnable);
	this->GetDlgItem(IDE_JJG_RIGHT)->EnableWindow(bEnable);
	this->GetDlgItem(IDS_JJG_RIGHT)->EnableWindow(bEnable);
	this->GetDlgItem(IDE_JJG_BOTTOM)->EnableWindow(bEnable);
	this->GetDlgItem(IDS_JJG_BOTTOM)->EnableWindow(bEnable);
}

void CImageBasePropEditDlg::SetImageEditEnableStyle(bool bEnable)
{
	if (bEnable)
	{
		// 九宫格状态
		SetJjgEditCtrlStyle(m_nSelelShowImgType == 2);
	}
	else
	{
		// 九宫格状态
		SetJjgEditCtrlStyle(false);
	}

	this->GetDlgItem(IDB_DELETE_IMAGEBASE)->EnableWindow(bEnable);
	this->GetDlgItem(IDB_EDIT_IMAGEBASE)->EnableWindow(bEnable);
	this->GetDlgItem(IDE_SHOW_AREA_LEFT)->EnableWindow(bEnable);
	this->GetDlgItem(IDS_SHOW_AREA_LEFT)->EnableWindow(bEnable);
	this->GetDlgItem(IDE_SHOW_AREA_TOP)->EnableWindow(bEnable);
	this->GetDlgItem(IDS_SHOW_AREA_TOP)->EnableWindow(bEnable);
	this->GetDlgItem(IDE_SHOW_AREA_RIGHT)->EnableWindow(bEnable);
	this->GetDlgItem(IDS_SHOW_AREA_RIGHT)->EnableWindow(bEnable);
	this->GetDlgItem(IDE_SHOW_AREA_BOTTOM)->EnableWindow(bEnable);
	this->GetDlgItem(IDS_SHOW_AREA_BOTTOM)->EnableWindow(bEnable);
	this->GetDlgItem(IDR_PINGPU)->EnableWindow(bEnable);
	this->GetDlgItem(IDR_QUANLASHEN)->EnableWindow(bEnable);
	this->GetDlgItem(IDR_JJG)->EnableWindow(bEnable);
	this->GetDlgItem(IDOK)->EnableWindow(bEnable);
}

void CImageBasePropEditDlg::OnBnClickedOk()
{
	if (m_pParentImgProp == NULL)
	{
		OnCancel();
		return;
	}

	IPropertyImageBase* pImgBase = GetSelectImageBase();
	if (pImgBase == NULL)
	{
		OnCancel();
		return;
	}

	IPropertyImageBase* pOldImgBase = m_pParentImgProp->GetImageBaseProp();
	if (pOldImgBase != NULL)
	{
		// 当前使用计数器-1
		pOldImgBase->SetActivePropetry(false);
	}

	// 当前使用计数器+1
	pImgBase->SetActivePropetry(true);
	m_pParentImgProp->SetImageBaseProp(pImgBase);
	m_pParentImgProp->SetRelevancyPropName((char*)pImgBase->GetObjectName());

	OnOK();
}

void CImageBasePropEditDlg::InitImageBaseShow(IUiFeatureKernel* pUiKernel, IPropertyImage* pParentImgProp)
{
	m_pParentImgProp = pParentImgProp;
	m_pUiKernel = pUiKernel;
	m_ImageBaseList.InitImageBaseShow(pUiKernel, pParentImgProp);
}

IPropertyImageBase* CImageBasePropEditDlg::GetSelectImageBase()
{
	return m_ImageBaseList.GetSelectImageBase();
}

void CImageBasePropEditDlg::OnBnClickedNewImagebase()
{
	m_ModifyImgDlg.IsCreateImageBase(true);
	if (m_ModifyImgDlg.DoModal() != IDOK)
		return;

	CString strName;
	m_ModifyImgDlg.GetImageBaseName(strName);
	if (strName.GetLength() <= 0 || FindNameInImageBaseNameList(strName))
		return;

	if (!m_ImageBaseList.CreateImageBaseProp(strName))
	{
		AfxMessageBox(_T("创建图片属性失败！"), MB_OK | MB_ICONERROR);
		return;
	}
}

bool CImageBasePropEditDlg::FindNameInImageBaseNameList(CString &strName)
{
	for (int i = 0; i < m_ImageBaseList.GetItemCount(); i++)
	{
		CString strComName = m_ImageBaseList.GetItemText(i, 1);
		if (strComName.CompareNoCase(strName) == 0)
		{
			CString strInfo(_T(""));
			strInfo.Format(_T("已经存在名为【%s】的图片属性！"), strComName);
			AfxMessageBox(strInfo, MB_OK | MB_ICONERROR);
			return true;
		}
	}

	return false;
}

void CImageBasePropEditDlg::OnBnClickedEditImagebase()
{
	m_ModifyImgDlg.IsCreateImageBase(false);
	if (m_ModifyImgDlg.DoModal() != IDOK)
		return;



	CString strName;
	m_ModifyImgDlg.GetImageBaseName(strName);
	if (strName.GetLength() <= 0 || FindNameInImageBaseNameList(strName))
		return;

}

void CImageBasePropEditDlg::OnBnClickedDeleteImagebase()
{
	// TODO: Add your control notification handler code here
}

void CImageBasePropEditDlg::OnBnClickedGetLocalImage()
{
	// TODO: Add your control notification handler code here
}

void CImageBasePropEditDlg::OnBnClickedDeleteLocalImage()
{
	// TODO: Add your control notification handler code here
}
