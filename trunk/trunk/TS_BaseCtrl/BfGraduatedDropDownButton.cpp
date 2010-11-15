
#include "BfGraduatedDropDownButton.h"
#include "BfPopupMenu.h"

// 右侧下拉按钮所占的大小
#define DROP_DOWN_BTN_WDITH							(9)

CBfGraduatedDropDownButton::CBfGraduatedDropDownButton(void)
{
	m_bIsDownInDropWnd = false;
	m_bIsMoveInDropWnd = false;
}

CBfGraduatedDropDownButton::~CBfGraduatedDropDownButton(void)
{
}

void CBfGraduatedDropDownButton::DrawGraduatedButton(int nDrawSta)
{
	// 外圈
	Pen OutPen(Color(200, 25, 100, 120));
	CRect OutRect(m_WndRect);
	OutRect.right -= 1;
	OutRect.bottom -= 1;
	m_pDoGrap->DrawLine(&OutPen, OutRect.left + 1, OutRect.top, OutRect.right - 1, OutRect.top);
	m_pDoGrap->DrawLine(&OutPen, OutRect.right, OutRect.top + 1, OutRect.right, OutRect.bottom - 1);
	m_pDoGrap->DrawLine(&OutPen, OutRect.left + 1, OutRect.bottom, OutRect.right - 1, OutRect.bottom);
	m_pDoGrap->DrawLine(&OutPen, OutRect.left, OutRect.top + 1, OutRect.left, OutRect.bottom - 1);

	// 内圈
	CRect InRect(OutRect);
	InRect.left += 1;
	InRect.top += 1;
	Point p1(InRect.left, InRect.top - 1), p2(InRect.left, InRect.top + InRect.Height());
	Color col1(200, 255, 255, 255), col2(200, 180, 222, 248);
	LinearGradientBrush lgBrush(p1, p2, col1, col2);
	Pen InPen(&lgBrush);
	m_pDoGrap->DrawRectangle(&InPen, InRect.left, InRect.top, InRect.Width() - 1, InRect.Height() - 1);

	CRect InDropRect(InRect);
	InDropRect.right -= 1;
	InDropRect.left = (InDropRect.right - DROP_DOWN_BTN_WDITH);
	InDropRect.top += 1;
	InDropRect.bottom -= 1;

	// 最内圈高光
	if (nDrawSta == GRADUATE_STA_LBUTTONDOWN)
	{
		CRect InBRect(InRect);
		InBRect.left += 1;
		InBRect.top += 1;
		InBRect.right -= 1;
		InBRect.bottom -= 1;
		p1 = Point(InBRect.left, InBRect.top + (InBRect.Height() / 2)), p2 = Point(InBRect.left, InBRect.bottom);
		LinearGradientBrush lgBrush1(p1, p2, m_DownColor, m_UpColor);
		m_pDoGrap->FillRectangle(&lgBrush1, InBRect.left, p1.Y + 1, InBRect.Width() - DROP_DOWN_BTN_WDITH, (InBRect.Height() / 2) - 1);
	}
	else if (nDrawSta == GRADUATE_STA_NORMAL)
	{
		if (m_bIsMoveInDropWnd)
		{
			p1 = Point(InDropRect.left, InDropRect.top - 1), p2 = Point(InDropRect.left, InDropRect.bottom);
			LinearGradientBrush lgBrush2(p1, p2, m_UpColor, m_DownColor);
			m_pDoGrap->FillRectangle(&lgBrush2, InDropRect.left, p1.Y, InDropRect.Width(), InDropRect.Height());
		}
		else
		{
			CRect InBRect(InRect);
			InBRect.left += 1;
			InBRect.top += 1;
			InBRect.right -= 1;
			InBRect.bottom -= 1;
			p1 = Point(InBRect.left, InBRect.top - 1), p2 = Point(InBRect.left, InBRect.top + (InBRect.Height() / 2));
			LinearGradientBrush lgBrush1(p1, p2, m_UpColor, m_DownColor);
			m_pDoGrap->FillRectangle(&lgBrush1, InBRect.left, InBRect.top, InBRect.Width() - DROP_DOWN_BTN_WDITH, (InBRect.Height() / 2));
		}
	}

	if (m_bIsDownInDropWnd)
	{
		p1 = Point(InDropRect.left, InDropRect.top), p2 = Point(InDropRect.left, InDropRect.bottom);
		LinearGradientBrush lgBrush1(p1, p2, m_DownColor, m_UpColor);
		m_pDoGrap->FillRectangle(&lgBrush1, InDropRect.left, p1.Y + 1, InDropRect.Width(), InDropRect.Height() - 1);
	}

	// 四角虚幻
	Color xhColor(50, 50, 50, 50);
	SolidBrush xhBrush(xhColor);
	// 左上角
	CRect JRect(m_WndRect);
	JRect.right = JRect.left + 2;
	JRect.bottom = JRect.top + 2;
	m_pDoGrap->FillRectangle(&xhBrush, JRect.left, JRect.top, JRect.Width(), JRect.Height());
	// 右上角
	JRect = m_WndRect;
	JRect.left = JRect.right - 2;
	JRect.bottom = JRect.top + 2;
	m_pDoGrap->FillRectangle(&xhBrush, JRect.left, JRect.top, JRect.Width(), JRect.Height());
	// 左下角
	JRect = m_WndRect;
	JRect.right = JRect.left + 2;
	JRect.top = JRect.bottom - 2;
	m_pDoGrap->FillRectangle(&xhBrush, JRect.left, JRect.top, JRect.Width(), JRect.Height());
	// 右下角
	JRect = m_WndRect;
	JRect.left = JRect.right - 2;
	JRect.top = JRect.bottom - 2;
	m_pDoGrap->FillRectangle(&xhBrush, JRect.left, JRect.top, JRect.Width(), JRect.Height());
}

void CBfGraduatedDropDownButton::NormalDraw()
{
	CRect SjRect(m_WndRect);
	SjRect.right -= 3;
	SjRect.left = SjRect.right - DROP_SJ_W;
	SjRect.top += (m_WndRect.Height() / 2 - DROP_SJ_H / 2);
	SjRect.bottom = SjRect.top + DROP_SJ_H;

	// 绘制三角形
	GraphicsPath path;
	Point p1(SjRect.left, SjRect.top);
	Point p2(SjRect.right, SjRect.top);
	Point p3(SjRect.left + DROP_SJ_W / 2, SjRect.bottom);
	path.AddLine(p1, p2);
	path.AddLine(p2, p3);
	path.AddLine(p3, p1);
	//创建Region
	Region region(&path);
	//填充区域 
	m_pDoGrap->FillRegion(&SolidBrush(Color::Olive), &region);
}

void CBfGraduatedDropDownButton::OnLButtonDown(CPoint point)
{
	if (point.x < (m_WndRect.right - DROP_DOWN_BTN_WDITH))
		m_bIsDownInDropWnd = false;
	else
		m_bIsDownInDropWnd = true;

	if (m_bIsDownInDropWnd)
	{
		CPoint MenuBegin(m_WndRect.left, m_WndRect.bottom + 3);
		::ClientToScreen(m_hParent, &MenuBegin);
		m_PopupMenu.TrackPopupMenu(m_hParent, MenuBegin.x, MenuBegin.y);
	}

	CBfGraduatedButton::OnLButtonDown(point);
}

void CBfGraduatedDropDownButton::OnMouseMove(CPoint point)
{
	bool bOldFlag = m_bIsMoveInDropWnd;

	if (point.x < (m_WndRect.right - DROP_DOWN_BTN_WDITH))
		m_bIsMoveInDropWnd = false;
	else
		m_bIsMoveInDropWnd = true;

	if (m_bIsMoveInDropWnd != bOldFlag)
		m_nDrawCtns = 1;

	CBfGraduatedButton::OnMouseMove(point);
}

void CBfGraduatedDropDownButton::OnLButtonUp(CPoint point)
{
	m_bIsDownInDropWnd = false;
	CBfGraduatedButton::OnLButtonUp(point);
}

void CBfGraduatedDropDownButton::OnMouseLeave(CPoint point)
{
	m_bIsMoveInDropWnd = false;
	CBfGraduatedButton::OnMouseLeave(point);
}

void CBfGraduatedDropDownButton::OnDestroy()
{
	m_PopupMenu.Destroy();
	CBfGraduatedButton::OnDestroy();
}

// 创建窗口
bool CBfGraduatedDropDownButton::CreateWnd(CDirectUiDlg *pParentDlg, CDirectUiManager *pUiManager, CDirectUiWindowMsgCtrl *pMsgCtrl,
								   CRect WndRect, int nWndId, WND_TYPE WndType, int nImageId, CString strImagePath, IMAGE_TYPE nImageType)
{
	bool bRet = CBfGraduatedButton::CreateWnd(pParentDlg, pUiManager, pMsgCtrl, WndRect, nWndId, WndType, nImageId, strImagePath, nImageType);

	if (m_PopupMenu.Create())
	{
		m_PopupMenu.AppendMenu(MFT_STRING, 65535, _T("test1"));
		m_PopupMenu.AppendMenu(MFT_STRING, 65536, _T("test2"));
		m_PopupMenu.AppendMenu(MFT_STRING, 65537, _T("test3"));
		m_PopupMenu.AppendMenu(MFT_STRING, 65538, _T("test4"));
	}

	return bRet;
}
