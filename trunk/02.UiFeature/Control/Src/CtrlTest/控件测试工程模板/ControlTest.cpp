// UiFeatureRun.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32TestWindow.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	DWORD dwMainThreadId = ::GetCurrentThreadId();

	CWin32TestWindow RunWindow;
	if (!RunWindow.ShowWin32TestWindow(dwMainThreadId))
	{
		MessageBox(NULL, _T("´´½¨²âÊÔ´°¿Ú´íÎó£¡"), _T("Ô¤ÀÀ´°¿Ú"), MB_OK | MB_ICONERROR);
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
