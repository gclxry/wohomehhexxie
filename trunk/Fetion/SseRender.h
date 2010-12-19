
#pragma once
#include <atltypes.h>

class CSseRender
{
public:
	CSseRender(void);
	~CSseRender(void);

	static void SolidBrush32ARGB(DWORD *pImgData, CSize ImgSize, CRect DrawRect, BYTE byR, BYTE byG, BYTE byB, BYTE byA = 255);
};
