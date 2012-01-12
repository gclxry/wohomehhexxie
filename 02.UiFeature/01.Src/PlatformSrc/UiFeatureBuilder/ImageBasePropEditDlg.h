#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "ImageBaseView.h"
#include "ModifyImageBaseDlg.h"
#include "ImageBaseNameList.h"
#include "LocalImageList.h"

// CImageBasePropEditDlg dialog

class CImageBasePropEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CImageBasePropEditDlg)

public:
	CImageBasePropEditDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CImageBasePropEditDlg();

	void SetImageEditEnableStyle(bool bEnable);

// Dialog Data
	enum { IDD = IDD_IMAGE_EDIT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	void SetChildPos();

	CStatic m_Static_1;
	CStatic m_Static_2;
	CStatic m_Static_3;
	CButton m_OkBtn;
	CImageBaseNameList m_ImageBaseList;
	CLocalImageList m_LocalImageList;

	CImageBaseView *m_pImageView;

	int m_nShowAreaLeft;
	int m_nShowAreaTop;
	int m_nShowAreaBottom;
	int m_nShowAreaRight;
	int m_nJggLeft;
	int m_nJggTop;
	int m_nJggRight;
	int m_nJggBottom;
	int m_nSelelShowImgType;
	CComboBox m_ShowBiLi_Combo;

	CModifyImageBaseDlg m_ModifyImgDlg;

private:
	void SetNewDeltaposValue(int &nSetValue, int nDelta);
	void SetJjgEditCtrlStyle(bool bEnable);
	bool FindNameInImageBaseNameList(CString &strName);

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
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
};
