
#pragma once
#include "ModifyPropBaseNameDlg.h"
#include "..\..\inc\IPropertyBase.h"
#include "..\..\inc\IUiFeatureKernel.h"
#include "..\..\inc\IPropertyFont.h"
#include "FontBaseNameList.h"


// CModifyFontBaseDlg dialog

class CModifyFontBaseDlg : public CDialog
{
	DECLARE_DYNAMIC(CModifyFontBaseDlg)

public:
	CModifyFontBaseDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CModifyFontBaseDlg();

// Dialog Data
	enum { IDD = IDD_FONT_EDIT_DLG };

	void InitFontBaseShow(IUiFeatureKernel* pUiKernel, IPropertyFont* pParentFontProp);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	CFontBaseNameList m_FontBaseNameList;
	CModifyPropBaseNameDlg m_ModifyFontDlg;

	IPropertyFont* m_pParentFontProp;
	ONE_RESOURCE_PROP_MAP* m_pFontBaseMap;


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedSelectFont();
	afx_msg void OnBnClickedSelectTextColor();
	afx_msg void OnBnClickedNewFontBase();
	afx_msg void OnBnClickedDeleteFontBase();
	afx_msg void OnBnClickedEditFontBase();
	virtual BOOL OnInitDialog();
};
