
#pragma once
#include <atltypes.h>


#define ARGB_MARK(r,g,b,a)          (((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)|(((DWORD)(BYTE)(a))<<24))

class CSseRender
{
public:
	CSseRender(void);
	~CSseRender(void);

	static void SolidBrush32ARGB(DWORD *pImgData, CSize ImgSize, CRect DrawRect, DWORD dwColor);
};
