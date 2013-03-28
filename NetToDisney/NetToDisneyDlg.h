
// NetToDisneyDlg.h : ͷ�ļ�
//

#pragma once
#include "explorer1.h"


// CNetToDisneyDlg �Ի���
class CNetToDisneyDlg : public CDialog
{
// ����
public:
	CNetToDisneyDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_NETTODISNEY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
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

	// ���ɵ���Ϣӳ�亯��
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
