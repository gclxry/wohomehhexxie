
#include "stdafx.h"
#include "AggDraw2DTo3D.h"

CAggDraw2DTo3D::CAggDraw2DTo3D()
{
}

CAggDraw2DTo3D::~CAggDraw2DTo3D()
{
}

bool CAggDraw2DTo3D::load_pmap(const char* fn, unsigned idx, rendering_buffer* dst)
{
	pixel_map pmap_tmp;

	if(!pmap_tmp.load_from_bmp(fn))
		return false;

	rendering_buffer rbuf_tmp;
	rbuf_tmp.attach(pmap_tmp.buf(),
		pmap_tmp.width(),
		pmap_tmp.height(),
		m_flip_y ?
		pmap_tmp.stride() :
	-pmap_tmp.stride());

	m_pmap_img[idx].create(pmap_tmp.width(), 
		pmap_tmp.height(), 
		org_e(m_bpp),
		0);

	dst->attach(m_pmap_img[idx].buf(),
		m_pmap_img[idx].width(),
		m_pmap_img[idx].height(),
		m_flip_y ?
		m_pmap_img[idx].stride() :
	-m_pmap_img[idx].stride());

	switch(m_format)
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
		case 16: color_conv(dst, &rbuf_tmp, color_conv_rgb555_to_bgra32()); break;
		case 24: color_conv(dst, &rbuf_tmp, color_conv_bgr24_to_bgra32()); break;
		case 32: color_conv(dst, &rbuf_tmp, color_conv_bgra32_to_bgra32()); break;
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

