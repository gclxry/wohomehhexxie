
#include "SysUnit.h"

CString CSysUnit::GetAppPath()
{
	CString strPath = _T("");
	TCHAR szBuffer[FS_MAX_PATH];
	if (::GetModuleFileName(NULL, szBuffer, FS_MAX_PATH))
	{
		strPath = szBuffer;
		while (strPath.GetAt(strPath.GetLength() - 1) != '\\' && strPath.GetLength() > 0)
		{
			strPath.Delete(strPath.GetLength() - 1, 1);
		}
	}

	return strPath;
}

// ���ô����͸������
void CSysUnit::SetWindowToTransparence(HWND hWnd, bool bIsTrans)
{
	DWORD dwExStyle = GetWindowLong(hWnd, GWL_EXSTYLE);

	if (bIsTrans)
	{
		// ͸��
		if ((dwExStyle & WS_EX_LAYERED) != WS_EX_LAYERED)
			::SetWindowLong(hWnd, GWL_EXSTYLE, dwExStyle^WS_EX_LAYERED);
	}
	else
	{
		// ��͸��
		if ((dwExStyle & WS_EX_LAYERED) == WS_EX_LAYERED)
		{
			dwExStyle &= (~WS_EX_LAYERED);
			::SetWindowLong(hWnd, GWL_EXSTYLE, dwExStyle);
		}
	}
}
