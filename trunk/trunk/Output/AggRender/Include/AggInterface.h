
#pragma once

#include <windows.h>
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
	static void CreatePixelMap(HBITMAP hBitmap, pixel_map &PixMap, rendering_buffer &RenderBuf);
};
