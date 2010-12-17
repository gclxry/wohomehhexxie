
#include "stdafx.h"
#include "Gauss.h"

void CGaussBlur::Alpha (BYTE* buf, int width, int bytes)
{
	for (int i=0 ; i < width * bytes ; i += bytes)
	{
		double   alpha = buf[i + bytes - 1] * (1.0 / 255.0) ;
		for (int j = 0; j < bytes - 1; j++)
			buf[i + j] = (int)(buf[i + j] * alpha) ;
	}
}

void CGaussBlur::AlphaInvert (BYTE* buf, int width, int bytes)
{
	int   i, j;
	BYTE alpha;
	double recip_alpha;
	int    new_val;

	for (i = 0; i < width * bytes; i += bytes)
	{
		alpha = buf[i + bytes - 1];
		if (alpha != 0 && alpha != 255)
		{
			recip_alpha = 255.0 / alpha;
			for (j = 0; j < bytes - 1; j++)
			{
				new_val = (int)(buf[i + j] * recip_alpha);
				buf[i + j] = min (255, new_val);
			}
		}
	}
}


void CGaussBlur::GaussConstants (double n_p[], double n_m[], double d_p[], double d_m[], double bd_p[], double bd_m[], double std_dev)
{
	int    i;
	double constants [8];
	double div;

	// pi = acos(-1.0) or 4*atan(1.0)
	div = sqrt(acos(-1.0)*2) * std_dev;
	constants [0] = -1.783 / std_dev;
	constants [1] = -1.723 / std_dev;
	constants [2] = 0.6318 / std_dev;
	constants [3] = 1.997  / std_dev;
	constants [4] = 1.6803 / div;
	constants [5] = 3.735 / div;
	constants [6] = -0.6803 / div;
	constants [7] = -0.2598 / div;

	n_p [0] = constants[4] + constants[6];
	n_p [1] = exp (constants[1]) *
		(constants[7] * sin (constants[3]) -
		(constants[6] + 2 * constants[4]) * cos (constants[3])) +
		exp (constants[0]) *
		(constants[5] * sin (constants[2]) -
		(2 * constants[6] + constants[4]) * cos (constants[2]));
	n_p [2] = 2 * exp (constants[0] + constants[1]) *
		((constants[4] + constants[6]) * cos (constants[3]) * cos (constants[2]) -
		constants[5] * cos (constants[3]) * sin (constants[2]) -
		constants[7] * cos (constants[2]) * sin (constants[3])) +
		constants[6] * exp (2 * constants[0]) +
		constants[4] * exp (2 * constants[1]);
	n_p [3] = exp (constants[1] + 2 * constants[0]) *
		(constants[7] * sin (constants[3]) - constants[6] * cos (constants[3])) +
		exp (constants[0] + 2 * constants[1]) *
		(constants[5] * sin (constants[2]) - constants[4] * cos (constants[2]));
	n_p [4] = 0.0;

	d_p [0] = 0.0;
	d_p [1] = -2 * exp (constants[1]) * cos (constants[3]) -
		2 * exp (constants[0]) * cos (constants[2]);
	d_p [2] = 4 * cos (constants[3]) * cos (constants[2]) * exp (constants[0] + constants[1]) +
		exp (2 * constants[1]) + exp (2 * constants[0]);
	d_p [3] = -2 * cos (constants[2]) * exp (constants[0] + 2 * constants[1]) -
		2 * cos (constants[3]) * exp (constants[1] + 2 * constants[0]);
	d_p [4] = exp (2 * constants[0] + 2 * constants[1]);

	for (i = 0; i <= 4; i++)
		d_m [i] = d_p [i];

	n_m[0] = 0.0;
	for (i = 1; i <= 4; i++)
		n_m [i] = n_p[i] - d_p[i] * n_p[0];

	{
		double sum_n_p = 0.0;
		double sum_n_m = 0.0;
		double sum_d = 0.0;
		for (i = 0; i <= 4; i++)
		{
			sum_n_p += n_p[i];
			sum_n_m += n_m[i];
			sum_d += d_p[i];
		}

		double a = sum_n_p / (1.0 + sum_d);
		double b = sum_n_m / (1.0 + sum_d);

		for (i = 0; i <= 4; i++)
		{
			bd_p[i] = d_p[i] * a;
			bd_m[i] = d_m[i] * b;
		}
	}
}

void CGaussBlur::GaussIIRBlurImage (BYTE *img, const int width, const int height, const int colorDepth,int sigmaH,int sigmaV)
{
	const int   bytes = colorDepth / 8 ;

	int num = max(width,height)*bytes;
	double *val_p = new double[num],
		*val_m = new double[num];

	BYTE *src = new BYTE[num];

	double   n_p[5], n_m[5], d_p[5], d_m[5], bd_p[5], bd_m[5] ;

	// ´¹Ö±
	int     v = sigmaV ;
	double  std_dev = sqrt (-(v * v) / (2 * log (1.0 / 255.0))) ;

	GaussConstants (n_p, n_m, d_p, d_m, bd_p, bd_m, std_dev) ;

	for (int x=0 ; x < width ; x++)
	{
		memset (val_p, 0, num*sizeof(double)) ;
		memset (val_m, 0, num*sizeof(double)) ;

		// get col
		for (int y=0 ; y < height ; y++)
			memcpy(&src[bytes*y], &img[y*width*bytes +x*bytes], bytes) ;

		if (bytes == 4)
			Alpha (src, height, bytes) ;

		BYTE    * sp_p = src;
		BYTE    * sp_m = src + (height - 1) * bytes ;
		double  * vp = val_p;
		double  * vm = val_m + (height - 1) * bytes ;

		// Set up the first vals
		int     initial_p[4],
			initial_m[4] ;
		for (int i=0 ; i < bytes ; i++)
		{
			initial_p[i] = sp_p[i] ;
			initial_m[i] = sp_m[i] ;
		}

		for (int y=0 ; y < height ; y++)
		{
			double  * vpptr,
				* vmptr ;
			int     terms = (y < 4) ? y : 4 ;

			for (int b=0 ; b < bytes ; b++)
			{
				vpptr = vp + b; vmptr = vm + b;
				int   i ;
				for (i=0 ; i <= terms ; i++)
				{
					*vpptr += n_p[i] * sp_p[(-i * bytes) + b] - d_p[i] * vp[(-i * bytes) + b] ;
					*vmptr += n_m[i] * sp_m[(i * bytes) + b] - d_m[i] * vm[(i * bytes) + b] ;
				}
				for (int j=i ; j <= 4 ; j++)
				{
					*vpptr += (n_p[j] - bd_p[j]) * initial_p[b] ;
					*vmptr += (n_m[j] - bd_m[j]) * initial_m[b] ;
				}
			}

			sp_p += bytes ;
			sp_m -= bytes ;
			vp += bytes ;
			vm -= bytes ;
		}

		double  * pTmp_p = val_p, * pTmp_m = val_m ;
		for (int mm=0 ; mm < height ; mm++)
		{
			BYTE   * p = &img[mm*width*bytes + x*bytes] ;
			for (int b=0 ; b < bytes ; b++)
			{
				p[b] = min(255,max(0, int(*pTmp_p + *pTmp_m))) ; 
				pTmp_p++ ; 
				pTmp_m++ ;
			}
		}
	}

	// Ë®Æ½
	if(sigmaH != sigmaV)
	{
		int     h = sigmaH;
		double  std_dev = sqrt (-(h * h) / (2 * log (1.0 / 255.0))) ;

		GaussConstants (n_p, n_m, d_p, d_m, bd_p, bd_m, std_dev) ;
	}

	for (int y=0 ; y < height ; y++)
	{
		memset (val_p, 0, num*sizeof(double)) ;
		memset (val_m, 0, num*sizeof(double)) ;

		// get row
		memcpy (src, img+y*width* bytes, width* bytes) ;

		BYTE    * sp_p = src;
		BYTE    * sp_m = src + (width - 1) * bytes ;
		double  * vp = val_p ;
		double  * vm = val_m + (width - 1) * bytes ;

		// Set up the first vals
		int     initial_p[4],
			initial_m[4] ;
		for (int i=0 ; i < bytes ; i++)
		{
			initial_p[i] = sp_p[i] ;
			initial_m[i] = sp_m[i] ;
		}

		for (int x=0 ; x < width ; x++)
		{
			double  * vpptr,
				* vmptr ;
			int     terms = (x < 4) ? x : 4 ;

			for (int b=0 ; b < bytes ; b++)
			{
				vpptr = vp + b; vmptr = vm + b;
				int   i ;
				for (i=0 ; i <= terms ; i++)
				{
					*vpptr += n_p[i] * sp_p[(-i * bytes) + b] - d_p[i] * vp[(-i * bytes) + b] ;
					*vmptr += n_m[i] * sp_m[(i * bytes) + b] - d_m[i] * vm[(i * bytes) + b] ;
				}
				for (int j=i ; j <= 4 ; j++)
				{
					*vpptr += (n_p[j] - bd_p[j]) * initial_p[b] ;
					*vmptr += (n_m[j] - bd_m[j]) * initial_m[b] ;
				}
			}

			sp_p += bytes ;
			sp_m -= bytes ;
			vp += bytes ;
			vm -= bytes ;
		}

		double  * pTmp_p = val_p, * pTmp_m = val_m;
		for (int mm=0 ; mm < width ; mm++)
		{
			BYTE   * p = &img[y*width*bytes + mm*bytes] ;
			for (int b=0 ; b < bytes ; b++)
			{
				p[b] = min(255,max(0, int(*pTmp_p + *pTmp_m))) ; 
				pTmp_p++ ; 
				pTmp_m++ ;
			}
		}

		if (bytes == 4)
			AlphaInvert (img+y*width*bytes, width, bytes) ;

	}

	delete []val_p;
	delete []val_m;
	delete []src;
}
