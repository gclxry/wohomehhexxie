#pragma once


// CImageBasePropEditDlg dialog

class CImageBasePropEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CImageBasePropEditDlg)

public:
	CImageBasePropEditDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CImageBasePropEditDlg();

// Dialog Data
	enum { IDD = IDD_IMAGE_EDIT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedNewImagebase();
	afx_msg void OnBnClickedDeleteImagebase();
	afx_msg void OnBnClickedEditImagebase();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedGetLocalImage();
	afx_msg void OnBnClickedDeleteLocalImage();
	afx_msg void OnBnClickedPingpu();
	afx_msg void OnBnClickedQuanlashen();
	afx_msg void OnBnClickedJjg();
	afx_msg void OnDeltaposShowAreaLeft(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposShowAreaTop(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposShowAreaRight(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposShowAreaBottom(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposJjgLeft(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposJjgTop(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposJjgBottom(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposJjgRight(NMHDR *pNMHDR, LRESULT *pResult);
};
