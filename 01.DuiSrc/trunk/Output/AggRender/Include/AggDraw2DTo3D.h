
#pragma once

#include "AggInterface.h"

class CAggDraw2DTo3D
{
public:
	CAggDraw2DTo3D();
	virtual ~CAggDraw2DTo3D();

	// ��2D��ͼ��3D��ʽչ��
	static void CAggDraw2DTo3D::Draw2DTo3D(rendering_buffer &DstImgBuf, rendering_buffer &SrcImgBuf, CPoint vP[4]);

private:
};
