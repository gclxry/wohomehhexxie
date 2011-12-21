
#include "AggDraw2DTo3D.h"

CAggDraw2DTo3D::CAggDraw2DTo3D()
{
}

CAggDraw2DTo3D::~CAggDraw2DTo3D()
{
}

// 将2D图像以3D形式展现
// DstImgBuf：渲染后的目标图像数据
// SrcImgBuf：需要进行渲染的数据
// vP：渲染的四个顶点，此坐标是相对于DstImgBuf图片的坐标
// 顺序是-> 0[左下] 1[右下] 2[右上] 3[左上]
void CAggDraw2DTo3D::Draw2DTo3D(rendering_buffer &DstImgBuf, rendering_buffer &SrcImgBuf, CPoint vP[4])
{
	// agg 固定处理步骤
	// 1.顶点源 (Vertex Source)
	// 2.坐标转换管道 (Coordinate conversion pipeline)
	// 3.水平扫描线光栅(Scanline Rasterizer)
	// 4.渲染器(Renderers)
	// 5.渲染缓存(Rendering Buffer)

	// agg 类型定义
	typedef agg::pixfmt_bgra32 pixfmt;
	typedef agg::pixfmt_bgra32_pre pixfmt_pre;
	typedef agg::renderer_base<pixfmt_pre> renderer_base_pre;
	typedef agg::renderer_base<pixfmt> renderer_base;
	typedef pixfmt::color_type color_type;
	typedef agg::image_accessor_clone<pixfmt> img_accessor_type;
	typedef agg::span_interpolator_trans<agg::trans_perspective> interpolator_type;
	typedef agg::span_image_filter_rgba_2x2<img_accessor_type, interpolator_type> span_gen_type;
	// 色段插值服务
	typedef agg::span_interpolator_trans<agg::trans_perspective> interpolator_type;
	// 色段创建器
	typedef agg::span_image_filter_rgba_2x2<img_accessor_type, interpolator_type> span_gen_type;


	//----------------------------------------
	// 基本中层渲染结果缓存
	pixfmt            OutPixf(DstImgBuf);
	// 加强型中层渲染结果缓存
	pixfmt_pre        OutPixfPre(DstImgBuf);
	// 基本中层渲染器，用于清除背景
	renderer_base     OutBaseRender(OutPixf);
	// 加强型中层渲染器
	renderer_base_pre OutPreRender(OutPixfPre);

	// 清除背景
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
	// 行扫描抗锯齿光栅控制器
	agg::rasterizer_scanline_aa<> AaRasterizer;
	// 色段类型
	agg::scanline_u8  U8Scanline;
	AaRasterizer.add_path(Polygon4);
	AaRasterizer.clip_box(0, 0, DstImgBuf.width(), DstImgBuf.height());
	AaRasterizer.reset();
	AaRasterizer.move_to_d(Polygon4.xn(0), Polygon4.yn(0));
	AaRasterizer.line_to_d(Polygon4.xn(1), Polygon4.yn(1));
	AaRasterizer.line_to_d(Polygon4.xn(2), Polygon4.yn(2));
	AaRasterizer.line_to_d(Polygon4.xn(3), Polygon4.yn(3));


	//------------------------------------------------------------------------
	// 线段分配器
	agg::span_allocator<color_type> SaAlloc;
	// 双线性插值法滤波器
	agg::image_filter_bilinear FilterKernel;
	// 滤波器控制器
	agg::image_filter_lut FilterLut(FilterKernel, false);

	// 渲染源
	pixfmt PixfSrcImg(SrcImgBuf);
	// 图片访问器克隆
	typedef agg::image_accessor_clone<pixfmt> img_accessor_type;
	// 渲染源访问器
	img_accessor_type ImgAcc(PixfSrcImg);

	// 远景渲染服务器，四边形 -> 矩形
	agg::trans_perspective PerspectiveTranser(Polygon4.polygon(), 0.0, 0.0, SrcImgBuf.width(), SrcImgBuf.height());
	if(PerspectiveTranser.is_valid())
	{
		// 远景渲染色段插值服务器，校对类型
		interpolator_type InterpolatorType(PerspectiveTranser);
		// 色段创建器
		span_gen_type SaGen(ImgAcc, InterpolatorType, FilterLut);

		// 参数：
		// Rasterizer：光栅控制器
		// Scanline：span容器
		// BaseRenderer：渲染器
		// SpanAllocator：线段分配器
		// SpanGenerator：指定算法的色段创建器

		// 抗锯齿渲染，把SaGen通过SaAlloc渲染到OutPreRender上
		agg::render_scanlines_aa(AaRasterizer, U8Scanline, OutPreRender, SaAlloc, SaGen);
	}
}
