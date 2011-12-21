
#include "StdAfx.h"
#include "CommonFun.h"

string GetDllPath(char *pszDllName)
{
	string strPath = "";
	if (pszDllName != NULL)
	{
		char szPath[MAX_PATH + 1];
		memset(szPath, 0, MAX_PATH + 1);
		::GetModuleFileNameA(NULL, szPath, MAX_PATH);
		while (strlen(szPath) > 0 && szPath[strlen(szPath) - 1] != '\\')
			szPath[strlen(szPath) - 1] = '\0';

		strPath = szPath;
		strPath += pszDllName;
	}

	return strPath;
}
