//AK3D 模型管理类
#ifndef _AK3DMODELMGR_H_
#define _AK3DMODELMGR_H_

#include "AK3DBonesMgr.h"
#include "AK2DUI.h"

//AK3D 多边形结构
struct AK3D_POLYGON
{
	//顶点数量(3或4)
	unsigned char uVertexCount;

	//顶点指针数组
	struct AK3D_VERTEX *pVertexList[4];

	//顶点UV数组
	float UVList[4][2];

	//多边形颜色
	unsigned char r,g,b;
};

//AK3D 模型结构
struct AK3D_MODEL
{
	//模型ID
	unsigned long uID;

	//顶点表(每个元素包含一个 struct AK3D_VERTEX * 指针)
	CAKList VertexList;

	//多边形表(每个元素包含一个 struct AK3D_POLYGON * 指针)
	CAKList PolygonList;

	//贴图
	struct AK_2D_UI_PIC *pUIPic;

	//焦点坐标(模型减去此坐标,则对齐坐标系原点,例如将焦点定为人物脚掌位置,当减去此焦点后,人物全身将以脚掌对齐坐标系原点)
	float xFocus,yFocus,zFocus;

	//目标变换矩阵
	float DestMatrix[4*4];

	//骨骼管理对象
	CAK3DBonesMgr BonesMgr;
};

class CAK3DModelMgr
{
public:

	//设置模型目标矩阵
	void SetModelMatrix(struct AK3D_MODEL *pModel,float *pMatrix);

	//刷新模型显示数据(例如在调用SetModelMatrix函数之后,应该调用此函数)
	void UpdateModel(struct AK3D_MODEL *pModel);

	//创建顶点
	struct AK3D_VERTEX *CreateVertex(
	struct AK3D_MODEL *pModel,//模型
		float x,float y,float z//顶点
		);

	//查找顶点地址(根据位于顶点表的位置,位置从0开始)
	struct AK3D_VERTEX *FindVertex(
	struct AK3D_MODEL *pModel,//模型
		unsigned long uPos//位于顶点表的位置(>=0)
		);

	//查找顶点位置的值+1;0=没有找到
	unsigned long GetVertexPos(
	struct AK3D_MODEL *pModel,//模型
	struct AK3D_VERTEX *pVertex//顶点地址
		);

	//创建多边形
	struct AK3D_POLYGON *CreatePolygon(
	struct AK3D_MODEL *pModel,//模型
		unsigned char uCount,//顶点数量(3或4)
		unsigned long uPos1,//顶点位置1
		unsigned long uPos2,//顶点位置2
		unsigned long uPos3,//顶点位置3
		unsigned long uPos4=0//顶点位置4
		);

	//创建模型
	struct AK3D_MODEL *CreateModel(
		unsigned long uID//模型ID
		);
	
	//查找模型
	struct AK3D_MODEL *FindModel(
		unsigned long uID//模型ID
		);

	//随机修改模型顶点
	void RandomModifModelVertex(
	struct AK3D_MODEL *pModel,
		long dx,//X方向修改范围
		long dy,//Y方向修改范围
		long dz//Z方向修改范围
		);

	//创建立方体(盒子)
	struct AK3D_MODEL *CreateModel_Box(
		unsigned long uID,//模型ID
		float x,float y,float z,//左上角坐标
		float width,float length,float height//宽长高
		);

	//创建立方体(网格)
	struct AK3D_MODEL *CreateModel_Gridding(
		unsigned long uID,//模型ID
		float x,float y,float z,//左上角坐标
		float width,float length,//宽长
		long rows,long cols//网络行列数
		);

	CAK3DModelMgr();

	~CAK3DModelMgr();

	static CAK3DModelMgr & GetSingle()
	{
		static CAK3DModelMgr Single;
		return Single;
	}

protected:

	//模型列表(每个元素包含一个 struct AK3D_MODEL * 指针)
	CAKList m_ModelList;
};

#endif