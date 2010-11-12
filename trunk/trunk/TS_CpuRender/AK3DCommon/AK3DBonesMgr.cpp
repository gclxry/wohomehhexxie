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

/*����:
0=û�����¼���ϵ;
1=pBones1��pBones2���ϼ�;
2=pBones2��pBones1���ϼ�;
3=��������ͬ��;
*/
short CAK3DBonesMgr::CheckBones(struct AK3D_BONES *pBones1,struct AK3D_BONES *pBones2)
{
	if(pBones1==pBones2)return 3;

	struct AK3D_BONES *pBones;

	pBones=pBones1->pFather;
	while(pBones)
	{
		if(pBones==pBones2)return 2;

		//��һ��
		pBones=pBones->pFather;
	}

	pBones=pBones2->pFather;
	while(pBones)
	{
		if(pBones==pBones1)return 1;

		//��һ��
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
		case 3:return false;//��������ͬ��;
		case 1:return false;//�ӹ��������Ǹ��������ϼ�;
		}
	}

	AK_POS_PTR pos;
	struct AK3D_BONES *pBones;
	CAKList *pSonList;

	//����
	if(pSonBones->pFather)//�ӹ���
	{
		pSonList=&pSonBones->pFather->SonList;
		pos=pSonList->GetHeadPos();
		while(pos)
		{
			pBones=(struct AK3D_BONES *)pSonList->GetValue(pos);
			if(pBones==pSonBones)
			{
				//����
				pSonList->Remove(pos);
				break;
			}

			//��һ��
			pSonList->Next(&pos);
		}
	}
	else//������
	{
		pos=m_RootBonesList.GetHeadPos();
		while(pos)
		{
			pBones=(struct AK3D_BONES *)m_RootBonesList.GetValue(pos);
			if(pBones==pSonBones)
			{
				//����
				m_RootBonesList.Remove(pos);
				break;
			}

			//��һ��
			m_RootBonesList.Next(&pos);
		}
	}
	//����֡�б�����
	CAKList *pList=&pSonBones->FrameList;
	pos=pList->GetHeadPos();
	while(pos)
	{
		struct AK3D_BONES_FRAME *pFrame=(struct AK3D_BONES_FRAME *)pList->GetValue(pos);

		if(pFatherBones)pFrame->pFrontFrame=FindBonesFrame(pFatherBones,pFrame->uStartFrame);
		else pFrame->pFrontFrame=NULL;

		//��һ��
		pList->Next(&pos);
	}

	//����
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
	//�����ڹ���֡
	if(m_BonesTreeFrameList.GetCount()==0)return 0;

	//��ȡ���ֵ֡
	unsigned long uMaxFrame=(unsigned long)m_BonesTreeFrameList.GetValue(m_BonesTreeFrameList.GetTailPos());

	return uMaxFrame;
}

void CAK3DBonesMgr::SetPlayFrame(unsigned long uFrame)
{
	//�����ڹ���֡
	if(m_BonesTreeFrameList.GetCount()==0)return;

	//��ȡ���ֵ֡
	unsigned long uMaxFrame=GetMaxFrame();

	//Ҫ�����õ�ֵ֡������
	if(uFrame>uMaxFrame)return;

	struct AK3D_BONES *pBones,*pReturnBones=NULL;
	AK_POS_PTR pos,pos2,posRemove;
	AK_POS_PTR pos3;

	//����������ʱʹ�õ���ʱջ
	CAKList TmpBonesList;
	TmpBonesList.SetAutoFreeValue(false);

	//��ȡȡ���и�����,����ӵ���ʱջ
	pos=m_RootBonesList.GetHeadPos();
	while(pos)
	{
		//��ӵ���ʱջ
		TmpBonesList.AddTail(m_RootBonesList.GetValue(pos));

		//��һ��
		m_RootBonesList.Next(&pos);
	}

	//��һ�ؼ�֡
	struct AK3D_BONES_FRAME *pPreFrame=NULL;

	//����������
	pos=TmpBonesList.GetHeadPos();
	while(pos)
	{
		pBones=(struct AK3D_BONES *)TmpBonesList.GetValue(pos);

		//���õ�ǰ���������֡�汾
		pos3=pBones->FrameList.GetHeadPos();
		while(pos3)
		{
			struct AK3D_BONES_FRAME *pFrame=(struct AK3D_BONES_FRAME *)pBones->FrameList.GetValue(pos3);
			if(pFrame->uStartFrame>=uFrame)
			{
				if(pPreFrame)//������һ�ؼ�֡
				{
					//�����������ֵʱ���ɾ���ռ�İٷֱ�
					float total=pFrame->uStartFrame-pPreFrame->uStartFrame;
					float part=uFrame-pPreFrame->uStartFrame;
					float percent=part/total;

					//ͨ���������ֵ,��������ɾ���
					CMatrix4X4Mgr::GetSingle().InsertValue(
						pBones->DestMatrix,
						pPreFrame->DestMatrix,
						pFrame->DestMatrix,
						percent
						);
				}
				else//��������һ�ؼ�֡
				{
					CMatrix4X4Mgr::GetSingle().Copy(pBones->DestMatrix,pFrame->DestMatrix);
				}
				break;
			}

			//��һ��
			pBones->FrameList.Next(&pos3);

			pPreFrame=pFrame;
		}

		struct AK3D_BONES_FRAME *pFrame=FindBonesFrame(pBones,uFrame);
		if(pFrame)
		{
			pBones->pCurBonesFrame=pFrame;
		}
		
		posRemove=pos;

		//�����ӹ����б�,����ӵ���ʱջ
		if(pBones->SonList.GetCount()>0)
		{
			pos2=pBones->SonList.GetHeadPos();
			while(pos2)
			{
				//��ӵ���ʱջ
				TmpBonesList.AddTail(pBones->SonList.GetValue(pos2));

				//��һ��
				pBones->SonList.Next(&pos2);
			}
		}

		//��һ��
		TmpBonesList.Next(&pos);

		//����ʱջ��ɾ����ǰ����
		TmpBonesList.Remove(posRemove);
	}

	//�����ʱջ
	TmpBonesList.ClearAll();
}

struct AK3D_BONES * CAK3DBonesMgr::FindBones(unsigned long uID)
{
	struct AK3D_BONES *pBones,*pReturnBones=NULL;
	AK_POS_PTR pos,pos2,posRemove;

	//����������ʱʹ�õ���ʱջ
	CAKList TmpBonesList;
	TmpBonesList.SetAutoFreeValue(false);

	//��ȡȡ���и�����,����ӵ���ʱջ
	pos=m_RootBonesList.GetHeadPos();
	while(pos)
	{
		//��ӵ���ʱջ
		TmpBonesList.AddTail(m_RootBonesList.GetValue(pos));

		//��һ��
		m_RootBonesList.Next(&pos);
	}

	//����������
	pos=TmpBonesList.GetHeadPos();
	while(pos)
	{
		pBones=(struct AK3D_BONES *)TmpBonesList.GetValue(pos);

		//�ҵ���
		if(pBones->uID==uID)
		{
			pReturnBones=pBones;
			break;
		}

		posRemove=pos;

		//�����ӹ����б�,����ӵ���ʱջ
		if(pBones->SonList.GetCount()>0)
		{
			pos2=pBones->SonList.GetHeadPos();
			while(pos2)
			{
				//��ӵ���ʱջ
				TmpBonesList.AddTail(pBones->SonList.GetValue(pos2));

				//��һ��
				pBones->SonList.Next(&pos2);
			}
		}

		//��һ��
		TmpBonesList.Next(&pos);

		//����ʱջ��ɾ����ǰ����
		TmpBonesList.Remove(posRemove);
	}

	//�����ʱջ
	TmpBonesList.ClearAll();

	return pReturnBones;

}

struct AK3D_BONES * CAK3DBonesMgr::FindBones(char *pName)
{
	struct AK3D_BONES *pBones,*pReturnBones=NULL;
	AK_POS_PTR pos,pos2,posRemove;

	//����������ʱʹ�õ���ʱջ
	CAKList TmpBonesList;
	TmpBonesList.SetAutoFreeValue(false);

	//��ȡȡ���и�����,����ӵ���ʱջ
	pos=m_RootBonesList.GetHeadPos();
	while(pos)
	{
		//��ӵ���ʱջ
		TmpBonesList.AddTail(m_RootBonesList.GetValue(pos));

		//��һ��
		m_RootBonesList.Next(&pos);
	}

	//����������
	pos=TmpBonesList.GetHeadPos();
	while(pos)
	{
		pBones=(struct AK3D_BONES *)TmpBonesList.GetValue(pos);

		//�ҵ���
		if(strcmp(pBones->Name,pName)==0)
		{
			pReturnBones=pBones;
			break;
		}

		posRemove=pos;

		//�����ӹ����б�,����ӵ���ʱջ
		if(pBones->SonList.GetCount()>0)
		{
			pos2=pBones->SonList.GetHeadPos();
			while(pos2)
			{
				//��ӵ���ʱջ
				TmpBonesList.AddTail(pBones->SonList.GetValue(pos2));

				//��һ��
				pBones->SonList.Next(&pos2);
			}
		}

		//��һ��
		TmpBonesList.Next(&pos);

		//����ʱջ��ɾ����ǰ����
		TmpBonesList.Remove(posRemove);
	}

	//�����ʱջ
	TmpBonesList.ClearAll();

	return pReturnBones;

}

void CAK3DBonesMgr::RemoveAll()
{
	struct AK3D_BONES *pBones,*pReturnBones=NULL;
	AK_POS_PTR pos,pos2,posRemove;

	//����������ʱʹ�õ���ʱջ
	CAKList TmpBonesList;
	TmpBonesList.SetAutoFreeValue(false);

	//��ȡȡ���и�����,����ӵ���ʱջ
	pos=m_RootBonesList.GetHeadPos();
	while(pos)
	{
		//��ӵ���ʱջ
		TmpBonesList.AddTail(m_RootBonesList.GetValue(pos));

		posRemove=pos;

		//��һ��
		m_RootBonesList.Next(&pos);
	}
	m_RootBonesList.ClearAll();

	//����������
	pos=TmpBonesList.GetHeadPos();
	while(pos)
	{
		pBones=(struct AK3D_BONES *)TmpBonesList.GetValue(pos);

		posRemove=pos;

		//�����ӹ����б�,����ӵ���ʱջ
		if(pBones->SonList.GetCount()>0)
		{
			pos2=pBones->SonList.GetHeadPos();
			while(pos2)
			{
				//��ӵ���ʱջ
				TmpBonesList.AddTail(pBones->SonList.GetValue(pos2));

				//��һ��
				pBones->SonList.Next(&pos2);
			}
		}
		pBones->SonList.ClearAll();
		delete pBones;

		//��һ��
		TmpBonesList.Next(&pos);

		//����ʱջ��ɾ����ǰ����
		TmpBonesList.Remove(posRemove);
	}

	//�����ʱջ
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

		//���Ӽ���������
		pCurBones->pFather=NULL;
		
		//�Ӽ��������ӵ�����������
		m_RootBonesList.AddTail(pCurBones);

		//��һ��
		pList->Next(&pos);
	}
	pBones->SonList.ClearAll();

	//�븸����������
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

		//��һ��
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

		//��һ��
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

			//��һ��
			pList->Next(&pos2);
		}

		//��һ��
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

			//��һ��
			pList->Next(&pos2);
		}

		//��һ��
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
		
		//��һ��
		pList->Next(&pos);
	}
}

bool CAK3DBonesMgr::CreateFrame(unsigned long uStartFrame)
{
	struct AK3D_BONES *pBones,*pReturnBones=NULL;
	AK_POS_PTR pos,pos2,posRemove;
	struct AK3D_BONES_FRAME *pFrame;
	bool rt=true;

	//����������ʱʹ�õ���ʱջ
	CAKList TmpBonesList;
	TmpBonesList.SetAutoFreeValue(false);

	//��ȡȡ���и�����,����ӵ���ʱջ
	pos=m_RootBonesList.GetHeadPos();
	while(pos)
	{
		//��ӵ���ʱջ
		TmpBonesList.AddTail(m_RootBonesList.GetValue(pos));

		//��һ��
		m_RootBonesList.Next(&pos);
	}

	//����������
	pos=TmpBonesList.GetHeadPos();
	while(pos)
	{
		pBones=(struct AK3D_BONES *)TmpBonesList.GetValue(pos);

		//����uStartFrame֡�Ƿ����
		pFrame=FindBonesFrame(pBones,uStartFrame);
		if(!pFrame)//���uStartFrame������
		{
			//��������֡
			pFrame=new struct AK3D_BONES_FRAME;
			if(!pFrame)
			{
				rt=false;
				break;
			}

			//������ʼ֡��
			pFrame->uStartFrame=uStartFrame;

			//���õ�λ����
			CMatrix4X4Mgr::GetSingle().SetIdentityMatrix(pFrame->Matrix);

			//��ʼ��Ŀ�����
			memset(pFrame->DestMatrix,0,sizeof(float)*4*4);

			CAKList *pList=&pBones->FrameList;

			//��ӵ�����֡�б�
			if(!pList->AddTail(pFrame))
			{
				rt=false;
				break;
			}

			//����֡�б�����
			TaxisBonesFrame(pBones);

			//����ǰһ����֡��������
			struct AK3D_BONES_FRAME *pFrame2,*pFrontFrame=NULL;
			pos2=pList->GetHeadPos();
			while(pos2)
			{
				pFrame2=(struct AK3D_BONES_FRAME *)pList->GetValue(pos2);

				//�ҵ�����ӵĹ���֡
				if(pFrame2==pFrame)
				{
					if(pFrontFrame)
					{
						//����ǰһ������֡��������ӵĹ���֡����
						CMatrix4X4Mgr::GetSingle().Copy(pFrame->Matrix,pFrontFrame->Matrix);
						break;
					}
				}

				//��һ��
				pList->Next(&pos2);

				pFrontFrame=pFrame2;
			}

			//��¼��һ������֡�����ַ
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
			//��¼��һ������֡�����ַ
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

		//�����ӹ����б�,����ӵ���ʱջ
		if(pBones->SonList.GetCount()>0)
		{
			pos2=pBones->SonList.GetHeadPos();
			while(pos2)
			{
				//��ӵ���ʱջ
				TmpBonesList.AddTail(pBones->SonList.GetValue(pos2));

				//��һ��
				pBones->SonList.Next(&pos2);
			}
		}

		//��һ��
		TmpBonesList.Next(&pos);

		//����ʱջ��ɾ����ǰ����
		TmpBonesList.Remove(posRemove);
	}

	//�����ʱջ
	TmpBonesList.ClearAll();

	//��ӵ�������֡�б�
	if(!CreateBonesTreeListElement(uStartFrame))return false;
	
	//������֡�б�����
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
		
		//��һ��
		m_BonesTreeFrameList.Next(&pos);
	}

	return m_BonesTreeFrameList.AddTail((void *)uStartFrame);
}

void CAK3DBonesMgr::RemoveFrame(unsigned long uStartFrame)
{
	struct AK3D_BONES *pBones,*pReturnBones=NULL;
	AK_POS_PTR pos,pos2,posRemove;

	//����������ʱʹ�õ���ʱջ
	CAKList TmpBonesList;
	TmpBonesList.SetAutoFreeValue(false);

	//��ȡȡ���и�����,����ӵ���ʱջ
	pos=m_RootBonesList.GetHeadPos();
	while(pos)
	{
		//��ӵ���ʱջ
		TmpBonesList.AddTail(m_RootBonesList.GetValue(pos));

		//��һ��
		m_RootBonesList.Next(&pos);
	}

	//����������
	pos=TmpBonesList.GetHeadPos();
	while(pos)
	{
		pBones=(struct AK3D_BONES *)TmpBonesList.GetValue(pos);

		//ɾ������֡
		RemoveBonesFrame(pBones,uStartFrame);

		posRemove=pos;

		//�����ӹ����б�,����ӵ���ʱջ
		if(pBones->SonList.GetCount()>0)
		{
			pos2=pBones->SonList.GetHeadPos();
			while(pos2)
			{
				//��ӵ���ʱջ
				TmpBonesList.AddTail(pBones->SonList.GetValue(pos2));

				//��һ��
				pBones->SonList.Next(&pos2);
			}
		}

		//��һ��
		TmpBonesList.Next(&pos);

		//����ʱջ��ɾ����ǰ����
		TmpBonesList.Remove(posRemove);
	}

	//�����ʱջ
	TmpBonesList.ClearAll();

	//�ӹ�����֡�б������uStartFrame
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

		//��һ��
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

		//��һ��
		list.Next(&pos);
	}
}

struct AK3D_BONES_CTRL * CAK3DBonesMgr::FindBonesCtrl(struct AK3D_VERTEX *pVertex,struct AK3D_BONES *pBones)
{
	struct AK3D_BONES_CTRL *pCtrl;

	CAKList &List=pVertex->BonesCtrlList;

	//����һ���Ƿ��Ѿ�����
	AK_POS_PTR pos=List.GetHeadPos();
	while(pos)
	{
		pCtrl=(struct AK3D_BONES_CTRL *)List.GetValue(pos);

		//����Ѿ�������
		if(pCtrl->pBones==pBones)
		{
			return pCtrl;
		}

		//��һ��
		List.Next(&pos);
	}

	return NULL;
}

struct AK3D_BONES_CTRL * CAK3DBonesMgr::CreateBonesCtrl(struct AK3D_VERTEX *pVertex,struct AK3D_BONES *pBones,float Power)
{
	struct AK3D_BONES_CTRL *pCtrl=FindBonesCtrl(pVertex,pBones);

	//����Ѿ����������ϵ
	if(pCtrl)
	{
		pCtrl->Power=Power;
		return pCtrl;
	}

	CAKList &List=pVertex->BonesCtrlList;
	
	//��û������
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

	//��鲢����û�����ɵĹ���֡
	pos=m_BonesTreeFrameList.GetHeadPos();
	while(pos)
	{
		unsigned long uFrame=(unsigned long)m_BonesTreeFrameList.GetValue(pos);

		CreateFrame(uFrame);

		//��һ��
		m_BonesTreeFrameList.Next(&pos);
	}

	//����������ʱʹ�õ���ʱջ
	CAKList TmpBonesList;
	TmpBonesList.SetAutoFreeValue(false);

	//��ȡȡ���и�����,����ӵ���ʱջ
	pos=m_RootBonesList.GetHeadPos();
	while(pos)
	{
		//��ӵ���ʱջ
		TmpBonesList.AddTail(m_RootBonesList.GetValue(pos));

		//��һ��
		m_RootBonesList.Next(&pos);
	}

	//����������
	pos=TmpBonesList.GetHeadPos();
	while(pos)
	{
		pBones=(struct AK3D_BONES *)TmpBonesList.GetValue(pos);

		pList=&pBones->FrameList;

		if(pBones->pFather)//�ӹ���
		{
			pos2=pList->GetHeadPos();
			while(pos2)
			{
				pFrame=(struct AK3D_BONES_FRAME *)pList->GetValue(pos2);

				//���Ͼ�������
				//CMatrix4X4Mgr::GetSingle().Mul(pFrame->DestMatrix,pFrame->Matrix,pFrame->pFrontFrame->DestMatrix);
				CMatrix4X4Mgr::GetSingle().Mul(pFrame->DestMatrix,pFrame->pFrontFrame->DestMatrix,pFrame->Matrix);

				//��һ��
				pList->Next(&pos2);
			}
		}
		else//������
		{
			pos2=pList->GetHeadPos();
			while(pos2)
			{
				pFrame=(struct AK3D_BONES_FRAME *)pList->GetValue(pos2);

				CMatrix4X4Mgr::GetSingle().Copy(pFrame->DestMatrix,pFrame->Matrix);

				//��һ��
				pList->Next(&pos2);
			}
		}

		posRemove=pos;

		//�����ӹ����б�,����ӵ���ʱջ
		if(pBones->SonList.GetCount()>0)
		{
			pos2=pBones->SonList.GetHeadPos();
			while(pos2)
			{
				//��ӵ���ʱջ
				TmpBonesList.AddTail(pBones->SonList.GetValue(pos2));

				//��һ��
				pBones->SonList.Next(&pos2);
			}
		}

		//��һ��
		TmpBonesList.Next(&pos);

		//����ʱջ��ɾ����ǰ����
		TmpBonesList.Remove(posRemove);
	}

	//�����ʱջ
	TmpBonesList.ClearAll();

}




