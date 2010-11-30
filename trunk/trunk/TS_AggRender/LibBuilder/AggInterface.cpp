
#include "AggInterface.h"

CAggInterface::CAggInterface()
{
}

CAggInterface::~CAggInterface()
{
}

bool CAggInterface::load_pmap(pixel_map &PixMapImg, const char* fn, rendering_buffer* dst, pix_format_e format, bool IsFlipY)
{
	pixel_map pmap_tmp;

	if(!pmap_tmp.load_from_bmp(fn))
		return false;

	unsigned nBpp = 0;
	switch (format)
	{
	case pix_format_bw:
		nBpp = 1;
		break;

	case pix_format_gray8:
		nBpp = 8;
		break;

	case pix_format_gray16:
		nBpp = 16;
		break;

	case pix_format_rgb565:
	case pix_format_rgb555:
		nBpp = 16;
		break;

	case pix_format_rgbAAA:
	case pix_format_bgrAAA:
	case pix_format_rgbBBA:
	case pix_format_bgrABB:
		nBpp = 32;
		break;

	case pix_format_rgb24:
	case pix_format_bgr24:
		nBpp = 24;
		break;

	case pix_format_rgb48:
	case pix_format_bgr48:
		nBpp = 48;
		break;

	case pix_format_bgra32:
	case pix_format_abgr32:
	case pix_format_argb32:
	case pix_format_rgba32:
		nBpp = 32;
		break;

	case pix_format_bgra64:
	case pix_format_abgr64:
	case pix_format_argb64:
	case pix_format_rgba64:
		nBpp = 64;
		break;
	}

	rendering_buffer rbuf_tmp;
	rbuf_tmp.attach(pmap_tmp.buf(),
		pmap_tmp.width(),
		pmap_tmp.height(),
		IsFlipY ? pmap_tmp.stride() : -pmap_tmp.stride());

	PixMapImg.create(pmap_tmp.width(), pmap_tmp.height(), org_e(nBpp), 0);

	dst->attach(PixMapImg.buf(),
		PixMapImg.width(),
		PixMapImg.height(),
		IsFlipY ? PixMapImg.stride() : -PixMapImg.stride());

	switch (format)
	{
	case pix_format_gray8:
		switch(pmap_tmp.bpp())
		{
			//case 16: color_conv(dst, &rbuf_tmp, color_conv_rgb555_to_gray8()); break;
		case 24: color_conv(dst, &rbuf_tmp, color_conv_bgr24_to_gray8()); break;
			//case 32: color_conv(dst, &rbuf_tmp, color_conv_bgra32_to_gray8()); break;
		}
		break;

	case pix_format_gray16:
		switch(pmap_tmp.bpp())
		{
			//case 16: color_conv(dst, &rbuf_tmp, color_conv_rgb555_to_gray16()); break;
		case 24: color_conv(dst, &rbuf_tmp, color_conv_bgr24_to_gray16()); break;
			//case 32: color_conv(dst, &rbuf_tmp, color_conv_bgra32_to_gray16()); break;
		}
		break;

	case pix_format_rgb555:
		switch(pmap_tmp.bpp())
		{
		case 16: color_conv(dst, &rbuf_tmp, color_conv_rgb555_to_rgb555()); break;
		case 24: color_conv(dst, &rbuf_tmp, color_conv_bgr24_to_rgb555()); break;
		case 32: color_conv(dst, &rbuf_tmp, color_conv_bgra32_to_rgb555()); break;
		}
		break;

	case pix_format_rgb565:
		switch(pmap_tmp.bpp())
		{
		case 16: color_conv(dst, &rbuf_tmp, color_conv_rgb555_to_rgb565()); break;
		case 24: color_conv(dst, &rbuf_tmp, color_conv_bgr24_to_rgb565()); break;
		case 32: color_conv(dst, &rbuf_tmp, color_conv_bgra32_to_rgb565()); break;
		}
		break;

	case pix_format_rgb24:
		switch(pmap_tmp.bpp())
		{
		case 16: color_conv(dst, &rbuf_tmp, color_conv_rgb555_to_rgb24()); break;
		case 24: color_conv(dst, &rbuf_tmp, color_conv_bgr24_to_rgb24()); break;
		case 32: color_conv(dst, &rbuf_tmp, color_conv_bgra32_to_rgb24()); break;
		}
		break;

	case pix_format_bgr24:
		switch(pmap_tmp.bpp())
		{
		case 16: color_conv(dst, &rbuf_tmp, color_conv_rgb555_to_bgr24()); break;
		case 24: color_conv(dst, &rbuf_tmp, color_conv_bgr24_to_bgr24()); break;
		case 32: color_conv(dst, &rbuf_tmp, color_conv_bgra32_to_bgr24()); break;
		}
		break;

	case pix_format_rgb48:
		switch(pmap_tmp.bpp())
		{
			//case 16: color_conv(dst, &rbuf_tmp, color_conv_rgb555_to_rgb48()); break;
		case 24: color_conv(dst, &rbuf_tmp, color_conv_bgr24_to_rgb48()); break;
			//case 32: color_conv(dst, &rbuf_tmp, color_conv_bgra32_to_rgb48()); break;
		}
		break;

	case pix_format_bgr48:
		switch(pmap_tmp.bpp())
		{
			//case 16: color_conv(dst, &rbuf_tmp, color_conv_rgb555_to_bgr48()); break;
		case 24: color_conv(dst, &rbuf_tmp, color_conv_bgr24_to_bgr48()); break;
			//case 32: color_conv(dst, &rbuf_tmp, color_conv_bgra32_to_bgr48()); break;
		}
		break;

	case pix_format_abgr32:
		switch(pmap_tmp.bpp())
		{
		case 16: color_conv(dst, &rbuf_tmp, color_conv_rgb555_to_abgr32()); break;
		case 24: color_conv(dst, &rbuf_tmp, color_conv_bgr24_to_abgr32()); break;
		case 32: color_conv(dst, &rbuf_tmp, color_conv_bgra32_to_abgr32()); break;
		}
		break;

	case pix_format_argb32:
		switch(pmap_tmp.bpp())
		{
		case 16: color_conv(dst, &rbuf_tmp, color_conv_rgb555_to_argb32()); break;
		case 24: color_conv(dst, &rbuf_tmp, color_conv_bgr24_to_argb32()); break;
		case 32: color_conv(dst, &rbuf_tmp, color_conv_bgra32_to_argb32()); break;
		}
		break;

	case pix_format_bgra32:
		switch(pmap_tmp.bpp())
		{
		case 16:
			color_conv(dst, &rbuf_tmp, color_conv_rgb555_to_bgra32());
			break;

		case 24:
			color_conv(dst, &rbuf_tmp, color_conv_bgr24_to_bgra32());
			break;

		case 32:
			color_conv(dst, &rbuf_tmp, color_conv_bgra32_to_bgra32());
			break;
		}
		break;

	case pix_format_rgba32:
		switch(pmap_tmp.bpp())
		{
		case 16:
			color_conv(dst, &rbuf_tmp, color_conv_rgb555_to_rgba32());
			break;
		case 24:
			color_conv(dst, &rbuf_tmp, color_conv_bgr24_to_rgba32());
			break;
		case 32:
			color_conv(dst, &rbuf_tmp, color_conv_bgra32_to_rgba32());
			break;
		}
		break;

	case pix_format_abgr64:
		switch(pmap_tmp.bpp())
		{
			//case 16: color_conv(dst, &rbuf_tmp, color_conv_rgb555_to_abgr64()); break;
		case 24: color_conv(dst, &rbuf_tmp, color_conv_bgr24_to_abgr64()); break;
			//case 32: color_conv(dst, &rbuf_tmp, color_conv_bgra32_to_abgr64()); break;
		}
		break;

	case pix_format_argb64:
		switch(pmap_tmp.bpp())
		{
			//case 16: color_conv(dst, &rbuf_tmp, color_conv_rgb555_to_argb64()); break;
		case 24: color_conv(dst, &rbuf_tmp, color_conv_bgr24_to_argb64()); break;
			//case 32: color_conv(dst, &rbuf_tmp, color_conv_bgra32_to_argb64()); break;
		}
		break;

	case pix_format_bgra64:
		switch(pmap_tmp.bpp())
		{
			//case 16: color_conv(dst, &rbuf_tmp, color_conv_rgb555_to_bgra64()); break;
		case 24: color_conv(dst, &rbuf_tmp, color_conv_bgr24_to_bgra64()); break;
			//case 32: color_conv(dst, &rbuf_tmp, color_conv_bgra32_to_bgra64()); break;
		}
		break;

	case pix_format_rgba64:
		switch(pmap_tmp.bpp())
		{
			//case 16: color_conv(dst, &rbuf_tmp, color_conv_rgb555_to_rgba64()); break;
		case 24: color_conv(dst, &rbuf_tmp, color_conv_bgr24_to_rgba64()); break;
			//case 32: color_conv(dst, &rbuf_tmp, color_conv_bgra32_to_rgba64()); break;
		}
		break;
	}

	return true;
}

HANDLE CAggInterface::CreatePixelMap(HBITMAP hBitmap, pixel_map &PixMap, rendering_buffer &RenderBuf)
{
	// 位图中每个像素所占字节数
	WORD wBitsCount = 0;
	// 调色板大小
	DWORD dwPalettelSize = 0;
	DWORD dwBmdibitSize = 0;
	// 定义了位图的各种的信息
	BITMAP bmp;
	// 定义了大小、类型等BMP文件的信息
	BITMAPINFOHEADER BmpInfoHead;
	LPBITMAPINFOHEADER lpBmpInfoHead = NULL;
	HANDLE hFdib = NULL;

	// 得到BITMAP结构。
	int nRet = ::GetObject(hBitmap, sizeof(BITMAP), (void *)&bmp);
	if (nRet != 0)
	{
		// 以下代码是用BITMAP的信息填充BITMAPINFOHEADER结构
		wBitsCount = bmp.bmBitsPixel;
		BmpInfoHead.biSize = sizeof(BITMAPINFOHEADER);
		BmpInfoHead.biWidth = bmp.bmWidth;
		BmpInfoHead.biHeight = bmp.bmHeight;
		BmpInfoHead.biPlanes = 1;
		BmpInfoHead.biBitCount = wBitsCount;
		BmpInfoHead.biClrImportant=0;
		BmpInfoHead.biClrUsed = 0;
		BmpInfoHead.biCompression = BI_RGB;
		BmpInfoHead.biSizeImage=0;
		BmpInfoHead.biYPelsPerMeter=0;
		BmpInfoHead.biXPelsPerMeter=0;

		// 以下代码是获取调色板的长度，调色板现在的用处很少，因为256色的位图已经不多了
		if(wBitsCount <= 8)
			dwPalettelSize = (1 << wBitsCount)*sizeof(RGBQUAD);

		// 计算位图的大小，并分配相应的内存空间，注意的是没有分配BITMAPFILEHEADER
		dwBmdibitSize=((bmp.bmWidth*wBitsCount+31)/8)*bmp.bmHeight;
		int nLen = dwBmdibitSize + dwPalettelSize + sizeof(BITMAPINFOHEADER);
		if (nLen > 0)
		{
			hFdib = GlobalAlloc(GHND, nLen);
			if (IS_SAVE_HANDLE(hFdib))
			{
				lpBmpInfoHead = (LPBITMAPINFOHEADER)::GlobalLock(hFdib);
				if (lpBmpInfoHead != NULL)
				{
					// 将BmpInfoHead中的数据写入分配的内存中
					*lpBmpInfoHead = BmpInfoHead;
					HDC hdc=::GetDC(NULL);
					BYTE *pData = (BYTE*)((LPSTR)lpBmpInfoHead + sizeof(BITMAPINFOHEADER) + dwPalettelSize);
					nRet = ::GetDIBits(hdc, hBitmap, 0, (UINT)bmp.bmHeight, pData, (BITMAPINFO *)lpBmpInfoHead, DIB_RGB_COLORS);
					if (nRet > 0)
					{
						PixMap.attach_to_bmp((BITMAPINFO *)lpBmpInfoHead);
						RenderBuf.attach(PixMap.buf(), PixMap.width(), PixMap.height(), PixMap.stride());
					}

					::GlobalUnlock(hFdib);
				}
				//	::GlobalFree(hFdib);
			}
		}
	}

	return hFdib;
}

void CAggInterface::ClosePixelMap(HANDLE &hGMem)
{
	if (IS_SAVE_HANDLE(hGMem))
	{
		::GlobalFree(hGMem);
		hGMem = NULL;
	}
}

bool CAggInterface::CreatePixelMap(pixel_map &OutPixImg, rendering_buffer &OutBuf,
								   unsigned unWidth, unsigned unHeight, org_e org, unsigned unClearVal)
{
	OutPixImg.create(unWidth, unHeight, org, unClearVal);
	OutBuf.attach(OutPixImg.buf(), OutPixImg.width(), OutPixImg.height(), OutPixImg.stride());

	return (OutBuf.height() > 0 && OutBuf.width() > 0);
}

void CAggInterface::ClosePixelMap(pixel_map &OutPixImg)
{
	OutPixImg.clear();
}
