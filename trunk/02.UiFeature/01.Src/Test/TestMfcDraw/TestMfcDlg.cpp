
// TestMfcDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestMfc.h"
#include "TestMfcDlg.h"
#include "..\..\Inc\ICommonFun.h"
#include "..\..\Inc\UiFeatureDefs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestMfcDlg �Ի���




CTestMfcDlg::CTestMfcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestMfcDlg::IDD, pParent)
{
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strText = "����������Ҹ棺���Щ�����������˱������Լ�����ĸ��࣬��������ȥ���������ϲ����ʫ�裻��Ҫ������������ÿ���£���Ҫ����������У���Ҫ��˯��þ�˯��ã����ۺ�ʱ˵���Ұ��㡱��������ʵ�⣻���ۺ�ʱ˵���Բ��𡱣��뿴�ŶԷ����۾�������һ�����飻��Զ��Ҫ���ӱ��˵����룻�������ҵذ���Ҳ��������ˣ�������ʹ����������Ψһ��������һ����ȷ�ķ���������飬��Ҫð������Զ��Ҫ��òȡ�ˣ�������˵����ҪѸ�ٵ��룻���������㲻��ش������ʱ��Ц��˵����Ϊʲô��֪��������";

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
	GdiplusShutdown(m_gdiplusToken);
}

BOOL CTestMfcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

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

	// ����
	Gdiplus::Font TextFont(DstDc.GetSafeHdc(), &(m_FontProp.Font));
	// ������ɫ
	SolidBrush textBrush(Color(MAX_ALPHA, GetRValue(m_FontProp.FontColor), GetGValue(m_FontProp.FontColor), GetBValue(m_FontProp.FontColor)));

	Gdiplus::StringFormat strFormat;
	// ������� & ����»�������
	strFormat.SetHotkeyPrefix(HotkeyPrefixNone);
	// ������ʾЧ������������ʾ��Χ�ڣ�����µ�һ�����ֻ�������ϰ벿�֣���һ�н����ᱻ��ʾ
	strFormat.SetFormatFlags(StringFormatFlagsLineLimit);

	// ���ô�ֱ����ģʽ
	if (m_FontProp.VAligning == FAL_RIGHT_BOTTOM)
	{
		// ��ֱ����
		strFormat.SetLineAlignment(StringAlignmentFar);
	}
	else if (m_FontProp.VAligning == FAL_MIDDLE)
	{
		// ��ֱ����
		strFormat.SetLineAlignment(StringAlignmentCenter);
	}
	else
	{
		// ��ֱ����
		strFormat.SetLineAlignment(StringAlignmentNear);
	}

	// ����ˮƽ����
	if (m_FontProp.HAligning == FAL_RIGHT_BOTTOM)
	{
		// ˮƽ����
		strFormat.SetAlignment(StringAlignmentFar);
	}
	else if (m_FontProp.HAligning == FAL_MIDDLE)
	{
		// ˮƽ����
		strFormat.SetAlignment(StringAlignmentCenter);
	}
	else
	{
		// ˮƽ����
		strFormat.SetAlignment(StringAlignmentNear);
	}

	// GDI+Ĭ��������ʾ��ĩβ����...
	if (m_FontProp.ShowMode != FSM_MULTI_ROW)
	{
		// ��������ʾ
		strFormat.SetFormatFlags(StringFormatFlagsNoWrap);
		// ��������ʾ��Ĭ��ĩβ����...
		if (m_FontProp.ShowMode == FSM_ONE_ROW_POINT)
		{
			// ������ʾ��������ʾ��Χ��ʾ...
			strFormat.SetTrimming(StringTrimmingEllipsisCharacter);
		}
	}

	if (m_FontPropBase.GetEffectState(FE_SHADOW))
	{
		// ��Ӱ����
	}

	if (m_FontPropBase.GetEffectState(FE_OBSCURE))
	{
		// ģ������
	}

	DoGrap.DrawString(A2W(m_strText.c_str()), m_strText.size(), &TextFont, OutFct, &strFormat, &textBrush);
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
	OnCancel();
}
