#pragma once


// CModifyImageBaseDlg dialog

class CModifyImageBaseDlg : public CDialog
{
	DECLARE_DYNAMIC(CModifyImageBaseDlg)

	void IsCreateImageBase(bool bIsCreate);
	void GetImageBaseName(CString &strName);

public:
	CModifyImageBaseDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CModifyImageBaseDlg();

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
