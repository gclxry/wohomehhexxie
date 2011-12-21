
#pragma once

#include "SseRender.h"


class CSse2Render : public CSseRender
{
public:
	CSse2Render(void);
	~CSse2Render(void);

private:
	bool m_bIsSupportSse2;
};
