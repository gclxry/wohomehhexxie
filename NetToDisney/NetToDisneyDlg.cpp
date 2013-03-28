
// NetToDisneyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "NetToDisney.h"
#include "NetToDisneyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNetToDisneyDlg 对话框

#define BEGIN_TIME		30
#define BEGIN_END		60




CNetToDisneyDlg::CNetToDisneyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNetToDisneyDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
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
END_MESSAGE_MAP()


// CNetToDisneyDlg 消息处理程序

BOOL CNetToDisneyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	InitUrl();

	CString strData = L"";
	strData.Format(L"%d", m_UrlList.GetSize());
	this->SetDlgItemText(IDE_ZONGSHU, strData);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CNetToDisneyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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
	m_WebCtrl.Navigate(L"http://www.dol.cn/concern/vote/cast.w?beVotedUid=vote1497868&actId=1&optionItem=1&voteItem=1497868&user=1497754&swid=F0690C88-573B-470F-99DE-895F8EFDBC79&rand=3919", NULL, NULL, NULL, NULL);

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
		AfxMessageBox(L"找不到数据文件！");
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
	int nTime = 30;
	srand((unsigned int)time(0));
	while(true)
	{
		nTime = rand() % 40;
		if (nTime >= 20)
			break;
	}

	return nTime;
}

int CNetToDisneyDlg::BeginTimer()
{

}