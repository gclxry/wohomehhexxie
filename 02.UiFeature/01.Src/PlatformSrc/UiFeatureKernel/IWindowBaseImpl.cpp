
#include "stdafx.h"
#include "IWindowBaseImpl.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IPropertyControl.h"
#include "..\..\Inc\ICommonFun.h"
#include "IPropertySkinManagerImpl.h"
#include "IUiFeatureKernelImpl.h"
#include "CriSec.h"

// 弹出任务栏菜单消息，XP以下适用
#define WM_POPUPSYSTEMMENU						(0x0313)
// 绘制窗口和被选中的控件的边框的8个方块的宽度
#define FANGKUAI_SIZE							(6)



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IWindowBaseImpl::IWindowBaseImpl()
{
	SetObjectType(PROP_TYPE_WINDOW_NAME);

	m_Blend.BlendOp = AC_SRC_OVER;
	m_Blend.BlendFlags = 0;
	m_Blend.AlphaFormat = AC_SRC_ALPHA;
	m_Blend.SourceConstantAlpha = 255;

	m_hParent = NULL;
	m_hWnd = NULL;
	m_ChildCtrlsVec.clear();

	m_bIsDesignMode = false;
	m_bIsLButtonDown = false;
	m_pLButtonDownCtrl = NULL;
	m_pMouseHoverCtrl = NULL;
	m_pFocusCtrl = NULL;
	m_hBuilderView = NULL;
	m_nCurMouseStyle = -1;

	memset(&m_BD_FangKuai8, 0, sizeof(FANGKUAI_8));

	m_strSkinPath = "";
	m_strWindowObjectName = "";

	m_pUiKernel = IUiFeatureKernelImpl::GetInstance();
	m_pSkinPropMgr = IPropertySkinManagerImpl::GetInstance();
	m_pUiEngine = IUiFeatureKernelImpl::GetInstance()->GetUiEngine();

	m_bIsFullScreen = false;

	m_pXmlPropWindow = NULL;
	// Group:base
	m_pPropGroupBase = NULL;
	// base-类型名称
	m_pPropBase_TypeName = NULL;
	// base-objectid
	m_pPropBase_ObjectId = NULL;
	// base-name
	m_pPropBase_Name = NULL;
	// base-windowtitle
	m_pPropBase_WindowText = NULL;
	// base-visible
	m_pPropBase_Visible = NULL;
	// base-支持分层窗口
	m_pPropBase_Layered = NULL;
	// base-topmost
	m_pPropBase_TopMost = NULL;
	// base-sysbase
	m_pPropGroupSysBase = NULL;
	// base-sysbase-最大化
	m_pPropSysBase_CanFullScreen = NULL;
	// base-sysbase-最小化
	m_pPropSysBase_CanMiniSize = NULL;

	// Group-size
	m_pPropGroupWindowSize = NULL;
	// size-width
	m_pPropSize_WindowWidth = NULL;
	// size-height
	m_pPropSize_WindowHeight = NULL;

	// Group-drag(拖拽窗口)
	m_pPropGroupDrag = NULL;
	// drag-enable
	m_pPropDrag_Enable = NULL;

	// Group-Size(窗口的大小)
	m_pPropGroupSize = NULL;
	m_pPropSize_Enable = NULL;
	// Size-leftspace
	m_pPropSize_MaxWidth = NULL;
	// Size-rightspace
	m_pPropSize_MaxHeight = NULL;
	// Size-topspace
	m_pPropSize_MinWidth = NULL;
	// Size-bottomspace
	m_pPropSize_MinHeight = NULL;

	// Group-stretching(拉伸窗口)
	m_pPropGroupStretching = NULL;
	// stretching-enable
	m_pPropStretching_Enable = NULL;
	// stretching-leftspace
	m_pPropStretching_LeftSpace = NULL;
	// stretching-rightspace
	m_pPropStretching_RightSpace = NULL;
	// stretching-topspace
	m_pPropStretching_TopSpace = NULL;
	// stretching-bottomspace
	m_pPropStretching_BottomSpace = NULL;
	// Group-WindowRgn
	m_pPropGroupWindowRgn = NULL;
}

IWindowBaseImpl::~IWindowBaseImpl()
{
	ReleaseChildVec(&m_ChildCtrlsVec);
}

// 释放子控件列表
void IWindowBaseImpl::ReleaseChildVec(CHILD_CTRLS_VEC *pChildCtrlsVec)
{
	if (pChildCtrlsVec == NULL)
		return;

	for (CHILD_CTRLS_VEC::iterator pCtrlItem = pChildCtrlsVec->begin(); pCtrlItem != pChildCtrlsVec->end(); pCtrlItem++)
	{
		IControlBase* pCtrl = *pCtrlItem;
		if (pCtrl == NULL)
			continue;

		pCtrl->OnDestroy();
		// 释放子控件
		ReleaseChildVec(pCtrl->GetChildControlsVec());
		SAFE_DELETE(pCtrl);
	}
	pChildCtrlsVec->clear();
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
	IPropertyWindow* pWndProp = pPropSkinMgr->PG_InitWindowSkin(m_strSkinPath.c_str(), m_strWindowObjectName.c_str());
	if (pWndProp == NULL)
	{
		// 向窗口发送通知：初始化皮肤异常
		::PostMessage(m_hWnd, UM_INIT_WINDOW_ERROR, -2, NULL);
		return;
	}

	// 设置对话框属性
	PP_SetWindowPropetry(pWndProp, false);

	// 创建控件
	if (!CreateChildCtrlVec(NULL, GetChildPropControlVec(), &m_ChildCtrlsVec))
	{
		// 向窗口发送通知：创建控件失败
		::PostMessage(m_hWnd, UM_INIT_WINDOW_ERROR, -3, NULL);
		return;
	}

//////////////////////////////////////////////////////////////////////////
	// 初始化拉伸窗口操作
	m_WndResize.InitResizeInfo(this, m_pPropBase_Layered,
		m_pPropSize_Enable, m_pPropSize_MaxWidth, m_pPropSize_MaxHeight, m_pPropSize_MinWidth, m_pPropSize_MinHeight,
		m_pPropStretching_Enable, m_pPropStretching_LeftSpace, m_pPropStretching_RightSpace, m_pPropStretching_TopSpace, m_pPropStretching_BottomSpace);

	// 根据窗口基本属性，设置窗口基本样式
	SetWindowStyleByProp();

	// 向窗口发送通知：初始化皮肤完成
	::PostMessage(m_hWnd, UM_INIT_WINDOW_SUCCESS, NULL, NULL);
}

// 根据窗口基本属性，设置窗口基本样式
void IWindowBaseImpl::SetWindowStyleByProp()
{
	// 设置窗体的透明特性
	if (m_pPropBase_Layered != NULL)
		SetWindowTransparence(m_pPropBase_Layered->GetValue());

	// 窗口标题
	if (m_pPropBase_WindowText != NULL)
		::SetWindowTextA(this->GetSafeHandle(), m_pPropBase_WindowText->GetString());

	// 设置窗口置顶
	if (m_pPropBase_TopMost != NULL)
	{
		SIZE wndSize = this->PP_GetWindowPropSize();
		::SetWindowPos(this->GetSafeHandle(), (m_pPropBase_TopMost->GetValue() ? HWND_TOPMOST : HWND_NOTOPMOST), 0, 0, wndSize.cx, wndSize.cy, SWP_NOSIZE | SWP_NOMOVE);
	}

	// 当窗口的属性发生变化时需要通知窗口进行刷新
	RefreshWindowStyle();
}

// 设置窗体的透明特性
void IWindowBaseImpl::SetWindowTransparence(bool bIsTrans)
{
	DWORD dwExStyle = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
	if (bIsTrans)
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

// 创建控件
bool IWindowBaseImpl::CreateChildCtrlVec(IControlBase *pParentCtrl, PROP_CONTROL_VEC* pPropCtrlVec, CHILD_CTRLS_VEC* pCtrlVec)
{
	if (pPropCtrlVec == NULL || pCtrlVec == NULL || IUiFeatureKernelImpl::GetInstance() == NULL)
		return false;

	IWindowBase* pBaseThis = dynamic_cast<IWindowBase*>(this);
	if (pBaseThis == NULL)
		return false;

	for (PROP_CONTROL_VEC::iterator pCtrlItem = pPropCtrlVec->begin(); pCtrlItem != pPropCtrlVec->end(); pCtrlItem++)
	{
		IPropertyControl* pPropCtrl = *pCtrlItem;
		if (pPropCtrl == NULL)
			continue;

		IControlBase *pNewCtrl = IUiFeatureKernelImpl::GetInstance()->CreateControlByPropetry(pBaseThis, pParentCtrl, pPropCtrl);
		if (pNewCtrl == NULL)
			return false;

		if (!CreateChildCtrlVec(pNewCtrl, pPropCtrl->GetChildPropControlVec(), pNewCtrl->GetChildControlsVec()))
			return false;
	}

	return true;
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
			string strCtrlName = pCtrl->GetObjectName();
			if (strCtrlName.compare(pszCtrlName) == 0)
			{
				*ppCtrl = pCtrl;
				return true;
			}

			if (GetControlByName(pCtrl->GetChildControlsVec(), pszCtrlName, ppCtrl))
				return true;
		}
	}

	return false;
}

// 初始化：由外部调用，内部发送开始初始化的消息真正开始初始化
void IWindowBaseImpl::PG_InitWindowBase(HWND hWnd, char *pszSkinPath, char *pszWndName)
{
	if (m_hWnd != NULL || hWnd == NULL || pszSkinPath == NULL || pszWndName == NULL)
		return;

	m_hWnd = hWnd;
	m_strSkinPath = pszSkinPath;
	m_strWindowObjectName = pszWndName;

//	// 发送初始化消息
//	::PostMessage(hWnd, UM_INIT_WINDOW_BASE, NULL, NULL);
	OnInitWindowBase();
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
	else
	{
		// 取得窗口中设置属性的窗口大小
		SIZE WndSize = PP_GetWindowPropSize();
		RetRect.right = WndSize.cx;
		RetRect.bottom = WndSize.cy;
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

// 初始化对话框、加载窗口皮肤完成，在分层窗口模式下，初始化窗口后，显示窗口
void IWindowBaseImpl::OnInitWindowBaseEnd()
{
	if (m_pPropBase_Layered != NULL && m_pPropBase_Layered->GetValue() && m_pPropBase_TopMost != NULL)
	{
		// 在分层窗口模式下，初始化窗口后，显示窗口
		SIZE WndSize = this->PP_GetWindowPropSize();

		// 设置默认大小
		RECT WorkArea, CenterRect;
		INIT_RECT(WorkArea);
		INIT_RECT(CenterRect);
		::SystemParametersInfo(SPI_GETWORKAREA, 0, &WorkArea, 0);

		CenterRect.left = (RECT_WIDTH(WorkArea) - WndSize.cx) / 2;
		CenterRect.right = CenterRect.left + WndSize.cx;
		CenterRect.top = (RECT_HEIGHT(WorkArea) - WndSize.cy) / 2;
		CenterRect.bottom = CenterRect.top + WndSize.cy;

		// 设置窗口置顶样式
		::SetWindowPos(m_hWnd, (m_pPropBase_TopMost->GetValue() ? HWND_TOPMOST : HWND_NOTOPMOST),
			0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

		RedrawWindow(&CenterRect);
	}
}

// 立即重绘窗口
void IWindowBaseImpl::RedrawWindow(RECT *pDrawRect)
{
	if (IS_SAFE_HANDLE(m_hWnd) && m_pPropBase_Visible != NULL &&  m_pPropBase_Visible->GetValue())
	{
		if (m_pPropBase_Layered != NULL && m_pPropBase_Layered->GetValue())
		{
			HDC hDc = ::GetDC(m_hWnd);
			OnPaint(hDc, pDrawRect);
			::ReleaseDC(m_hWnd, hDc);
		}
		else
		{
			::RedrawWindow(m_hWnd, pDrawRect, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
		}
	}
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
		// 需要外部对话框接受的消息：使用皮肤初始化窗口异常
	case UM_INIT_WINDOW_ERROR:
		OnInitWindowBaseEnd();
		break;

//		// 初始化窗口
//	case UM_INIT_WINDOW_BASE:
//		bPassOn = false;
//		OnInitWindowBase();
//		break;


	case WM_GETMINMAXINFO:
		bPassOn = !OnGetMinMaxInfo((MINMAXINFO*)lParam);
		break;

	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = pt.y = 0;
			::GetCursorPos(&pt);
			::ScreenToClient(m_hWnd, &pt);
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

	case WM_NCHITTEST:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			::ScreenToClient(m_hWnd, &pt);
			LRESULT lResult = OnNcHitTest(pt.x, pt.y);
			if (lResult != -1)
			{
				bPassOn = false;
				return lResult;
			}
		}
		break;

	case WM_SETCURSOR:
		bPassOn = !OnSetCursor((HWND)wParam, LOWORD(lParam), HIWORD(lParam));
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
			HDC hDc = ::BeginPaint(m_hWnd, &ps);
			OnPaint(hDc);
			::EndPaint(m_hWnd, &ps);
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
bool IWindowBaseImpl::OnGetMinMaxInfo(MINMAXINFO *pMinMaxInfo)
{
	if (pMinMaxInfo == NULL || m_pPropSize_Enable == NULL || !m_pPropSize_Enable->GetValue())
		return false;

	bool bRet = false;
	if (m_pPropSize_MaxWidth != NULL && m_pPropSize_MaxWidth->GetValue() > 0
		&& m_pPropSize_MaxHeight != NULL && m_pPropSize_MaxHeight->GetValue() > 0)
	{
		pMinMaxInfo->ptMaxTrackSize.x = m_pPropSize_MaxWidth->GetValue();
		pMinMaxInfo->ptMaxTrackSize.y = m_pPropSize_MaxHeight->GetValue();
		bRet = true;
	}

	if (m_pPropSize_MinWidth != NULL && m_pPropSize_MinWidth->GetValue() > 0
		&& m_pPropSize_MaxWidth->GetValue() > m_pPropSize_MinWidth->GetValue()
		&& m_pPropSize_MinHeight != NULL && m_pPropSize_MinHeight->GetValue() > 0
		&& m_pPropSize_MaxHeight->GetValue() > m_pPropSize_MinHeight->GetValue())
	{
		pMinMaxInfo->ptMinTrackSize.x = m_pPropSize_MinWidth->GetValue();
		pMinMaxInfo->ptMinTrackSize.y = m_pPropSize_MinHeight->GetValue();
		bRet = true;
	}

	return bRet;
}

void IWindowBaseImpl::OnPaint(HDC hWndDc, RECT *pLayeredRect)
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
	if (PP_GetLayeredWindow())
	{
		POINT ptWinPos = {WndRect.left, WndRect.top};
		POINT ptSrc = {0, 0};
		SIZE sizeWindow = {RECT_WIDTH(WndRect), RECT_HEIGHT(WndRect)};
		
		if (pLayeredRect != NULL)
		{
			// 设置目标渲染窗口位置
			ptWinPos.x = pLayeredRect->left;
			ptWinPos.y = pLayeredRect->top;
			sizeWindow.cx = RECT_WIDTH(*pLayeredRect);
			sizeWindow.cy = RECT_HEIGHT(*pLayeredRect);
		}

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
		if (pCtrl != NULL && pCtrl->IsVisible())
		{
			if (pCtrl->GetReceiveMouseMessage())
			{
				RECT CtrlRct = pCtrl->GetWindowRect();
				if (::PtInRect(&CtrlRct, pt))
				{
					*ppControl = pCtrl;
					CHILD_CTRLS_VEC *pCtrlsVec = pCtrl->GetChildControlsVec();
					CheckMouseInControl(pCtrlsVec, pt, ppControl);
					return true;
				}
			}
			else
			{
				CHILD_CTRLS_VEC *pCtrlsVec = pCtrl->GetChildControlsVec();
				if (CheckMouseInControl(pCtrlsVec, pt, ppControl))
					return true;
			}
		}
	}

	return false;
}

void IWindowBaseImpl::ResizeInLayeredWindow(RECT NewWndRect)
{
	if (m_pPropBase_TopMost == NULL || m_pPropBase_Layered == NULL || !m_pPropBase_Layered->GetValue())
		return;

	// 分层窗口不能直接渲染，必须先要设置窗口大小才可以
	::SetWindowPos(m_hWnd, (m_pPropBase_TopMost->GetValue() ? HWND_TOPMOST : HWND_NOTOPMOST),
		0, 0, RECT_WIDTH(NewWndRect), RECT_HEIGHT(NewWndRect), SWP_NOMOVE);

	OnSize(0, RECT_WIDTH(NewWndRect), RECT_HEIGHT(NewWndRect));

	RedrawWindow(&NewWndRect);
}

void IWindowBaseImpl::OnMouseMove(int nVirtKey, POINT pt)
{
	if (!IsInit())
		return;

	// 窗口的拉伸操作
	RECT OutOldRect, OutNewRect;
	if (m_WndResize.ResizeInLayeredWindow(OutOldRect, OutNewRect))
	{
		ResizeInLayeredWindow(OutNewRect);
		return;
	}

	if (m_bIsLButtonDown)
	{
		if (m_pLButtonDownCtrl != NULL)
		{
			// 如果允许在控件内部进行自由拖动
			if (m_pLButtonDownCtrl->GetDragInControl())
			{
				m_pLButtonDownCtrl->OnMouseDragInCtrl(pt);
				return;
			}
		}

		// 鼠标按下是，需要锁定一个控件进行鼠标移动处理
		if (m_pMouseHoverCtrl != NULL)
		{
			RECT CtrlRct = m_pMouseHoverCtrl->GetWindowRect();
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
	else
	{
		// 鼠标是否移动到了窗口可以进行拉伸操作的边缘
		if (m_WndResize.MouseMoveInWindowFrame(pt) != HTNOWHERE)
			return;

		SetWindowCursor(UF_IDC_ARROW);

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

// 显示自定义光标
void IWindowBaseImpl::SetWindowCursor(int nCursor)
{
	if (nCursor == m_nCurMouseStyle)
	{
		if (UF_IDC_ARROW == m_nCurMouseStyle)
			m_nCurMouseStyle = -1;
		return;
	}

	::ShowCursor(FALSE);
	m_nCurMouseStyle = nCursor;
	::ShowCursor(TRUE);
	::PostMessage(this->m_hWnd, WM_SETCURSOR, NULL, NULL);
}

bool IWindowBaseImpl::OnSetCursor(HWND hWnd, int nHitTest, int nMsgId)
{
	if (m_nCurMouseStyle != -1)
	{
		HCURSOR hCursor = ::LoadCursor(NULL, MAKEINTRESOURCE(m_nCurMouseStyle));
		if (hCursor != NULL)
		{
			HCURSOR hSetCur = ::SetCursor(hCursor);
			if (hSetCur != NULL)
			{
				::DestroyCursor(hSetCur);
				return true;
			}
		}
	}

	return false;
}

LRESULT IWindowBaseImpl::OnNcHitTest(int nX, int nY)
{
	if (m_pPropBase_Layered == NULL || !m_pPropBase_Layered->GetValue())
	{
		// 非分层模式下才进行拉伸操作
		POINT pt;
		pt.x = nX;
		pt.y = nY;
		int nHit = m_WndResize.MouseMoveInWindowFrame(pt);
		if (nHit != HTNOWHERE)
			return nHit;
	}

	return -1;
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

	// 判断是否进入了拉伸窗口范围，进入则开始进行拉伸操作
	if (m_WndResize.BeginResizeInLayeredWindow())
		return;

	// 取得当前鼠标按下的控件
	IControlBase *pControl = NULL;
	CheckMouseInControl(&m_ChildCtrlsVec, pt, &pControl);
	if (pControl == NULL)
	{
		SetFocusCtrl(NULL);

		// 是否最大化
		if (PP_IsFullScreen())
			return;

		// 是否支持鼠标点击移动窗口
		if (PP_GetDragWindow())
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

	// 释放窗口拉伸操作
	m_WndResize.EndResizeInLayeredWindow();

	::ReleaseCapture();
	m_bIsLButtonDown = false;

	if (m_pLButtonDownCtrl != NULL)
	{
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
				ParentRctInWnd = pParentCtrl->GetWindowRect();
			}

			// 计算当前控件的位置
			SetControlWindowPostion(pCtrl, ParentRctInWnd);

			// 设置子控件的位置
			SetControlPostion(pCtrl->GetChildControlsVec(), NewSize);
		}
	}
}

// 根据控件布局信息得到相对于窗口的位置
void IWindowBaseImpl::SetControlWindowPostion(IControlBase* pCtrl, RECT ParentRctInWnd)
{
	if (pCtrl == NULL)
		return;

	RECT RctInWnd;
	INIT_RECT(RctInWnd);
	CONTROL_LAYOUT_INFO CtrlLayout = pCtrl->GetLayout();
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

	pCtrl->SetWindowRect(RctInWnd);
}

// 销毁子类化窗口、释放资源
void IWindowBaseImpl::OnDestroy()
{
}

void IWindowBaseImpl::OnCreate()
{
}

void IWindowBaseImpl::BD_OnTimer(UINT nTimerId, HWND hView)
{
	// TBD 动画图片在播放的时候，删除控件、添加控件会导致崩溃，
	// 时间原因，先不修正，暂时不支持在VIEW中播放动画
	// 问题的结症在于，对于队列的操作
	KERNEL_CRI_SEC;
	m_hBuilderView = hView;
//	OnTimer(nTimerId);
}

void IWindowBaseImpl::OnTimer(UINT nTimerId)
{
	if (!IsInit() || m_pSkinPropMgr == NULL)
		return;

	bool bNeedDraw = false;
	if (nTimerId == UM_DFT_ANIMATION_TIMER)
	{
		ONE_RESOURCE_PROP_MAP* pImagePropMap = ((IPropertySkinManagerImpl*)m_pSkinPropMgr)->GetOneResourcePropMap(PROP_TYPE_IMAGE_NAME);
		if (pImagePropMap == NULL)
			return;

		for (ONE_RESOURCE_PROP_MAP::iterator pImage = pImagePropMap->begin(); pImage != pImagePropMap->end(); pImage++)
		{
			IPropertyImage* pImageProp = dynamic_cast<IPropertyImage*>(pImage->second);
			if (pImageProp == NULL)
				continue;

			IFeatureObject* pOwner = pImageProp->GetOwnerObject();
			if (pOwner == NULL)
				continue;

			IControlBase* pCtrl = dynamic_cast<IControlBase*>(pOwner);
			if (pCtrl != NULL)
			{
				// 非自身窗口控件，不进行动画绘制
				IWindowBaseImpl* pWnd = dynamic_cast<IWindowBaseImpl*>(pCtrl->GetOwnerWindow());
				if (pWnd == NULL || pWnd != this)
					continue;

				// 不可见，不刷新控件界面
				if (!pCtrl->IsVisible())
					continue;
			}
			else
			{
				// 非自身窗口控件，不进行动画绘制
				IWindowBaseImpl* pWnd = dynamic_cast<IWindowBaseImpl*>(pOwner);
				if (pWnd == NULL || pWnd != this)
					continue;
			}

			if (pImageProp->OnDrawAnimation())
			{
				if (pCtrl == NULL)
				{
					this->InvalidateRect(NULL);
				}
				else
				{
					pCtrl->RedrawControl();
					this->InvalidateRect(&(pCtrl->GetWindowRect()));
				}

				bNeedDraw = true;
			}
		}
	}

	for (CHILD_CTRLS_VEC::iterator pCtrlItem = m_ChildCtrlsVec.begin(); pCtrlItem != m_ChildCtrlsVec.end(); pCtrlItem++)
	{
		IControlBase* pCtrl = *pCtrlItem;
		if (pCtrl != NULL)
		{
			if (nTimerId == UM_DFT_ANIMATION_TIMER && pCtrl->IsVisible())
			{
				bool bDraw = pCtrl->OnDrawAnimation();
				if (bDraw)
				{
					bNeedDraw = true;
					this->InvalidateRect(&(pCtrl->GetWindowRect()));
				}
			}
			else
			{
				pCtrl->OnTimer(nTimerId);
			}
		}
	}

	if (bNeedDraw)
		this->UpdateWindow();
}

void IWindowBaseImpl::InvalidateRect(RECT *lpRect)
{
	if (::IsWindow(m_hWnd))
		::InvalidateRect(m_hWnd, lpRect, FALSE);
}

void IWindowBaseImpl::UpdateWindow()
{
	if (::IsWindow(m_hWnd))
	{
		::UpdateWindow(m_hWnd);
	}
	else
	{
		if (::IsWindow(m_hBuilderView))
			::RedrawWindow(m_hBuilderView, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
	}
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

// 向队列未插入一个控件
void IWindowBaseImpl::AppendChildContrl(IControlBase *pCtrl)
{
	if (pCtrl != NULL)
		m_ChildCtrlsVec.push_back(pCtrl);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// 功能函数 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 循环遍历每个控件的绘制
void IWindowBaseImpl::DrawControl()
{
	RECT WndRct = this->GetClientRect();
	for (CHILD_CTRLS_VEC::iterator pCtrlItem = m_ChildCtrlsVec.begin(); pCtrlItem != m_ChildCtrlsVec.end(); pCtrlItem++)
	{
		IControlBase* pCtrl = *pCtrlItem;
		if (pCtrl != NULL)
		{
			pCtrl->OnPaintControl(m_WndMemDc, WndRct);
		}
	}
}

// 是否为设计模式
bool IWindowBaseImpl::IsDesignMode()
{
	return m_bIsDesignMode;
}

void IWindowBaseImpl::BD_InitWindowBase(IPropertyWindow *pWindowProp, bool bSetDftProp)
{
	m_bIsDesignMode = true;
	if (pWindowProp == NULL)
		return;

	// 在Builder中绘制用的边框色块
	BD_NewFrameImage();

	PP_SetWindowPropetry(pWindowProp, bSetDftProp);
	this->SetObjectId(pWindowProp->GetObjectId());
	if (m_pPropBase_Name == NULL || m_pPropBase_Name->GetString() == NULL || strlen(m_pPropBase_Name->GetString()) <= 0)
	{
		if (m_pPropBase_Name != NULL)
			m_pPropBase_Name->SetString("【新建窗体名称】");
		this->SetObjectName("【新建窗体名称】");
	}
	else
	{
		this->SetObjectName(m_pPropBase_Name->GetString());
	}
}

// 在Builder中绘制用的边框色块
void IWindowBaseImpl::BD_NewFrameImage()
{
	if (m_pSkinPropMgr == NULL)
		return;

	m_BuilderWndFrameImageBase.SetUiKernel(IUiFeatureKernelImpl::GetInstance());
	m_BuilderCtrlFrameImageBase.SetUiKernel(IUiFeatureKernelImpl::GetInstance());

	// 在Builder中绘制用的边框色块
	string strPath = PathHelper("ControlsRes\\BuilderWindowFrame.bmp");
	BD_NewFrameImageBase(&m_BuilderWndFrameImageBase, strPath);

	strPath = PathHelper("ControlsRes\\BuilderCtrlFrame.bmp");
	BD_NewFrameImageBase(&m_BuilderCtrlFrameImageBase, strPath);
}

void IWindowBaseImpl::BD_NewFrameImageBase(IPropertyImageBase *pImgBase, string strImgPath)
{
	if (pImgBase == NULL)
		return;

	IMAGE_BASE_PROP ImgBase;
	IPropertyImageBase::InitPropImageBase(&ImgBase);

	ImgBase.bIsZipFile = false;
	ImgBase.strFileName = strImgPath;
	ImgBase.ImgShowType = IST_ALL_LASHEN;
	ImgBase.RectInImage.left = ImgBase.RectInImage.top = 0;
	ImgBase.RectInImage.right = ImgBase.RectInImage.bottom = FANGKUAI_SIZE;
	INIT_RECT(ImgBase.jggInfo);

	pImgBase->SetImageProp(&ImgBase);
}

bool IWindowBaseImpl::IsInit()
{
	return (m_pXmlPropWindow != NULL && m_pSkinPropMgr != NULL);
}

void IWindowBaseImpl::BD_DrawWindowView(CDrawingBoard &ViewMemDc)
{
	if (ViewMemDc.GetSafeHdc() == NULL || m_pUiEngine == NULL || m_pPropSize_WindowWidth == NULL || m_pPropSize_WindowHeight == NULL)
		return;

	int nWidth = m_pPropSize_WindowWidth->GetValue();
	int nHeight = m_pPropSize_WindowHeight->GetValue();
	
	// 创建内存dc
	m_WndMemDc.Create(nWidth, nHeight, 0, false, true);
	if (m_WndMemDc.GetBits() == NULL)
		return;

	// 循环遍历每个控件的绘制
	DrawControl();

	// 绘制到父DC上
	m_pUiEngine->AlphaBlend(ViewMemDc, m_BD_FangKuai8.EntityRct.left, m_BD_FangKuai8.EntityRct.top, nWidth, nHeight,
		m_WndMemDc, 0, 0, nWidth, nHeight);

	// 绘制窗口的选择状态
	BD_DrawSelectRect(ViewMemDc, m_BD_FangKuai8, true);

	// 绘制焦点控件的选择状态
	if (m_pFocusCtrl != NULL)
	{
		FANGKUAI_8 *pFangKuai8 = m_pFocusCtrl->BD_GetFangKuai8Rect();
		BD_DrawSelectRect(ViewMemDc, *pFangKuai8, false);
	}
}

// 绘制窗口和被选中的控件的边框的8个方块
void IWindowBaseImpl::BD_DrawSelectRect(CDrawingBoard &MemDc, FANGKUAI_8 &FangKuai8, bool bIsWndFrame)
{
	IPropertyImageBase *pPropImg = &m_BuilderCtrlFrameImageBase;
	if (bIsWndFrame)
		pPropImg = &m_BuilderWndFrameImageBase;

	FangKuai8.LeftTop.left = FangKuai8.EntityRct.left - FANGKUAI_SIZE;
	FangKuai8.LeftTop.top = FangKuai8.EntityRct.top - FANGKUAI_SIZE;
	FangKuai8.LeftTop.right = FangKuai8.LeftTop.left + FANGKUAI_SIZE;
	FangKuai8.LeftTop.bottom = FangKuai8.LeftTop.top + FANGKUAI_SIZE;
	pPropImg->DrawImage(MemDc, FangKuai8.LeftTop);

	FangKuai8.LeftMid.left = FangKuai8.EntityRct.left - FANGKUAI_SIZE;
	FangKuai8.LeftMid.top = FangKuai8.EntityRct.top + (RECT_HEIGHT(FangKuai8.EntityRct) / 2) - (FANGKUAI_SIZE / 2);
	FangKuai8.LeftMid.right = FangKuai8.LeftMid.left + FANGKUAI_SIZE;
	FangKuai8.LeftMid.bottom = FangKuai8.LeftMid.top + FANGKUAI_SIZE;
	pPropImg->DrawImage(MemDc, FangKuai8.LeftMid);

	FangKuai8.LeftBottom.left = FangKuai8.EntityRct.left - FANGKUAI_SIZE;
	FangKuai8.LeftBottom.top = FangKuai8.EntityRct.bottom;
	FangKuai8.LeftBottom.right = FangKuai8.LeftBottom.left + FANGKUAI_SIZE;
	FangKuai8.LeftBottom.bottom = FangKuai8.LeftBottom.top + FANGKUAI_SIZE;
	pPropImg->DrawImage(MemDc, FangKuai8.LeftBottom);

	FangKuai8.MidTop.left = FangKuai8.EntityRct.left + (RECT_WIDTH(FangKuai8.EntityRct) / 2) - (FANGKUAI_SIZE / 2);
	FangKuai8.MidTop.top = FangKuai8.EntityRct.top - FANGKUAI_SIZE;
	FangKuai8.MidTop.right = FangKuai8.MidTop.left + FANGKUAI_SIZE;
	FangKuai8.MidTop.bottom = FangKuai8.MidTop.top + FANGKUAI_SIZE;
	pPropImg->DrawImage(MemDc, FangKuai8.MidTop);

	FangKuai8.MidBottom.left = FangKuai8.EntityRct.left + (RECT_WIDTH(FangKuai8.EntityRct) / 2) - (FANGKUAI_SIZE / 2);
	FangKuai8.MidBottom.top = FangKuai8.EntityRct.bottom;
	FangKuai8.MidBottom.right = FangKuai8.MidBottom.left + FANGKUAI_SIZE;
	FangKuai8.MidBottom.bottom = FangKuai8.MidBottom.top + FANGKUAI_SIZE;
	pPropImg->DrawImage(MemDc, FangKuai8.MidBottom);

	FangKuai8.RightTop.left = FangKuai8.EntityRct.right;
	FangKuai8.RightTop.top = FangKuai8.EntityRct.top - FANGKUAI_SIZE;
	FangKuai8.RightTop.right = FangKuai8.RightTop.left + FANGKUAI_SIZE;
	FangKuai8.RightTop.bottom = FangKuai8.RightTop.top + FANGKUAI_SIZE;
	pPropImg->DrawImage(MemDc, FangKuai8.RightTop);

	FangKuai8.RightMid.left = FangKuai8.EntityRct.right;
	FangKuai8.RightMid.top = FangKuai8.EntityRct.top + (RECT_HEIGHT(FangKuai8.EntityRct) / 2) - (FANGKUAI_SIZE / 2);
	FangKuai8.RightMid.right = FangKuai8.RightMid.left + FANGKUAI_SIZE;
	FangKuai8.RightMid.bottom = FangKuai8.RightMid.top + FANGKUAI_SIZE;
	pPropImg->DrawImage(MemDc, FangKuai8.RightMid);

	FangKuai8.RightBottom.left = FangKuai8.EntityRct.right;
	FangKuai8.RightBottom.top = FangKuai8.EntityRct.bottom;
	FangKuai8.RightBottom.right = FangKuai8.RightBottom.left + FANGKUAI_SIZE;
	FangKuai8.RightBottom.bottom = FangKuai8.RightBottom.top + FANGKUAI_SIZE;
	pPropImg->DrawImage(MemDc, FangKuai8.RightBottom);
}

// 取得窗口中设置属性的窗口大小
SIZE IWindowBaseImpl::PP_GetWindowPropSize()
{
	SIZE WndSize;
	WndSize.cx = WndSize.cy = 0;
	if (m_pPropSize_WindowWidth != NULL && m_pPropSize_WindowHeight != NULL)
	{
		WndSize.cx = m_pPropSize_WindowWidth->GetValue();
		WndSize.cy = m_pPropSize_WindowHeight->GetValue();
	}

	return WndSize;
}

// 得到在Builder中显示的四周8个方块的位置
FANGKUAI_8* IWindowBaseImpl::BD_GetFangKuai8Rect()
{
	return &m_BD_FangKuai8;
}

// 取得子控件列表
CHILD_CTRLS_VEC* IWindowBaseImpl::GetChildControlsVec()
{
	return &m_ChildCtrlsVec;
}

// 取得当前输入位置的控件
IControlBase* IWindowBaseImpl::BD_GetMouseInControl(POINT pt)
{
	if (!::PtInRect(&(m_BD_FangKuai8.EntityRct), pt))
		return NULL;

	IControlBase* pControl = NULL;
	BD_CheckMouseInControl(&m_ChildCtrlsVec, pt, &pControl);
	return pControl;
}

bool IWindowBaseImpl::BD_CheckMouseInControl(CHILD_CTRLS_VEC *pCtrlVec, POINT pt, IControlBase** ppControl)
{
	if (pCtrlVec == NULL || ppControl == NULL)
		return false;

	int nCtns = pCtrlVec->size();
	for (int i = nCtns - 1; i >= 0; i--)
	{
		IControlBase* pCtrl = (*pCtrlVec)[i];
		if (pCtrl != NULL && pCtrl->IsVisible())
		{
			FANGKUAI_8 *pCtrlFangkuai8 = pCtrl->BD_GetFangKuai8Rect();
			if (::PtInRect(&pCtrlFangkuai8->EntityRct, pt))
			{
				*ppControl = pCtrl;
				CHILD_CTRLS_VEC *pCtrlsVec = pCtrl->GetChildControlsVec();
				BD_CheckMouseInControl(pCtrlsVec, pt, ppControl);
				return true;
			}
		}
	}

	return false;
}

// 取得当前激活的控件
IControlBase* IWindowBaseImpl::BD_GetFocusControl()
{
	return m_pFocusCtrl;
}

// 设置当前激活的控件
void IWindowBaseImpl::BD_SetFocusControl(IControlBase* pControl)
{
	m_pFocusCtrl = pControl;
}

// 设置控件在编辑模式下的位置和大小
void IWindowBaseImpl::BD_SetControlRect(IControlBase* pControl, RECT RctInView)
{
	if (pControl == NULL || pControl->BD_GetFangKuai8Rect() == NULL)
		return;

	FANGKUAI_8* pFk8 = pControl->BD_GetFangKuai8Rect();
	pFk8->EntityRct = RctInView;

	RECT InWindowRect;
	INIT_RECT(InWindowRect);
	InWindowRect.left = RctInView.left - m_BD_FangKuai8.EntityRct.left;
	InWindowRect.right = InWindowRect.left + RECT_WIDTH(RctInView);
	InWindowRect.top = RctInView.top - m_BD_FangKuai8.EntityRct.top;
	InWindowRect.bottom = InWindowRect.top + RECT_HEIGHT(RctInView);

	pControl->ResetWindowRect(InWindowRect);
}

// 初始化所有控件在Builder中的显示位置
void IWindowBaseImpl::BD_SetAllCtrlRectInView()
{
	BD_SetControlRectInView(&m_ChildCtrlsVec);
}

void IWindowBaseImpl::BD_SetControlRectInView(CHILD_CTRLS_VEC *pChildCtrlsVec)
{
	if (pChildCtrlsVec == NULL)
		return;

	for (CHILD_CTRLS_VEC::iterator pCtrlItem = pChildCtrlsVec->begin(); pCtrlItem != pChildCtrlsVec->end(); pCtrlItem++)
	{
		IControlBase* pCtrl = *pCtrlItem;
		if (pCtrl == NULL || pCtrl->GetOwnerWindow() == NULL)
			continue;

		FANGKUAI_8* pSetFk8 = pCtrl->BD_GetFangKuai8Rect();
		if (pSetFk8 == NULL)
			continue;

		FANGKUAI_8* pWndFk8 = pCtrl->GetOwnerWindow()->BD_GetFangKuai8Rect();
		if (pWndFk8 == NULL)
			continue;

		RECT CtrlRct = pCtrl->GetWindowRect();

		pSetFk8->EntityRct.left = pWndFk8->EntityRct.left + CtrlRct.left;
		pSetFk8->EntityRct.right = pSetFk8->EntityRct.left + RECT_WIDTH(CtrlRct);
		pSetFk8->EntityRct.top = pWndFk8->EntityRct.top + CtrlRct.top;
		pSetFk8->EntityRct.bottom = pSetFk8->EntityRct.top + RECT_HEIGHT(CtrlRct);

		BD_SetControlRectInView(pCtrl->GetChildControlsVec());
	}
}

// 重新计算子控件的位置和大小
void IWindowBaseImpl::ResetChildCtrlPostion(CHILD_CTRLS_VEC* pChildVec, bool bMemToProp)
{
	if (pChildVec == NULL)
		return;

	for (CHILD_CTRLS_VEC::iterator pCtrlItem = pChildVec->begin(); pCtrlItem != pChildVec->end(); pCtrlItem++)
	{
		IControlBase* pCtrl = *pCtrlItem;
		if (pCtrl == NULL || pCtrl->GetOwnerWindow() == NULL)
			continue;

		RECT ParentRct;
		INIT_RECT(ParentRct);
		IControlBase* pParentCtrl = pCtrl->GetParentControl();
		if (pParentCtrl != NULL)
			ParentRct = pParentCtrl->GetWindowRect();
		else
			ParentRct = pCtrl->GetOwnerWindow()->GetClientRect();

		SetControlWindowPostion(pCtrl, ParentRct);

		if (bMemToProp)
			pCtrl->ResetWindowRect(pCtrl->GetWindowRect());

		ResetChildCtrlPostion(pCtrl->GetChildControlsVec(), bMemToProp);
	}
}

IUiFeatureKernel* IWindowBaseImpl::GetUiKernel()
{
	return m_pUiKernel;
}