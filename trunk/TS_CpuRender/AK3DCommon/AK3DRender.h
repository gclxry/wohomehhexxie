//AK 3D 渲染器类

#ifndef _AK3DRENDER_H_
#define _AK3DRENDER_H_

#include "../AKPicDrawCommon/AKPicDraw.h"
#include "../AK2DUICommon/AK2DUI.h"
#include "AK3DModelMgr.h"

class CAK3DRender
{
public:

	//重设深度缓冲(ZValue可视范围内最远处的Z坐标)
	void ResetZBuffer(float ZValue);

	//选择渲染目标
	void SelectPicDraw(CAKPicDraw *pPicDraw);

	//计算多边形是否可见
	bool IsPolygonDisplay(struct AK3D_VERTEX *v1,struct AK3D_VERTEX *v2,struct AK3D_VERTEX *v3);

	//计算多边形光强度
	float GetPolygonPower(struct AK3D_VERTEX *v1,struct AK3D_VERTEX *v2,struct AK3D_VERTEX *v3);

	//获取水平扫描线y与线段(xx1,yy1,zz1,xx2,yy2,zz2)的交点并保存在(xx,yy,zz),存在交点返回true;不存在返回false;
	//穿过两端点不算相交
	bool GetIntersection1(
		float y,
		float x1,float y1,float z1,
		float x2,float y2,float z2,
		float &xx,float &yy,float &zz
		);

	//获取水平扫描线y与线段(xx1,yy1,zz1,xx2,yy2,zz2)的交点并保存在(xx,yy,zz),存在交点返回true;不存在返回false;
	//(增加计算UV)
	//穿过两端点不算相交
	bool GetIntersection1(
		float y,
		float x1,float y1,float z1,float u1,float v1,
		float x2,float y2,float z2,float u2,float v2,
		float &xx,float &yy,float &zz,float &uu,float &vv
		);

	//获取垂直扫描线x与线段(xx1,yy1,zz1,xx2,yy2,zz2)的交点并保存在(xx,yy,zz),存在交点返回true;不存在返回false;
	//穿过两端点不算相交
	bool GetIntersection2(
		float x,
		float x1,float y1,float z1,
		float x2,float y2,float z2,
		float &xx,float &yy,float &zz
		);

	//获取垂直扫描线x与线段(xx1,yy1,zz1,xx2,yy2,zz2)的交点并保存在(xx,yy,zz),存在交点返回true;不存在返回false;
	//(增加计算UV)
	//穿过两端点不算相交
	bool GetIntersection2(
		float x,
		float x1,float y1,float z1,float u1,float v1,
		float x2,float y2,float z2,float u2,float v2,
		float &xx,float &yy,float &zz,float &uu,float &vv
		);

	//裁剪线段,可见或部分可见返回true;完成不可见返回false;裁剪结果保存在(xx1,yy1,zz1,xx2,yy2,zz2)
	bool CutOutLine(
		float x1,float y1,float z1,
		float x2,float y2,float z2,
		float &xx1,float &yy1,float &zz1,
		float &xx2,float &yy2,float &zz2
		);

	//创建线段扫描交点集
	void CreateIntersectionArray(
		float x1,float y1,float z1,
		float x2,float y2,float z2
		);

	//创建线段扫描交点集(增加计算UV)
	void CreateIntersectionArray(
		float x1,float y1,float z1,
		float x2,float y2,float z2,
		float u1,float v1,
		float u2,float v2
		);

	//渲染三角形(渲染方式1)
	void Draw1(
	struct AK3D_VERTEX *v1,//顶点1
	struct AK3D_VERTEX *v2,//顶点2
	struct AK3D_VERTEX *v3//顶点3
		);

	//渲染四边形(渲染方式1)
	void CAK3DRender::DrawRect1(
	struct AK3D_VERTEX *v1,//顶点1
	struct AK3D_VERTEX *v2,//顶点2
	struct AK3D_VERTEX *v3,//顶点3
	struct AK3D_VERTEX *v4//顶点4
		);

	//渲染三角形(渲染方式2)
	void CAK3DRender::Draw2(
	struct AK3D_VERTEX *v1,//顶点1
	struct AK3D_VERTEX *v2,//顶点2
	struct AK3D_VERTEX *v3,//顶点3
		float *uv1,//顶点UV1
		float *uv2,//顶点UV2
		float *uv3,//顶点UV3
		bool bIsUseAlpha = false//是否使用alpha通道
		);

	//渲染四边形(渲染方式2)
	void DrawRect2(
	struct AK3D_VERTEX *v1,//顶点1
	struct AK3D_VERTEX *v2,//顶点2
	struct AK3D_VERTEX *v3,//顶点3
	struct AK3D_VERTEX *v4,//顶点4
		float *uv1,//顶点UV1
		float *uv2,//顶点UV2
		float *uv3,//顶点UV3
		float *uv4,//顶点UV4
		bool bIsUseAlpha = false//是否使用alpha
		);

	//渲染模型
	void DrawModel(
	struct AK3D_MODEL *pModel,//模型
		unsigned short uRenderStyle=1//渲染方式:0=不带贴图渲染(计算反射光强);1=不带贴图渲染(计算反射光强);2=带贴图渲染(忽略反射光强);3=带贴图渲染(计算反射光强);
		);

	//对象编号数量
#define AK_3D_RENDER_MAX_COUNT 10

	//CAK3DRender对象(uID为对象编号:0~AK_3D_RENDER_MAX_COUNT)
	static CAK3DRender *GetInst(unsigned short uID=0)
	{
		static CAK3DRender AK3DRenderList[AK_3D_RENDER_MAX_COUNT];

		if(uID<AK_3D_RENDER_MAX_COUNT)return &AK3DRenderList[uID];
		else return NULL;
	}

	CAK3DRender();

	~CAK3DRender();

protected:

	//渲染目标
	CAKPicDraw *m_pPicDraw;

	//屏幕宽高
	long m_ScrWidth,m_ScrHeight;

	//////////////////////////////////////////////////////////////////
	//三角形棱边与扫描线产生的交点集合
	float *m_XArray[2];
	float *m_ZArray[2];
	float *m_UArray[2];
	float *m_VArray[2];

	//交点数量集合(指出每行的交点数量:0~2)
	unsigned char *m_pIntersectionCountArray;

	//深度缓冲
	float *m_pZBuffer;
	//////////////////////////////////////////////////////////////////
};

#endif