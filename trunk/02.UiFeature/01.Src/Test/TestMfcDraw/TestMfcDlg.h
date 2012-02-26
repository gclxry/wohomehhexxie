
// TestMfcDlg.h : ͷ�ļ�
//

#pragma once
#include "..\..\Inc\CDrawingBoard.h"
#include "..\..\Inc\IPropertyFontBase.h"

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
	ULONG_PTR m_gdiplusToken;
	CDrawingBoard DstDc;
	IPropertyFontBase m_FontPropBase;
	string m_strText;

	void TestDrawText();
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
