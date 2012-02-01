#pragma once
#include "afxwin.h"
#include "..\..\Inc\IPropertyImageBase.h"


// CImageAnimationSettingDlg dialog

class CImageAnimationSettingDlg : public CDialog
{
	DECLARE_DYNAMIC(CImageAnimationSettingDlg)

public:
	CImageAnimationSettingDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CImageAnimationSettingDlg();

// Dialog Data
	enum { IDD = IDD_IMAGE_ANIMATION_SETTING_DLG };

	void SetImageBase(IPropertyImageBase *pImageBase);

private:
	IMAGE_BASE_PROP *m_pImageBase;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void EnableAnimationSetting();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedImgAnimationStaticImg();
	afx_msg void OnBnClickedImgAnimationGif();
	afx_msg void OnBnClickedImgAnimationXulie();
	int m_nImagePlayType;
	CComboBox m_BofangTypeComboBox;
	CComboBox m_LoopTypeComboBox;
	afx_msg void OnCbnSelchangeImgPlayShunxu();
	afx_msg void OnCbnSelchangeImgXunhuanCtns();
	virtual BOOL OnInitDialog();
};
