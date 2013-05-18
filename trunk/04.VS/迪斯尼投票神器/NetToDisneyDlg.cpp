
// NetToDisneyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NetToDisney.h"
#include "NetToDisneyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNetToDisneyDlg �Ի���




CNetToDisneyDlg::CNetToDisneyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNetToDisneyDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nTimerId = 0;
	m_nCurrentPost = 0;
}

void CNetToDisneyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_WebCtrl);
}

BEGIN_MESSAGE_MAP(CNetToDisneyDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDCANCEL, &CNetToDisneyDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CNetToDisneyDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDB_BEGIN, &CNetToDisneyDlg::OnBnClickedBegin)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CNetToDisneyDlg ��Ϣ�������

BOOL CNetToDisneyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	InitUrl();

	CString strData = L"";
	strData.Format(L"%d", m_UrlList.GetSize());
	this->SetDlgItemText(IDE_ZONGSHU, strData);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CNetToDisneyDlg::OnPaint()
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
HCURSOR CNetToDisneyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CNetToDisneyDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void CNetToDisneyDlg::OnBnClickedOk()
{
	OnBnClickedBegin();
}

BEGIN_EVENTSINK_MAP(CNetToDisneyDlg, CDialog)
	ON_EVENT(CNetToDisneyDlg, IDC_EXPLORER1, 270, CNetToDisneyDlg::FileDownloadExplorer1, VTS_BOOL VTS_PBOOL)
END_EVENTSINK_MAP()

void CNetToDisneyDlg::FileDownloadExplorer1(BOOL ActiveDocument, BOOL* Cancel)
{
	if (Cancel != NULL)
		*Cancel = true;
}

void CNetToDisneyDlg::OnBnClickedBegin()
{
	srand((unsigned int)time(0));

	BeginTimer();
	this->GetDlgItem(IDB_BEGIN)->EnableWindow(FALSE);
}

const WCHAR* CNetToDisneyDlg::PathHelperW(LPCWSTR pszFileName)
{
	static WCHAR _sszDir[MAX_PATH + 1];
	memset(_sszDir, 0, sizeof(_sszDir));
	::GetModuleFileNameW(NULL, _sszDir, MAX_PATH);
	::PathRemoveFileSpecW(_sszDir);

	wcscat_s(_sszDir, MAX_PATH, L"\\");
	if (pszFileName != NULL && wcslen(pszFileName) > 0)
		wcscat_s(_sszDir, MAX_PATH, pszFileName);

	return _sszDir;
}

bool CNetToDisneyDlg::InitUrl()
{
	CString strPath = PathHelperW(L"url.txt");

	CStdioFile urlFile;
	if (!urlFile.Open(strPath, CFile::modeRead))
	{
		AfxMessageBox(L"�Ҳ��������ļ���");
		return false;
	}

	CString strUrl = L"";
	while (urlFile.ReadString(strUrl))
	{
		if (strUrl.GetLength() <= 4)
			continue;

		m_UrlList.Add(strUrl);
	}
	urlFile.Close();
	return true;
}

int CNetToDisneyDlg::GetTime()
{
	int nTime = 5;
	//while(true)
	//{
	//	nTime = rand() % 33;
	//	if (nTime >= 17)
	//		break;
	//}

	CString strData = L"";
	strData.Format(L"��һƱ��ͶƱʱ�䣺%d ��", nTime);
	this->SetDlgItemText(IDE_INFO, strData);
	return (nTime * 1000);
}

void CNetToDisneyDlg::BeginTimer()
{
	m_nTimerId = 1;
	this->SetTimer(m_nTimerId, GetTime(), NULL);
}

void CNetToDisneyDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (m_nTimerId == nIDEvent)
	{
		if (m_nCurrentPost < m_UrlList.GetSize())
		{
			CString strData = m_UrlList[m_nCurrentPost++];

			CString strUrl = L"";

			int nR = rand() % 8000;

			strUrl.Format(L"%s%d", strData, nR);
			this->SetDlgItemText(IDE_URL, strUrl);

			m_WebCtrl.Navigate(strUrl, NULL, NULL, NULL, NULL);

			strData.Format(L"%d", m_nCurrentPost);
			this->SetDlgItemText(IDE_TOULEDE, strData);
		}

		this->KillTimer(m_nTimerId);
		m_nTimerId = 0;

		if (m_nCurrentPost < m_UrlList.GetSize())
		{
			BeginTimer();
		}
		else
		{
			CString strData = L"";
			strData.Format(L"ͶƱ��ϣ�һ��Ͷ�� %d Ʊ��������������", m_nCurrentPost);
			this->SetDlgItemText(IDE_TOULEDE, strData);
			this->SetDlgItemText(IDE_INFO, strData);

			this->MessageBox(strData);
		}
	}

	CDialog::OnTimer(nIDEvent);
}
