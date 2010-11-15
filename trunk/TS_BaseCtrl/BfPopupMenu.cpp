#include "StdAfx.h"
#include "BfPopupMenu.h"
#include "BfBaseDlg.h"
#include "PuppetSubclassWnd.h"

// 菜单边框大小
#define MENU_FRAME										(3)
// 非客户区尺寸
#define MENU_NO_CLIENT									(5)
// 菜单左侧颜色条宽度
#define MENU_LEFT										(15)

CBfPopupMenu::CBfPopupMenu(void)
{
	m_nSelIndex = -2;
	m_PuppetWndType = PWT_MENU;
	m_hMenu = NULL;
	m_MenuTextList.clear();
}

CBfPopupMenu::~CBfPopupMenu(void)
{
	Destroy();
}

bool CBfPopupMenu::Create()
{
	m_hMenu = ::CreatePopupMenu();
	return IS_SAVE_HANDLE(m_hMenu);
}

void CBfPopupMenu::Destroy()
{
	if (IS_SAVE_HANDLE(m_hMenu))
	{
		::DestroyMenu(m_hMenu);
		m_hMenu = NULL;
	}

	for (MENU_TEXT_LIST::iterator pItem = m_MenuTextList.begin();
		pItem != m_MenuTextList.end(); pItem++)
	{
		CString *pText = pItem->second;
		if (pText != NULL)
			delete pText;
	}
	m_MenuTextList.clear();
}

bool CBfPopupMenu::AppendMenu(UINT uFlags, UINT uIDNewItem, LPCWSTR lpNewItem)
{
	bool bRet = false;

//	uFlags |= MF_OWNERDRAW;
	uFlags |= MF_BYCOMMAND;

	if (IS_SAVE_HANDLE(m_hMenu))
	{
		CString *pText = new CString(lpNewItem);
		if (pText != NULL)
		{
			m_MenuTextList.insert(pair<UINT, CString*>(uIDNewItem, pText));
			bRet = (::AppendMenu(m_hMenu, uFlags, uIDNewItem, (LPCTSTR)lpNewItem) ? true: false);
		}
	}

	return bRet;
}

void CBfPopupMenu::TrackPopupMenu(HWND hParent, int x, int y)
{
	if (IS_SAVE_HANDLE(m_hMenu) && hParent != NULL)
	{
		SystemParametersInfo(SPI_SETDROPSHADOW, 0, (PVOID)FALSE, SPIF_SENDCHANGE);
		g_PuppetMenuList.SetCurrentMenuWnd(this);
		_RPT0(_CRT_WARN, "SetCurrentMenuWnd(this)\n");
		::TrackPopupMenu(m_hMenu, TPM_LEFTBUTTON, x, y, 0, hParent, NULL);
		_RPT0(_CRT_WARN, "SetCurrentMenuWnd(NULL)\n");
		g_PuppetMenuList.SetCurrentMenuWnd(NULL);
		SystemParametersInfo(SPI_SETDROPSHADOW, 0, (PVOID)TRUE, SPIF_SENDCHANGE);

		CBfBaseDlg::SetNeetLButtonUpMsg();
	}
}

void CBfPopupMenu::OnMeasureItem(MEASUREITEMSTRUCT *lpMis)
{
	if (lpMis != NULL)
	{
		lpMis->itemHeight = 20;
		lpMis->itemWidth = 150;
	}
}

void CBfPopupMenu::OnDrawItem(DRAWITEMSTRUCT *lpDrawSta)
{
	if (lpDrawSta == NULL || lpDrawSta->CtlType != ODT_MENU || lpDrawSta->itemData == NULL || lpDrawSta->hDC == NULL)
		return;

	HDC hPaintDc = lpDrawSta->hDC;
	CRect ItemRect = lpDrawSta->rcItem;
	HDC hMemoryDC = ::CreateCompatibleDC(hPaintDc);
	if (hMemoryDC != NULL)
	{
		HBITMAP hMemoryBitmap = ::CreateCompatibleBitmap(hPaintDc, ItemRect.Width(), ItemRect.Height());
		if (hMemoryDC != NULL)
		{
			::SelectObject(hMemoryDC, hMemoryBitmap);

			// 开始画图
			DrawItem(lpDrawSta, hMemoryDC);

			::BitBlt(hPaintDc, ItemRect.left, ItemRect.top, ItemRect.Width(), ItemRect.Height(),
				hMemoryDC, 0, 0, SRCCOPY);

			::DeleteObject(hMemoryBitmap);
		}
		::DeleteDC(hMemoryDC);
	}
}

void CBfPopupMenu::DrawItem(DRAWITEMSTRUCT *lpDrawSta, HDC hMemoryDC)
{
	// 当整个控件都需要被绘制时，设置该值
	bool bIsDrawEntry = ((lpDrawSta->itemAction & ODA_DRAWENTIRE) != 0);
	// 如果控件需要在获得或失去焦点时被绘制，则设置该值
	bool bIsFocus = ((lpDrawSta->itemAction & ODA_FOCUS) != 0);
	// 如果控件需要在选中状态改变时被绘制，则设置该值
	bool bIsSelect = ((lpDrawSta->itemAction & ODA_SELECT) != 0);

	// 如果菜单项将被选中，则可设置该值
	bool bIsChecked = ((lpDrawSta->itemState & ODS_CHECKED) != 0);
	// 默认值
	bool bIsDefault = ((lpDrawSta->itemState & ODS_DEFAULT) != 0);
	// 如果控件将被禁止，则设置该值
	bool bIsDisagled = ((lpDrawSta->itemState & ODS_DISABLED) != 0);
	// 如果控件需要被灰色显示，则设置该值
	bool bIsGrayed = ((lpDrawSta->itemState & ODS_GRAYED) != 0);
	// 如果控件需要输入焦点，则设置该值
	bool bIsOdsFocus = ((lpDrawSta->itemState & ODS_FOCUS) != 0);
	// 如果鼠标指针位于控件之上，则设置该值，这时控件会显示高亮颜色。
	bool bIsHotlight = ((lpDrawSta->itemState & ODS_HOTLIGHT) != 0);
	// 表示没有激活的菜单项
	bool bIsInactive = ((lpDrawSta->itemState & ODS_INACTIVE) != 0);
	// 控件是否有快速键盘
	bool bIsNoAccel = ((lpDrawSta->itemState & ODS_NOACCEL) != 0);
	// 不绘制捕获焦点的效果
	bool bIsNoFocusRect = ((lpDrawSta->itemState & ODS_NOFOCUSRECT) != 0);
	// 选中的菜单项
	bool bIsSelected = ((lpDrawSta->itemState & ODS_SELECTED) != 0);

	Graphics DoGrap(hMemoryDC);
	CRect ItemRect = lpDrawSta->rcItem;
	CString *pText = (CString *)(lpDrawSta->itemData);

	// 开始绘图操作
	SolidBrush FillBrush(Color(255, 0, 0));
	DoGrap.FillRectangle(&FillBrush, 0, 0, ItemRect.Width(), ItemRect.Height());
}

void CBfPopupMenu::SetMenuWndHookInfo(HWND hWnd, WNDPROC pOldWndProc)
{
	m_hWnd = hWnd;
	m_pOldWndProc = pOldWndProc;
}

LRESULT CBfPopupMenu::WndProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hDc = NULL;
	LRESULT lResult = 1;

	switch (message)
	{
		/*		//首先要去掉菜单窗口的WS_BORDER风格和WS_EX_DLGMODALFRAME , WS_EX_WINDOWEDGE扩展风格 
		case WM_CREATE:
		{ 
		lResult = CallWindowProc(m_pOldWndProc, hWnd, message, wParam, lParam); 
		DWORD dwStyle = ::GetWindowLong(hWnd, GWL_STYLE); 
		DWORD dwNewStyle = (dwStyle & ~WS_BORDER); 
		::SetWindowLong(hWnd, GWL_STYLE, dwNewStyle); 
		DWORD dwExStyle = ::GetWindowLong(hWnd, GWL_EXSTYLE); 
		DWORD dwNewExStyle = (dwExStyle & ~(WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE)); 
		::SetWindowLong(hWnd, GWL_EXSTYLE, dwNewExStyle); 
		return lResult; 
		break; 
		} 

		//这里/阻止非客户区的绘制 
		case WM_PRINT:
		return CallWindowProc(m_pOldWndProc, hWnd, WM_PRINTCLIENT, wParam, lParam); 
		break; 

		//最后, 因为你在MeasureItem里指定的菜单大小，系统会自动替你加上边框，我们必须去掉这部分额外的尺寸 
		case WM_WINDOWPOSCHANGING:
		{ 
		//将菜单大小改小 
		LPWINDOWPOS lpPos = (LPWINDOWPOS)lParam; 
		lpPos->cx -= 2*GetSystemMetrics(SM_CXBORDER)+4; 
		lpPos->cy -= 2*GetSystemMetrics(SM_CYBORDER)+4; 
		lResult = CallWindowProc(m_pOldWndProc, hWnd, message, wParam, lParam); 
		return 0; 
		}

		case WM_GETICON: 
		return CallWindowProc(m_pOldWndProc, hWnd, message, wParam, lParam); 


		// 绘制非客户区区域
		case WM_NCPAINT:
		OnNcPaint(hWnd, wParam, lParam);
		return 0;

		case WM_PRINT:
		lResult = CallWindowProc(m_pOldWndProc, hWnd, message, wParam, lParam);
		OnNcPaint(hWnd, wParam, lParam);
		return lResult;

		case WM_PAINT:
		hDc = ::GetDC(hWnd);
		SendMessage(hWnd, WM_PRINTCLIENT, (WPARAM)hDc, PRF_CLIENT | PRF_CHECKVISIBLE);
		return 0;

		case WM_PRINTCLIENT:
		OnPrintClient(hWnd, wParam, lParam);
		return 0;

		// 设置非客户区域大小
		case WM_NCCALCSIZE:
		return OnNcCalcSize(wParam, lParam);

		case 0x1e5:
		return CallWindowProc(m_pOldWndProc, hWnd, message, wParam, lParam);

		// 绘制客户区区域
		case WM_ERASEBKGND:
		return TRUE;

		// 初始化
		case WM_CREATE:
		return CallWindowProc(m_pOldWndProc, hWnd, message, wParam, lParam);

		case WM_NCDESTROY:
		return CallWindowProc(m_pOldWndProc, hWnd, message, wParam, lParam);

		case WM_MEASUREITEM:
		return CallWindowProc(m_pOldWndProc, hWnd, message, wParam, lParam);

		case WM_DRAWITEM:
		return CallWindowProc(m_pOldWndProc, hWnd, message, wParam, lParam);
		*/


	case WM_CREATE:
		_RPT0(_CRT_WARN, "WM_CREATE\n");
		break;

	case WM_SIZE:
		_RPT0(_CRT_WARN, "WM_SIZE\n");
		break;

	case WM_NCCALCSIZE:
		_RPT0(_CRT_WARN, "WM_NCCALCSIZE\n");
		lResult = CallWindowProc(m_pOldWndProc, m_hWnd, message, wParam, lParam);
		OnNcCalcSize(wParam, lParam);
		return lResult;

	case WM_MOVE:
		_RPT0(_CRT_WARN, "WM_MOVE\n");
		break;

	case WM_WINDOWPOSCHANGED:
		_RPT0(_CRT_WARN, "WM_WINDOWPOSCHANGED\n");
		break;

	case WM_WINDOWPOSCHANGING:
		_RPT0(_CRT_WARN, "WM_WINDOWPOSCHANGING\n");
		OnWindowPosChanging(wParam, lParam);
		lResult = CallWindowProc(m_pOldWndProc, m_hWnd, message, wParam, lParam);
		return lResult;

	case WM_PRINT:
		_RPT0(_CRT_WARN, "WM_PRINT\n");
		lResult = CallWindowProc(m_pOldWndProc, m_hWnd, message, wParam, lParam);
		OnNcPaint(m_hWnd, wParam, lParam);
		return lResult;

	case 0x00AF:
		_RPT0(_CRT_WARN, "0x00AF\n");
		break;

	case WM_NCPAINT:
		_RPT0(_CRT_WARN, "WM_NCPAINT\n");
		break;

	case WM_PRINTCLIENT:
		_RPT0(_CRT_WARN, "WM_PRINTCLIENT\n");
		OnPrintClient(m_hWnd, wParam, lParam);
		return 0;

	case WM_PAINT:
		_RPT0(_CRT_WARN, "WM_PAINT\n");
		break;

	case WM_GETICON:
		_RPT0(_CRT_WARN, "WM_GETICON\n");
		break;

	case 0x01E5:
		_RPT0(_CRT_WARN, "0x01E5\n");
		OnDrawSelect(m_hWnd, wParam, lParam);
		break;

	case WM_ERASEBKGND:
		_RPT0(_CRT_WARN, "WM_ERASEBKGND\n");
		break;

	case WM_DESTROY:
		_RPT0(_CRT_WARN, "WM_DESTROY\n");
		break;

	case WM_NCDESTROY:
		_RPT0(_CRT_WARN, "WM_NCDESTROY\n");
		break;

	default:
		{
			USES_CONVERSION;
			CString strMsg = _T("");
			strMsg.Format(_T("default message=%d(0x%X)\n"), message, message);
			_RPT0(_CRT_WARN, W2A(strMsg));
		}
		break;
	}

	return CallWindowProc(m_pOldWndProc, m_hWnd, message, wParam, lParam);
}

LRESULT CBfPopupMenu::OnNcCalcSize(WPARAM wParam, LPARAM lParam)
{
	LPRECT pRect = wParam ? &((LPNCCALCSIZE_PARAMS)lParam)->rgrc[0] : (LPRECT)lParam;

	pRect->left += MENU_FRAME;
	pRect->right -= MENU_FRAME;
	pRect->top += MENU_FRAME;
	pRect->bottom -= MENU_FRAME;

	return 1;
}

LRESULT CBfPopupMenu::OnWindowPosChanging(WPARAM wParam, LPARAM lParam)
{
	WINDOWPOS* lpWndPos = (WINDOWPOS*)lParam;
	if (lpWndPos != NULL && lpWndPos->cx > 0)
	{
		lpWndPos->cx += (MENU_FRAME * 2);
		lpWndPos->cy += (MENU_FRAME * 2);
	}

	return 1;
}

LRESULT CBfPopupMenu::OnDrawSelect(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	int nSel = (int)wParam;

	if (m_nSelIndex != nSel)
	{
		m_nSelIndex = nSel;

		CRect ClientRect(0, 0, 0, 0);
		::GetClientRect(hWnd, &ClientRect);

		//		::SendMessage(hWnd, WM_SETREDRAW, FALSE, 0);
		//		CallWindowProc(m_pOldWndProc, hWnd, 0x01E5, wParam, lParam);
		//		::SendMessage(hWnd, WM_SETREDRAW, TRUE, 0);
	}

	::RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);

	return 0;
}

LRESULT CBfPopupMenu::OnNcPaint(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	HDC hPaintDc = (HDC)wParam;
	if (IS_SAVE_HANDLE(hWnd) && IS_SAVE_HANDLE(hPaintDc))
	{
		CRect WndRect(0, 0, 0, 0), ClientRect(0, 0, 0, 0);
		::GetWindowRect(hWnd, &WndRect);
		::GetClientRect(hWnd, &ClientRect);
		ClientToScreen(hWnd, ClientRect);
		::OffsetRect(&ClientRect, -WndRect.left, -WndRect.top);

		HDC hMemoryDC = ::CreateCompatibleDC(hPaintDc);
		if (hMemoryDC != NULL)
		{
			HBITMAP hMemoryBitmap = ::CreateCompatibleBitmap(hPaintDc, WndRect.Width(), WndRect.Height());
			if (hMemoryDC != NULL)
			{
				::SelectObject(hMemoryDC, hMemoryBitmap);

				// 开始画图
				OnNcPaintDraw(hWnd, hMemoryDC);

				int nSaveDC = ::SaveDC(hPaintDc);
				// 将客户区裁剪掉
				::ExcludeClipRect(hPaintDc, ClientRect.left, ClientRect.top, ClientRect.right, ClientRect.bottom);
				::BitBlt(hPaintDc, 0, 0, WndRect.Width(), WndRect.Height(),
					hMemoryDC, 0, 0, SRCCOPY);
				::RestoreDC(hPaintDc, nSaveDC);

				::DeleteObject(hMemoryBitmap);
			}
			::DeleteDC(hMemoryDC);
		}
	}

	return 1;
}

void CBfPopupMenu::OnNcPaintDraw(HWND hWnd, HDC hMemoryDC)
{
	CRect WndRect(0, 0, 0, 0), ClientRect(0, 0, 0, 0);
	::GetWindowRect(hWnd, &WndRect);
	::GetClientRect(hWnd, &ClientRect);
	ClientToScreen(hWnd, ClientRect);
	::OffsetRect(&ClientRect, -WndRect.left, -WndRect.top);

	HBITMAP hScreenBmp = GetScreenBitmap(WndRect);
	if (IS_SAVE_HANDLE(hScreenBmp))
	{
		// 将屏幕贴图贴到dc上。
		::SelectObject(hMemoryDC, hScreenBmp);
		::DeleteObject(hScreenBmp);

		Graphics DoGrap(hMemoryDC);
		int nLgSize = MENU_NO_CLIENT;

		Pen LinePen(Color(255, 102, 102, 102));

		//		DoGrap.DrawRectangle(&LinePen, 0, 0, WndRect.Width() - 1, WndRect.Height() - 1);
		//		DoGrap.DrawRectangle(&LinePen, ClientRect.left, ClientRect.top, ClientRect.Width() - 1, ClientRect.Height() - 1);

		//////// 四边虚幻 //////////////////////////////////////////////////////////////////
		// 上边
		Point p1(0, 0), p2(0, nLgSize);
		Color col1(20, 102, 102, 102), col2(100, 102, 102, 102);
		LinearGradientBrush lgBrush(p1, p2, col1, col2);
		DoGrap.FillRectangle(&lgBrush, nLgSize, 0, WndRect.Width() - (nLgSize * 2), nLgSize);
		//DoGrap.FillRectangle(&lgBrush, 0, 0, WndRect.Width(), nLgSize);

		// 左边
		p2 = Point(nLgSize, 0);
		LinearGradientBrush lgBrush1(p1, p2, col1, col2);
		DoGrap.FillRectangle(&lgBrush1, 0, nLgSize, nLgSize, WndRect.Height() - (nLgSize * 2));

		// 右边
		p1 = Point(WndRect.Width() - nLgSize - 1, 0);
		p2 = Point(WndRect.Width(), 0);
		LinearGradientBrush lgBrush2(p1, p2, col2, col1);
		DoGrap.FillRectangle(&lgBrush2, WndRect.Width() - nLgSize, nLgSize, nLgSize, WndRect.Height() - (nLgSize * 2));

		// 下边
		p1 = Point(0, WndRect.Height() - nLgSize - 1);
		p2 = Point(0, WndRect.Height());
		LinearGradientBrush lgBrush3(p1, p2, col2, col1);
		DoGrap.FillRectangle(&lgBrush3, nLgSize, WndRect.Height() - nLgSize, WndRect.Width() - (nLgSize * 2), nLgSize);

		//////// 四边内灰线 //////////////////////////////////////////////////////////////////
		CRect OutR(0, 0, 0, 0);
		nLgSize--;
		OutR.left = nLgSize;
		OutR.right = WndRect.Width() - nLgSize - 1;
		OutR.top = nLgSize;
		OutR.bottom = WndRect.Height() - nLgSize - 1;

		DoGrap.DrawLine(&LinePen, OutR.left + 1, OutR.top, OutR.right - 1, OutR.top);
		DoGrap.DrawLine(&LinePen, OutR.left, OutR.top + 1, OutR.left, OutR.bottom - 1);
		DoGrap.DrawLine(&LinePen, OutR.left + 1, OutR.bottom, OutR.right - 1, OutR.bottom);
		DoGrap.DrawLine(&LinePen, OutR.right, OutR.top + 1, OutR.right, OutR.bottom - 1);

		//////// 内部白底 //////////////////////////////////////////////////////////////////
		CRect InR(OutR);
		InR.left++;
		InR.top++;
		SolidBrush FillBrush(Color(255, 255, 255));
		DoGrap.FillRectangle(&FillBrush, InR.left, InR.top, InR.Width(), InR.Height());

		//		DoGrap.DrawRectangle(&LinePen, OutR.left, OutR.top, OutR.Width() - 1, OutR.Height() - 1);

		//////// 四角椭圆 //////////////////////////////////////////////////////////////////
		::SetPixel(hMemoryDC, OutR.left + 1, OutR.top + 1, RGB(102, 102, 102));
		::SetPixel(hMemoryDC, OutR.right - 1, OutR.top + 1, RGB(102, 102, 102));
		::SetPixel(hMemoryDC, OutR.right - 1, OutR.bottom - 1, RGB(102, 102, 102));
		::SetPixel(hMemoryDC, OutR.left + 1, OutR.bottom - 1, RGB(102, 102, 102));

		//////// 四角渐变虚幻 //////////////////////////////////////////////////////////////////

		// 左上角
		int nXhW = MENU_NO_CLIENT;
		col1 = Color(0, 102, 102, 102);
		col2 = Color(70, 102, 102, 102);
		p1 = Point(0, 0);
		p2 = Point(nXhW, nXhW);
		LinearGradientBrush lgBrush4(p1, p2, col1, col2);
		DoGrap.FillRectangle(&lgBrush4, p1.X, p1.Y, nXhW, nXhW);

		// 右上角
		p1 = Point(WndRect.Width(), 0);
		p2 = Point(WndRect.Width() - nXhW, nXhW);
		LinearGradientBrush lgBrush5(p1, p2, col1, col2);
		DoGrap.FillRectangle(&lgBrush5, WndRect.Width() - nXhW, 0, nXhW, nXhW);

		// 左下角
		p1 = Point(0, WndRect.Height());
		p2 = Point(nXhW, WndRect.Height() - nXhW);
		LinearGradientBrush lgBrush6(p1, p2, col1, col2);
		DoGrap.FillRectangle(&lgBrush6, 0, WndRect.Height() - nXhW, nXhW, nXhW);

		// 右下角
		p1 = Point(WndRect.Width(), WndRect.Height());
		p2 = Point(WndRect.Width() - nXhW, WndRect.Height() - nXhW);
		LinearGradientBrush lgBrush7(p1, p2, col1, col2);
		DoGrap.FillRectangle(&lgBrush7, WndRect.Width() - nXhW, WndRect.Height() - nXhW, nXhW, nXhW);
	}
}

LRESULT CBfPopupMenu::OnPrintClient(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	HDC hPaintDc = (HDC)wParam;
	CRect ClientRect(0, 0, 0, 0);
	::GetClientRect(hWnd, &ClientRect);

	if (IS_SAVE_HANDLE(hWnd) && IS_SAVE_HANDLE(hPaintDc))
	{
		HDC hMemoryDC = ::CreateCompatibleDC(hPaintDc);
		if (hMemoryDC != NULL)
		{
			HBITMAP hMemoryBitmap = ::CreateCompatibleBitmap(hPaintDc, ClientRect.Width(), ClientRect.Height());
			if (hMemoryDC != NULL)
			{
				::SelectObject(hMemoryDC, hMemoryBitmap);

				// 开始画图
				PrintClientDraw(hWnd, hMemoryDC, lParam);

				::BitBlt(hPaintDc, ClientRect.left, ClientRect.top, ClientRect.Width(), ClientRect.Height(),
					hMemoryDC, 0, 0, SRCCOPY);

				::DeleteObject(hMemoryBitmap);
			}
			::DeleteDC(hMemoryDC);
		}
	}

	return 1;
}

void CBfPopupMenu::PrintClientDraw(HWND hWnd, HDC hMemoryDC, LPARAM lParam)
{
	if (IS_SAVE_HANDLE(hWnd) && IS_SAVE_HANDLE(hMemoryDC))
	{
		CRect ClientRect(0, 0, 0, 0);
		::GetClientRect(hWnd, &ClientRect);

		Graphics DoGrap(hMemoryDC);
		// 开始绘图操作
		SolidBrush FillBrush(Color(255, 255, 255));
		DoGrap.FillRectangle(&FillBrush, 0, 0, ClientRect.Width(), ClientRect.Height());

		SolidBrush FillBrush1(Color(232, 237, 239));
		DoGrap.FillRectangle(&FillBrush1, 0, 0, MENU_LEFT, ClientRect.Height());


		CallWindowProc(m_pOldWndProc, hWnd, WM_PRINTCLIENT, (WPARAM)hMemoryDC, lParam);
	}
}
