
#include "stdafx.h"
#include "Fetion.h"
#include "LogonDlgBusiness.h"
#include "RgnDlg.h"
#include "MistDlg.h"


int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// ��ʼ��
	CUiMethod::InitGdiPlus();

	// ҵ��ʼ

	// ��¼����
//	CLogonDlgBusiness LogonDlg(hInstance, NULL, IDI_FETION);
//	LogonDlg.ShowWindow();

	// RGN����
//	CRgnDlg *pRgnDlg = new CRgnDlg(hInstance, NULL, IDI_FETION);
//	pRgnDlg->ShowWindow();

	CMistDlg *pMistDlg = new CMistDlg(hInstance, NULL, IDI_FETION);;
	pMistDlg->ShowWindow();


	// ����Ϣѭ��:
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

	// �ͷ���Դ
	CUiMethod::UnInitGdiPlus();

	// �˳�
	return (int)msg.wParam;
}
