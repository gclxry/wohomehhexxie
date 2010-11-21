
#pragma once

#include "resource.h"
//#include "AggRender.h"


#include <atlbase.h>
#include <atltypes.h>

#include "agg_trans_perspective.h"
#include "agg_span_image_filter_rgba.h"
#include "agg_rendering_buffer.h"
#include "platform\win32\agg_win32_bmp.h"
#include "platform\agg_platform_support.h"
#include "util\agg_color_conv.h"
#include "util\agg_color_conv_rgb8.h"
#include "util\agg_color_conv_rgb16.h"
#include "agg_span_interpolator_trans.h"
#include "agg_span_allocator.h"
#include "agg_image_accessors.h"
#include "agg_rasterizer_scanline_aa.h"
#include "agg_pixfmt_rgba.h"
#include "agg_scanline_u.h"
#include "interactive_polygon.h"

using namespace agg;



class CAggInterface
{
public:
	CAggInterface();
	virtual ~CAggInterface();

	static bool load_pmap(pixel_map &PixMapImg, const char* fn, rendering_buffer* dst, pix_format_e format = agg::pix_format_bgra32, bool IsFlipY = true);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////
class CAggDraw2DTo3D
{
public:
	CAggDraw2DTo3D();
	virtual ~CAggDraw2DTo3D();

	// 将2D的图以3D形式展现
	void Draw2DTo3D(HDC hMemoryDC, HBITMAP hMemoryBitmap, unsigned char* pMemoryBitmapBits, CRect &PicRect,
		CPoint &ptLeftUp, CPoint &ptRightUp, CPoint &ptLeftDown, CPoint &ptRightDown);

private:
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////


void OnTimer(HWND hWnd, WPARAM wParam, LPARAM lParam);
void OnSize(WPARAM wParam, LPARAM lParam);
void OnCreate();
void Draw(HWND hWnd, HDC hdc);
void AggDraw(HWND hWnd, HDC hMemoryDC, HBITMAP hMemoryBitmap);
