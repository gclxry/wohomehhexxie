
// TestMfcDlg.h : ͷ�ļ�
//

#pragma once
#include "..\..\Inc\UiFeature.h"

// CTestMfcDlg �Ի���
class CTestMfcDlg : public CDialog
{
// ����
public:
	CTestMfcDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CTestMfcDlg();

// �Ի�������
	enum { IDD = IDD_TESTMFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	HMODULE m_hKernelDll;
	IWindowBase *m_pWindowBase;


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
