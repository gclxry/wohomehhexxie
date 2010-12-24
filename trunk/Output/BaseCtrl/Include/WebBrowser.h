

#pragma once
#include "Windows.h"

class CBfWebBrowser
{
public:
	CBfWebBrowser();
	virtual ~CBfWebBrowser();

	bool LaunchIE(LPTSTR szResourceURL);
};
