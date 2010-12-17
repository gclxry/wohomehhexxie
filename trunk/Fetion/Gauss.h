
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

	static void Alpha (BYTE* buf, int width, int bytes);
	static void AlphaInvert (BYTE* buf, int width, int bytes);
	// derive the constants for calculating the gaussian from the std dev
	static void GaussConstants (double n_p[], double n_m[], double d_p[], double d_m[], double bd_p[], double bd_m[], double std_dev);
	static void GaussIIRBlurImage (BYTE *img, const int width, const int height, const int colorDepth,int sigmaH,int sigmaV);
};
