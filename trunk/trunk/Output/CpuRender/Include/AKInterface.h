
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

	// ����λͼ�Ļ��棬һ���ڴ��ڴ�С�����仯������WM_SIZE��Ϣ����������
	void SetDrawBuffer(int Width, int nHeight);

	// ��2D��ͼ��3D��ʽչ��
	void Draw2DTo3D(HDC hMemoryDC, HBITMAP hMemoryBitmap, unsigned char* pMemoryBitmapBits, CRect &PicRect,
		CPoint &ptLeftUp, CPoint &ptRightUp, CPoint &ptLeftDown, CPoint &ptRightDown);

private:
	// ��3DͼƬ��ʾ��ָ��DC��
	void DisplayBmpData(HDC hMemoryDC, HBITMAP hMemoryBitmap, long x, long y, unsigned char *pBmp, long rows, long cols);

private:
	unsigned char *m_pSEffectsBmpData;
};
