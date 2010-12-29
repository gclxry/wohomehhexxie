
#pragma once

#include <math.h>

class CGaussBlur
{
public:
	CGaussBlur ()
	{
		m_pnWeightList = NULL;
		m_nRadius = 1;
	}

	~CGaussBlur()
	{
		if (m_pnWeightList != NULL)
		{
			delete []m_pnWeightList;
			m_pnWeightList = NULL;
		}
	}

	void InitWeights(double Q, int radius);
	// 
	void ImageGaussBlur(BYTE *Data,int width, int height,int left,int top,int right,int bottom);
	void ImageGaussBlur(BYTE *Data,int width, int height);

private:
	void _ImageGaussiabBlur(BYTE *Data,int widthFrom,int widthTo,int heightFrom,int heightTo,int stride,BYTE *ptrTemp);

private:
	int *m_pnWeightList;
	int m_nRadius;
};
