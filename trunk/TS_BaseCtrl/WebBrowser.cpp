
#include "WebBrowser.h"
#include "exdisp.h"
#include "mshtmlc.h"

#pragma comment(lib,"atl")
#pragma comment(lib,"User32.lib")

CComModule _Module;


CWebBrowser::CWebBrowser()
{
	::CoInitialize(NULL);

	m_WndRect.SetRectEmpty();
}

CWebBrowser::~CWebBrowser()
{

}

void CWebBrowser::MoveWindow(CRect WndRect)
{
	m_WndRect = WndRect;

	if (IS_SAVE_HANDLE(m_WinContainer.m_hWnd))
	{
		m_WinContainer.MoveWindow(&m_WndRect);
	}
}

bool CWebBrowser::LaunchIE(HWND hParent, CRect ShowRect, CString strUrl)
{
	IWebBrowser2* pWebBrowser;
	VARIANT varMyURL;
	LPOLESTR pszName = OLESTR("shell.Explorer.2");

	HWND hWnd = m_WinContainer.Create(hParent, ShowRect, _T(""), WS_CHILD | WS_VISIBLE);
	DWORD dwErr = ::GetLastError();
	m_WinContainer.CreateControl(pszName);
	m_WinContainer.QueryControl(__uuidof(IWebBrowser2), (void**)&pWebBrowser); 
	VariantInit(&varMyURL);
	varMyURL.vt = VT_BSTR; 
	varMyURL.bstrVal = ::SysAllocString(_T("http://www.baidu.com"));
	pWebBrowser-> Navigate2(&varMyURL,0,0,0,0);
	VariantClear(&varMyURL); 
	pWebBrowser-> Release(); 

	return true;
}

