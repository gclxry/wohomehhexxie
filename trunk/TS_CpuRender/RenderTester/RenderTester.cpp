
#include "stdafx.h"
#include "RenderTester.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������
HWND g_hWnd = NULL;

//��ʾ����λͼ
unsigned char *m_pBmpData = NULL;
//��ʾ����λͼ���
long m_BmpWidth = 0, m_BmpHeight = 0;

// �˴���ģ���а����ĺ�����ǰ������:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	ULONG_PTR gdiplusToken = NULL;
	//��ʼ��gdiplus�Ļ���
	GdiplusStartupInput gdiplusStartupInput;
	// ��ʼ��GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: �ڴ˷��ô��롣

	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TESTGDI, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TESTGDI));

	// ����Ϣѭ��:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GdiplusShutdown(gdiplusToken);

	if(m_pBmpData)
		delete [] m_pBmpData;

	return (int) msg.wParam;
}



//
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
//  ע��:
//
//    ����ϣ��
//    �˴�������ӵ� Windows 95 �еġ�RegisterClassEx��
//    ����֮ǰ�� Win32 ϵͳ����ʱ������Ҫ�˺��������÷������ô˺���ʮ����Ҫ��
//    ����Ӧ�ó���Ϳ��Ի�ù�����
//    ����ʽ��ȷ�ġ�Сͼ�ꡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TESTGDI));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_TESTGDI);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	g_hWnd = hWnd;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Draw(hWnd, hdc);
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_CREATE:
		OnCreate();
		break;

	case WM_TIMER:
		OnTimer(wParam, lParam);
		break;

	case WM_SIZE:
		OnSize(wParam, lParam);
		break;

	case WM_ERASEBKGND:
		return 1;

	default:
		break; 
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void OnTimer(WPARAM wParam, LPARAM lParam)
{
	int wTimerID = (int)wParam;
	if (wTimerID == 0)
	{
		//::RedrawWindow(g_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
		::InvalidateRect(g_hWnd, NULL, true);
	}
}

void OnSize(WPARAM wParam, LPARAM lParam)
{
	int cx = LOWORD(lParam); 
	int cy = HIWORD(lParam);

	SetBmpData(cx,cy);
	CAKPicDraw::GetInst()->SelectPic(m_pBmpData,m_BmpWidth,m_BmpHeight);

	CAK3DRender::GetInst()->SelectPicDraw(CAKPicDraw::GetInst());
}

void OnCreate()
{
	USES_CONVERSION;

	//������ͼ
	unsigned char *pData;
	long Width,Height;
	struct AK_2D_UI_PIC *pUIPic;

	CString strPath = CUiMethod::GetAppPath() + _T("ɽˮ��.jpg");
	
	AKLoadPic(W2A(strPath.LockBuffer()),&pData,&Width,&Height);
	strPath.UnlockBuffer();

	pUIPic=CAK2DUI::GetSingle().CreateUIPic(1,Width,Height);
	if(pUIPic)
	{
		memcpy(pUIPic->pData, pData, Width*Height*4);

		// ����alphaֵ
		unsigned char *pDataA = NULL;
		for(int i=0;i<(Width*Height);++i)
		{
			pDataA=&pUIPic->pData[i*4];
			pDataA[3]=255;
		}
	}
	else
	{
		::PostQuitMessage(0);
		return;
	}
	delete [] pData;

	::MoveWindow(g_hWnd, 0, 0, 800, 600, TRUE);
	::SetTimer(g_hWnd, 0, 0, NULL);
}

void Draw(HWND hWnd, HDC hdc)
{
	CRect WndRect(0, 0, 0, 0);
	::GetClientRect(hWnd, WndRect);
	HDC hMemoryDC = ::CreateCompatibleDC(hdc);
	if (hMemoryDC != NULL)
	{
		HBITMAP hMemoryBitmap = ::CreateCompatibleBitmap(hdc, WndRect.Width(), WndRect.Height());
		if (hMemoryBitmap != NULL)
		{
			::SelectObject(hMemoryDC, hMemoryBitmap);
			DrawGdiPlus(hWnd, hMemoryDC, hMemoryBitmap);
			::BitBlt(hdc, 0, 0, WndRect.Width(), WndRect.Height(), hMemoryDC, 0, 0, SRCCOPY);
			::DeleteObject(hMemoryBitmap);
		}
		::DeleteDC(hMemoryDC);
	}
}

void DrawGdiPlus(HWND hWnd, HDC hMemoryDC, HBITMAP hMemoryBitmap)
{
/*	CRect WndRect(0, 0, 0, 0);
	::GetClientRect(hWnd, WndRect);

	Graphics Grap(hMemoryDC);

	// ����ɫ��͸���ȣ�200
	SolidBrush FillBrush(Color(200, 255, 0, 255));
	Grap.FillRectangle(&FillBrush, 0, 0, WndRect.Width(), WndRect.Height());*/

	CRect rc;
	::GetClientRect(g_hWnd, &rc);

	//����
	CAKPicDraw::GetInst()->SelectPic(m_pBmpData, m_BmpWidth, m_BmpHeight);
	memset(m_pBmpData, 0, m_BmpWidth*m_BmpHeight*4);

	//������Ȼ���
	CAK3DRender::GetInst()->ResetZBuffer(-10000);

	//ѡ��ʹ�õ���ͼ
	AK_2D_UI_PIC *pUIPic=CAK2DUI::GetSingle().FindUIPic(1);
	CAKPicDraw::GetInst(AK_PIC_DRAW_MAX_COUNT-1)->SelectPic(pUIPic->pData,pUIPic->uWidth,pUIPic->uHeight);

	//���嶥���uv
	//	DEF_VERTEX(v1,200,100,0);
	//	DEF_VERTEX(v2,400,100,0);
	//	DEF_VERTEX(v3,600,500,0);
	//	DEF_VERTEX(v4,50,500,0);

	// v1 ���£�v2 ���£�v3 ���ϣ�v4 ����
	DEF_VERTEX(v1,200,100,0);
	DEF_VERTEX(v2,400,50,0);
	DEF_VERTEX(v3,400,500,0);
	DEF_VERTEX(v4,200,450,0);

	DEF_UV(uv1,0,0);
	DEF_UV(uv2,1023,0);
	DEF_UV(uv3,1023,767);
	DEF_UV(uv4,0,767);

	//��Ⱦ
	CAK3DRender::GetInst()->DrawRect2(&v1,&v2,&v3,&v4,uv1,uv2,uv3,uv4,true);

	//��λͼ��ʾ����
	DisplayBmpData(hMemoryDC,hMemoryBitmap,0,0,m_pBmpData,m_BmpHeight,m_BmpWidth);
}

void DisplayBmpData(HDC hMemoryDC, HBITMAP hMemoryBitmap, long x, long y, unsigned char *pBmp, long rows, long cols)
{
	//��ȡ��ǰDC��������ʾλ��(16/24/32)
	int BitCount=::GetDeviceCaps(hMemoryDC, BITSPIXEL);
	switch(BitCount)
	{
	case 16://16λɫ
		{
			long i,index1,index2;
			long total=rows*cols;
			unsigned short r,g,b;
			unsigned short *pValue;

			for(i=0,index1=0,index2=0;i<total;++i)
			{
				index1+=4;
				index2+=2;

				b=pBmp[index1];
				g=pBmp[index1+1];
				r=pBmp[index1+2];

				pValue=(unsigned short *)&pBmp[index2];

				*pValue=(r/8<<11)|(g/4<<5)|(b/8);
			}

			::SetBitmapBits(hMemoryBitmap, cols*rows*2*sizeof(unsigned char), pBmp);
			break;
		}

	case 24://24λɫ
		{
			long i,index1,index2;
			long total=rows*cols;

			for(i=0,index1=0,index2=0;i<total;++i)
			{
				index1+=4;
				index2+=3;

				memcpy(&pBmp[index2],&pBmp[index1],sizeof(unsigned char)*3);
			}

			::SetBitmapBits(hMemoryBitmap, cols*rows*3*sizeof(unsigned char),pBmp);
			break;
		}

	case 32://32λɫ
		{
			::SetBitmapBits(hMemoryBitmap, cols*rows*4*sizeof(unsigned char),pBmp);
			break;
		}

	default://����λɫ
		{
			::TextOut(hMemoryDC, (cols-7*16)/2, rows/2, _T("��ʾģʽ��֧��"), 7);
			break;
		}
	}
}

bool SetBmpData(long w,long h)
{
	if(m_pBmpData)delete[] m_pBmpData;

	m_BmpWidth=w;
	m_BmpHeight=h;

	long size=w*h*4*sizeof(unsigned char);

	m_pBmpData = new unsigned char[size];

	return (m_pBmpData != NULL);
}
