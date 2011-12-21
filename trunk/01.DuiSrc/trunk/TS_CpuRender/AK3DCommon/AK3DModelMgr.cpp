#include "stdafx.h"

#include "AK3DModelMgr.h"
#include "AK3DRender.h"

CAK3DModelMgr::CAK3DModelMgr()
{
}

CAK3DModelMgr::~CAK3DModelMgr()
{
	AK_POS_PTR pos=m_ModelList.GetHeadPos();
	while(pos)
	{
		struct AK3D_MODEL *pModel=(struct AK3D_MODEL *)m_ModelList.GetValue(pos);

		pModel->VertexList.ClearAll();

		pModel->PolygonList.ClearAll();

		//下一个
		m_ModelList.Next(&pos);
	}
}

void CAK3DModelMgr::SetModelMatrix(struct AK3D_MODEL *pModel,float *pMatrix)
{
	CMatrix4X4Mgr::GetSingle().Copy(pModel->DestMatrix,pMatrix);
}

void CAK3DModelMgr::UpdateModel(struct AK3D_MODEL *pModel)
{
	//调试时使用,代表第几帧(>=0)
	unsigned long uCurBonesTreeFrame=0;

	float x,y,z;
	AK_POS_PTR pos2;
	AK_POS_PTR pos=pModel->VertexList.GetHeadPos();
	while(pos)
	{
		struct AK3D_VERTEX *pVertex=(struct AK3D_VERTEX *)pModel->VertexList.GetValue(pos);

		//当前顶点与骨骼矩阵进行变换
		CAKList *pList=&pVertex->BonesCtrlList;
		unsigned long BonesCtrlCount=pList->GetCount();
		if(BonesCtrlCount>0&&uCurBonesTreeFrame!=0)
		{
			float Power=1.0f/BonesCtrlCount;
			pVertex->xDest=0;
			pVertex->yDest=0;
			pVertex->zDest=0;
			pos2=pList->GetHeadPos();
			while(pos2)
			{
				struct AK3D_BONES_CTRL *pCtrl=(struct AK3D_BONES_CTRL *)pList->GetValue(pos2);
				
				CMatrix4X4Mgr::GetSingle().VertexTransform(pCtrl->pBones->DestMatrix,pVertex->x,pVertex->y,pVertex->z,&x,&y,&z);
				pVertex->xDest+=x*Power;
				pVertex->yDest+=y*Power;
				pVertex->zDest+=z*Power;

				//下一个
				pList->Next(&pos2);
			}
		}
		else//uCurBonesTreeFrame==0代表初始状态//BonesCtrlCount==0代表没有受到任何一个骨骼的控制
		{
			pVertex->xDest=pVertex->x;
			pVertex->yDest=pVertex->y;
			pVertex->zDest=pVertex->z;
		}

		//当前顶点根据模型焦点对齐坐标系原点
		pVertex->xDest-=pModel->xFocus;
		pVertex->yDest-=pModel->yFocus;
		pVertex->zDest-=pModel->zFocus;
		
		//当前顶点与模型目标矩阵进行变换
		CMatrix4X4Mgr::GetSingle().VertexTransform(
			pModel->DestMatrix,
			pVertex->xDest,pVertex->yDest,pVertex->zDest,
			&pVertex->xDest,&pVertex->yDest,&pVertex->zDest
			);

		//下一个
		pModel->VertexList.Next(&pos);
	}

}

struct AK3D_MODEL *CAK3DModelMgr::FindModel(
	unsigned long uID//模型ID
	)
{
	AK_POS_PTR pos=m_ModelList.GetHeadPos();
	while(pos)
	{
		struct AK3D_MODEL *pModel=(struct AK3D_MODEL *)m_ModelList.GetValue(pos);
		if(pModel->uID==uID)
		{
			return pModel;
		}

		//下一个
		m_ModelList.Next(&pos);
	}

	return NULL;
}

struct AK3D_MODEL *CAK3DModelMgr::CreateModel(
	unsigned long uID//模型ID
	)
{
	struct AK3D_MODEL *pModel=FindModel(uID);
	if(pModel)return NULL;

	pModel=new struct AK3D_MODEL;
	if(!pModel)return NULL;

	pModel->uID=uID;
	pModel->pUIPic=NULL;
	pModel->xFocus=0;
	pModel->yFocus=0;
	pModel->zFocus=0;
	CMatrix4X4Mgr::GetSingle().SetIdentityMatrix(pModel->DestMatrix);

	bool rt=m_ModelList.AddTail(pModel);
	if(rt)return pModel;
	else
	{
		delete pModel;
		return NULL;
	}
}

struct AK3D_VERTEX *CAK3DModelMgr::FindVertex(struct AK3D_MODEL *pModel,unsigned long uPos)
{
	unsigned long uCurPos=0;
	AK_POS_PTR pos=pModel->VertexList.GetHeadPos();
	while(pos)
	{
		if(uCurPos==uPos)
		{
			struct AK3D_VERTEX *pVertex=(struct AK3D_VERTEX *)pModel->VertexList.GetValue(pos);
			return pVertex;
		}
		
		//下一个
		pModel->VertexList.Next(&pos);
		++uCurPos;
	}

	return NULL;
}

struct AK3D_VERTEX *CAK3DModelMgr::CreateVertex(
struct AK3D_MODEL *pModel,
	float x,float y,float z
	)
{
	struct AK3D_VERTEX *pVertex=new struct AK3D_VERTEX;
	if(!pVertex)return NULL;

	pVertex->x=x;
	pVertex->y=y;
	pVertex->z=z;

	if(!pModel->VertexList.AddTail(pVertex))
	{
		delete pVertex;
		return NULL;
	}

	return pVertex;
}

struct AK3D_POLYGON *CAK3DModelMgr::CreatePolygon(
struct AK3D_MODEL *pModel,
	unsigned char uCount,
	unsigned long uPos1,
	unsigned long uPos2,
	unsigned long uPos3,
	unsigned long uPos4
	)
{
	if(uCount!=3&&uCount!=4)return NULL;

	struct AK3D_POLYGON *pPolygon=new struct AK3D_POLYGON;
	if(!pPolygon)return NULL;

	pPolygon->r=255;
	pPolygon->g=255;
	pPolygon->b=255;
	pPolygon->uVertexCount=uCount;
	pPolygon->pVertexList[0]=FindVertex(pModel,uPos1);
	pPolygon->pVertexList[1]=FindVertex(pModel,uPos2);
	pPolygon->pVertexList[2]=FindVertex(pModel,uPos3);

	if(uCount==4)
	{
		pPolygon->pVertexList[3]=FindVertex(pModel,uPos4);
	}
	else
	{
		pPolygon->pVertexList[3]=NULL;
	}

	//默认UV
	pPolygon->UVList[0][0]=pPolygon->pVertexList[0]->x;
	pPolygon->UVList[0][1]=pPolygon->pVertexList[0]->y;
	pPolygon->UVList[1][0]=pPolygon->pVertexList[1]->x;
	pPolygon->UVList[1][1]=pPolygon->pVertexList[1]->y;
	pPolygon->UVList[2][0]=pPolygon->pVertexList[2]->x;
	pPolygon->UVList[2][1]=pPolygon->pVertexList[2]->y;
	pPolygon->UVList[3][0]=pPolygon->pVertexList[3]->x;
	pPolygon->UVList[3][1]=pPolygon->pVertexList[3]->y;

	bool rt=pModel->PolygonList.AddTail(pPolygon);
	if(rt)return pPolygon;
	else
	{
		delete pPolygon;
		return NULL;
	}
}

unsigned long CAK3DModelMgr::GetVertexPos(struct AK3D_MODEL *pModel,struct AK3D_VERTEX *pVertex)
{
	unsigned long i=0;
	AK_POS_PTR pos=pModel->VertexList.GetHeadPos();
	while(pos)
	{
		++i;
		struct AK3D_VERTEX *pCurVertex=(struct AK3D_VERTEX *)pModel->VertexList.GetValue(pos);
		if(pCurVertex==pVertex)return i;

		//下一个
		pModel->VertexList.Next(&pos);
	}

	return 0;
}

void CAK3DModelMgr::RandomModifModelVertex(struct AK3D_MODEL *pModel,long dx,long dy,long dz)
{
	AK_POS_PTR pos=pModel->VertexList.GetHeadPos();
	while(pos)
	{
		struct AK3D_VERTEX *pVertex=(struct AK3D_VERTEX *)pModel->VertexList.GetValue(pos);

		if(dx>0)
		{
			pVertex->x+=rand()%dx-(dx/2);
		}

		if(dy>0)
		{
			pVertex->y+=rand()%dy-(dy/2);
		}

		if(dz>0)
		{
			pVertex->z+=rand()%dz-(dz/2);
		}

		//下一个
		pModel->VertexList.Next(&pos);
	}
}

struct AK3D_MODEL *CAK3DModelMgr::CreateModel_Box(
		unsigned long uID,//模型ID
		float x,float y,float z,
		float width,float length,float height
		)
{
	struct AK3D_MODEL *pModel=CreateModel(uID);
	if(!pModel)return NULL;

	struct AK3D_POLYGON *pPolygon;

	//创建顶点表
	struct AK3D_VERTEX *v1=CreateVertex(pModel,x,y,z);
	struct AK3D_VERTEX *v2=CreateVertex(pModel,x,y+length,z);
	struct AK3D_VERTEX *v3=CreateVertex(pModel,x+width,y+length,z);
	CreateVertex(pModel,x+width,y,z);
	CreateVertex(pModel,x,y,z+height);
	CreateVertex(pModel,x,y+length,z+height);
	CreateVertex(pModel,x+width,y+length,z+height);
	CreateVertex(pModel,x+width,y,z+height);

	bool rt=CAK3DRender::GetInst()->IsPolygonDisplay(v1,v2,v3);

	if(!rt)
	{
		//创建多边形表
		pPolygon=CreatePolygon(pModel,4,0,1,2,3);
		if(pPolygon)
		{
			pPolygon->UVList[0][0]=0;
			pPolygon->UVList[0][1]=0;
			pPolygon->UVList[1][0]=0;
			pPolygon->UVList[1][1]=height-1;
			pPolygon->UVList[2][0]=width-1;
			pPolygon->UVList[2][1]=height-1;
			pPolygon->UVList[3][0]=width-1;
			pPolygon->UVList[3][1]=0;
		}
		CreatePolygon(pModel,4,7,6,5,4);
		CreatePolygon(pModel,4,0,4,5,1);
		CreatePolygon(pModel,4,2,6,7,3);
		CreatePolygon(pModel,4,1,5,6,2);
		CreatePolygon(pModel,4,3,7,4,0);
	}
	else
	{
		//创建多边形表
		CreatePolygon(pModel,4,3,2,1,0);
		CreatePolygon(pModel,4,4,5,6,7);
		CreatePolygon(pModel,4,1,5,4,0);
		CreatePolygon(pModel,4,3,7,6,2);
		CreatePolygon(pModel,4,2,6,5,1);
		CreatePolygon(pModel,4,0,4,7,3);
	}

	//设置顶点UV
	AK_POS_PTR pos=pModel->PolygonList.GetHeadPos();
	while(pos)
	{
		pPolygon=(struct AK3D_POLYGON *)pModel->PolygonList.GetValue(pos);

		pPolygon->UVList[0][0]=0;
		pPolygon->UVList[0][1]=0;
		pPolygon->UVList[1][0]=0;
		pPolygon->UVList[1][1]=400;
		pPolygon->UVList[2][0]=400;
		pPolygon->UVList[2][1]=400;
		pPolygon->UVList[3][0]=400;
		pPolygon->UVList[3][1]=0;

		//下一个
		pModel->PolygonList.Next(&pos);
	}

	pModel->xFocus=(x+width)/2;
	pModel->yFocus=(y+length)/2;
	pModel->zFocus=z;

	return pModel;
}

struct AK3D_MODEL *CAK3DModelMgr::CreateModel_Gridding(
		unsigned long uID,//模型ID
		float x,float y,float z,
		float width,float length,
		long rows,long cols
		)
{
	struct AK3D_MODEL *pModel=CreateModel(uID);
	if(!pModel)return NULL;

	float GridWidth=width/cols;
	float GridLength=length/rows;

	long VertexCount=(rows+1)*(cols+1);

	//创建顶点表
	long i,CurRow=0,CurCol=0;
	for(CurRow=0;CurRow<=rows;++CurRow)
	{
		for(CurCol=0;CurCol<=cols;++CurCol)
		{
			CreateVertex(pModel,x+CurCol*GridWidth,y+CurRow*GridLength,z);
		}
	}

	/*for(i=0;i<VertexCount;++i)
	{
		CreateVertex(pModel,x+CurCol*GridWidth,y+CurRow*GridLength,z);
		++CurCol;
		if(CurCol>=cols)
		{
			CurCol=0;
			++CurRow;
		}
	}*/

	//创建多边形表
	long j,pos1,pos2,pos3,pos4;
	for(i=0;i<rows;++i)
	{
		for(j=0;j<cols;++j)
		{
			pos1=i*(cols+1)+j;
			pos2=i*(cols+1)+(j+1);
			pos3=(i+1)*(cols+1)+(j+1);
			pos4=(i+1)*(cols+1)+j;

			struct AK3D_POLYGON *pPolygon=CreatePolygon(pModel,4,pos1,pos2,pos3,pos4);
		}
	}

	pModel->xFocus=(x+width)/2;
	pModel->yFocus=(y+length)/2;
	pModel->zFocus=z;

	return pModel;
}

