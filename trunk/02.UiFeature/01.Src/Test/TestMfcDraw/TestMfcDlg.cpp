
// TestMfcDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestMfc.h"
#include "TestMfcDlg.h"
#include "..\..\Inc\ICommonFun.h"
#include "..\..\Inc\UiFeatureDefs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestMfcDlg 对话框




CTestMfcDlg::CTestMfcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestMfcDlg::IDD, pParent)
{
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strText = "给你生活的忠告：多吃些粗粮，给别人比他们自己期许的更多，并且用心去做；熟记你喜欢的诗歌；不要轻信你听到的每件事；不要花光你的所有；不要想睡多久就睡多久；无论何时说“我爱你”，请真心实意；无论何时说“对不起”，请看着对方的眼睛；相信一见钟情；永远不要忽视别人的梦想；深情热烈地爱，也许你会受伤，但这是使人生完整的唯一方法；用一种明确的方法解决争议，不要冒犯；永远不要以貌取人；慢慢地说，但要迅速地想；当别人问你不想回答的问题时，笑着说“你为什么想知道？”。";

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


// CTestMfcDlg 消息处理程序

CTestMfcDlg::~CTestMfcDlg()
{
	GdiplusShutdown(m_gdiplusToken);
}

BOOL CTestMfcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestMfcDlg::OnPaint()
{
	USES_CONVERSION;
	CPaintDC dc(this);

	RECT ClientRct;
	INIT_RECT(ClientRct);
	this->GetClientRect(&ClientRct);

	DstDc.Create(RECT_WIDTH(ClientRct), RECT_HEIGHT(ClientRct), 0, false, true);

	Graphics DoGrap(DstDc.GetSafeHdc());

	SolidBrush BkSBrush(Color(255, 255, 255, 255));

	RectF ToRctF;
	ToRctF.X = ClientRct.left;
	ToRctF.Y = ClientRct.top;
	ToRctF.Width = RECT_WIDTH(ClientRct);
	ToRctF.Height = RECT_HEIGHT(ClientRct);

	DoGrap.FillRectangle(&BkSBrush, ToRctF);

	TestDrawText();

	::BitBlt(dc.m_hDC, 0, 0, RECT_WIDTH(ClientRct), RECT_HEIGHT(ClientRct), DstDc.GetSafeHdc(), 0, 0, SRCCOPY);
}

void CTestMfcDlg::TestDrawText()
{
	USES_CONVERSION;

	Graphics DoGrap(DstDc.GetSafeHdc());

	RectF OutFct;
	OutFct.X = 30;
	OutFct.Y = 30;
	OutFct.Width = 200;
	OutFct.Height = 50;

	SolidBrush frameSBrush(Color(255, 255, 0, 0));

	Pen framePen(&frameSBrush);
	DoGrap.DrawRectangle(&framePen, OutFct);

	FONT_PROP* pFont = m_FontPropBase.GetFontProp();
	FONT_PROP m_FontProp = *pFont;

//	m_strText = "ABCDEFGHIGKABCDEFGHIGKABCDEFGHIGKABCDEFGHIGKABCDEFGHIGKABCDEFGHIGKABCDEFGHIGKABCDEFGHIGK";
//	m_FontProp.ShowMode = FSM_ONE_ROW_POINT;

//////////////////////////////////////////////////////////////////////////

	// 字体
	Gdiplus::Font TextFont(DstDc.GetSafeHdc(), &(m_FontProp.Font));
	// 文字颜色
	SolidBrush textBrush(Color(MAX_ALPHA, GetRValue(m_FontProp.FontColor), GetGValue(m_FontProp.FontColor), GetBValue(m_FontProp.FontColor)));

	Gdiplus::StringFormat strFormat;
	// 文字输出 & 变成下划线问题
	strFormat.SetHotkeyPrefix(HotkeyPrefixNone);
	// 文字显示效果：在文字显示范围内，最底下的一行如果只出现了上半部分，这一行将不会被显示
	strFormat.SetFormatFlags(StringFormatFlagsLineLimit);

	// 设置垂直对齐模式
	if (m_FontProp.VAligning == FAL_RIGHT_BOTTOM)
	{
		// 垂直靠下
		strFormat.SetLineAlignment(StringAlignmentFar);
	}
	else if (m_FontProp.VAligning == FAL_MIDDLE)
	{
		// 垂直居中
		strFormat.SetLineAlignment(StringAlignmentCenter);
	}
	else
	{
		// 垂直靠上
		strFormat.SetLineAlignment(StringAlignmentNear);
	}

	// 设置水平对齐
	if (m_FontProp.HAligning == FAL_RIGHT_BOTTOM)
	{
		// 水平靠右
		strFormat.SetAlignment(StringAlignmentFar);
	}
	else if (m_FontProp.HAligning == FAL_MIDDLE)
	{
		// 水平居中
		strFormat.SetAlignment(StringAlignmentCenter);
	}
	else
	{
		// 水平靠左
		strFormat.SetAlignment(StringAlignmentNear);
	}

	// GDI+默认折行显示，末尾不带...
	if (m_FontProp.ShowMode != FSM_MULTI_ROW)
	{
		// 不折行显示
		strFormat.SetFormatFlags(StringFormatFlagsNoWrap);
		// 不折行显示，默认末尾不带...
		if (m_FontProp.ShowMode == FSM_ONE_ROW_POINT)
		{
			// 单行显示，超过显示范围显示...
			strFormat.SetTrimming(StringTrimmingEllipsisCharacter);
		}
	}

	if (m_FontPropBase.GetEffectState(FE_SHADOW))
	{
		// 阴影文字
	}

	if (m_FontPropBase.GetEffectState(FE_OBSCURE))
	{
		// 模糊文字
	}

	DoGrap.DrawString(A2W(m_strText.c_str()), m_strText.size(), &TextFont, OutFct, &strFormat, &textBrush);
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTestMfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTestMfcDlg::OnBnClickedOk()
{
}

void CTestMfcDlg::OnBnClickedCancel()
{
	OnCancel();
}
