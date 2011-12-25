
#include "stdafx.h"
#include "IWindowBaseImpl.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IPropertyControl.h"
#include "..\..\Inc\IPropertyControlManager.h"
#include "IPropertySkinManagerImpl.h"

// 弹出任务栏菜单消息，XP以下适用
#define WM_POPUPSYSTEMMENU						(0x0313)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IWindowBaseImpl::IWindowBaseImpl()
{
	m_Blend.BlendOp = AC_SRC_OVER;
	m_Blend.BlendFlags = 0;
	m_Blend.AlphaFormat = AC_SRC_ALPHA;
	m_Blend.SourceConstantAlpha = 255;

	m_hParent = NULL;
	m_hWnd = NULL;
	m_bIsLayeredWnd = false;
	m_ChildCtrlsVec.clear();

	m_bIsLButtonDown = false;
	m_pLButtonDownCtrl = NULL;
	m_pMouseHoverCtrl = NULL;
	m_pFocusCtrl = NULL;

	m_strSkinPath = "";
	m_strWindowName = "";
}

IWindowBaseImpl::~IWindowBaseImpl()
{
}

// 重绘控件
void IWindowBaseImpl::RedrawControl(IControlBase* pCtrl, bool bDrawImmediately)
{
	if (pCtrl == NULL)
		return;

//	pCtrl->
//	if (this->RedrawWindow())
//	{
//	}
}

// 设置窗体的透明特性
void IWindowBaseImpl::SetLayeredWindow(bool bIsLayered)
{
	m_bIsLayeredWnd = bIsLayered;
	DWORD dwExStyle = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
	if (m_bIsLayeredWnd)
	{
		// 透明
		if ((dwExStyle & WS_EX_LAYERED) != WS_EX_LAYERED)
		{
			dwExStyle |= WS_EX_LAYERED;
			::SetWindowLong(m_hWnd, GWL_EXSTYLE, dwExStyle);
		}
	}
	else
	{
		// 不透明
		if ((dwExStyle & WS_EX_LAYERED) == WS_EX_LAYERED)
		{
			dwExStyle &= (~WS_EX_LAYERED);
			::SetWindowLong(m_hWnd, GWL_EXSTYLE, dwExStyle);
		}
	}
}

// 初始化是否完成
bool IWindowBaseImpl::IsInit()
{
	return m_WndPropMgr.IsInit();
}

// 当窗口的属性发生变化时需要通知窗口进行刷新时调用
void IWindowBaseImpl::RefreshWindowStyle()
{
	// 会触发 WM_NCCALCSIZE 消息
	::SetWindowPos(m_hWnd, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE);
}

// 内部接受到初始化消息，开始初始化窗口，加载皮肤
void IWindowBaseImpl::OnInitWindowBase()
{
//// 设置对话框基本样式 //////////////////////////////////////////////////////////////////////
	// 取得对话框基本样式属性
	DWORD dwStyle = ::GetWindowLong(m_hWnd, GWL_STYLE);
	dwStyle &= (~WS_POPUP);
	dwStyle &= (~WS_DLGFRAME);
	// 对话框基本样式属性
	dwStyle |= WS_OVERLAPPED | WS_THICKFRAME;
	::SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);

//////////////////////////////////////////////////////////////////////////
	// 初始化对话框皮肤
	IPropertySkinManager *pPropSkinMgr = IPropertySkinManagerImpl::GetInstance();
	if (pPropSkinMgr == NULL)
	{
		// 向窗口发送通知：初始化皮肤异常
		::PostMessage(m_hWnd, UM_INIT_WINDOW_ERROR, -1, NULL);
		return;
	}

	// 初始化对话框皮肤
	IPropertyGroup* pWndPropGroup = pPropSkinMgr->InitWindowSkin(m_strSkinPath.c_str(), m_strWindowName.c_str());
	if (pWndPropGroup == NULL)
	{
		// 向窗口发送通知：初始化皮肤异常
		::PostMessage(m_hWnd, UM_INIT_WINDOW_ERROR, -2, NULL);
		return;
	}
	// 设置对话框属性
	m_WndPropMgr.SetXmlPropetry(pWndPropGroup);

//////////////////////////////////////////////////////////////////////////
	// 当窗口的属性发生变化时需要通知窗口进行刷新
	RefreshWindowStyle();

	// 向窗口发送通知：初始化皮肤完成
	::PostMessage(m_hWnd, UM_INIT_WINDOW_SUCCESS, NULL, NULL);
}

// 取得窗口控件指针
IControlBase* IWindowBaseImpl::GetControl(char *pszCtrlName)
{
	IControlBase *pCtrl = NULL;
	GetControlByName(&m_ChildCtrlsVec, pszCtrlName, &pCtrl);
	return pCtrl;
}

bool IWindowBaseImpl::GetControlByName(CHILD_CTRLS_VEC *pCtrlVec, char *pszCtrlName, IControlBase **ppCtrl)
{
	if (pCtrlVec == NULL || pszCtrlName == NULL || ppCtrl == NULL)
		return NULL;

	int nCtns = m_ChildCtrlsVec.size();
	for (int i = 0; i < nCtns; i++)
	{
		IControlBase *pCtrl = m_ChildCtrlsVec[i];
		if (pCtrl != NULL)
		{
			IPropertyControlManager* pCtrlProp = pCtrl->GetControlBaseProp();
			if (pCtrlProp == NULL)
				continue;

			string strCtrlName = pCtrlProp->GetName();
			if (strCtrlName.compare(pszCtrlName) == 0)
			{
				*ppCtrl = pCtrl;
				return true;
			}

			if (GetControlByName(pCtrl->GetChildCtrlsVec(), pszCtrlName, ppCtrl))
				return true;
		}
	}

	return false;
}

// 初始化：由外部调用，内部发送开始初始化的消息真正开始初始化
void IWindowBaseImpl::InitWindowBase(HWND hWnd, char *pszSkinPath, char *pszWndName)
{
	if (m_hWnd != NULL || hWnd == NULL || pszSkinPath == NULL || pszWndName == NULL)
		return;

	m_hWnd = hWnd;
	m_strSkinPath = pszSkinPath;
	m_strWindowName = pszWndName;
	// 发送初始化消息
	::PostMessage(hWnd, UM_INIT_WINDOW_BASE, NULL, NULL);
}

// 取得窗口句柄
HWND IWindowBaseImpl::GetSafeHandle()
{
	return m_hWnd;
}

// 得到窗口屏幕坐标
RECT IWindowBaseImpl::GetWindowRect()
{
	RECT RetRect;
	INIT_RECT(RetRect);

	if (IS_SAFE_HANDLE(m_hWnd))
		::GetWindowRect(m_hWnd, &RetRect);

	return RetRect;
}

// 得到客户端坐标
RECT IWindowBaseImpl::GetClientRect()
{
	RECT RetRect;
	INIT_RECT(RetRect);

	if (IS_SAFE_HANDLE(m_hWnd))
	{
		::GetWindowRect(m_hWnd, &RetRect);
		int nW = RetRect.right - RetRect.left;
		int nH = RetRect.bottom - RetRect.top;

		INIT_RECT(RetRect);
		RetRect.right = nW;
		RetRect.bottom = nH;
	}

	return RetRect;
}

// 将窗口移到屏幕中央
void IWindowBaseImpl::CenterWindow()
{
	RECT WndRect = GetClientRect();
	int cx = RECT_WIDTH(WndRect);
	int cy = RECT_HEIGHT(WndRect);

	if (IS_SAFE_HANDLE(m_hWnd) && cx > 0 && cy > 0)
	{
		// 设置默认大小
		RECT WorkArea, CenterRect;
		INIT_RECT(WorkArea);
		INIT_RECT(CenterRect);
		::SystemParametersInfo(SPI_GETWORKAREA, 0, &WorkArea, 0);

		CenterRect.left = (RECT_WIDTH(WorkArea) - cx) / 2;
		CenterRect.right = CenterRect.left + cx;
		CenterRect.top = (RECT_HEIGHT(WorkArea) - cy) / 2;
		CenterRect.bottom = CenterRect.top + cy;

		::MoveWindow(m_hWnd, CenterRect.left, CenterRect.top, RECT_WIDTH(CenterRect), RECT_HEIGHT(CenterRect), TRUE);
	}
}

// 窗口属性
IPropertyWindowManager* IWindowBaseImpl::GetWindowProp()
{
	return &m_WndPropMgr;
}

// 本窗口的消息处理函数，bPassOn参数为true是，消息会继续传递处理；false时，处理完毕，不再下传
LRESULT IWindowBaseImpl::WindowProc(UINT nMsgId, WPARAM wParam, LPARAM lParam, bool &bPassOn)
{
	// bPassOn参数为true是，消息会继续传递处理；false时，处理完毕，不再下传
	bPassOn = true;
	if (!::IsWindow(m_hWnd))
		return 0;

	switch (nMsgId)
	{
		// 需要外部对话框接受的消息：使用皮肤初始化窗口正确结束
	case UM_INIT_WINDOW_SUCCESS:
		break;

		// 需要外部对话框接受的消息：使用皮肤初始化窗口异常
	case UM_INIT_WINDOW_ERROR:
		break;

		// 初始化窗口
	case UM_INIT_WINDOW_BASE:
		bPassOn = false;
		OnInitWindowBase();
		break;

	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			OnMouseMove((int)wParam, pt);
		}
		break;

	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			OnLButtonDown((int)wParam, pt);
		}
		break;

	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			OnLButtonUp((int)wParam, pt);
		}
		break;

	case WM_LBUTTONDBLCLK:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			OnLButtonDbClick((int)wParam, pt);
		}
		break;

	case WM_RBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			OnRButtonDown((int)wParam, pt);
		}
		break;

	case WM_KEYDOWN:
		OnKeyDown((int)wParam, (int)lParam);
		break;

	case WM_SYSCOMMAND:
		if (OnSysCommand((int)wParam, LOWORD(lParam), HIWORD(lParam)))
		{
			bPassOn = false;
			return TRUE;
		}
		break;

	case WM_TIMER:
		OnTimer((UINT)wParam);
		break;

	case WM_KILLFOCUS:
		OnKillFocus(wParam, lParam);
		break;

	case WM_SETFOCUS:
		OnSetFocus(wParam, lParam);
		break;

	case WM_DESTROY:
		OnDestroy();
		break;

	case WM_SIZE:
		OnSize((UINT)wParam, LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_SIZING:
		OnSizing((UINT)wParam, (LPRECT)lParam);
		break;

	case WM_ENTERSIZEMOVE:
		OnEnterSizeMove();
		break;

	case WM_EXITSIZEMOVE:
		OnExitSizeMove();
		break;

	case WM_PAINT:
		{
			bPassOn = false;
			PAINTSTRUCT ps;
			HDC hDc = BeginPaint(m_hWnd, &ps);
			OnPaint(hDc);
			EndPaint(m_hWnd, &ps);
			return TRUE;
		}
		break;

	case WM_POPUPSYSTEMMENU:
		{
			bPassOn = false;
			POINT pt;
			::GetCursorPos(&pt);
			OnPopupSystemMenu(pt);
		}
		return TRUE;

	case WM_NCCALCSIZE:
		bPassOn = false;
		return 0;

	case WM_ERASEBKGND:
	case WM_NCPAINT:
	case WM_NCACTIVATE:
	case 0x00AE:	// WM_NCUAHDRAWCAPTION
	case 0x00AF:	// WM_NCUAHDRAWFRAME
		bPassOn = false;
		return WM_PAINT;

	default:
		break;
	}

	return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// 消息处理 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IWindowBaseImpl::OnPaint(HDC hWndDc)
{
	if (!IS_SAFE_HANDLE(hWndDc) && !IsInit())
		return;

	RECT WndRect = this->GetWindowRect();
	m_WndMemDc.Create(RECT_WIDTH(WndRect), RECT_HEIGHT(WndRect), 0, false, true);
	if (m_WndMemDc.GetBits() == NULL)
		return;

	// 循环遍历每个控件的绘制
	DrawControl();

	// 绘制到窗口上
	if (m_bIsLayeredWnd)
	{
		POINT ptWinPos = {WndRect.left, WndRect.top};
		POINT ptSrc = {0, 0};
		SIZE sizeWindow = {RECT_WIDTH(WndRect), RECT_HEIGHT(WndRect)};
		::UpdateLayeredWindow(m_hWnd, hWndDc, &ptWinPos, &sizeWindow, m_WndMemDc.GetSafeHdc(), &ptSrc, 0, &m_Blend, ULW_ALPHA);
	}
	else
	{
		::BitBlt(hWndDc, 0, 0, RECT_WIDTH(WndRect), RECT_HEIGHT(WndRect), m_WndMemDc.GetSafeHdc(), 0, 0, SRCCOPY);
	}
}

bool IWindowBaseImpl::CheckMouseInControl(CHILD_CTRLS_VEC *pCtrlVec, POINT pt, IControlBase **ppControl)
{
	if (pCtrlVec == NULL || ppControl == NULL)
		return false;

	int nCtns = pCtrlVec->size();
	for (int i = nCtns - 1; i >= 0; i--)
	{
		IControlBase* pCtrl = (*pCtrlVec)[i];
		if (pCtrl != NULL)
		{
			IPropertyControlManager* pCtrlProp = pCtrl->GetControlBaseProp();
			if (pCtrlProp != NULL && pCtrlProp->IsVisible())
			{
				if (pCtrlProp->GetReceiveMouseMessage())
				{
					RECT CtrlRct = pCtrlProp->GetCtrlInWindowRect();
					if (::PtInRect(&CtrlRct, pt))
					{
						*ppControl = pCtrl;
						CHILD_CTRLS_VEC *pCtrlsVec = pCtrl->GetChildCtrlsVec();
						CheckMouseInControl(pCtrlsVec, pt, ppControl);
						return true;
					}
				}
				else
				{
					CHILD_CTRLS_VEC *pCtrlsVec = pCtrl->GetChildCtrlsVec();
					if (CheckMouseInControl(pCtrlsVec, pt, ppControl))
						return true;
				}
			}
		}
	}

	return false;
}

void IWindowBaseImpl::OnMouseMove(int nVirtKey, POINT pt)
{
	if (!IsInit())
		return;

	if (m_bIsLButtonDown)
	{
		if (m_pLButtonDownCtrl != NULL)
		{
			// 如果允许在控件内部进行自由拖动
			IPropertyControlManager* pCtrlProp = m_pLButtonDownCtrl->GetControlBaseProp();
			if (pCtrlProp != NULL && pCtrlProp->GetDragControl())
			{
				m_pLButtonDownCtrl->OnMouseDrag(pt);
				return;
			}
		}

		// 鼠标按下是，需要锁定一个控件进行鼠标移动处理
		if (m_pMouseHoverCtrl != NULL)
		{
			IPropertyControlManager* pCtrlProp = m_pMouseHoverCtrl->GetControlBaseProp();
			if (pCtrlProp != NULL)
			{
				RECT CtrlRct = pCtrlProp->GetCtrlInWindowRect();
				if (::PtInRect(&CtrlRct, pt))
				{
					if (m_pMouseHoverCtrl->IsMousehover())
					{
						m_pMouseHoverCtrl->OnMouseMove(pt);
					}
					else
					{
						m_pMouseHoverCtrl->SetMouseHover(true);
						m_pMouseHoverCtrl->OnMouseEnter(pt);
					}
				}
				else
				{
					if (m_pMouseHoverCtrl->IsMousehover())
					{
						m_pMouseHoverCtrl->SetMouseHover(false);
						m_pMouseHoverCtrl->OnMouseLeave();
					}
				}
			}
		}
	}
	else
	{
		// 取得当前MouseMove的控件
		IControlBase *pControl = NULL;
		CheckMouseInControl(&m_ChildCtrlsVec, pt, &pControl);
		if (pControl == NULL)
		{
			if (m_pMouseHoverCtrl != NULL)
			{
				m_pMouseHoverCtrl->SetMouseHover(false);
				m_pMouseHoverCtrl->OnMouseLeave();
				m_pMouseHoverCtrl = NULL;
			}
			return;
		}

		// 派发鼠标消息到控件
		if (m_pMouseHoverCtrl == pControl)
		{
			m_pMouseHoverCtrl->OnMouseMove(pt);
		}
		else
		{
			if (m_pMouseHoverCtrl != NULL)
			{
				m_pMouseHoverCtrl->SetMouseHover(false);
				m_pMouseHoverCtrl->OnMouseLeave();
			}

			m_pMouseHoverCtrl = pControl;
			m_pMouseHoverCtrl->SetMouseHover(true);
			m_pMouseHoverCtrl->OnMouseEnter(pt);
		}
	}
}

void IWindowBaseImpl::OnLButtonDbClick(int nVirtKey, POINT pt)
{
	if (!IsInit())
		return;

	// 取得当前鼠标按下的控件
	IControlBase *pControl = NULL;
	CheckMouseInControl(&m_ChildCtrlsVec, pt, &pControl);
	if (pControl == NULL)
		return;

	pControl->OnLButtonDbClick(pt);
	SetFocusCtrl(pControl);
}

void IWindowBaseImpl::OnRButtonDown(int nVirtKey, POINT pt)
{
	if (!IsInit())
		return;

	// 取得当前鼠标按下的控件
	IControlBase *pControl = NULL;
	CheckMouseInControl(&m_ChildCtrlsVec, pt, &pControl);
	if (pControl == NULL)
		return;

	pControl->OnRButtonDown(pt);
	SetFocusCtrl(pControl);
}

// 设置当前得到焦点的控件，如果参数为NULL，说明当前没有控件得到焦点，所有控件都失去焦点
void IWindowBaseImpl::SetFocusCtrl(IControlBase *pControl)
{
	if (m_pFocusCtrl != NULL)
	{
		m_pFocusCtrl->OnKillFocus();
		m_pFocusCtrl = NULL;
	}

	if (pControl != NULL)
	{
		m_pFocusCtrl = pControl;
		m_pFocusCtrl->OnSetFocus();
	}
}

void IWindowBaseImpl::OnLButtonDown(int nVirtKey, POINT pt)
{
	if (!IsInit())
		return;

	// 取得当前鼠标按下的控件
	IControlBase *pControl = NULL;
	CheckMouseInControl(&m_ChildCtrlsVec, pt, &pControl);
	if (pControl == NULL)
	{
		SetFocusCtrl(NULL);

		// 是否最大化
		if (m_WndPropMgr.IsFullScreen())
			return;

		// 是否支持鼠标点击移动窗口
		if (m_WndPropMgr.GetDragWindow())
			::PostMessage(m_hWnd, WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(pt.x, pt.y));

		return;
	}

	::SetCapture(m_hWnd);
	m_bIsLButtonDown = true;

	// 派发鼠标消息到控件
	m_pLButtonDownCtrl = pControl;
	m_pLButtonDownCtrl->OnLButtonDown(pt);
	SetFocusCtrl(m_pLButtonDownCtrl);
}

void IWindowBaseImpl::OnLButtonUp(int nVirtKey, POINT pt)
{
	if (!IsInit())
		return;

	if (m_pLButtonDownCtrl != NULL)
	{
		::ReleaseCapture();
		m_bIsLButtonDown = false;
		m_pLButtonDownCtrl->OnLButtonUp(pt);
		m_pLButtonDownCtrl = NULL;
	}
}

void IWindowBaseImpl::OnSize(UINT nType, int cx, int cy)
{
	if (!IsInit())
		return;

	SIZE NSize;
	NSize.cx = cx;
	NSize.cy = cy;
	SetControlPostion(&m_ChildCtrlsVec, NSize);
}

void IWindowBaseImpl::SetControlPostion(CHILD_CTRLS_VEC *pCtrlVec, SIZE NewSize)
{
	if (pCtrlVec == NULL)
		return;

	int nCtns = pCtrlVec->size();
	for (int i = 0; i < nCtns; i++)
	{
		IControlBase* pCtrl = (*pCtrlVec)[i];
		if (pCtrl != NULL)
		{
			RECT ParentRctInWnd;
			INIT_RECT(ParentRctInWnd);

			IControlBase* pParentCtrl = pCtrl->GetParentControl();
			if (pParentCtrl == NULL)
			{
				// 没有父控件，说明直接附着在对话框上
				ParentRctInWnd.right = NewSize.cx;
				ParentRctInWnd.bottom = NewSize.cy;
			}
			else
			{
				IPropertyControlManager* pParentCtrlProp = pParentCtrl->GetControlBaseProp();
				if (pParentCtrlProp == NULL)
					continue;
				ParentRctInWnd = pParentCtrlProp->GetCtrlInWindowRect();
			}

			// 计算当前控件的位置
			SetControlWindowPostion(pCtrl, ParentRctInWnd);

			// 设置子控件的位置
			SetControlPostion(pCtrl->GetChildCtrlsVec(), NewSize);
		}
	}
}

// 根据控件布局信息得到相对于窗口的位置
void IWindowBaseImpl::SetControlWindowPostion(IControlBase* pCtrl, RECT ParentRctInWnd)
{
	if (pCtrl == NULL)
		return;

	IPropertyControlManager* pCtrlProp = pCtrl->GetControlBaseProp();
	if (pCtrlProp == NULL)
		return;

	RECT RctInWnd;
	INIT_RECT(RctInWnd);
	CONTROL_LAYOUT_INFO CtrlLayout = pCtrlProp->GetLayout();
	if (CtrlLayout.clType == CL_G_LEFT_TOP)
	{
		// 固定大小：左上角定位
		RctInWnd.left = ParentRctInWnd.left + CtrlLayout.nLeftSpace;
		RctInWnd.right = RctInWnd.left + CtrlLayout.nWidth;
		RctInWnd.top = ParentRctInWnd.top + CtrlLayout.nTopSpace;
		RctInWnd.bottom = RctInWnd.top + CtrlLayout.nHeight;
	}
	else if (CtrlLayout.clType == CL_G_LEFT_BOTTOM)
	{
		// 固定大小：左下角定位
		RctInWnd.left = ParentRctInWnd.left + CtrlLayout.nLeftSpace;
		RctInWnd.right = RctInWnd.left + CtrlLayout.nWidth;
		RctInWnd.bottom = ParentRctInWnd.bottom - CtrlLayout.nBottomSpace;
		RctInWnd.top = RctInWnd.bottom - CtrlLayout.nHeight;
	}
	else if (CtrlLayout.clType == CL_G_RIGHT_TOP)
	{
		// 固定大小：右上角定位
		RctInWnd.right = ParentRctInWnd.right - CtrlLayout.nRightSpace;
		RctInWnd.left = RctInWnd.right - CtrlLayout.nWidth;
		RctInWnd.top = ParentRctInWnd.top + CtrlLayout.nTopSpace;
		RctInWnd.bottom = RctInWnd.top + CtrlLayout.nHeight;
	}
	else if (CtrlLayout.clType == CL_G_RIGHT_BOTTOM)
	{
		// 固定大小：右下角定位
		RctInWnd.right = ParentRctInWnd.right - CtrlLayout.nRightSpace;
		RctInWnd.left = RctInWnd.right - CtrlLayout.nWidth;
		RctInWnd.bottom = ParentRctInWnd.bottom - CtrlLayout.nBottomSpace;
		RctInWnd.top = RctInWnd.bottom - CtrlLayout.nHeight;
	}
	else if (CtrlLayout.clType == CL_L_LEFT)
	{
		// 拉伸变动大小：撑满左侧
		RctInWnd.left = ParentRctInWnd.left + CtrlLayout.nLeftSpace;
		RctInWnd.right = RctInWnd.left + CtrlLayout.nWidth;
		RctInWnd.top = ParentRctInWnd.top + CtrlLayout.nTopSpace;
		RctInWnd.bottom = ParentRctInWnd.bottom - CtrlLayout.nBottomSpace;
	}
	else if (CtrlLayout.clType == CL_L_RIGHT)
	{
		// 拉伸变动大小：撑满右侧
		RctInWnd.right = ParentRctInWnd.right - CtrlLayout.nRightSpace;
		RctInWnd.left = RctInWnd.right - CtrlLayout.nWidth;
		RctInWnd.top = ParentRctInWnd.top + CtrlLayout.nTopSpace;
		RctInWnd.bottom = ParentRctInWnd.bottom - CtrlLayout.nBottomSpace;
	}
	else if (CtrlLayout.clType == CL_L_TOP)
	{
		// 拉伸变动大小：撑满上方
		RctInWnd.left = ParentRctInWnd.left + CtrlLayout.nLeftSpace;
		RctInWnd.right = ParentRctInWnd.right - CtrlLayout.nRightSpace;
		RctInWnd.top = ParentRctInWnd.top + CtrlLayout.nTopSpace;
		RctInWnd.bottom = RctInWnd.top + CtrlLayout.nHeight;
	}
	else if (CtrlLayout.clType == CL_L_BOTTOM)
	{
		// 拉伸变动大小：撑满下方
		RctInWnd.left = ParentRctInWnd.left + CtrlLayout.nLeftSpace;
		RctInWnd.right = ParentRctInWnd.right - CtrlLayout.nRightSpace;
		RctInWnd.bottom = ParentRctInWnd.bottom - CtrlLayout.nBottomSpace;
		RctInWnd.top = RctInWnd.bottom - CtrlLayout.nHeight;
	}
	else if (CtrlLayout.clType == CL_L_ALL)
	{
		// 拉伸变动大小：撑满全部
		RctInWnd = ParentRctInWnd;
	}
	else if (CtrlLayout.clType == CL_L_MIDDLE)
	{
		// 拉伸变动大小：居中
		RctInWnd.left = ParentRctInWnd.left + CtrlLayout.nLeftSpace;
		RctInWnd.right = ParentRctInWnd.right - CtrlLayout.nRightSpace;
		RctInWnd.top = ParentRctInWnd.top + CtrlLayout.nTopSpace;
		RctInWnd.bottom = ParentRctInWnd.bottom - CtrlLayout.nBottomSpace;
	}

	pCtrlProp->SetCtrlInWindowRect(RctInWnd);
}

// 销毁子类化窗口、释放资源
void IWindowBaseImpl::OnDestroy()
{
}

void IWindowBaseImpl::OnCreate()
{
}

void IWindowBaseImpl::OnTimer(UINT nTimerId)
{
	if (!IsInit())
		return;
}

void IWindowBaseImpl::OnKeyDown(int nVirtKey, int nFlag)
{
	if (!IsInit())
		return;

}

bool IWindowBaseImpl::OnSysCommand(int nSysCommand, int xPos, int yPos)
{
	if (!IsInit())
		return false;

	return false;
}

void IWindowBaseImpl::OnKillFocus(WPARAM wParam, LPARAM lParam)
{
	if (!IsInit())
		return;
}

void IWindowBaseImpl::OnSetFocus(WPARAM wParam, LPARAM lParam)
{
	if (!IsInit())
		return;
}

void IWindowBaseImpl::OnSizing(UINT nSide, LPRECT lpRect)
{
	if (!IsInit())
		return;
}

void IWindowBaseImpl::OnEnterSizeMove()
{
	if (!IsInit())
		return;
}

void IWindowBaseImpl::OnExitSizeMove()
{
	if (!IsInit())
		return;
}

void IWindowBaseImpl::OnPopupSystemMenu(POINT pt)
{
	if (!IsInit())
		return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// 功能函数 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 循环遍历每个控件的绘制
void IWindowBaseImpl::DrawControl()
{
	for (CHILD_CTRLS_VEC::iterator pCtrlItem = m_ChildCtrlsVec.begin(); pCtrlItem != m_ChildCtrlsVec.end(); pCtrlItem++)
	{
		IControlBase* pCtrl = *pCtrlItem;
		if (pCtrl != NULL)
		{
			pCtrl->OnPaintControl(m_WndMemDc);
		}
	}
}

void IWindowBaseImpl::RedrawWindow(RECT* pDrawRct)
{
	::RedrawWindow(m_hWnd, pDrawRct, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}
