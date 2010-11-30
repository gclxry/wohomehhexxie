
#include "AggDraw2DTo3D.h"

CAggDraw2DTo3D::CAggDraw2DTo3D()
{
}

CAggDraw2DTo3D::~CAggDraw2DTo3D()
{
}

// ��2Dͼ����3D��ʽչ��
// DstImgBuf����Ⱦ���Ŀ��ͼ������
// SrcImgBuf����Ҫ������Ⱦ������
// vP����Ⱦ���ĸ����㣬�������������DstImgBufͼƬ������
// ˳����-> 0[����] 1[����] 2[����] 3[����]
void CAggDraw2DTo3D::Draw2DTo3D(rendering_buffer &DstImgBuf, rendering_buffer &SrcImgBuf, CPoint vP[4])
{
	// agg �̶�������
	// 1.����Դ (Vertex Source)
	// 2.����ת���ܵ� (Coordinate conversion pipeline)
	// 3.ˮƽɨ���߹�դ(Scanline Rasterizer)
	// 4.��Ⱦ��(Renderers)
	// 5.��Ⱦ����(Rendering Buffer)

	// agg ���Ͷ���
	typedef agg::pixfmt_bgra32 pixfmt;
	typedef agg::pixfmt_bgra32_pre pixfmt_pre;
	typedef agg::renderer_base<pixfmt_pre> renderer_base_pre;
	typedef agg::renderer_base<pixfmt> renderer_base;
	typedef pixfmt::color_type color_type;
	typedef agg::image_accessor_clone<pixfmt> img_accessor_type;
	typedef agg::span_interpolator_trans<agg::trans_perspective> interpolator_type;
	typedef agg::span_image_filter_rgba_2x2<img_accessor_type, interpolator_type> span_gen_type;
	// ɫ�β�ֵ����
	typedef agg::span_interpolator_trans<agg::trans_perspective> interpolator_type;
	// ɫ�δ�����
	typedef agg::span_image_filter_rgba_2x2<img_accessor_type, interpolator_type> span_gen_type;


	//----------------------------------------
	// �����в���Ⱦ�������
	pixfmt            OutPixf(DstImgBuf);
	// ��ǿ���в���Ⱦ�������
	pixfmt_pre        OutPixfPre(DstImgBuf);
	// �����в���Ⱦ���������������
	renderer_base     OutBaseRender(OutPixf);
	// ��ǿ���в���Ⱦ��
	renderer_base_pre OutPreRender(OutPixfPre);

	// �������
	OutBaseRender.clear(agg::rgba(0.0, 1, 1, 0.0));

	//----------------------------------------
	agg::interactive_polygon Polygon4(4, 0.0);

	int nDstW = DstImgBuf.width();
	int nDstH = DstImgBuf.height();

	Polygon4.xn(0) = vP[0].x;
	Polygon4.yn(0) = nDstW - vP[0].y;
	Polygon4.xn(1) = vP[1].x;
	Polygon4.yn(1) = nDstW - vP[1].y;
	Polygon4.xn(2) = vP[2].x;
	Polygon4.yn(2) = nDstW - vP[2].y;
	Polygon4.xn(3) = vP[3].x;
	Polygon4.yn(3) = nDstW - vP[3].y;

	//-------------------------------------------------
	// ��ɨ�迹��ݹ�դ������
	agg::rasterizer_scanline_aa<> AaRasterizer;
	// ɫ������
	agg::scanline_u8  U8Scanline;
	AaRasterizer.add_path(Polygon4);
	AaRasterizer.clip_box(0, 0, DstImgBuf.width(), DstImgBuf.height());
	AaRasterizer.reset();
	AaRasterizer.move_to_d(Polygon4.xn(0), Polygon4.yn(0));
	AaRasterizer.line_to_d(Polygon4.xn(1), Polygon4.yn(1));
	AaRasterizer.line_to_d(Polygon4.xn(2), Polygon4.yn(2));
	AaRasterizer.line_to_d(Polygon4.xn(3), Polygon4.yn(3));


	//------------------------------------------------------------------------
	// �߶η�����
	agg::span_allocator<color_type> SaAlloc;
	// ˫���Բ�ֵ���˲���
	agg::image_filter_bilinear FilterKernel;
	// �˲���������
	agg::image_filter_lut FilterLut(FilterKernel, false);

	// ��ȾԴ
	pixfmt PixfSrcImg(SrcImgBuf);
	// ͼƬ��������¡
	typedef agg::image_accessor_clone<pixfmt> img_accessor_type;
	// ��ȾԴ������
	img_accessor_type ImgAcc(PixfSrcImg);

	// Զ����Ⱦ���������ı��� -> ����
	agg::trans_perspective PerspectiveTranser(Polygon4.polygon(), 0.0, 0.0, SrcImgBuf.width(), SrcImgBuf.height());
	if(PerspectiveTranser.is_valid())
	{
		// Զ����Ⱦɫ�β�ֵ��������У������
		interpolator_type InterpolatorType(PerspectiveTranser);
		// ɫ�δ�����
		span_gen_type SaGen(ImgAcc, InterpolatorType, FilterLut);

		// ������
		// Rasterizer����դ������
		// Scanline��span����
		// BaseRenderer����Ⱦ��
		// SpanAllocator���߶η�����
		// SpanGenerator��ָ���㷨��ɫ�δ�����

		// �������Ⱦ����SaGenͨ��SaAlloc��Ⱦ��OutPreRender��
		agg::render_scanlines_aa(AaRasterizer, U8Scanline, OutPreRender, SaAlloc, SaGen);
	}
}
