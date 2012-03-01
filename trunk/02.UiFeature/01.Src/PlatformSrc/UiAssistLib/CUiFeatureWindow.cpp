
#include "stdafx.h"
#include <assert.h>
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\CUiFeatureWindow.h"
#include "..\..\Inc\UiFeatureKernel.h"

CUiFeatureWindow::CUiFeatureWindow()
{
	m_hWnd = NULL;
	m_pWindowBase = NULL;
	m_strWndText = "Welcome UiFeature";
	m_hParentWnd = NULL;
	m_lParam = NULL;

	INIT_RECT(m_rctCreate);
	m_nCreateShow = SW_SHOW;
	m_hCreateWaitEvent = NULL;
	m_hUiThread = NULL;
	m_dwUiThreadId = 0;

	m_hKernelDll = NULL;
	m_pUiFeatureKernel = NULL;
	m_strKernelDllPath = "";
	m_strSkinPath = "";
	m_strSkinWndName = "";
}

CUiFeatureWindow::~CUiFeatureWindow()
{
	SAFE_FREE_LIBRARY(m_hKernelDll);
	CloseWindow();
	SAFE_CLOSE_HANDLE(m_hUiThread);
	m_dwUiThreadId = 0;
}

bool CUiFeatureWindow::CreateWindowWithNewThread(HWND hParent, RECT WndRect, char *pszWndText, int nShow, LPARAM lParam)
{
	return false;
}

// 控件发送消息接口
LRESULT CUiFeatureWindow::OnCtrlMessage(IControlBase* pCtrl, int nMsgId, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

IWindowBase* CUiFeatureWindow::GetUiFeatureWindow()
{
	return m_pWindowBase;
}

bool CUiFeatureWindow::InitInstance()
{
	m_hWnd = ::CreateWindowExA(0, FEATURE_CLASS_NAME, m_strWndText.c_str(), WS_OVERLAPPED | WS_THICKFRAME,
		m_rctCreate.left, m_rctCreate.top, RECT_WIDTH(m_rctCreate), RECT_HEIGHT(m_rctCreate), m_hParentWnd, NULL, ::GetModuleHandle(NULL), this);

	// 设置创建对话框参数
	SetCreateWindowParam(m_lParam);

	// 对话框初始化
	if (IS_SAFE_HANDLE(m_hWnd))
	{
		IControlMessage *pCtrlMsg = dynamic_cast<IControlMessage*>(this);
		if (pCtrlMsg == NULL)
		{
			assert(false);
			return false;
		}

		m_pWindowBase = m_pUiFeatureKernel->PG_InitFeatureSkin(m_hWnd, (char*)m_strSkinPath.c_str(), (char*)m_strSkinWndName.c_str());
		if (m_pWindowBase == NULL)
		{
			assert(false);
			return false;
		}

		// 设置控件回调
		m_pWindowBase->SetCtrlMsgCallBack(pCtrlMsg);
		if (IS_RECT_EMPTY(m_rctCreate))
		{
			SIZE WndSize = m_pWindowBase->PP_GetWindowPropSize();
			INIT_RECT(m_rctCreate);
			m_rctCreate.right = WndSize.cx;
			m_rctCreate.bottom = WndSize.cy;
			this->MoveWindow(m_rctCreate);
			this->CenterWindow();
		}

		OnCreate();
		this->ShowWindow(SW_HIDE);
	}

	return IS_SAFE_HANDLE(m_hWnd);
}

LRESULT CUiFeatureWindow::WndProc(UINT nMsgId, WPARAM wParam, LPARAM lParam)
{
	switch (nMsgId)
	{
		// 初始化对话框错误
	case UM_INIT_WINDOW_ERROR:
		OnInitWindowEnd((int)wParam);
		break;

		// 初始化对话框成功
	case UM_INIT_WINDOW_SUCCESS:
		OnInitWindowEnd(0);
		break;

	default:
		break;
	}

	return CWin32Window::WndProc(nMsgId, wParam, lParam);
}

// 初始化对话框结束
void CUiFeatureWindow::OnInitWindowEnd(int nErrorCode)
{
	if (nErrorCode == 0)
	{
		// 成功
		this->ShowWindow(m_nCreateShow);
	}
	else
	{
		// 失败
		char szError[MAX_PATH];
		memset(szError, 0, MAX_PATH);
		sprintf_s(szError, MAX_PATH, "创建Feature窗口错误，错误码：%d", nErrorCode);
		MessageBoxA(NULL, szError, "内核窗口", MB_OK | MB_ICONERROR);
	}
}

// 创建一个窗口，参数：
// char* pszDllDir：UiFeatureKernel.dll的全路径
// char* pszSkinPath：*.ufd皮肤文件的全路径
// char *pszWndName：*.ufd皮肤文件中对话框的名字
// HWND hParent：父窗口
// RECT WndRect：窗口显示位置，坐标为屏幕位置
// int nShow：显示模式，如：SW_SHOW、SW_HIDE
// LPARAM lParam：创建窗口时传入的参数，可以通过 GetCreateWindowParam 函数取得
bool CUiFeatureWindow::CreateFeatureWindow(char* pszKernelDllPath, char* pszSkinPath, char *pszSkinWndName, HWND hParent, RECT WndRect, int nShow, LPARAM lParam)
{
	if (pszKernelDllPath == NULL || pszSkinPath == NULL || pszSkinWndName == NULL)
		return false;

	m_strKernelDllPath = pszKernelDllPath;
	m_strSkinPath = pszSkinPath;
	m_strSkinWndName = pszSkinWndName;

	HMODULE m_hKernelDll = ::LoadLibraryA(m_strKernelDllPath.c_str());
	if (m_hKernelDll == NULL)
		return false;

	GETKERNELWINDOWINTERFACE GetKernel = (GETKERNELWINDOWINTERFACE)::GetProcAddress(m_hKernelDll, "GetKernelWindowInterface");
	if (GetKernel == NULL)
	{
		SAFE_FREE_LIBRARY(m_hKernelDll);
		return false;
	}

	m_pUiFeatureKernel = GetKernel();
	if (m_pUiFeatureKernel == NULL)
	{
		SAFE_FREE_LIBRARY(m_hKernelDll);
		return false;
	}

	return CWin32Window::CreateWindowWithNewThread(hParent, WndRect, "Welcome UiFeature", nShow, lParam);
}
