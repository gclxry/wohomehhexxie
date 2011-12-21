
#pragma once

#include "AggInterface.h"

class CAggDraw2DTo3D
{
public:
	CAggDraw2DTo3D();
	virtual ~CAggDraw2DTo3D();

	// 将2D的图以3D形式展现
	static void CAggDraw2DTo3D::Draw2DTo3D(rendering_buffer &DstImgBuf, rendering_buffer &SrcImgBuf, CPoint vP[4]);

private:
};
