
// TestMfcDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestMfc.h"
#include "TestMfcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestMfcDlg �Ի���




CTestMfcDlg::CTestMfcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestMfcDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_hKernelDll = NULL;
	m_pWindowBase = NULL;
}

void CTestMfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestMfcDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CTestMfcDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTestMfcDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CTestMfcDlg ��Ϣ�������

CTestMfcDlg::~CTestMfcDlg()
{
	if (m_hKernelDll != NULL)
	{
		::FreeLibrary(m_hKernelDll);
		m_hKernelDll = NULL;
	}
}

BOOL CTestMfcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��


//////////////////////////////////////////////////////////////////////////
	char szPath[MAX_PATH + 1];
	memset(szPath, 0, MAX_PATH + 1);
	::GetModuleFileNameA(NULL, szPath, MAX_PATH);
	while (strlen(szPath) > 0 && szPath[strlen(szPath) - 1] != '\\')
		szPath[strlen(szPath) - 1] = '\0';

	string strPath = szPath;
	strPath += "UiFeatureKernel.dll";

	m_hKernelDll = ::LoadLibraryA(strPath.c_str());
	if (m_hKernelDll != NULL)
	{
		GETKERNELWINDOWINTERFACE GetKernel = (GETKERNELWINDOWINTERFACE)::GetProcAddress(m_hKernelDll, "GetKernelWindowInterface");
		if (GetKernel != NULL)
		{
			IKernelWindow *pKernelWnd = GetKernel();
			if (pKernelWnd != NULL)
			{
				// TBD
				string strUfd = szPath;
				strUfd += SKIN_DATA_DIR;
				strUfd += "skintest.ufd";
				m_pWindowBase = pKernelWnd->PG_InitFeatureSkin(m_hWnd, (char*)strUfd.c_str(), "���Դ���");
			}
		}
	}
//////////////////////////////////////////////////////////////////////////

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestMfcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTestMfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTestMfcDlg::OnBnClickedOk()
{
}

void CTestMfcDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}
