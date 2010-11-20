
#pragma once

#include "AggRenderDefs.h"

class CAggInterface
{
public:
	CAggInterface();
	virtual ~CAggInterface();

	bool load_pmap(const char* fn, unsigned idx, rendering_buffer* dst);
};
