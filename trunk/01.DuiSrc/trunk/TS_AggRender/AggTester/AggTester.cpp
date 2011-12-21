
#include "stdafx.h"
#include "AggTester.h"


#define MAX_LOADSTRING 100

HINSTANCE g_hInstance = NULL;
// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 此代码模块中包含的函数的前向声明:
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

	// TODO: 在此放置代码。
	CUiMethod::InitGdiPlus();

	g_hInstance = hInstance;

	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TESTGDI, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TESTGDI));

	// 主消息循环:
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
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
//  注释:
//
//    仅当希望
//    此代码与添加到 Windows 95 中的“RegisterClassEx”
//    函数之前的 Win32 系统兼容时，才需要此函数及其用法。调用此函数十分重要，
//    这样应用程序就可以获得关联的
//    “格式正确的”小图标。
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
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 将实例句柄存储在全局变量中

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
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
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
	// agg 固定处理步骤
	// 1.顶点源 (Vertex Source)
	// 2.坐标转换管道 (Coordinate conversion pipeline)
	// 3.水平扫描线光栅(Scanline Rasterizer)
	// 4.渲染器(Renderers)
	// 5.渲染缓存(Rendering Buffer)

	// agg 类型定义
	typedef agg::pixfmt_bgra32 pixfmt;
	typedef agg::pixfmt_bgra32_pre pixfmt_pre;
	typedef agg::renderer_base<pixfmt_pre> renderer_base_pre;
	typedef agg::renderer_base<pixfmt> renderer_base;
	typedef pixfmt::color_type color_type;
	typedef agg::image_accessor_clone<pixfmt> img_accessor_type;
	typedef agg::span_interpolator_trans<agg::trans_perspective> interpolator_type;
	typedef agg::span_image_filter_rgba_2x2<img_accessor_type, interpolator_type> span_gen_type;
	// 色段插值服务
	typedef agg::span_interpolator_trans<agg::trans_perspective> interpolator_type;
	// 色段创建器
	typedef agg::span_image_filter_rgba_2x2<img_accessor_type, interpolator_type> span_gen_type;


	//----------------------------------------
	pixel_map OutPixImg;
	rendering_buffer OutBuf;

	CRect WndRect(0, 0, 0, 0);
	::GetClientRect(hWnd, &WndRect);
	OutPixImg.create(WndRect.Width(), WndRect.Height(), org_color32);
	OutBuf.attach(OutPixImg.buf(), OutPixImg.width(), OutPixImg.height(), OutPixImg.stride());

	// 基本中层渲染结果缓存
	pixfmt            OutPixf(OutBuf);
	// 加强型中层渲染结果缓存
	pixfmt_pre        OutPixfPre(OutBuf);
	// 基本中层渲染器，用于清除背景
	renderer_base     OutBaseRender(OutPixf);
	// 加强型中层渲染器
	renderer_base_pre OutPreRender(OutPixfPre);

	// 清除背景
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
	// 行扫描抗锯齿光栅控制器
	agg::rasterizer_scanline_aa<> AaRasterizer;
	// 色段类型
	agg::scanline_u8  U8Scanline;
	AaRasterizer.add_path(Polygon4);
	AaRasterizer.clip_box(0, 0, OutBuf.width(), OutBuf.height());
	AaRasterizer.reset();
	AaRasterizer.move_to_d(Polygon4.xn(0), Polygon4.yn(0));
	AaRasterizer.line_to_d(Polygon4.xn(1), Polygon4.yn(1));
	AaRasterizer.line_to_d(Polygon4.xn(2), Polygon4.yn(2));
	AaRasterizer.line_to_d(Polygon4.xn(3), Polygon4.yn(3));


	//------------------------------------------------------------------------
	// 线段分配器
	agg::span_allocator<color_type> SaAlloc;
	// 双线性插值法滤波器
	agg::image_filter_bilinear FilterKernel;
	// 滤波器控制器
	agg::image_filter_lut FilterLut(FilterKernel, false);

	// 渲染源
	pixfmt PixfSrcImg(DstBuf);
	// 图片访问器克隆
	typedef agg::image_accessor_clone<pixfmt> img_accessor_type;
	// 渲染源访问器
	img_accessor_type ImgAcc(PixfSrcImg);

	// 远景渲染服务器，四边形 -> 矩形
	agg::trans_perspective PerspectiveTranser(Polygon4.polygon(), 0.0, 0.0, DstBuf.width(), DstBuf.height());
	if(PerspectiveTranser.is_valid())
	{
		// 远景渲染色段插值服务器，校对类型
		interpolator_type InterpolatorType(PerspectiveTranser);
		// 色段创建器
		span_gen_type SaGen(ImgAcc, InterpolatorType, FilterLut);

		// 参数：
		// Rasterizer：光栅控制器
		// Scanline：span容器
		// BaseRenderer：渲染器
		// SpanAllocator：线段分配器
		// SpanGenerator：指定算法的色段创建器

		// 抗锯齿渲染，把SaGen通过SaAlloc渲染到OutPreRender上
		agg::render_scanlines_aa(AaRasterizer, U8Scanline, OutPreRender, SaAlloc, SaGen);
	}

	OutPixImg.draw(hMemoryDC);
	OutPixImg.clear();
}
*/
