#pragma once
#include "BaseDlgDefs.h"
#include "GifImage.h"

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
