#include "stdafx.h"

#include "AK3DBonesMgr.h"

CAK3DBonesMgr::CAK3DBonesMgr()
{
	m_RootBonesList.SetAutoFreeValue(false);
	m_BonesTreeFrameList.SetAutoFreeValue(false);
}

CAK3DBonesMgr::~CAK3DBonesMgr()
{
	RemoveAll();
}

unsigned long CAK3DBonesMgr::GetFreeID()
{
	unsigned long i;

	for(i=1;i<=4294967295;++i)
	{
		if(!FindBones(i))
		{
			return i;
		}
	}

	return 0;
}

struct AK3D_BONES * CAK3DBonesMgr::CreateBones()
{
	struct AK3D_BONES *pNew=new struct AK3D_BONES;
	if(!pNew)return NULL;

	/*memset(pNew->Matrix,0,sizeof(float)*4*4);
	pNew->Matrix[0]=1;
	pNew->Matrix[5]=1;
	pNew->Matrix[10]=1;
	pNew->Matrix[15]=1;*/
	
	pNew->xFocus=0;
	pNew->yFocus=0;
	pNew->zFocus=0;

	pNew->pCurBonesFrame=NULL;

	CMatrix4X4Mgr::GetSingle().SetIdentityMatrix(pNew->DestMatrix);

	strcpy(pNew->Name,"");

	pNew->pFather=NULL;

	pNew->SonList.SetAutoFreeValue(false);

	pNew->uID=GetFreeID();
	if(pNew->uID==0)
	{
		delete pNew;
		return NULL;
	}

	bool rt=m_RootBonesList.AddTail(pNew);
	if(!rt)
	{
		delete pNew;
		return NULL;
	}

	return pNew;
}

/*返回:
0=没有上下级关系;
1=pBones1是pBones2的上级;
2=pBones2是pBones1的上级;
3=两者是相同的;
*/
short CAK3DBonesMgr::CheckBones(struct AK3D_BONES *pBones1,struct AK3D_BONES *pBones2)
{
	if(pBones1==pBones2)return 3;

	struct AK3D_BONES *pBones;

	pBones=pBones1->pFather;
	while(pBones)
	{
		if(pBones==pBones2)return 2;

		//上一个
		pBones=pBones->pFather;
	}

	pBones=pBones2->pFather;
	while(pBones)
	{
		if(pBones==pBones1)return 1;

		//上一个
		pBones=pBones->pFather;
	}

	return 0;

}

bool CAK3DBonesMgr::JoinBones(struct AK3D_BONES *pSonBones,struct AK3D_BONES *pFatherBones)
{
	if(pFatherBones)
	{
		switch(CheckBones(pSonBones,pFatherBones))
		{
		case 3:return false;//骨骼是相同的;
		case 1:return false;//子骨骼不能是父骨骼的上级;
		}
	}

	AK_POS_PTR pos;
	struct AK3D_BONES *pBones;
	CAKList *pSonList;

	//脱离
	if(pSonBones->pFather)//子骨骼
	{
		pSonList=&pSonBones->pFather->SonList;
		pos=pSonList->GetHeadPos();
		while(pos)
		{
			pBones=(struct AK3D_BONES *)pSonList->GetValue(pos);
			if(pBones==pSonBones)
			{
				//脱离
				pSonList->Remove(pos);
				break;
			}

			//下一个
			pSonList->Next(&pos);
		}
	}
	else//根骨骼
	{
		pos=m_RootBonesList.GetHeadPos();
		while(pos)
		{
			pBones=(struct AK3D_BONES *)m_RootBonesList.GetValue(pos);
			if(pBones==pSonBones)
			{
				//脱离
				m_RootBonesList.Remove(pos);
				break;
			}

			//下一个
			m_RootBonesList.Next(&pos);
		}
	}
	//骨骼帧列表脱离
	CAKList *pList=&pSonBones->FrameList;
	pos=pList->GetHeadPos();
	while(pos)
	{
		struct AK3D_BONES_FRAME *pFrame=(struct AK3D_BONES_FRAME *)pList->GetValue(pos);

		if(pFatherBones)pFrame->pFrontFrame=FindBonesFrame(pFatherBones,pFrame->uStartFrame);
		else pFrame->pFrontFrame=NULL;

		//下一个
		pList->Next(&pos);
	}

	//连接
	if(pFatherBones)
	{
		pFatherBones->SonList.AddTail(pSonBones);
	}
	else
	{
		m_RootBonesList.AddTail(pSonBones);
	}
	pSonBones->pFather=pFatherBones;

	return true;
}

unsigned long CAK3DBonesMgr::GetMaxFrame()
{
	//不存在骨骼帧
	if(m_BonesTreeFrameList.GetCount()==0)return 0;

	//获取最大帧值
	unsigned long uMaxFrame=(unsigned long)m_BonesTreeFrameList.GetValue(m_BonesTreeFrameList.GetTailPos());

	return uMaxFrame;
}

void CAK3DBonesMgr::SetPlayFrame(unsigned long uFrame)
{
	//不存在骨骼帧
	if(m_BonesTreeFrameList.GetCount()==0)return;

	//获取最大帧值
	unsigned long uMaxFrame=GetMaxFrame();

	//要求设置的帧值不存在
	if(uFrame>uMaxFrame)return;

	struct AK3D_BONES *pBones,*pReturnBones=NULL;
	AK_POS_PTR pos,pos2,posRemove;
	AK_POS_PTR pos3;

	//遍历骨骼树时使用的临时栈
	CAKList TmpBonesList;
	TmpBonesList.SetAutoFreeValue(false);

	//获取取所有根骨骼,并添加到临时栈
	pos=m_RootBonesList.GetHeadPos();
	while(pos)
	{
		//添加到临时栈
		TmpBonesList.AddTail(m_RootBonesList.GetValue(pos));

		//下一个
		m_RootBonesList.Next(&pos);
	}

	//上一关键帧
	struct AK3D_BONES_FRAME *pPreFrame=NULL;

	//遍历骨骼树
	pos=TmpBonesList.GetHeadPos();
	while(pos)
	{
		pBones=(struct AK3D_BONES *)TmpBonesList.GetValue(pos);

		//设置当前骨骼矩阵的帧版本
		pos3=pBones->FrameList.GetHeadPos();
		while(pos3)
		{
			struct AK3D_BONES_FRAME *pFrame=(struct AK3D_BONES_FRAME *)pBones->FrameList.GetValue(pos3);
			if(pFrame->uStartFrame>=uFrame)
			{
				if(pPreFrame)//存在上一关键帧
				{
					//计算两矩阵插值时过渡矩阵占的百分比
					float total=pFrame->uStartFrame-pPreFrame->uStartFrame;
					float part=uFrame-pPreFrame->uStartFrame;
					float percent=part/total;

					//通过两矩阵插值,计算出过渡矩阵
					CMatrix4X4Mgr::GetSingle().InsertValue(
						pBones->DestMatrix,
						pPreFrame->DestMatrix,
						pFrame->DestMatrix,
						percent
						);
				}
				else//不存在上一关键帧
				{
					CMatrix4X4Mgr::GetSingle().Copy(pBones->DestMatrix,pFrame->DestMatrix);
				}
				break;
			}

			//下一个
			pBones->FrameList.Next(&pos3);

			pPreFrame=pFrame;
		}

		struct AK3D_BONES_FRAME *pFrame=FindBonesFrame(pBones,uFrame);
		if(pFrame)
		{
			pBones->pCurBonesFrame=pFrame;
		}
		
		posRemove=pos;

		//搜索子骨骼列表,并添加到临时栈
		if(pBones->SonList.GetCount()>0)
		{
			pos2=pBones->SonList.GetHeadPos();
			while(pos2)
			{
				//添加到临时栈
				TmpBonesList.AddTail(pBones->SonList.GetValue(pos2));

				//下一个
				pBones->SonList.Next(&pos2);
			}
		}

		//下一个
		TmpBonesList.Next(&pos);

		//从临时栈中删除当前骨骼
		TmpBonesList.Remove(posRemove);
	}

	//清除临时栈
	TmpBonesList.ClearAll();
}

struct AK3D_BONES * CAK3DBonesMgr::FindBones(unsigned long uID)
{
	struct AK3D_BONES *pBones,*pReturnBones=NULL;
	AK_POS_PTR pos,pos2,posRemove;

	//遍历骨骼树时使用的临时栈
	CAKList TmpBonesList;
	TmpBonesList.SetAutoFreeValue(false);

	//获取取所有根骨骼,并添加到临时栈
	pos=m_RootBonesList.GetHeadPos();
	while(pos)
	{
		//添加到临时栈
		TmpBonesList.AddTail(m_RootBonesList.GetValue(pos));

		//下一个
		m_RootBonesList.Next(&pos);
	}

	//遍历骨骼树
	pos=TmpBonesList.GetHeadPos();
	while(pos)
	{
		pBones=(struct AK3D_BONES *)TmpBonesList.GetValue(pos);

		//找到了
		if(pBones->uID==uID)
		{
			pReturnBones=pBones;
			break;
		}

		posRemove=pos;

		//搜索子骨骼列表,并添加到临时栈
		if(pBones->SonList.GetCount()>0)
		{
			pos2=pBones->SonList.GetHeadPos();
			while(pos2)
			{
				//添加到临时栈
				TmpBonesList.AddTail(pBones->SonList.GetValue(pos2));

				//下一个
				pBones->SonList.Next(&pos2);
			}
		}

		//下一个
		TmpBonesList.Next(&pos);

		//从临时栈中删除当前骨骼
		TmpBonesList.Remove(posRemove);
	}

	//清除临时栈
	TmpBonesList.ClearAll();

	return pReturnBones;

}

struct AK3D_BONES * CAK3DBonesMgr::FindBones(char *pName)
{
	struct AK3D_BONES *pBones,*pReturnBones=NULL;
	AK_POS_PTR pos,pos2,posRemove;

	//遍历骨骼树时使用的临时栈
	CAKList TmpBonesList;
	TmpBonesList.SetAutoFreeValue(false);

	//获取取所有根骨骼,并添加到临时栈
	pos=m_RootBonesList.GetHeadPos();
	while(pos)
	{
		//添加到临时栈
		TmpBonesList.AddTail(m_RootBonesList.GetValue(pos));

		//下一个
		m_RootBonesList.Next(&pos);
	}

	//遍历骨骼树
	pos=TmpBonesList.GetHeadPos();
	while(pos)
	{
		pBones=(struct AK3D_BONES *)TmpBonesList.GetValue(pos);

		//找到了
		if(strcmp(pBones->Name,pName)==0)
		{
			pReturnBones=pBones;
			break;
		}

		posRemove=pos;

		//搜索子骨骼列表,并添加到临时栈
		if(pBones->SonList.GetCount()>0)
		{
			pos2=pBones->SonList.GetHeadPos();
			while(pos2)
			{
				//添加到临时栈
				TmpBonesList.AddTail(pBones->SonList.GetValue(pos2));

				//下一个
				pBones->SonList.Next(&pos2);
			}
		}

		//下一个
		TmpBonesList.Next(&pos);

		//从临时栈中删除当前骨骼
		TmpBonesList.Remove(posRemove);
	}

	//清除临时栈
	TmpBonesList.ClearAll();

	return pReturnBones;

}

void CAK3DBonesMgr::RemoveAll()
{
	struct AK3D_BONES *pBones,*pReturnBones=NULL;
	AK_POS_PTR pos,pos2,posRemove;

	//遍历骨骼树时使用的临时栈
	CAKList TmpBonesList;
	TmpBonesList.SetAutoFreeValue(false);

	//获取取所有根骨骼,并添加到临时栈
	pos=m_RootBonesList.GetHeadPos();
	while(pos)
	{
		//添加到临时栈
		TmpBonesList.AddTail(m_RootBonesList.GetValue(pos));

		posRemove=pos;

		//下一个
		m_RootBonesList.Next(&pos);
	}
	m_RootBonesList.ClearAll();

	//遍历骨骼树
	pos=TmpBonesList.GetHeadPos();
	while(pos)
	{
		pBones=(struct AK3D_BONES *)TmpBonesList.GetValue(pos);

		posRemove=pos;

		//搜索子骨骼列表,并添加到临时栈
		if(pBones->SonList.GetCount()>0)
		{
			pos2=pBones->SonList.GetHeadPos();
			while(pos2)
			{
				//添加到临时栈
				TmpBonesList.AddTail(pBones->SonList.GetValue(pos2));

				//下一个
				pBones->SonList.Next(&pos2);
			}
		}
		pBones->SonList.ClearAll();
		delete pBones;

		//下一个
		TmpBonesList.Next(&pos);

		//从临时栈中删除当前骨骼
		TmpBonesList.Remove(posRemove);
	}

	//清除临时栈
	TmpBonesList.ClearAll();
}

void CAK3DBonesMgr::RemoveBones(struct AK3D_BONES *pBones)
{
	struct AK3D_BONES *pCurBones;
	CAKList *pList;

	pList=&pBones->SonList;
	AK_POS_PTR pos=pList->GetHeadPos();
	while(pos)
	{
		pCurBones=(struct AK3D_BONES *)pList->GetValue(pos);

		//与子级骨骼脱离
		pCurBones->pFather=NULL;
		
		//子级骨骼连接到骨骼树根部
		m_RootBonesList.AddTail(pCurBones);

		//下一个
		pList->Next(&pos);
	}
	pBones->SonList.ClearAll();

	//与父级骨骼脱离
	if(pBones->pFather)pList=&pBones->pFather->SonList;
	else pList=&m_RootBonesList;
	pos=pList->GetHeadPos();
	while(pos)
	{
		pCurBones=(struct AK3D_BONES *)pList->GetValue(pos);

		if(pCurBones==pBones)
		{
			pList->Remove(pos);
			break;
		}

		//下一个
		pList->Next(&pos);
	}

	delete pBones;

}

struct AK3D_BONES_FRAME * CAK3DBonesMgr::FindBonesFrame(struct AK3D_BONES *pBones,unsigned long uStartFrame)
{
	struct AK3D_BONES_FRAME *pFrame;
	CAKList *pList=&pBones->FrameList;
	AK_POS_PTR pos=pList->GetHeadPos();

	while(pos)
	{
		pFrame=(struct AK3D_BONES_FRAME *)pList->GetValue(pos);
		if(pFrame->uStartFrame==uStartFrame)
		{
			return pFrame;
		}

		//下一个
		pList->Next(&pos);
	}

	return NULL;
}

void CAK3DBonesMgr::TaxisBonesFrame(struct AK3D_BONES *pBones)
{
	struct AK3D_BONES_FRAME *pFrame,*pFrame2;
	CAKList *pList=&pBones->FrameList;
	AK_POS_PTR pos=pList->GetHeadPos();
	AK_POS_PTR pos2;

	while(pos)
	{
		pos2=pos->pNext;
		while(pos2)
		{
			pFrame=(struct AK3D_BONES_FRAME *)pList->GetValue(pos);
			pFrame2=(struct AK3D_BONES_FRAME *)pList->GetValue(pos2);

			if(pFrame2->uStartFrame<pFrame->uStartFrame)
			{
				pList->Change(pos,pos2);
			}

			//下一个
			pList->Next(&pos2);
		}

		//下一个
		pList->Next(&pos);
	}
}

void CAK3DBonesMgr::TaxisBonesTreeFrameList()
{
	unsigned long uFrame,uFrame2;
	CAKList *pList=&m_BonesTreeFrameList;
	AK_POS_PTR pos=pList->GetHeadPos();
	AK_POS_PTR pos2;

	while(pos)
	{
		pos2=pos->pNext;
		while(pos2)
		{
			uFrame=(unsigned long)pList->GetValue(pos);
			uFrame2=(unsigned long)pList->GetValue(pos2);

			if(uFrame2<uFrame)
			{
				pList->Change(pos,pos2);
			}

			//下一个
			pList->Next(&pos2);
		}

		//下一个
		pList->Next(&pos);
	}
}

void CAK3DBonesMgr::RemoveBonesFrame(struct AK3D_BONES *pBones,unsigned long uStartFrame)
{
	struct AK3D_BONES_FRAME *pFrame;
	CAKList *pList=&pBones->FrameList;
	AK_POS_PTR pos=pList->GetHeadPos();
	
	while(pos)
	{
		pFrame=(struct AK3D_BONES_FRAME *)pList->GetValue(pos);

		if(pFrame->uStartFrame==uStartFrame)
		{
			pList->Remove(pos);
			return;
		}
		
		//下一个
		pList->Next(&pos);
	}
}

bool CAK3DBonesMgr::CreateFrame(unsigned long uStartFrame)
{
	struct AK3D_BONES *pBones,*pReturnBones=NULL;
	AK_POS_PTR pos,pos2,posRemove;
	struct AK3D_BONES_FRAME *pFrame;
	bool rt=true;

	//遍历骨骼树时使用的临时栈
	CAKList TmpBonesList;
	TmpBonesList.SetAutoFreeValue(false);

	//获取取所有根骨骼,并添加到临时栈
	pos=m_RootBonesList.GetHeadPos();
	while(pos)
	{
		//添加到临时栈
		TmpBonesList.AddTail(m_RootBonesList.GetValue(pos));

		//下一个
		m_RootBonesList.Next(&pos);
	}

	//遍历骨骼树
	pos=TmpBonesList.GetHeadPos();
	while(pos)
	{
		pBones=(struct AK3D_BONES *)TmpBonesList.GetValue(pos);

		//查找uStartFrame帧是否存在
		pFrame=FindBonesFrame(pBones,uStartFrame);
		if(!pFrame)//如果uStartFrame不存在
		{
			//创建骨骼帧
			pFrame=new struct AK3D_BONES_FRAME;
			if(!pFrame)
			{
				rt=false;
				break;
			}

			//设置起始帧数
			pFrame->uStartFrame=uStartFrame;

			//设置单位矩阵
			CMatrix4X4Mgr::GetSingle().SetIdentityMatrix(pFrame->Matrix);

			//初始化目标矩阵
			memset(pFrame->DestMatrix,0,sizeof(float)*4*4);

			CAKList *pList=&pBones->FrameList;

			//添加到骨骼帧列表
			if(!pList->AddTail(pFrame))
			{
				rt=false;
				break;
			}

			//骨骼帧列表排序
			TaxisBonesFrame(pBones);

			//复制前一骨骼帧矩阵内容
			struct AK3D_BONES_FRAME *pFrame2,*pFrontFrame=NULL;
			pos2=pList->GetHeadPos();
			while(pos2)
			{
				pFrame2=(struct AK3D_BONES_FRAME *)pList->GetValue(pos2);

				//找到新添加的骨骼帧
				if(pFrame2==pFrame)
				{
					if(pFrontFrame)
					{
						//复制前一个骨骼帧矩阵到新添加的骨骼帧矩阵
						CMatrix4X4Mgr::GetSingle().Copy(pFrame->Matrix,pFrontFrame->Matrix);
						break;
					}
				}

				//下一个
				pList->Next(&pos2);

				pFrontFrame=pFrame2;
			}

			//记录上一级骨骼帧矩阵地址
			if(pBones->pFather)
			{
				pFrame->pFrontFrame=FindBonesFrame(pBones->pFather,uStartFrame);
			}
			else
			{
				pFrame->pFrontFrame=NULL;
			}

		}
		else
		{
			//记录上一级骨骼帧矩阵地址
			if(pBones->pFather)
			{
				pFrame->pFrontFrame=FindBonesFrame(pBones->pFather,uStartFrame);
			}
			else
			{
				pFrame->pFrontFrame=NULL;
			}
		}
		posRemove=pos;

		//搜索子骨骼列表,并添加到临时栈
		if(pBones->SonList.GetCount()>0)
		{
			pos2=pBones->SonList.GetHeadPos();
			while(pos2)
			{
				//添加到临时栈
				TmpBonesList.AddTail(pBones->SonList.GetValue(pos2));

				//下一个
				pBones->SonList.Next(&pos2);
			}
		}

		//下一个
		TmpBonesList.Next(&pos);

		//从临时栈中删除当前骨骼
		TmpBonesList.Remove(posRemove);
	}

	//清除临时栈
	TmpBonesList.ClearAll();

	//添加到骨骼树帧列表
	if(!CreateBonesTreeListElement(uStartFrame))return false;
	
	//骨骼树帧列表排序
	TaxisBonesTreeFrameList();

	return rt;
}

bool CAK3DBonesMgr::CreateBonesTreeListElement(unsigned long uStartFrame)
{
	unsigned long uFrame;
	AK_POS_PTR pos=m_BonesTreeFrameList.GetHeadPos();
	while(pos)
	{
		uFrame=(unsigned long)m_BonesTreeFrameList.GetValue(pos);

		if(uFrame==uStartFrame)return true;
		
		//下一个
		m_BonesTreeFrameList.Next(&pos);
	}

	return m_BonesTreeFrameList.AddTail((void *)uStartFrame);
}

void CAK3DBonesMgr::RemoveFrame(unsigned long uStartFrame)
{
	struct AK3D_BONES *pBones,*pReturnBones=NULL;
	AK_POS_PTR pos,pos2,posRemove;

	//遍历骨骼树时使用的临时栈
	CAKList TmpBonesList;
	TmpBonesList.SetAutoFreeValue(false);

	//获取取所有根骨骼,并添加到临时栈
	pos=m_RootBonesList.GetHeadPos();
	while(pos)
	{
		//添加到临时栈
		TmpBonesList.AddTail(m_RootBonesList.GetValue(pos));

		//下一个
		m_RootBonesList.Next(&pos);
	}

	//遍历骨骼树
	pos=TmpBonesList.GetHeadPos();
	while(pos)
	{
		pBones=(struct AK3D_BONES *)TmpBonesList.GetValue(pos);

		//删除骨骼帧
		RemoveBonesFrame(pBones,uStartFrame);

		posRemove=pos;

		//搜索子骨骼列表,并添加到临时栈
		if(pBones->SonList.GetCount()>0)
		{
			pos2=pBones->SonList.GetHeadPos();
			while(pos2)
			{
				//添加到临时栈
				TmpBonesList.AddTail(pBones->SonList.GetValue(pos2));

				//下一个
				pBones->SonList.Next(&pos2);
			}
		}

		//下一个
		TmpBonesList.Next(&pos);

		//从临时栈中删除当前骨骼
		TmpBonesList.Remove(posRemove);
	}

	//清除临时栈
	TmpBonesList.ClearAll();

	//从骨骼树帧列表中清除uStartFrame
	unsigned long uFrame;
	pos=m_BonesTreeFrameList.GetHeadPos();
	while(pos)
	{
		uFrame=(unsigned long)m_BonesTreeFrameList.GetValue(pos);

		if(uFrame==uStartFrame)
		{
			m_BonesTreeFrameList.Remove(pos);
			break;
		}

		//下一个
		m_BonesTreeFrameList.Next(&pos);
	}

}

void CAK3DBonesMgr::RemoveBonesCtrl(struct AK3D_VERTEX *pVertex,struct AK3D_BONES *pBones)
{
	struct AK3D_BONES_CTRL *pCtrl;
	CAKList &list=pVertex->BonesCtrlList;
	AK_POS_PTR pos=list.GetHeadPos();
	while(pos)
	{
		pCtrl=(struct AK3D_BONES_CTRL *)list.GetValue(pos);

		if(pCtrl->pBones==pBones)
		{
			list.Remove(pos);
			break;
		}

		//下一个
		list.Next(&pos);
	}
}

struct AK3D_BONES_CTRL * CAK3DBonesMgr::FindBonesCtrl(struct AK3D_VERTEX *pVertex,struct AK3D_BONES *pBones)
{
	struct AK3D_BONES_CTRL *pCtrl;

	CAKList &List=pVertex->BonesCtrlList;

	//查找一下是否已经捆绑
	AK_POS_PTR pos=List.GetHeadPos();
	while(pos)
	{
		pCtrl=(struct AK3D_BONES_CTRL *)List.GetValue(pos);

		//如果已经捆绑了
		if(pCtrl->pBones==pBones)
		{
			return pCtrl;
		}

		//下一个
		List.Next(&pos);
	}

	return NULL;
}

struct AK3D_BONES_CTRL * CAK3DBonesMgr::CreateBonesCtrl(struct AK3D_VERTEX *pVertex,struct AK3D_BONES *pBones,float Power)
{
	struct AK3D_BONES_CTRL *pCtrl=FindBonesCtrl(pVertex,pBones);

	//如果已经存在捆绑关系
	if(pCtrl)
	{
		pCtrl->Power=Power;
		return pCtrl;
	}

	CAKList &List=pVertex->BonesCtrlList;
	
	//还没有捆绑
	pCtrl=new struct AK3D_BONES_CTRL;
	if(!pCtrl)return NULL;

	pCtrl->pBones=pBones;
	pCtrl->Power=Power;

	if(!List.AddTail(pCtrl))return NULL;

	return pCtrl;
}

void CAK3DBonesMgr::UpdateBonesTreeMatrix()
{
	struct AK3D_BONES *pBones;
	AK_POS_PTR pos,pos2,posRemove;
	CAKList *pList;
	struct AK3D_BONES_FRAME *pFrame;

	//检查并生成没有生成的骨骼帧
	pos=m_BonesTreeFrameList.GetHeadPos();
	while(pos)
	{
		unsigned long uFrame=(unsigned long)m_BonesTreeFrameList.GetValue(pos);

		CreateFrame(uFrame);

		//下一个
		m_BonesTreeFrameList.Next(&pos);
	}

	//遍历骨骼树时使用的临时栈
	CAKList TmpBonesList;
	TmpBonesList.SetAutoFreeValue(false);

	//获取取所有根骨骼,并添加到临时栈
	pos=m_RootBonesList.GetHeadPos();
	while(pos)
	{
		//添加到临时栈
		TmpBonesList.AddTail(m_RootBonesList.GetValue(pos));

		//下一个
		m_RootBonesList.Next(&pos);
	}

	//遍历骨骼树
	pos=TmpBonesList.GetHeadPos();
	while(pos)
	{
		pBones=(struct AK3D_BONES *)TmpBonesList.GetValue(pos);

		pList=&pBones->FrameList;

		if(pBones->pFather)//子骨骼
		{
			pos2=pList->GetHeadPos();
			while(pos2)
			{
				pFrame=(struct AK3D_BONES_FRAME *)pList->GetValue(pos2);

				//复合矩阵运算
				//CMatrix4X4Mgr::GetSingle().Mul(pFrame->DestMatrix,pFrame->Matrix,pFrame->pFrontFrame->DestMatrix);
				CMatrix4X4Mgr::GetSingle().Mul(pFrame->DestMatrix,pFrame->pFrontFrame->DestMatrix,pFrame->Matrix);

				//下一个
				pList->Next(&pos2);
			}
		}
		else//父骨骼
		{
			pos2=pList->GetHeadPos();
			while(pos2)
			{
				pFrame=(struct AK3D_BONES_FRAME *)pList->GetValue(pos2);

				CMatrix4X4Mgr::GetSingle().Copy(pFrame->DestMatrix,pFrame->Matrix);

				//下一个
				pList->Next(&pos2);
			}
		}

		posRemove=pos;

		//搜索子骨骼列表,并添加到临时栈
		if(pBones->SonList.GetCount()>0)
		{
			pos2=pBones->SonList.GetHeadPos();
			while(pos2)
			{
				//添加到临时栈
				TmpBonesList.AddTail(pBones->SonList.GetValue(pos2));

				//下一个
				pBones->SonList.Next(&pos2);
			}
		}

		//下一个
		TmpBonesList.Next(&pos);

		//从临时栈中删除当前骨骼
		TmpBonesList.Remove(posRemove);
	}

	//清除临时栈
	TmpBonesList.ClearAll();

}




