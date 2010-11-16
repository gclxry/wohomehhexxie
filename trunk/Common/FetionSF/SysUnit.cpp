
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
