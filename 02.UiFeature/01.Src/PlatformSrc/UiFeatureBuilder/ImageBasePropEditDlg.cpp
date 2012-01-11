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
{
	m_pImageView = NULL;
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
	return TRUE;
}

void CImageBasePropEditDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	SetChildPos();
}

void CImageBasePropEditDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void CImageBasePropEditDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CImageBasePropEditDlg::OnBnClickedNewImagebase()
{
	// TODO: Add your control notification handler code here
}

void CImageBasePropEditDlg::OnBnClickedDeleteImagebase()
{
	// TODO: Add your control notification handler code here
}

void CImageBasePropEditDlg::OnBnClickedEditImagebase()
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

void CImageBasePropEditDlg::OnBnClickedPingpu()
{
	// TODO: Add your control notification handler code here
}

void CImageBasePropEditDlg::OnBnClickedQuanlashen()
{
	// TODO: Add your control notification handler code here
}

void CImageBasePropEditDlg::OnBnClickedJjg()
{
	// TODO: Add your control notification handler code here
}

void CImageBasePropEditDlg::OnDeltaposShowAreaLeft(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CImageBasePropEditDlg::OnDeltaposShowAreaTop(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CImageBasePropEditDlg::OnDeltaposShowAreaRight(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CImageBasePropEditDlg::OnDeltaposShowAreaBottom(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CImageBasePropEditDlg::OnDeltaposJjgLeft(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CImageBasePropEditDlg::OnDeltaposJjgTop(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CImageBasePropEditDlg::OnDeltaposJjgBottom(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CImageBasePropEditDlg::OnDeltaposJjgRight(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
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
