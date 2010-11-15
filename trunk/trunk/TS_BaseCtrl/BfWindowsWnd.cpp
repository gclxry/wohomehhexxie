
#include "BfWindowsWnd.h"


#pragma warning(disable:4312)
#pragma warning(disable:4244)

#define WND_PROP_NAME						_T("BfWndX")

CBfWindowsWnd::CBfWindowsWnd(HINSTANCE hInstance)
{
	m_hInstance = hInstance;
	if (m_hInstance == NULL)
		assert(!"HINSTANCE can't set to NULL!");

	m_hWindowsWnd = NULL;
	m_OldWndProc = NULL;
}

CBfWindowsWnd::~CBfWindowsWnd(void)
{
}

UINT CBfWindowsWnd::GetClassStyle() const
{
	return 0;
}

LRESULT CBfWindowsWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::CallWindowProc(m_OldWndProc, m_hWindowsWnd, uMsg, wParam, lParam);
}

void CBfWindowsWnd::OnFinalMessage(HWND hWnd)
{
}

LRESULT CALLBACK CBfWindowsWnd::__ControlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CBfWindowsWnd* pThis = NULL;
	if (uMsg == WM_NCCREATE)
	{
		LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
		pThis = static_cast<CBfWindowsWnd*>(lpcs->lpCreateParams);
		::SetProp(hWnd, WND_PROP_NAME, (HANDLE)pThis);
		pThis->m_hWindowsWnd = hWnd;
	} 
	else
	{
		pThis = reinterpret_cast<CBfWindowsWnd*>(::GetProp(hWnd, WND_PROP_NAME));
		if (uMsg == WM_NCDESTROY && pThis != NULL)
		{
			LRESULT lRes = ::CallWindowProc(pThis->m_OldWndProc, hWnd, uMsg, wParam, lParam);
			::SetProp(hWnd, WND_PROP_NAME, NULL);
			pThis->m_hWindowsWnd = NULL;
			pThis->OnFinalMessage(hWnd);
			return lRes;
		}
	}

	if (pThis != NULL)
		return pThis->HandleMessage(uMsg, wParam, lParam);
	else
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK CBfWindowsWnd::__WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CBfWindowsWnd* pThis = NULL;
	if (uMsg == WM_NCCREATE)
	{
		LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
		pThis = static_cast<CBfWindowsWnd*>(lpcs->lpCreateParams);
		pThis->m_hWindowsWnd = hWnd;
		::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LPARAM>(pThis));
	} 
	else
	{
		pThis = reinterpret_cast<CBfWindowsWnd*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
		if (uMsg == WM_NCDESTROY && pThis != NULL)
		{
			LRESULT lRes = ::CallWindowProc(pThis->m_OldWndProc, hWnd, uMsg, wParam, lParam);
			::SetWindowLongPtr(pThis->m_hWindowsWnd, GWLP_USERDATA, 0L);
			pThis->m_hWindowsWnd = NULL;
			pThis->OnFinalMessage(hWnd);
			return lRes;
		}
	}

	if (pThis != NULL)
		return pThis->HandleMessage(uMsg, wParam, lParam);
	else
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}

bool CBfWindowsWnd::RegisterSuperClass()
{
	WNDCLASSEX wc = {0};
	wc.cbSize = sizeof(WNDCLASSEX);

	if (!::GetClassInfoEx(NULL, GetSuperClassName(), &wc))
	{
		if (!::GetClassInfoEx(m_hInstance, GetSuperClassName(), &wc) )
		{
			assert(!"Unable to locate window class");
			return NULL;
		}
	}

	m_OldWndProc = wc.lpfnWndProc;
	wc.lpfnWndProc = CBfWindowsWnd::__ControlProc;
	wc.hInstance = m_hInstance;
	wc.lpszClassName = GetWindowClassName();
	ATOM ret = ::RegisterClassEx(&wc);
	assert((ret!=NULL) || (::GetLastError() == ERROR_CLASS_ALREADY_EXISTS));
	return ((ret != NULL) || (::GetLastError() == ERROR_CLASS_ALREADY_EXISTS));
}

bool CBfWindowsWnd::RegisterWindowClass()
{
	WNDCLASS wc = {0};
	wc.style = GetClassStyle();
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.lpfnWndProc = CBfWindowsWnd::__WndProc;
	wc.hInstance = m_hInstance;
	wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = GetWindowClassName();
	ATOM ret = ::RegisterClass(&wc);
	assert((ret!=NULL) || (::GetLastError() == ERROR_CLASS_ALREADY_EXISTS));
	return ((ret != NULL) || (::GetLastError() == ERROR_CLASS_ALREADY_EXISTS));
}

HWND CBfWindowsWnd::CreateWindowsWnd(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, int x, int y, int cx, int cy, HMENU hMenu)
{
	if (GetSuperClassName() != NULL && !RegisterSuperClass())
		return NULL;

	if (GetWindowClassName() != NULL && !RegisterWindowClass())
		return NULL;

	m_hWindowsWnd = ::CreateWindowEx(dwExStyle, GetWindowClassName(), pstrName, dwStyle, x, y, cx, cy, hwndParent, hMenu, m_hInstance, this);
	assert(m_hWindowsWnd != NULL);
	return m_hWindowsWnd;
}
