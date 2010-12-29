
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

	void InitWeights(double dbQ, int nRadius);
	void ImageGaussBlur(BYTE *pbyData, int nWidth, int nHeight, int nLeft, int nTop, int nRight,int nBottom);
	void ImageGaussBlur(BYTE *pbyData, int nWidth, int nHeight);

private:
	void _ImageGaussiabBlur(BYTE *pbyData, int nWidthFrom, int nWidthTo, int nHeightFrom, int nHeightTo, int nStride, BYTE *ptrTemp);

private:
	int *m_pnWeightList;
	int m_nRadius;
};
