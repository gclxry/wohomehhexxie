
#pragma once
#include "ModifyPropBaseNameDlg.h"
#include "..\..\inc\IPropertyBase.h"
#include "..\..\inc\IUiFeatureKernel.h"
#include "..\..\inc\IPropertyFont.h"
#include "..\..\inc\IPropertyFontBase.h"
#include "FontBaseNameList.h"
#include "FontProViewStatic.h"
#include "afxwin.h"
#include "afxcmn.h"


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
	void UpdateCurrentFontBaseProp(IPropertyFontBase* pCurFontBaseProp);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	CFontBaseNameList m_FontBaseNameList;
	CModifyPropBaseNameDlg m_ModifyFontDlg;

	IUiFeatureKernel* m_pUiKernel;
	IPropertyFont* m_pParentFontProp;
	IPropertyFontBase* m_pCurFontBaseProp;
	ONE_RESOURCE_PROP_MAP* m_pFontBaseMap;

	void LOGFONT_W_A(LOGFONTW& wFont, LOGFONTA &aFont, bool bW2A);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedSelectFont();
	afx_msg void OnBnClickedSelectTextColor();
	afx_msg void OnBnClickedNewFontBase();
	afx_msg void OnBnClickedDeleteFontBase();
	afx_msg void OnBnClickedEditFontBase();
	afx_msg void OnCbnSelchangeValigningCombo();
	afx_msg void OnCbnSelchangeHaligningCombo();
	afx_msg void OnBnClickedDanhangBuPoint();
	afx_msg void OnBnClickedDanhangXianshiPoint();
	afx_msg void OnBnClickedZhehangXianshi();
	afx_msg void OnBnClickedShadowEffect();
	afx_msg void OnBnClickedObscureEffect();
	afx_msg void OnBnClickedPictureText();
	virtual BOOL OnInitDialog();

protected:
	CComboBox m_VAligningCombo;
	CComboBox m_HAligningCombo;
	int m_nXianshiMode;
	CButton m_EffectShadow;
	CButton m_EffectObscure;
	CFontProViewStatic m_FontProViewStatic;
	CButton m_PictureTextCheckBox;
};
