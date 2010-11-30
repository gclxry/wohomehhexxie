
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

void CAggInterface::CreatePixelMap(HBITMAP hBitmap, pixel_map &PixMap, rendering_buffer &RenderBuf)
{
	// 位图中每个像素所占字节数。 
	WORD wbitsCount = 0;
	// 调色板大小 
	DWORD dwpalettelsize = 0;
	DWORD dwbmdibitsize = 0; 
	// 定义了位图的各种的信息。 
	BITMAP bitmap;
	// 定义了大小、类型等BMP文件的信息。 
	BITMAPINFOHEADER bi; 
	LPBITMAPINFOHEADER lpbi; 
	HANDLE fdib;

	// 得到BITMAP结构。
	::GetObject(hBitmap, sizeof(BITMAP), (void *)&bitmap);

	// 以下代码是用BITMAP的信息填充BITMAPINFOHEADER结构 
	wbitsCount = bitmap.bmBitsPixel; 
	bi.biSize = sizeof(BITMAPINFOHEADER); 
	bi.biWidth = bitmap.bmWidth; 
	bi.biHeight = bitmap.bmHeight; 
	bi.biPlanes = 1; 
	bi.biBitCount = wbitsCount;
	bi.biClrImportant=0; 
	bi.biClrUsed=0; 
	bi.biCompression=BI_RGB; 
	bi.biSizeImage=0; 
	bi.biYPelsPerMeter=0; 
	bi.biXPelsPerMeter=0; 

	// 以下代码是获取调色板的长度，调色板现在的用处很少，因为256色的位图已经不多了。 
	if(wbitsCount <= 8)
		dwpalettelsize = (1 << wbitsCount)*sizeof(RGBQUAD);

	// 计算位图的大小，并分配相应的内存空间，注意的是没有分配BITMAPFILEHEADER。 
	dwbmdibitsize=((bitmap.bmWidth*wbitsCount+31)/8)*bitmap.bmHeight; 
	int nLen = dwbmdibitsize + dwpalettelsize + sizeof(BITMAPINFOHEADER);
	fdib = GlobalAlloc(GHND, nLen); 
	lpbi = (LPBITMAPINFOHEADER)::GlobalLock(fdib); 
	// 将bi中的数据写入分配的内存中。 
	*lpbi = bi;
	HDC hdc=::GetDC(NULL); 
	BYTE *pData = (BYTE*)((LPSTR)lpbi + sizeof(BITMAPINFOHEADER) + dwpalettelsize);
	int nRet = ::GetDIBits(hdc, hBitmap, 0, (UINT)bitmap.bmHeight, pData, (BITMAPINFO *)lpbi, DIB_RGB_COLORS); 
	// GetDIBits是最重要的函数，真正获得位图数据的工作就由它完成，它第一个参数为HDC,第二个参数为位图句柄，
	// 第三个参数为扫描行的开始行，一般为0，第四个为结束行，一般就是高度，第四个参数最重要，它表示接收数据的起始地址，
	// 这个地址一般是在调色板之后。第五个参数指的是接收BITMAPINFO结构的地址，这个结构上面没有写，它其实就是BITMAPINFO结构加上调色板信息。
	// 最后一个参数是格式。一般是DIB_RGB_COLORS

	PixMap.attach_to_bmp((BITMAPINFO *)lpbi);
	RenderBuf.attach(PixMap.buf(), PixMap.width(), PixMap.height(), PixMap.stride());

	// 关闭相关句柄
	::GlobalUnlock(fdib);
//	::GlobalFree(fdib);
}
