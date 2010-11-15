#pragma once
#include "BaseDlgDefs.h"
#include "GifImage.h"

// 加载的图片类型
enum IMAGE_TYPE
{
	IT_BMP	= 1,
	IT_PNG	= 2,
	IT_JPG	= 3,
	IT_GIF	= 4,
};

class CResImage
{
public:
	CResImage();
	virtual ~CResImage();

	bool LoadImageFromFile(CString strPath, IMAGE_TYPE nType);
	bool LoadImageFromRes(UINT nID, IMAGE_TYPE nType);
	bool IsReady();
	Image *GetImage();
	CGifImage *GetGifImage();
	void FreeResImage();

	static IMAGE_TYPE GetImageTypeFromLocal(CString strPath);

private:
	Bitmap * LoadBmpImage(CString strPath);
	Bitmap * LoadBmpImage(UINT nBmpId);
	Image* LoadImage(CString strPath);
	Image* LoadImage(UINT nID);

private:
	bool m_bIsFromRes;
	Bitmap *m_pBmp;
	Image *m_pPngImg;
	CGifImage m_GifImg;
	HGLOBAL m_hMem;
	IMAGE_TYPE m_ImgType;
};
