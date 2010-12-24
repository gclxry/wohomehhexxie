
#include "WebBrowser.h"
#include "exdisp.h"
#include "mshtmlc.h"

CWebBrowser::CWebBrowser()
{

}

CWebBrowser::~CWebBrowser()
{

}

bool CWebBrowser::LaunchIE(LPTSTR szResourceURL)
{
	::CoInitialize(NULL);

	IWebBrowser2 *pwb;
	HRESULT hres = CoCreateInstance(CLSID_InternetExplorer, NULL, CLSCTX_LOCAL_SERVER, IID_IWebBrowser2, (void **)&pwb);

	if (SUCCEEDED(hres)) 
	{
		int dx, dy;
		DWORD dwFlags;

		pwb->put_RegisterAsBrowser(VARIANT_TRUE);

		IServiceProvider *psp;
		if (SUCCEEDED(pwb->QueryInterface(IID_IServiceProvider, (void**) &psp))) 
		{
			IHTMLWindow2 *phw;
			if (SUCCEEDED(psp->QueryService(IID_IHTMLWindow2, IID_IHTMLWindow2, (void**)&phw))) 
			{
				VARIANT var;
				var.vt = VT_BOOL;
				var.boolVal = 666;
				phw->put_opener(var);
				phw->Release();
			} 
			psp->Release();
		}

		// turn off chrome
		pwb->put_MenuBar(FALSE);
		pwb->put_StatusBar(FALSE);
		pwb->put_ToolBar(FALSE);
		pwb->put_AddressBar(FALSE);
		pwb->put_Resizable(FALSE);

		int iWidth = 800;
		int iHeight = 600;

		pwb->ClientToWindow(&iWidth, &iHeight);

		if (iWidth > 0)
			pwb->put_Width(iWidth);

		if (iHeight > 0)
			pwb->put_Height(iHeight);

		if ((dx = ((GetSystemMetrics(SM_CXSCREEN) - iWidth) / 2)) > 0)     // center the on screen window 
			pwb->put_Left(dx);

		if ((dy = ((GetSystemMetrics(SM_CYSCREEN) - iHeight) / 2)) > 0)
			pwb->put_Top(dy);    

		pwb->put_Visible(TRUE);
		pwb->Navigate("www.baidu.com", NULL, NULL, NULL, NULL);

/*
		BSTR bstr = BSTRFROMANSI(szResourceURL);
		HRESULT hr = pwb->Navigate(bstr, PVAREMPTY, PVAREMPTY, PVAREMPTY, PVAREMPTY);

		SysFreeString(bstr);
*/		
		pwb->Release();

		return true;
	}
	return false;
}
