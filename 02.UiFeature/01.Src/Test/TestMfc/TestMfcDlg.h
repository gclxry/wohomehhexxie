
// TestMfcDlg.h : 头文件
//

#pragma once
#include "..\..\Inc\UiFeature.h"

// CTestMfcDlg 对话框
class CTestMfcDlg : public CDialog
{
// 构造
public:
	CTestMfcDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CTestMfcDlg();

// 对话框数据
	enum { IDD = IDD_TESTMFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	HMODULE m_hKernelDll;
	IWindowBase *m_pWindowBase;


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
