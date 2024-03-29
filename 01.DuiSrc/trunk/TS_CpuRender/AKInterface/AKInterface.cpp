
#include "stdafx.h"
#include "AKInterface.h"

CAKDraw2DTo3D::CAKDraw2DTo3D()
{
	m_pSEffectsBmpData = NULL;
}

CAKDraw2DTo3D::~CAKDraw2DTo3D()
{
	SAVE_DELETE_LIST(m_pSEffectsBmpData);
}

void CAKDraw2DTo3D::SetDrawBuffer(int Width, int nHeight)
{
	SAVE_DELETE_LIST(m_pSEffectsBmpData);

	long lSize = Width * nHeight * 4 * sizeof(unsigned char);
	m_pSEffectsBmpData = new unsigned char[lSize];

	if (m_pSEffectsBmpData != NULL)
	{
		CAKPicDraw::GetInst()->SelectPic(m_pSEffectsBmpData, Width, nHeight);
		CAK3DRender::GetInst()->SelectPicDraw(CAKPicDraw::GetInst());
	}
}

void CAKDraw2DTo3D::Draw2DTo3D(HDC hMemoryDC, HBITMAP hMemoryBitmap, unsigned char* pMemoryBitmapBits, CRect &PicRect,
								CPoint &ptLeftUp, CPoint &ptRightUp, CPoint &ptLeftDown, CPoint &ptRightDown)
{
	if (!IS_SAVE_HANDLE(hMemoryDC) || !IS_SAVE_HANDLE(hMemoryBitmap) || pMemoryBitmapBits == NULL || m_pSEffectsBmpData == NULL || PicRect.IsRectEmpty())
		return;

	AK_2D_UI_PIC *pUIPic = CAK2DUI::GetSingle().CreateUIPic(1, PicRect.Width(), PicRect.Height());
	if (pUIPic == NULL)
		return;

	memcpy(pUIPic->pData, pMemoryBitmapBits, PicRect.Width() * PicRect.Height() * 4);

	//清屏
	CAKPicDraw::GetInst()->SelectPic(m_pSEffectsBmpData, PicRect.Width(), PicRect.Height());
	memset(m_pSEffectsBmpData, 0, PicRect.Width() * PicRect.Height() * 4);

	//重置深度缓冲
	CAK3DRender::GetInst()->ResetZBuffer(-10000);

	//选择使用的贴图
	CAKPicDraw::GetInst(AK_PIC_DRAW_MAX_COUNT-1)->SelectPic(pUIPic->pData, pUIPic->uWidth, pUIPic->uHeight);

	// 图片数据的显示和实际看见的效果是反着的
	// 顶点，输出矩阵 v1 左下，v2 右下，v3 右上，v4 左上
	DEF_VERTEX(v1, ptLeftDown.x, ptLeftDown.y, 0);
	DEF_VERTEX(v2, ptRightDown.x, ptRightDown.y, 0);
	DEF_VERTEX(v3, ptRightUp.x, ptRightUp.y, 0);
	DEF_VERTEX(v4, ptLeftUp.x, ptLeftUp.y, 0);

	// 图片矩阵，即图片的大小，大小值以0开始，如：宽位1024，值为 1023
	// uv1 左下，uv2 右下，uv3 右上，uv4 左上
	DEF_UV(uv1, 0, 0);
	DEF_UV(uv2, (float)(PicRect.Width() - 1), 0);
	DEF_UV(uv3, (float)(PicRect.Width() - 1), (float)(PicRect.Height() - 1));
	DEF_UV(uv4, 0, (float)(PicRect.Height() - 1));

	//渲染
	CAK3DRender::GetInst()->DrawRect2(&v1, &v2, &v3, &v4, uv1, uv2, uv3, uv4, false);

	//把位图显示出来 
	DisplayBmpData(hMemoryDC, hMemoryBitmap, 0, 0, m_pSEffectsBmpData, PicRect.Width(), PicRect.Height());

	CAK2DUI::GetSingle().FreePicList();
}

void CAKDraw2DTo3D::DisplayBmpData(HDC hMemoryDC, HBITMAP hMemoryBitmap, long x, long y, unsigned char *pBmp, long rows, long cols)
{
	// 获取当前DC的像素显示位数(16/24/32)
	int BitCount=::GetDeviceCaps(hMemoryDC, BITSPIXEL);
	switch (BitCount)
	{
		// 16位色
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

		// 24位色
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

		// 32位色
	case 32:
		{
			::SetBitmapBits(hMemoryBitmap, cols*rows*4*sizeof(unsigned char),pBmp);
			break;
		}

		// 其它位色
	default:
		{
			::TextOut(hMemoryDC, (cols-7*16)/2, rows/2, _T("显示模式不支持"), 7);
			break;
		}
	}
}
