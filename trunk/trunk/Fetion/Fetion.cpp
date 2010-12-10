
#include "stdafx.h"
#include "Fetion.h"
#include "LogonDlgBusiness.h"
#include "RgnDlg.h"
#include "MistDlg.h"


int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// 初始化
	CUiMethod::InitGdiPlus();

	// 业务开始

	// 登录窗口
//	CLogonDlgBusiness LogonDlg(hInstance, NULL, IDI_FETION);
//	LogonDlg.ShowWindow();

	// RGN测试
//	CRgnDlg *pRgnDlg = new CRgnDlg(hInstance, NULL, IDI_FETION);
//	pRgnDlg->ShowWindow();

	CMistDlg *pMistDlg = new CMistDlg(hInstance, NULL, IDI_FETION);;
	pMistDlg->ShowWindow();


	// 主消息循环:
	MSG msg;
	HACCEL hAccelTable;
	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FETION));
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
//	delete pRgnDlg;
	delete pMistDlg;

	// 释放资源
	CUiMethod::UnInitGdiPlus();

	// 退出
	return (int)msg.wParam;
}
