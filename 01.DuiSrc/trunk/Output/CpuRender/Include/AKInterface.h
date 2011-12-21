
#pragma once

#include "CpuRenderDef.h"
#include "AKTrajectory.h"
#include "AKPicDraw.h"
#include "AK3DRender.h"

class CAKDraw2DTo3D
{
public:
	CAKDraw2DTo3D();
	virtual ~CAKDraw2DTo3D();

	// 设置位图的缓存，一般在窗口大小发生变化，即：WM_SIZE消息触发是设置
	void SetDrawBuffer(int Width, int nHeight);

	// 将2D的图以3D形式展现
	void Draw2DTo3D(HDC hMemoryDC, HBITMAP hMemoryBitmap, unsigned char* pMemoryBitmapBits, CRect &PicRect,
		CPoint &ptLeftUp, CPoint &ptRightUp, CPoint &ptLeftDown, CPoint &ptRightDown);

private:
	// 将3D图片显示到指定DC上
	void DisplayBmpData(HDC hMemoryDC, HBITMAP hMemoryBitmap, long x, long y, unsigned char *pBmp, long rows, long cols);

private:
	unsigned char *m_pSEffectsBmpData;
};
