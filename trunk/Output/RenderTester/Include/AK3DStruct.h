//AK3D 数据结构

#define NAME_MAX_LEN 24

#include "AKList.h"

//AK3D 顶点结构
struct AK3D_VERTEX
{
	//顶点坐标
	float x,y,z;

	//骨骼控制顶点结构列表(每一个元素包含一个 struct AK3D_BONES_CTRL * 指针)
	CAKList BonesCtrlList;

	//目标顶点坐标
	float xDest,yDest,zDest;
};

//AK3D 骨骼结构
struct AK3D_BONES
{
	//骨骼帧列表(每一个元素包含一个 struct AK3D_BONES_FRAME * 指针),列表里面每个帧对应该着一个骨骼矩阵版本
	CAKList FrameList;

	//当前骨骼帧地址
	struct AK3D_BONES_FRAME *pCurBonesFrame;

	//当前骨骼帧版本的目标矩阵(直接用于骨骼动画顶点变换)
	float DestMatrix[4*4];

	//父骨骼结构
	struct AK3D_BONES *pFather;

	//子骨骼结构列表(每一个元素包含一个 struct AK3D_BONES * 指针)
	CAKList SonList;

	//骨骼唯一名称
	char Name[NAME_MAX_LEN+1];

	//骨骼唯一编号
	unsigned long uID;

	//焦点
	float xFocus,yFocus,zFocus;
};

//AK3D 骨骼控制顶点结构
struct AK3D_BONES_CTRL
{
	//顶点受控权值
	float Power;

	//骨骼
	struct AK3D_BONES *pBones;
};

//AK3D 骨骼帧结构
struct AK3D_BONES_FRAME
{
	//起始帧(>=0)
	unsigned long uStartFrame;

	//骨骼矩阵
	float Matrix[4*4];

	//目标矩阵(直接作用于顶点)
	float DestMatrix[4*4];

	//上级骨骼帧结构(对应同一帧)
	struct AK3D_BONES_FRAME *pFrontFrame;
};
