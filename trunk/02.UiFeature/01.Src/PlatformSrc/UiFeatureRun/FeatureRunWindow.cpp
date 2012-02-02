#include "StdAfx.h"
#include "FeatureRunWindow.h"
#include "..\..\Inc\ICommonFun.h"
#include "..\..\Inc\UiFeatureDefs.h"

CFeatureRunWindow::CFeatureRunWindow()
{
	m_dwMainThreadId = 0;
}

CFeatureRunWindow::~CFeatureRunWindow()
{
}

bool CFeatureRunWindow::ShowFeatureRunWindow(char* pCmdLine, DWORD dwMainThreadId)
{
	USES_CONVERSION;
	if (pCmdLine == NULL || strlen(pCmdLine) <= 0)
		return false;
	m_dwMainThreadId = dwMainThreadId;

//	MessageBox(NULL, A2W(pCmdLine), _T("Ô¤ÀÀ´°¿Ú"), MB_OK | MB_ICONERROR);

	string strKernelDllPath = PathHelper(NAME_KERNEL_DLL);

	CString strCmd(A2W(pCmdLine));
	CString strFirst = strCmd.Mid(1, strCmd.GetLength() - 1);
	strCmd = strFirst;
	strFirst = strCmd.Left(strCmd.Find('\"'));
	CString strSecond = strCmd.Mid(strFirst.GetLength() + 3, strCmd.GetLength() - strFirst.GetLength() - 3 - 1);

	CRect WndRct(0, 0, 0, 0);
	return CreateFeatureWindow((char*)strKernelDllPath.c_str(), W2A(strFirst), W2A(strSecond), NULL, WndRct, SW_SHOW, NULL);
}

void CFeatureRunWindow::OnKeyDown(int nVirtKey, int nFlag)
{
	if (nVirtKey == VK_ESCAPE)
	{
		this->CloseSelf();
		::PostThreadMessage(m_dwMainThreadId, WM_QUIT, 0, 0);
	}
}