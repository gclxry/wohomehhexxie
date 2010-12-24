
#pragma once

#include <math.h>
#include <GdiPlus.h>
using namespace Gdiplus;

class CGaussBlur
{
public:
	CGaussBlur ()
	{
	}

	void ImageGaussiabBlur(BYTE *Data,int width, int height,double Q, int radius);
};
