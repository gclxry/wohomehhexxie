
#pragma once
#include "ModifyPropBaseNameDlg.h"


// CModifyFontBaseDlg dialog

class CModifyFontBaseDlg : public CDialog
{
	DECLARE_DYNAMIC(CModifyFontBaseDlg)

public:
	CModifyFontBaseDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CModifyFontBaseDlg();

// Dialog Data
	enum { IDD = IDD_FONT_EDIT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	CModifyPropBaseNameDlg m_ModifyFontDlg;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedSelectFont();
	afx_msg void OnBnClickedSelectTextColor();
	afx_msg void OnBnClickedNewFontBase();
	afx_msg void OnBnClickedDeleteFontBase();
	afx_msg void OnBnClickedEditFontBase();
};
