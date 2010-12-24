

#pragma once
#include "Windows.h"

class CWebBrowser
{
public:
	CWebBrowser();
	virtual ~CWebBrowser();

	bool LaunchIE(LPTSTR szResourceURL);
};
