
#include "stdafx.h"
#include "AKInterface.h"


CAKDraw2DTo3D::CAKDraw2DTo3D()
{

}

CAKDraw2DTo3D::~CAKDraw2DTo3D()
{

}

void CAKDraw2DTo3D::SetDrawBuffer(unsigned char *pBmpData, int Width, int nHeight)
{
	if (pBmpData != NULL)
	{
		CAKPicDraw::GetInst()->SelectPic(pBmpData, Width, nHeight);
		CAK3DRender::GetInst()->SelectPicDraw(CAKPicDraw::GetInst());
	}
}

void CAKDraw2DTo3D::Draw2DTo3D(HDC hMemoryDC, HBITMAP hMemoryBitmap, unsigned char *pBmpData, CRect &PicRect,
								CPoint &ShowLeftTop, CPoint &ShowRightTop, CPoint &ShowLeftDown, CPoint &ShowRightDown)
{
	if (!IS_SAVE_HANDLE(hMemoryDC) || !IS_SAVE_HANDLE(hMemoryBitmap) || pBmpData == NULL || PicRect.IsRectEmpty())
		return;

	//����
	CAKPicDraw::GetInst()->SelectPic(pBmpData, PicRect.Width(), PicRect.Height());
	memset(pBmpData, 0, PicRect.Width() * PicRect.Height() * 4);

	//������Ȼ���
	CAK3DRender::GetInst()->ResetZBuffer(-10000);

	//ѡ��ʹ�õ���ͼ
	AK_2D_UI_PIC *pUIPic = CAK2DUI::GetSingle().FindUIPic(1);
	CAKPicDraw::GetInst(AK_PIC_DRAW_MAX_COUNT-1)->SelectPic(pUIPic->pData, pUIPic->uWidth, pUIPic->uHeight);

	// ���㣬������� v1 ���£�v2 ���£�v3 ���ϣ�v4 ����
	DEF_VERTEX(v1, 200, 100, 0);
	DEF_VERTEX(v2, 400, 50, 0);
	DEF_VERTEX(v3, 400, 500, 0);
	DEF_VERTEX(v4, 200, 450, 0);

	// ͼƬ���󣬼�ͼƬ�Ĵ�С����Сֵ��0��ʼ���磺��λ1024��ֵΪ 1023
	// uv1 ���£�uv2 ���£�uv3 ���ϣ�uv4 ����
	DEF_UV(uv1, 0, 0);
	DEF_UV(uv2, 1023, 0);
	DEF_UV(uv3, 1023, 767);
	DEF_UV(uv4, 0, 767);

	//��Ⱦ
	CAK3DRender::GetInst()->DrawRect2(&v1, &v2, &v3, &v4, uv1, uv2, uv3, uv4, true);

	//��λͼ��ʾ����
	DisplayBmpData(hMemoryDC,hMemoryBitmap,0,0,m_pSEffectsBmpData, rc.Width(), rc.Height());
}

void CAKDraw2DTo3D::DisplayBmpData(HDC hMemoryDC, HBITMAP hMemoryBitmap, long x, long y, unsigned char *pBmp, long rows, long cols)
{
	// ��ȡ��ǰDC��������ʾλ��(16/24/32)
	int BitCount=::GetDeviceCaps(hMemoryDC, BITSPIXEL);
	switch (BitCount)
	{
		// 16λɫ
	case 16:
		{
			long i,index1,index2;
			long total=rows*cols;
			unsigned short r,g,b;
			unsigned short *pValue;

			for(i=0,index1=0,index2=0;i<total;++i)
			{
				index1+=4;
				index2+=2;

				b=pBmp[index1];
				g=pBmp[index1+1];
				r=pBmp[index1+2];

				pValue=(unsigned short *)&pBmp[index2];

				*pValue=(r/8<<11)|(g/4<<5)|(b/8);
			}

			::SetBitmapBits(hMemoryBitmap, cols*rows*2*sizeof(unsigned char), pBmp);
			break;
		}

		// 24λɫ
	case 24:
		{
			long i,index1,index2;
			long total=rows*cols;

			for(i=0,index1=0,index2=0;i<total;++i)
			{
				index1+=4;
				index2+=3;

				memcpy(&pBmp[index2],&pBmp[index1],sizeof(unsigned char)*3);
			}

			::SetBitmapBits(hMemoryBitmap, cols*rows*3*sizeof(unsigned char),pBmp);
			break;
		}

		// 32λɫ
	case 32:
		{
			::SetBitmapBits(hMemoryBitmap, cols*rows*4*sizeof(unsigned char),pBmp);
			break;
		}

		// ����λɫ
	default:
		{
			::TextOut(hMemoryDC, (cols-7*16)/2, rows/2, _T("��ʾģʽ��֧��"), 7);
			break;
		}
	}
}
