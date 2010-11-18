
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

	// ����λͼ�Ļ��棬һ���ڴ��ڴ�С�����仯������WM_SIZE��Ϣ���������ã�pBmpData�����ǵ�������������
	// �˻������Ϊ32λλͼ
	// �磺
	// CRect WndRect = this->GetClientRect();
	// long lSize = WndRect.Width() * WndRect.Height() * 4 * sizeof(unsigned char);
	// pBmpData = new unsigned char[lSize];
	void SetDrawBuffer(unsigned char *pBmpData, int Width, int nHeight);

	// ��2D��ͼ��3D��ʽչ��
	void Draw2DTo3D();

private:
	// ��3DͼƬ��ʾ��ָ��DC��
	void DisplayBmpData(HDC hMemoryDC, HBITMAP hMemoryBitmap, long x, long y, unsigned char *pBmp, long rows, long cols);
};
