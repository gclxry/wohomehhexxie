#pragma once


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

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
