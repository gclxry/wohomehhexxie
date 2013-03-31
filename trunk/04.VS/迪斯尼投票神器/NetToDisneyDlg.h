
// NetToDisneyDlg.h : 头文件
//

#pragma once
#include "explorer1.h"


// CNetToDisneyDlg 对话框
class CNetToDisneyDlg : public CDialog
{
// 构造
public:
	CNetToDisneyDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_NETTODISNEY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CExplorer1 m_WebCtrl;
	CStringArray m_UrlList;
	int m_nTimerId;
	int m_nCurrentPost;

	bool InitUrl();
	const WCHAR* PathHelperW(LPCWSTR pszFileName);
	int GetTime();
	void BeginTimer();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBegin();
	DECLARE_EVENTSINK_MAP()
	void FileDownloadExplorer1(BOOL ActiveDocument, BOOL* Cancel);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
