#pragma once
#include "afxcmn.h"
#include "MouseStyleList.h"
#include "..\..\Inc\IUiFeatureKernel.h"
#include "..\..\Inc\IPropertyCursor.h"


// CModifyMouseStyleDlg dialog

class CModifyMouseStyleDlg : public CDialog
{
	DECLARE_DYNAMIC(CModifyMouseStyleDlg)

public:
	CModifyMouseStyleDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CModifyMouseStyleDlg();

// Dialog Data
	enum { IDD = IDD_MOUSE_STYLE_EDIT_DLG };

	void InitCursorBaseShow(IUiFeatureKernel* pUiKernel, IPropertyCursor* pParentCursorProp);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	CMouseStyleList m_MouseStyleList;

	IPropertyCursor* m_pParentCursorProp;
	ONE_RESOURCE_PROP_MAP* m_pCursorBaseMap;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
};
