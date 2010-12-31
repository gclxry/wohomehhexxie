
#include "stdafx.h"
#include "Fetion.h"
#include "LogonDlgBusiness.h"
#include "RgnDlg.h"
#include "MistDlg.h"
#include "GroundGlassDlg.h"
#include "SseDlg.h"
#include "IeDlg.h"
#include "RichEditDlg.h"


int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// ��ʼ��
	CUiMethod::InitGdiPlus();

	// ҵ��ʼ

	// ��¼����
//	CLogonDlgBusiness *pTestDlg = new CLogonDlgBusiness(hInstance, NULL, IDI_FETION);
//	pTestDlg->ShowWindow();

	// RGN����
//	CRgnDlg *pTestDlg = new CRgnDlg(hInstance, NULL, IDI_FETION);
//	pTestDlg->ShowWindow();

//	CMistDlg *pTestDlg = new CMistDlg(hInstance, NULL, IDI_FETION);;
//	pTestDlg->ShowWindow();

//	CGroundGlassDlg *pTestDlg = new CGroundGlassDlg(hInstance, NULL, IDI_FETION);;
//	pTestDlg->ShowWindow();

	CSseDlg *pTestDlg = new CSseDlg(hInstance, NULL, IDI_FETION);;
	pTestDlg->ShowWindow();

//	CIeDlg *pTestDlg = new CIeDlg(hInstance, NULL, IDI_FETION);;
//	pTestDlg->ShowWindow();

//	CRichEditDlg *pTestDlg = new CRichEditDlg(hInstance, NULL, IDI_FETION);;
//	pTestDlg->ShowWindow();

	// ����Ϣѭ��
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
	delete pTestDlg;

	// �ͷ���Դ
	CUiMethod::UnInitGdiPlus();

	// �˳�
	return (int)msg.wParam;
}
