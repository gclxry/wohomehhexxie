// UiFeatureRun.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "UiFeatureRun.h"
#include "FeatureRunWindow.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	USES_CONVERSION;
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	if (lpCmdLine == NULL || strlen(W2A(lpCmdLine)) <= 0)
	{
		MessageBox(NULL, _T("ÊäÈë²ÎÊý´íÎó£¡"), _T("Ô¤ÀÀ´°¿Ú"), MB_OK | MB_ICONERROR);
		return -1;
	}

	DWORD dwMainThreadId = ::GetCurrentThreadId();

	CFeatureRunWindow RunWindow;
	if (!RunWindow.ShowFeatureRunWindow(W2A(lpCmdLine), dwMainThreadId))
	{
		MessageBox(NULL, _T("´´½¨Ô¤ÀÀ´°¿Ú´íÎó£¡"), _T("Ô¤ÀÀ´°¿Ú"), MB_OK | MB_ICONERROR);
		return -1;
	}

	MSG msg;
	while (::GetMessage(&msg, NULL, 0, 0))
	{
		if (msg.message == WM_QUIT)
			RunWindow.WaitWindowThreadEnd();

		if (!::TranslateAccelerator(msg.hwnd, NULL, &msg))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}
	return 0;
}
