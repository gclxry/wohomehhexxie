

#pragma once
#include <Windows.h>
#include <atltypes.h>
#include <atlstr.h>
#include <atlwin.h>
#include "FetionSF.h"


class CWebBrowser
{
public:
	CWebBrowser();
	virtual ~CWebBrowser();

	bool LaunchIE(HWND hParent, CRect ShowRect, CString strUrl);
	void MoveWindow(CRect WndRect);

private:
	CRect m_WndRect;
	CAxWindow m_WinContainer;
};
