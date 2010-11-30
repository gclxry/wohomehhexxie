
#include "stdafx.h"
#include "AggTester.h"


#define MAX_LOADSTRING 100

HINSTANCE g_hInstance = NULL;
// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

// �˴���ģ���а����ĺ�����ǰ������:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: �ڴ˷��ô��롣
	CUiMethod::InitGdiPlus();

	g_hInstance = hInstance;

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
	CUiMethod::UnInitGdiPlus();

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
		OnTimer(hWnd, wParam, lParam);
		break;

	case WM_SIZE:
		OnSize(wParam, lParam);
		break;

	case WM_ERASEBKGND:
		return 1;

	default:
		break; 
	}

	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

void OnTimer(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	int wTimerID = (int)wParam;
	if (wTimerID == 0)
	{
	}
}

void OnSize(WPARAM wParam, LPARAM lParam)
{
	int cx = LOWORD(lParam); 
	int cy = HIWORD(lParam);
}

pixel_map SrcMapImg;
rendering_buffer SrcImgBuf;
pixel_map DstMapImg;
rendering_buffer DstImgBuf;
HANDLE g_hMem = NULL;

void OnCreate()
{
	USES_CONVERSION;

	Gdiplus::Bitmap GBmp(_T("spheres.bmp"));
	Color colorBackground;
	HBITMAP hbmReturn = NULL;
	GBmp.GetHBITMAP(colorBackground, &hbmReturn);

	g_hMem = CAggInterface::CreatePixelMap(hbmReturn, SrcMapImg, SrcImgBuf);
	CAggInterface::CreatePixelMap(DstMapImg, DstImgBuf, 380, 400);
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
			AggDraw(hWnd, hMemoryDC, hMemoryBitmap);
			::BitBlt(hdc, 0, 0, WndRect.Width(), WndRect.Height(), hMemoryDC, 0, 0, SRCCOPY);
			::DeleteObject(hMemoryBitmap);
		}
		::DeleteDC(hMemoryDC);
	}
}

void AggDraw(HWND hWnd, HDC hMemoryDC, HBITMAP hMemoryBitmap)
{
	if (g_hMem != NULL)
	{
		CAggDraw2DTo3D Agg;
		CPoint vP[4];
		int nCut = 50;
		vP[0] = CPoint(0, SrcImgBuf.height() - nCut);
		vP[1] = CPoint(SrcImgBuf.width(), SrcImgBuf.height());
		vP[2] = CPoint(SrcImgBuf.width(), 0);
		vP[3] = CPoint(0, nCut);

		Agg.Draw2DTo3D(DstImgBuf, SrcImgBuf, vP);

		DstMapImg.draw(hMemoryDC);
	}
}

/*
{
	// agg �̶�������
	// 1.����Դ (Vertex Source)
	// 2.����ת���ܵ� (Coordinate conversion pipeline)
	// 3.ˮƽɨ���߹�դ(Scanline Rasterizer)
	// 4.��Ⱦ��(Renderers)
	// 5.��Ⱦ����(Rendering Buffer)

	// agg ���Ͷ���
	typedef agg::pixfmt_bgra32 pixfmt;
	typedef agg::pixfmt_bgra32_pre pixfmt_pre;
	typedef agg::renderer_base<pixfmt_pre> renderer_base_pre;
	typedef agg::renderer_base<pixfmt> renderer_base;
	typedef pixfmt::color_type color_type;
	typedef agg::image_accessor_clone<pixfmt> img_accessor_type;
	typedef agg::span_interpolator_trans<agg::trans_perspective> interpolator_type;
	typedef agg::span_image_filter_rgba_2x2<img_accessor_type, interpolator_type> span_gen_type;
	// ɫ�β�ֵ����
	typedef agg::span_interpolator_trans<agg::trans_perspective> interpolator_type;
	// ɫ�δ�����
	typedef agg::span_image_filter_rgba_2x2<img_accessor_type, interpolator_type> span_gen_type;


	//----------------------------------------
	pixel_map OutPixImg;
	rendering_buffer OutBuf;

	CRect WndRect(0, 0, 0, 0);
	::GetClientRect(hWnd, &WndRect);
	OutPixImg.create(WndRect.Width(), WndRect.Height(), org_color32);
	OutBuf.attach(OutPixImg.buf(), OutPixImg.width(), OutPixImg.height(), OutPixImg.stride());

	// �����в���Ⱦ�������
	pixfmt            OutPixf(OutBuf);
	// ��ǿ���в���Ⱦ�������
	pixfmt_pre        OutPixfPre(OutBuf);
	// �����в���Ⱦ���������������
	renderer_base     OutBaseRender(OutPixf);
	// ��ǿ���в���Ⱦ��
	renderer_base_pre OutPreRender(OutPixfPre);

	// �������
	OutBaseRender.clear(agg::rgba(0.0, 1, 1, 1.0));

	//----------------------------------------
	agg::interactive_polygon Polygon4(4, 0.0);

	int nCut = 100;
	Polygon4.xn(0) = 0;
	Polygon4.yn(0) = WndRect.Height() - DstBuf.height() + nCut;
	Polygon4.xn(1) = DstBuf.width();
	Polygon4.yn(1) = WndRect.Height() - DstBuf.height();
	Polygon4.xn(2) = DstBuf.width();
	Polygon4.yn(2) = WndRect.Height();
	Polygon4.xn(3) = 0;
	Polygon4.yn(3) = WndRect.Height() - nCut;

	//-------------------------------------------------
	// ��ɨ�迹��ݹ�դ������
	agg::rasterizer_scanline_aa<> AaRasterizer;
	// ɫ������
	agg::scanline_u8  U8Scanline;
	AaRasterizer.add_path(Polygon4);
	AaRasterizer.clip_box(0, 0, OutBuf.width(), OutBuf.height());
	AaRasterizer.reset();
	AaRasterizer.move_to_d(Polygon4.xn(0), Polygon4.yn(0));
	AaRasterizer.line_to_d(Polygon4.xn(1), Polygon4.yn(1));
	AaRasterizer.line_to_d(Polygon4.xn(2), Polygon4.yn(2));
	AaRasterizer.line_to_d(Polygon4.xn(3), Polygon4.yn(3));


	//------------------------------------------------------------------------
	// �߶η�����
	agg::span_allocator<color_type> SaAlloc;
	// ˫���Բ�ֵ���˲���
	agg::image_filter_bilinear FilterKernel;
	// �˲���������
	agg::image_filter_lut FilterLut(FilterKernel, false);

	// ��ȾԴ
	pixfmt PixfSrcImg(DstBuf);
	// ͼƬ��������¡
	typedef agg::image_accessor_clone<pixfmt> img_accessor_type;
	// ��ȾԴ������
	img_accessor_type ImgAcc(PixfSrcImg);

	// Զ����Ⱦ���������ı��� -> ����
	agg::trans_perspective PerspectiveTranser(Polygon4.polygon(), 0.0, 0.0, DstBuf.width(), DstBuf.height());
	if(PerspectiveTranser.is_valid())
	{
		// Զ����Ⱦɫ�β�ֵ��������У������
		interpolator_type InterpolatorType(PerspectiveTranser);
		// ɫ�δ�����
		span_gen_type SaGen(ImgAcc, InterpolatorType, FilterLut);

		// ������
		// Rasterizer����դ������
		// Scanline��span����
		// BaseRenderer����Ⱦ��
		// SpanAllocator���߶η�����
		// SpanGenerator��ָ���㷨��ɫ�δ�����

		// �������Ⱦ����SaGenͨ��SaAlloc��Ⱦ��OutPreRender��
		agg::render_scanlines_aa(AaRasterizer, U8Scanline, OutPreRender, SaAlloc, SaGen);
	}

	OutPixImg.draw(hMemoryDC);
	OutPixImg.clear();
}
*/
