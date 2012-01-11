// ImageBasePropEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UiFeatureBuilder.h"
#include "ImageBasePropEditDlg.h"


// CImageBasePropEditDlg dialog

IMPLEMENT_DYNAMIC(CImageBasePropEditDlg, CDialog)

CImageBasePropEditDlg::CImageBasePropEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImageBasePropEditDlg::IDD, pParent)
{

}

CImageBasePropEditDlg::~CImageBasePropEditDlg()
{
}

void CImageBasePropEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
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
END_MESSAGE_MAP()


// CImageBasePropEditDlg message handlers

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
