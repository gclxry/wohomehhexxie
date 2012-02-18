#pragma once
#include "afxcmn.h"
#include "MouseStyleList.h"


// CModifyMouseStyleDlg dialog

class CModifyMouseStyleDlg : public CDialog
{
	DECLARE_DYNAMIC(CModifyMouseStyleDlg)

public:
	CModifyMouseStyleDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CModifyMouseStyleDlg();

// Dialog Data
	enum { IDD = IDD_MOUSE_STYLE_EDIT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CMouseStyleList m_MouseStyleList;
	virtual BOOL OnInitDialog();
};
