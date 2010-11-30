
#include "stdafx.h"
#include "AggTester.h"


#define MAX_LOADSTRING 100

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

pixel_map PixMapImg;
rendering_buffer DstBuf;

void OnCreate()
{
	USES_CONVERSION;

	CAggInterface::load_pmap(PixMapImg, "test.bmp", &DstBuf);
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
	// agg �̶�������
	// 1.����Դ (Vertex Source)
	// 2.����ת���ܵ� (Coordinate conversion pipeline)
	// 3.ˮƽɨ���߹�դ(Scanline Rasterizer)
	// 4.��Ⱦ��(Renderers)
	// 5.��Ⱦ����(Rendering Buffer)




	typedef agg::pixfmt_bgra32 pixfmt;
	typedef agg::pixfmt_bgra32_pre pixfmt_pre;
	typedef agg::renderer_base<pixfmt_pre> renderer_base_pre;
	typedef agg::renderer_base<pixfmt> renderer_base;

	typedef pixfmt::color_type color_type;
	typedef agg::image_accessor_clone<pixfmt> img_accessor_type;
	typedef agg::span_interpolator_trans<agg::trans_perspective> interpolator_type;
	typedef agg::span_image_filter_rgba_2x2<img_accessor_type, interpolator_type> span_gen_type;



	//----------------------------------------
	pixel_map OutPixImg;
	rendering_buffer OutBuf;

	CRect WndRect(0, 0, 0, 0);
	::GetClientRect(hWnd, &WndRect);
	OutPixImg.create(WndRect.Width(), WndRect.Height(), org_color32);
	OutBuf.attach(OutPixImg.buf(), OutPixImg.width(), OutPixImg.height(), OutPixImg.stride());

	// �����в���Ⱦ�������
	pixfmt            pixf(OutBuf);
	// ��ǿ���в���Ⱦ�������
	pixfmt_pre        pixf_pre(OutBuf);
	// �����в���Ⱦ���������������
	renderer_base     rb(pixf);
	// ��ǿ���в���Ⱦ��
	renderer_base_pre rb_pre(pixf_pre);

	// �������
	rb.clear(agg::rgba(0.0, 1, 1));



	//----------------------------------------
	agg::interactive_polygon m_quad(4, 5.0);

	m_quad.xn(0) = 0;
	m_quad.yn(0) = 0;
	m_quad.xn(1) = DstBuf.width() - 100;
	m_quad.yn(1) = 100;
	m_quad.xn(2) = DstBuf.width() - 100;
	m_quad.yn(2) = DstBuf.height() - 100;
	m_quad.xn(3) = 100;
	m_quad.yn(3) = DstBuf.height() - 100;

	//-------------------------------------------------
	// ��ɨ�迹��ݹ�դ������
	agg::rasterizer_scanline_aa<> g_rasterizer;
	// ɫ������
	agg::scanline_u8  g_scanline;
	g_rasterizer.add_path(m_quad);
	g_rasterizer.clip_box(0, 0, OutBuf.width(), OutBuf.height());
	g_rasterizer.reset();
	g_rasterizer.move_to_d(m_quad.xn(0), m_quad.yn(0));
	g_rasterizer.line_to_d(m_quad.xn(1), m_quad.yn(1));
	g_rasterizer.line_to_d(m_quad.xn(2), m_quad.yn(2));
	g_rasterizer.line_to_d(m_quad.xn(3), m_quad.yn(3));


	//------------------------------------------------------------------------
	// �߶η�����
	agg::span_allocator<color_type> sa;
	// ˫���Բ�ֵ���˲���
	agg::image_filter_bilinear filter_kernel;
	// �˲���������
	agg::image_filter_lut filter(filter_kernel, false);

	// ��ȾԴ
	pixfmt pixf_img(DstBuf);
	// ͼƬ��������¡
	typedef agg::image_accessor_clone<pixfmt> img_accessor_type;
	// ��ȾԴ������
	img_accessor_type ia(pixf_img);

	// Զ����Ⱦ���������ı��� -> ����
	agg::trans_perspective tr(m_quad.polygon(), 0.0, 0.0, DstBuf.width(), DstBuf.height());
	if(tr.is_valid())
	{
		//-----------------------
		// ɫ�β�ֵ����
		typedef agg::span_interpolator_trans<agg::trans_perspective> interpolator_type;
		// Զ����Ⱦɫ�β�ֵ������
		interpolator_type interpolator(tr);
		// ɫ�δ�����
		typedef agg::span_image_filter_rgba_2x2<img_accessor_type, interpolator_type> span_gen_type;
		span_gen_type sg(ia, interpolator, filter);

		// ������
		// Rasterizer����դ������
		// Scanline��span����
		// BaseRenderer����Ⱦ��
		// SpanAllocator���߶η�����
		// SpanGenerator��ָ���㷨��ɫ�δ�����

		// �������Ⱦ����sgͨ��sa��Ⱦ��rb_pre�ϣ�
		agg::render_scanlines_aa(g_rasterizer, g_scanline, rb_pre, sa, sg);
	}

	//PixMapImg.draw(hMemoryDC);

	OutPixImg.draw(hMemoryDC);
	OutPixImg.clear();
}

CAggInterface::CAggInterface()
{
}

CAggInterface::~CAggInterface()
{
}

bool CAggInterface::load_pmap(pixel_map &PixMapImg, const char* fn, rendering_buffer* dst, pix_format_e format, bool IsFlipY)
{
	pixel_map pmap_tmp;

	if(!pmap_tmp.load_from_bmp(fn))
		return false;

	unsigned nBpp = 0;
	switch (format)
	{
	case pix_format_bw:
		nBpp = 1;
		break;

	case pix_format_gray8:
		nBpp = 8;
		break;

	case pix_format_gray16:
		nBpp = 16;
		break;

	case pix_format_rgb565:
	case pix_format_rgb555:
		nBpp = 16;
		break;

	case pix_format_rgbAAA:
	case pix_format_bgrAAA:
	case pix_format_rgbBBA:
	case pix_format_bgrABB:
		nBpp = 32;
		break;

	case pix_format_rgb24:
	case pix_format_bgr24:
		nBpp = 24;
		break;

	case pix_format_rgb48:
	case pix_format_bgr48:
		nBpp = 48;
		break;

	case pix_format_bgra32:
	case pix_format_abgr32:
	case pix_format_argb32:
	case pix_format_rgba32:
		nBpp = 32;
		break;

	case pix_format_bgra64:
	case pix_format_abgr64:
	case pix_format_argb64:
	case pix_format_rgba64:
		nBpp = 64;
		break;
	}

	rendering_buffer rbuf_tmp;
	rbuf_tmp.attach(pmap_tmp.buf(),
		pmap_tmp.width(),
		pmap_tmp.height(),
		IsFlipY ? pmap_tmp.stride() : -pmap_tmp.stride());

	PixMapImg.create(pmap_tmp.width(), pmap_tmp.height(), org_e(nBpp), 0);

	dst->attach(PixMapImg.buf(),
		PixMapImg.width(),
		PixMapImg.height(),
		IsFlipY ? PixMapImg.stride() : -PixMapImg.stride());

	switch (format)
	{
	case pix_format_gray8:
		switch(pmap_tmp.bpp())
		{
			//case 16: color_conv(dst, &rbuf_tmp, color_conv_rgb555_to_gray8()); break;
		case 24: color_conv(dst, &rbuf_tmp, color_conv_bgr24_to_gray8()); break;
			//case 32: color_conv(dst, &rbuf_tmp, color_conv_bgra32_to_gray8()); break;
		}
		break;

	case pix_format_gray16:
		switch(pmap_tmp.bpp())
		{
			//case 16: color_conv(dst, &rbuf_tmp, color_conv_rgb555_to_gray16()); break;
		case 24: color_conv(dst, &rbuf_tmp, color_conv_bgr24_to_gray16()); break;
			//case 32: color_conv(dst, &rbuf_tmp, color_conv_bgra32_to_gray16()); break;
		}
		break;

	case pix_format_rgb555:
		switch(pmap_tmp.bpp())
		{
		case 16: color_conv(dst, &rbuf_tmp, color_conv_rgb555_to_rgb555()); break;
		case 24: color_conv(dst, &rbuf_tmp, color_conv_bgr24_to_rgb555()); break;
		case 32: color_conv(dst, &rbuf_tmp, color_conv_bgra32_to_rgb555()); break;
		}
		break;

	case pix_format_rgb565:
		switch(pmap_tmp.bpp())
		{
		case 16: color_conv(dst, &rbuf_tmp, color_conv_rgb555_to_rgb565()); break;
		case 24: color_conv(dst, &rbuf_tmp, color_conv_bgr24_to_rgb565()); break;
		case 32: color_conv(dst, &rbuf_tmp, color_conv_bgra32_to_rgb565()); break;
		}
		break;

	case pix_format_rgb24:
		switch(pmap_tmp.bpp())
		{
		case 16: color_conv(dst, &rbuf_tmp, color_conv_rgb555_to_rgb24()); break;
		case 24: color_conv(dst, &rbuf_tmp, color_conv_bgr24_to_rgb24()); break;
		case 32: color_conv(dst, &rbuf_tmp, color_conv_bgra32_to_rgb24()); break;
		}
		break;

	case pix_format_bgr24:
		switch(pmap_tmp.bpp())
		{
		case 16: color_conv(dst, &rbuf_tmp, color_conv_rgb555_to_bgr24()); break;
		case 24: color_conv(dst, &rbuf_tmp, color_conv_bgr24_to_bgr24()); break;
		case 32: color_conv(dst, &rbuf_tmp, color_conv_bgra32_to_bgr24()); break;
		}
		break;

	case pix_format_rgb48:
		switch(pmap_tmp.bpp())
		{
			//case 16: color_conv(dst, &rbuf_tmp, color_conv_rgb555_to_rgb48()); break;
		case 24: color_conv(dst, &rbuf_tmp, color_conv_bgr24_to_rgb48()); break;
			//case 32: color_conv(dst, &rbuf_tmp, color_conv_bgra32_to_rgb48()); break;
		}
		break;

	case pix_format_bgr48:
		switch(pmap_tmp.bpp())
		{
			//case 16: color_conv(dst, &rbuf_tmp, color_conv_rgb555_to_bgr48()); break;
		case 24: color_conv(dst, &rbuf_tmp, color_conv_bgr24_to_bgr48()); break;
			//case 32: color_conv(dst, &rbuf_tmp, color_conv_bgra32_to_bgr48()); break;
		}
		break;

	case pix_format_abgr32:
		switch(pmap_tmp.bpp())
		{
		case 16: color_conv(dst, &rbuf_tmp, color_conv_rgb555_to_abgr32()); break;
		case 24: color_conv(dst, &rbuf_tmp, color_conv_bgr24_to_abgr32()); break;
		case 32: color_conv(dst, &rbuf_tmp, color_conv_bgra32_to_abgr32()); break;
		}
		break;

	case pix_format_argb32:
		switch(pmap_tmp.bpp())
		{
		case 16: color_conv(dst, &rbuf_tmp, color_conv_rgb555_to_argb32()); break;
		case 24: color_conv(dst, &rbuf_tmp, color_conv_bgr24_to_argb32()); break;
		case 32: color_conv(dst, &rbuf_tmp, color_conv_bgra32_to_argb32()); break;
		}
		break;

	case pix_format_bgra32:
		switch(pmap_tmp.bpp())
		{
		case 16: color_conv(dst, &rbuf_tmp, color_conv_rgb555_to_bgra32()); break;
		case 24: color_conv(dst, &rbuf_tmp, color_conv_bgr24_to_bgra32()); break;
		case 32: color_conv(dst, &rbuf_tmp, color_conv_bgra32_to_bgra32()); break;
		}
		break;

	case pix_format_rgba32:
		switch(pmap_tmp.bpp())
		{
		case 16:
			color_conv(dst, &rbuf_tmp, color_conv_rgb555_to_rgba32());
			break;
		case 24:
			color_conv(dst, &rbuf_tmp, color_conv_bgr24_to_rgba32());
			break;
		case 32:
			color_conv(dst, &rbuf_tmp, color_conv_bgra32_to_rgba32());
			break;
		}
		break;

	case pix_format_abgr64:
		switch(pmap_tmp.bpp())
		{
			//case 16: color_conv(dst, &rbuf_tmp, color_conv_rgb555_to_abgr64()); break;
		case 24: color_conv(dst, &rbuf_tmp, color_conv_bgr24_to_abgr64()); break;
			//case 32: color_conv(dst, &rbuf_tmp, color_conv_bgra32_to_abgr64()); break;
		}
		break;

	case pix_format_argb64:
		switch(pmap_tmp.bpp())
		{
			//case 16: color_conv(dst, &rbuf_tmp, color_conv_rgb555_to_argb64()); break;
		case 24: color_conv(dst, &rbuf_tmp, color_conv_bgr24_to_argb64()); break;
			//case 32: color_conv(dst, &rbuf_tmp, color_conv_bgra32_to_argb64()); break;
		}
		break;

	case pix_format_bgra64:
		switch(pmap_tmp.bpp())
		{
			//case 16: color_conv(dst, &rbuf_tmp, color_conv_rgb555_to_bgra64()); break;
		case 24: color_conv(dst, &rbuf_tmp, color_conv_bgr24_to_bgra64()); break;
			//case 32: color_conv(dst, &rbuf_tmp, color_conv_bgra32_to_bgra64()); break;
		}
		break;

	case pix_format_rgba64:
		switch(pmap_tmp.bpp())
		{
			//case 16: color_conv(dst, &rbuf_tmp, color_conv_rgb555_to_rgba64()); break;
		case 24: color_conv(dst, &rbuf_tmp, color_conv_bgr24_to_rgba64()); break;
			//case 32: color_conv(dst, &rbuf_tmp, color_conv_bgra32_to_rgba64()); break;
		}
		break;
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
CAggDraw2DTo3D::CAggDraw2DTo3D()
{

}

CAggDraw2DTo3D::~CAggDraw2DTo3D()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
