#pragma once


// CModifyPropBaseNameDlg dialog

class CModifyPropBaseNameDlg : public CDialog
{
	DECLARE_DYNAMIC(CModifyPropBaseNameDlg)

	void IsCreate(bool bIsCreate);
	void GetPropBaseName(CString &strName);

public:
	CModifyPropBaseNameDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CModifyPropBaseNameDlg();

// Dialog Data
	enum { IDD = IDD_IMAGE_BASE_EDIT_CRATE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

private:
	bool m_bIsCreate;
	CString m_strImageBaseName;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
