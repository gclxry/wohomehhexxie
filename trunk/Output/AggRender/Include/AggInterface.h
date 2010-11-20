
#pragma once

#include "AggRenderDefs.h"

class CAggInterface
{
public:
	CAggInterface();
	virtual ~CAggInterface();

	static bool load_pmap(pixel_map &PixMapImg, const char* fn, rendering_buffer* dst, pix_format_e format = agg::pix_format_bgra32, bool IsFlipY = true);
};
