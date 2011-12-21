//AK3D 骨骼管理类
#ifndef _AK3DBONESMGR_H_
#define _AK3DBONESMGR_H_

#include "AK3DStruct.h"
#include "Matrix4X4Mgr.h"

class CAK3DBonesMgr
{
public:

	//获取最大帧值
	unsigned long GetMaxFrame();

	//设置当前骨骼树帧版本(uFrame为当前播放的帧数)
	void SetPlayFrame(unsigned long uFrame);

	//查找骨骼捆绑结构
	struct AK3D_BONES_CTRL * FindBonesCtrl(struct AK3D_VERTEX *pVertex,struct AK3D_BONES *pBones);

	//删除顶点和骨骼的捆绑
	void RemoveBonesCtrl(struct AK3D_VERTEX *pVertex,struct AK3D_BONES *pBones);

	//创建骨骼帧列表元素
	bool CreateBonesTreeListElement(unsigned long uStartFrame);

	//骨骼树帧列表排序
	void TaxisBonesTreeFrameList();

	//创建顶点和骨骼捆绑
	struct AK3D_BONES_CTRL * CreateBonesCtrl(struct AK3D_VERTEX *pVertex,struct AK3D_BONES *pBones,float Power);

	//更新所有骨骼最终作用矩阵,使最终作用于顶点的矩阵生效
	void UpdateBonesTreeMatrix();

	//骨骼帧列表排序(按起始帧数从小到大排序)
	void TaxisBonesFrame(struct AK3D_BONES *pBones);

	//删除骨骼帧
	void RemoveBonesFrame(struct AK3D_BONES *pBones,unsigned long uStartFrame);

	//查找骨骼关键帧
	struct AK3D_BONES_FRAME * FindBonesFrame(struct AK3D_BONES *pBones,unsigned long uStartFrame);

	//创建帧(所有骨骼都增加一个uStartFrame骨骼帧)
	bool CreateFrame(unsigned long uStartFrame);

	//删除帧(所有骨骼都删除一个uStartFrame骨骼帧)
	void RemoveFrame(unsigned long uStartFrame);

	//删除骨骼
	void RemoveBones(struct AK3D_BONES *pBones);

	//删除整棵骨骼树
	void RemoveAll();

	//检查骨骼pBones1与骨骼pBones2的关系,
	/*返回:
	0=没有上下级关系;
	1=pBones1是pBones2的上级;
	2=pBones2是pBones1的上级;
	3=两者是相同的;
	*/
	short CheckBones(struct AK3D_BONES *pBones1,struct AK3D_BONES *pBones2);

	//子骨骼pSonBones连接到父骨骼pFatherBones
	bool JoinBones(struct AK3D_BONES *pSonBones,struct AK3D_BONES *pFatherBones);

	//获取空闲骨骼唯一ID
	unsigned long GetFreeID();

	//查找骨骼(通过唯一ID)
	struct AK3D_BONES * FindBones(unsigned long uID);

	//查找骨骼(通过唯一名称)
	struct AK3D_BONES * CAK3DBonesMgr::FindBones(char *pName);

	//创建骨骼
	struct AK3D_BONES * CreateBones();

	CAK3DBonesMgr();

	~CAK3DBonesMgr();

public:

	//根骨骼列表
	CAKList m_RootBonesList;

	//骨骼树帧列表(每个元素代表一个帧数)
	CAKList m_BonesTreeFrameList;
};

#endif