
#include "StdAfx.h"
#include "Sse2Render.h"

CSse2Render::CSse2Render(void)
{
	m_bIsSupportSse2 = m_CpuSupport.IsSSE2();
}

CSse2Render::~CSse2Render(void)
{
}
