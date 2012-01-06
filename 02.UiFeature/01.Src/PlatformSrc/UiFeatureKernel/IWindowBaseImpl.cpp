
#include "stdafx.h"
#include "IWindowBaseImpl.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IPropertyControl.h"
#include "..\..\Inc\ICommonFun.h"
#include "IPropertySkinManagerImpl.h"
#include "IUiFeatureKernelImpl.h"

// �����������˵���Ϣ��XP��������
#define WM_POPUPSYSTEMMENU						(0x0313)
// ���ƴ��ںͱ�ѡ�еĿؼ��ı߿��8������Ŀ��
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

	m_bIsLButtonDown = false;
	m_pLButtonDownCtrl = NULL;
	m_pMouseHoverCtrl = NULL;
	m_pFocusCtrl = NULL;

	memset(&m_BD_FangKuai8, 0, sizeof(FANGKUAI_8));

	m_strSkinPath = "";
	m_strWindowObjectName = "";

	m_pSkinPropMgr = IPropertySkinManagerImpl::GetInstance();
	m_pUiEngine = IUiFeatureKernelImpl::GetInstance()->GetUiEngine();

	m_bIsFullScreen = false;

	m_pXmlPropWindow = NULL;
	// Group:base
	m_pPropGroupBase = NULL;
	// base-��������
	m_pPropBase_TypeName = NULL;
	// base-objectid
	m_pPropBase_ObjectId = NULL;
	// base-name
	m_pPropBase_Name = NULL;
	// base-windowtitle
	m_pPropBase_WindowText = NULL;
	// base-visible
	m_pPropBase_Visible = NULL;
	// base-֧�ֲַ㴰��
	m_pPropBase_Layered = NULL;
	// base-topmost
	m_pPropBase_TopMost = NULL;
	// base-sysbase
	m_pPropGroupSysBase = NULL;
	// base-sysbase-���
	m_pPropSysBase_CanFullScreen = NULL;
	// base-sysbase-��С��
	m_pPropSysBase_CanMiniSize = NULL;
	// Group-size
	m_pPropGroupSize = NULL;
	// size-width
	m_pPropSize_Width = NULL;
	// size-height
	m_pPropSize_Height = NULL;
	// Group-drag(��ק����)
	m_pPropGroupDrag = NULL;
	// drag-enable
	m_pPropDrag_Enable = NULL;
	// Group-stretching(���촰��)
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

// �ͷ��ӿؼ��б�
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
		// �ͷ��ӿؼ�
		ReleaseChildVec(pCtrl->GetChildCtrlsVec());
		SAFE_DELETE(pCtrl);
	}
	pChildCtrlsVec->clear();
}

// �ػ�ؼ�
void IWindowBaseImpl::RedrawControl(IControlBase* pCtrl, bool bDrawImmediately)
{
	if (pCtrl == NULL)
		return;

//	pCtrl->
//	if (this->RedrawWindow())
//	{
//	}
}

// �����ڵ����Է����仯ʱ��Ҫ֪ͨ���ڽ���ˢ��ʱ����
void IWindowBaseImpl::RefreshWindowStyle()
{
	// �ᴥ�� WM_NCCALCSIZE ��Ϣ
	::SetWindowPos(m_hWnd, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE | SWP_NOMOVE);
}

// �ڲ����ܵ���ʼ����Ϣ����ʼ��ʼ�����ڣ�����Ƥ��
void IWindowBaseImpl::OnInitWindowBase()
{
//// ���öԻ��������ʽ //////////////////////////////////////////////////////////////////////
	// ȡ�öԻ��������ʽ����
	DWORD dwStyle = ::GetWindowLong(m_hWnd, GWL_STYLE);
	dwStyle &= (~WS_POPUP);
	dwStyle &= (~WS_DLGFRAME);
	// �Ի��������ʽ����
	dwStyle |= WS_OVERLAPPED | WS_THICKFRAME;
	::SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);

//////////////////////////////////////////////////////////////////////////
	// ��ʼ���Ի���Ƥ��
	IPropertySkinManager *pPropSkinMgr = IPropertySkinManagerImpl::GetInstance();
	if (pPropSkinMgr == NULL)
	{
		// �򴰿ڷ���֪ͨ����ʼ��Ƥ���쳣
		::PostMessage(m_hWnd, UM_INIT_WINDOW_ERROR, -1, NULL);
		return;
	}

	// ��ʼ���Ի���Ƥ��
	IPropertyWindow* pWndProp = pPropSkinMgr->PG_InitWindowSkin(m_strSkinPath.c_str(), m_strWindowObjectName.c_str());
	if (pWndProp == NULL)
	{
		// �򴰿ڷ���֪ͨ����ʼ��Ƥ���쳣
		::PostMessage(m_hWnd, UM_INIT_WINDOW_ERROR, -2, NULL);
		return;
	}
	// ���öԻ�������
	PP_SetWindowPropetry(pWndProp, false);

//////////////////////////////////////////////////////////////////////////
	// �����ڵ����Է����仯ʱ��Ҫ֪ͨ���ڽ���ˢ��
	RefreshWindowStyle();

	// �򴰿ڷ���֪ͨ����ʼ��Ƥ�����
	::PostMessage(m_hWnd, UM_INIT_WINDOW_SUCCESS, NULL, NULL);
}

// ȡ�ô��ڿؼ�ָ��
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

			if (GetControlByName(pCtrl->GetChildCtrlsVec(), pszCtrlName, ppCtrl))
				return true;
		}
	}

	return false;
}

// ��ʼ�������ⲿ���ã��ڲ����Ϳ�ʼ��ʼ������Ϣ������ʼ��ʼ��
void IWindowBaseImpl::PG_InitWindowBase(HWND hWnd, char *pszSkinPath, char *pszWndName)
{
	if (m_hWnd != NULL || hWnd == NULL || pszSkinPath == NULL || pszWndName == NULL)
		return;

	m_hWnd = hWnd;
	m_strSkinPath = pszSkinPath;
	m_strWindowObjectName = pszWndName;
	// ���ͳ�ʼ����Ϣ
	::PostMessage(hWnd, UM_INIT_WINDOW_BASE, NULL, NULL);
}

// ȡ�ô��ھ��
HWND IWindowBaseImpl::GetSafeHandle()
{
	return m_hWnd;
}

// �õ�������Ļ����
RECT IWindowBaseImpl::GetWindowRect()
{
	RECT RetRect;
	INIT_RECT(RetRect);

	if (IS_SAFE_HANDLE(m_hWnd))
		::GetWindowRect(m_hWnd, &RetRect);

	return RetRect;
}

// �õ��ͻ�������
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

// �������Ƶ���Ļ����
void IWindowBaseImpl::CenterWindow()
{
	RECT WndRect = GetClientRect();
	int cx = RECT_WIDTH(WndRect);
	int cy = RECT_HEIGHT(WndRect);

	if (IS_SAFE_HANDLE(m_hWnd) && cx > 0 && cy > 0)
	{
		// ����Ĭ�ϴ�С
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

// �����ڵ���Ϣ��������bPassOn����Ϊtrue�ǣ���Ϣ��������ݴ���falseʱ��������ϣ������´�
LRESULT IWindowBaseImpl::WindowProc(UINT nMsgId, WPARAM wParam, LPARAM lParam, bool &bPassOn)
{
	// bPassOn����Ϊtrue�ǣ���Ϣ��������ݴ���falseʱ��������ϣ������´�
	bPassOn = true;
	if (!::IsWindow(m_hWnd))
		return 0;

	switch (nMsgId)
	{
		// ��Ҫ�ⲿ�Ի�����ܵ���Ϣ��ʹ��Ƥ����ʼ��������ȷ����
	case UM_INIT_WINDOW_SUCCESS:
		break;

		// ��Ҫ�ⲿ�Ի�����ܵ���Ϣ��ʹ��Ƥ����ʼ�������쳣
	case UM_INIT_WINDOW_ERROR:
		break;

		// ��ʼ������
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
///// ��Ϣ���� /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IWindowBaseImpl::OnPaint(HDC hWndDc)
{
	if (!IS_SAFE_HANDLE(hWndDc) && !IsInit())
		return;

	RECT WndRect = this->GetWindowRect();
	m_WndMemDc.Create(RECT_WIDTH(WndRect), RECT_HEIGHT(WndRect), 0, false, true);
	if (m_WndMemDc.GetBits() == NULL)
		return;

	// ѭ������ÿ���ؼ��Ļ���
	DrawControl();

	// ���Ƶ�������
	if (PP_GetLayeredWindow())
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
		if (pCtrl != NULL && pCtrl->IsVisible())
		{
			if (pCtrl->GetReceiveMouseMessage())
			{
				RECT CtrlRct = pCtrl->GetCtrlInWindowRect();
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
			// ��������ڿؼ��ڲ����������϶�
			if (m_pLButtonDownCtrl->GetDragInControl())
			{
				m_pLButtonDownCtrl->OnMouseDragInCtrl(pt);
				return;
			}
		}

		// ��갴���ǣ���Ҫ����һ���ؼ���������ƶ�����
		if (m_pMouseHoverCtrl != NULL)
		{
			RECT CtrlRct = m_pMouseHoverCtrl->GetCtrlInWindowRect();
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
		// ȡ�õ�ǰMouseMove�Ŀؼ�
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

		// �ɷ������Ϣ���ؼ�
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

	// ȡ�õ�ǰ��갴�µĿؼ�
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

	// ȡ�õ�ǰ��갴�µĿؼ�
	IControlBase *pControl = NULL;
	CheckMouseInControl(&m_ChildCtrlsVec, pt, &pControl);
	if (pControl == NULL)
		return;

	pControl->OnRButtonDown(pt);
	SetFocusCtrl(pControl);
}

// ���õ�ǰ�õ�����Ŀؼ����������ΪNULL��˵����ǰû�пؼ��õ����㣬���пؼ���ʧȥ����
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

	// ȡ�õ�ǰ��갴�µĿؼ�
	IControlBase *pControl = NULL;
	CheckMouseInControl(&m_ChildCtrlsVec, pt, &pControl);
	if (pControl == NULL)
	{
		SetFocusCtrl(NULL);

		// �Ƿ����
		if (PP_IsFullScreen())
			return;

		// �Ƿ�֧��������ƶ�����
		if (PP_GetDragWindow())
			::PostMessage(m_hWnd, WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(pt.x, pt.y));

		return;
	}

	::SetCapture(m_hWnd);
	m_bIsLButtonDown = true;

	// �ɷ������Ϣ���ؼ�
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
				// û�и��ؼ���˵��ֱ�Ӹ����ڶԻ�����
				ParentRctInWnd.right = NewSize.cx;
				ParentRctInWnd.bottom = NewSize.cy;
			}
			else
			{
				ParentRctInWnd = pParentCtrl->GetCtrlInWindowRect();
			}

			// ���㵱ǰ�ؼ���λ��
			SetControlWindowPostion(pCtrl, ParentRctInWnd);

			// �����ӿؼ���λ��
			SetControlPostion(pCtrl->GetChildCtrlsVec(), NewSize);
		}
	}
}

// ���ݿؼ�������Ϣ�õ�����ڴ��ڵ�λ��
void IWindowBaseImpl::SetControlWindowPostion(IControlBase* pCtrl, RECT ParentRctInWnd)
{
	if (pCtrl == NULL)
		return;

	RECT RctInWnd;
	INIT_RECT(RctInWnd);
	CONTROL_LAYOUT_INFO CtrlLayout = pCtrl->GetLayout();
	if (CtrlLayout.clType == CL_G_LEFT_TOP)
	{
		// �̶���С�����ϽǶ�λ
		RctInWnd.left = ParentRctInWnd.left + CtrlLayout.nLeftSpace;
		RctInWnd.right = RctInWnd.left + CtrlLayout.nWidth;
		RctInWnd.top = ParentRctInWnd.top + CtrlLayout.nTopSpace;
		RctInWnd.bottom = RctInWnd.top + CtrlLayout.nHeight;
	}
	else if (CtrlLayout.clType == CL_G_LEFT_BOTTOM)
	{
		// �̶���С�����½Ƕ�λ
		RctInWnd.left = ParentRctInWnd.left + CtrlLayout.nLeftSpace;
		RctInWnd.right = RctInWnd.left + CtrlLayout.nWidth;
		RctInWnd.bottom = ParentRctInWnd.bottom - CtrlLayout.nBottomSpace;
		RctInWnd.top = RctInWnd.bottom - CtrlLayout.nHeight;
	}
	else if (CtrlLayout.clType == CL_G_RIGHT_TOP)
	{
		// �̶���С�����ϽǶ�λ
		RctInWnd.right = ParentRctInWnd.right - CtrlLayout.nRightSpace;
		RctInWnd.left = RctInWnd.right - CtrlLayout.nWidth;
		RctInWnd.top = ParentRctInWnd.top + CtrlLayout.nTopSpace;
		RctInWnd.bottom = RctInWnd.top + CtrlLayout.nHeight;
	}
	else if (CtrlLayout.clType == CL_G_RIGHT_BOTTOM)
	{
		// �̶���С�����½Ƕ�λ
		RctInWnd.right = ParentRctInWnd.right - CtrlLayout.nRightSpace;
		RctInWnd.left = RctInWnd.right - CtrlLayout.nWidth;
		RctInWnd.bottom = ParentRctInWnd.bottom - CtrlLayout.nBottomSpace;
		RctInWnd.top = RctInWnd.bottom - CtrlLayout.nHeight;
	}
	else if (CtrlLayout.clType == CL_L_LEFT)
	{
		// ����䶯��С���������
		RctInWnd.left = ParentRctInWnd.left + CtrlLayout.nLeftSpace;
		RctInWnd.right = RctInWnd.left + CtrlLayout.nWidth;
		RctInWnd.top = ParentRctInWnd.top + CtrlLayout.nTopSpace;
		RctInWnd.bottom = ParentRctInWnd.bottom - CtrlLayout.nBottomSpace;
	}
	else if (CtrlLayout.clType == CL_L_RIGHT)
	{
		// ����䶯��С�������Ҳ�
		RctInWnd.right = ParentRctInWnd.right - CtrlLayout.nRightSpace;
		RctInWnd.left = RctInWnd.right - CtrlLayout.nWidth;
		RctInWnd.top = ParentRctInWnd.top + CtrlLayout.nTopSpace;
		RctInWnd.bottom = ParentRctInWnd.bottom - CtrlLayout.nBottomSpace;
	}
	else if (CtrlLayout.clType == CL_L_TOP)
	{
		// ����䶯��С�������Ϸ�
		RctInWnd.left = ParentRctInWnd.left + CtrlLayout.nLeftSpace;
		RctInWnd.right = ParentRctInWnd.right - CtrlLayout.nRightSpace;
		RctInWnd.top = ParentRctInWnd.top + CtrlLayout.nTopSpace;
		RctInWnd.bottom = RctInWnd.top + CtrlLayout.nHeight;
	}
	else if (CtrlLayout.clType == CL_L_BOTTOM)
	{
		// ����䶯��С�������·�
		RctInWnd.left = ParentRctInWnd.left + CtrlLayout.nLeftSpace;
		RctInWnd.right = ParentRctInWnd.right - CtrlLayout.nRightSpace;
		RctInWnd.bottom = ParentRctInWnd.bottom - CtrlLayout.nBottomSpace;
		RctInWnd.top = RctInWnd.bottom - CtrlLayout.nHeight;
	}
	else if (CtrlLayout.clType == CL_L_ALL)
	{
		// ����䶯��С������ȫ��
		RctInWnd = ParentRctInWnd;
	}
	else if (CtrlLayout.clType == CL_L_MIDDLE)
	{
		// ����䶯��С������
		RctInWnd.left = ParentRctInWnd.left + CtrlLayout.nLeftSpace;
		RctInWnd.right = ParentRctInWnd.right - CtrlLayout.nRightSpace;
		RctInWnd.top = ParentRctInWnd.top + CtrlLayout.nTopSpace;
		RctInWnd.bottom = ParentRctInWnd.bottom - CtrlLayout.nBottomSpace;
	}

	pCtrl->SetCtrlInWindowRect(RctInWnd);
}

// �������໯���ڡ��ͷ���Դ
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

// �����δ����һ���ؼ�
void IWindowBaseImpl::AppendChildContrl(IControlBase *pCtrl)
{
	if (pCtrl != NULL)
		m_ChildCtrlsVec.push_back(pCtrl);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// ���ܺ��� /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ѭ������ÿ���ؼ��Ļ���
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

void IWindowBaseImpl::BD_InitWindowBase(IPropertyWindow *pWindowProp, bool bSetDftProp)
{
	if (pWindowProp == NULL)
		return;

	// ��Builder�л����õı߿�ɫ��
	BD_NewFrameImage();

	PP_SetWindowPropetry(pWindowProp, bSetDftProp);
	this->SetObjectId(pWindowProp->GetObjectId());
	if (m_pPropBase_Name == NULL || m_pPropBase_Name->GetString() == NULL || strlen(m_pPropBase_Name->GetString()) <= 0)
	{
		if (m_pPropBase_Name != NULL)
			m_pPropBase_Name->SetString("���½��������ơ�");
		this->SetObjectName("���½��������ơ�");
	}
	else
	{
		this->SetObjectName(m_pPropBase_Name->GetString());
	}
}

// ��Builder�л����õı߿�ɫ��
void IWindowBaseImpl::BD_NewFrameImage()
{
	if (m_pSkinPropMgr == NULL)
		return;

	m_BuilderWndFrameImage.SetUiKernel(IUiFeatureKernelImpl::GetInstance());
	m_BuilderCtrlFrameImage.SetUiKernel(IUiFeatureKernelImpl::GetInstance());
	m_BuilderWndFrameImageBase.SetUiKernel(IUiFeatureKernelImpl::GetInstance());
	m_BuilderCtrlFrameImageBase.SetUiKernel(IUiFeatureKernelImpl::GetInstance());

	// ��Builder�л����õı߿�ɫ��
	m_BuilderWndFrameImage.SetRelevancyProp(&m_BuilderWndFrameImageBase);
	m_BuilderCtrlFrameImage.SetRelevancyProp(&m_BuilderCtrlFrameImageBase);

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

	ImgBase.bIsZipFile = false;
	ImgBase.strFileName = strImgPath;
	ImgBase.RectInImage.left = ImgBase.RectInImage.top = 0;
	ImgBase.RectInImage.right = ImgBase.RectInImage.bottom = FANGKUAI_SIZE;

	ImgBase.jggInfo.bMiddleStretch = true;
	ImgBase.jggInfo.bBottomStretch = false;
	ImgBase.jggInfo.bLeftStretch = false;
	ImgBase.jggInfo.bRightStretch = false;
	ImgBase.jggInfo.bTopStretch = false;
	ImgBase.jggInfo.nBottomSpace = ImgBase.jggInfo.nLeftSpace = ImgBase.jggInfo.nRightSpace = ImgBase.jggInfo.nTopSpace = 0;

	pImgBase->SetImageProp(&ImgBase);
}

bool IWindowBaseImpl::IsInit()
{
	return (m_pXmlPropWindow != NULL && m_pSkinPropMgr != NULL);
}

void IWindowBaseImpl::BD_DrawWindowView(CDrawingBoard &ViewMemDc)
{
	if (ViewMemDc.GetSafeHdc() == NULL || m_pUiEngine == NULL || m_pPropSize_Width == NULL || m_pPropSize_Height == NULL)
		return;

	RECT WndRct;
	INIT_RECT(WndRct);
	WndRct.right = m_pPropSize_Width->GetValue();
	WndRct.bottom = m_pPropSize_Height->GetValue();
	
	m_BD_FangKuai8.EntityRct.left = (ViewMemDc.GetDcSize().cx - RECT_WIDTH(WndRct)) / 2;
	m_BD_FangKuai8.EntityRct.right = m_BD_FangKuai8.EntityRct.left + RECT_WIDTH(WndRct);
	m_BD_FangKuai8.EntityRct.top = (ViewMemDc.GetDcSize().cy - RECT_HEIGHT(WndRct)) / 2;
	m_BD_FangKuai8.EntityRct.bottom = m_BD_FangKuai8.EntityRct.top + RECT_HEIGHT(WndRct);

	// �����ڴ�dc
	m_WndMemDc.Create(RECT_WIDTH(WndRct), RECT_HEIGHT(WndRct), 0, false, true);
	if (m_WndMemDc.GetBits() == NULL)
		return;

	// ѭ������ÿ���ؼ��Ļ���
	DrawControl();

	// ���Ƶ���DC��
	int nWidth = RECT_WIDTH(WndRct);
	int nHeight = RECT_HEIGHT(WndRct);
	m_pUiEngine->AlphaBlend(ViewMemDc, m_BD_FangKuai8.EntityRct.left, m_BD_FangKuai8.EntityRct.top, nWidth, nHeight,
		m_WndMemDc, 0, 0, nWidth, nHeight);

	// ���ƴ��ڵ�ѡ��״̬
	BD_DrawSelectRect(ViewMemDc, m_BD_FangKuai8.EntityRct, true);

	// ���ƽ���ؼ���ѡ��״̬
	if (m_pFocusCtrl != NULL)
	{
		RECT CtrlRct = m_pFocusCtrl->GetCtrlInWindowRect();
		nWidth = RECT_WIDTH(CtrlRct);
		nHeight = RECT_HEIGHT(CtrlRct);
		CtrlRct.left += m_BD_FangKuai8.EntityRct.left;
		CtrlRct.top += m_BD_FangKuai8.EntityRct.top;
		CtrlRct.right = CtrlRct.left + nWidth;
		CtrlRct.bottom = CtrlRct.top + nHeight;

		BD_DrawSelectRect(ViewMemDc, CtrlRct, false);
	}
}

// ���ƴ��ںͱ�ѡ�еĿؼ��ı߿��8������
void IWindowBaseImpl::BD_DrawSelectRect(CDrawingBoard &MemDc, RECT DrawRct, bool bIsWndFrame)
{
	IPropertyImage *pPropImg = &m_BuilderCtrlFrameImage;
	if (bIsWndFrame)
		pPropImg = &m_BuilderWndFrameImage;

	m_BD_FangKuai8.LeftTop.left = DrawRct.left - FANGKUAI_SIZE;
	m_BD_FangKuai8.LeftTop.top = DrawRct.top - FANGKUAI_SIZE;
	m_BD_FangKuai8.LeftTop.right = m_BD_FangKuai8.LeftTop.left + FANGKUAI_SIZE;
	m_BD_FangKuai8.LeftTop.bottom = m_BD_FangKuai8.LeftTop.top + FANGKUAI_SIZE;
	pPropImg->DrawImage(MemDc, m_BD_FangKuai8.LeftTop);

	m_BD_FangKuai8.LeftMid.left = DrawRct.left - FANGKUAI_SIZE;
	m_BD_FangKuai8.LeftMid.top = DrawRct.top + (RECT_HEIGHT(DrawRct) / 2) - (FANGKUAI_SIZE / 2);
	m_BD_FangKuai8.LeftMid.right = m_BD_FangKuai8.LeftMid.left + FANGKUAI_SIZE;
	m_BD_FangKuai8.LeftMid.bottom = m_BD_FangKuai8.LeftMid.top + FANGKUAI_SIZE;
	pPropImg->DrawImage(MemDc, m_BD_FangKuai8.LeftMid);

	m_BD_FangKuai8.LeftBottom.left = DrawRct.left - FANGKUAI_SIZE;
	m_BD_FangKuai8.LeftBottom.top = DrawRct.bottom;
	m_BD_FangKuai8.LeftBottom.right = m_BD_FangKuai8.LeftBottom.left + FANGKUAI_SIZE;
	m_BD_FangKuai8.LeftBottom.bottom = m_BD_FangKuai8.LeftBottom.top + FANGKUAI_SIZE;
	pPropImg->DrawImage(MemDc, m_BD_FangKuai8.LeftBottom);

	m_BD_FangKuai8.MidTop.left = DrawRct.left + (RECT_WIDTH(DrawRct) / 2) - (FANGKUAI_SIZE / 2);
	m_BD_FangKuai8.MidTop.top = DrawRct.top - FANGKUAI_SIZE;
	m_BD_FangKuai8.MidTop.right = m_BD_FangKuai8.MidTop.left + FANGKUAI_SIZE;
	m_BD_FangKuai8.MidTop.bottom = m_BD_FangKuai8.MidTop.top + FANGKUAI_SIZE;
	pPropImg->DrawImage(MemDc, m_BD_FangKuai8.MidTop);

	m_BD_FangKuai8.MidBottom.left = DrawRct.left + (RECT_WIDTH(DrawRct) / 2) - (FANGKUAI_SIZE / 2);
	m_BD_FangKuai8.MidBottom.top = DrawRct.bottom;
	m_BD_FangKuai8.MidBottom.right = m_BD_FangKuai8.MidBottom.left + FANGKUAI_SIZE;
	m_BD_FangKuai8.MidBottom.bottom = m_BD_FangKuai8.MidBottom.top + FANGKUAI_SIZE;
	pPropImg->DrawImage(MemDc, m_BD_FangKuai8.MidBottom);

	m_BD_FangKuai8.RightTop.left = DrawRct.right;
	m_BD_FangKuai8.RightTop.top = DrawRct.top - FANGKUAI_SIZE;
	m_BD_FangKuai8.RightTop.right = m_BD_FangKuai8.RightTop.left + FANGKUAI_SIZE;
	m_BD_FangKuai8.RightTop.bottom = m_BD_FangKuai8.RightTop.top + FANGKUAI_SIZE;
	pPropImg->DrawImage(MemDc, m_BD_FangKuai8.RightTop);

	m_BD_FangKuai8.RightMid.left = DrawRct.right;
	m_BD_FangKuai8.RightMid.top = DrawRct.top + (RECT_HEIGHT(DrawRct) / 2) - (FANGKUAI_SIZE / 2);
	m_BD_FangKuai8.RightMid.right = m_BD_FangKuai8.RightMid.left + FANGKUAI_SIZE;
	m_BD_FangKuai8.RightMid.bottom = m_BD_FangKuai8.RightMid.top + FANGKUAI_SIZE;
	pPropImg->DrawImage(MemDc, m_BD_FangKuai8.RightMid);

	m_BD_FangKuai8.RightBottom.left = DrawRct.right;
	m_BD_FangKuai8.RightBottom.top = DrawRct.bottom;
	m_BD_FangKuai8.RightBottom.right = m_BD_FangKuai8.RightBottom.left + FANGKUAI_SIZE;
	m_BD_FangKuai8.RightBottom.bottom = m_BD_FangKuai8.RightBottom.top + FANGKUAI_SIZE;
	pPropImg->DrawImage(MemDc, m_BD_FangKuai8.RightBottom);
}

// ȡ�ô������������ԵĴ��ڴ�С
SIZE IWindowBaseImpl::PP_GetWindowPropSize()
{
	SIZE WndSize;
	WndSize.cx = m_pPropSize_Width->GetValue();
	WndSize.cy = m_pPropSize_Height->GetValue();
	return WndSize;
}

// �õ���Builder����ʾ������8�������λ��
FANGKUAI_8* IWindowBaseImpl::BD_GetFangKuai8Rect()
{
	return &m_BD_FangKuai8;
}
