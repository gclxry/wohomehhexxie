#pragma once
#include "..\..\Inc\CUiFeatureWindow.h"

class CFeatureRunWindow : public CUiFeatureWindow
{
public:
	CFeatureRunWindow();
	virtual ~CFeatureRunWindow();

	bool ShowFeatureRunWindow(char* pCmdLine, DWORD dwMainThreadId);

protected:
	virtual void OnKeyDown(int nVirtKey, int nFlag);

private:
	DWORD m_dwMainThreadId;
};
