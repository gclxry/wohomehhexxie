
#pragma once

#include <math.h>

class CGaussBlur
{
public:
	CGaussBlur ()
	{
		m_pnWeights = NULL;
	}
	~CGaussBlur()
	{
		if (m_pnWeights != NULL)
		{
			delete []m_pnWeights;
			m_pnWeights = NULL;
		}
	}

	void InitWeights(double Q,int radius);
	// 
	void ImageGaussBlur(BYTE *Data,int width, int height,int left,int top,int right,int bottom,int radius);
	void ImageGaussBlur(BYTE *Data,int width, int height,int radius);

private:
	void _ImageGaussiabBlur(BYTE *Data,int widthFrom,int widthTo,int heightFrom,int heightTo,int stride,int radius,BYTE *ptrTemp);

private:
	int *m_pnWeights;
};
