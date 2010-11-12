#include "stdafx.h"

#include "AK2DUI.h"

CAK2DUI::CAK2DUI()
{
	m_pOnFocusUI=NULL;
	m_pOnLBtnDownUI=NULL;
	m_pOnMouseOverUI=NULL;

	m_uEventCount=0;
	m_uEventListPointer=0;

	m_ScrX=0;
	m_ScrY=0;
}

CAK2DUI::~CAK2DUI()
{
	FreeUIList();
	FreePicList();
}

void CAK2DUI::FreePicList()
{
	AK_POS_PTR pos2;
	AK_POS_PTR pos=m_PicList.GetHeadPos();
	while(pos)
	{
		pos2=pos;

		struct AK_2D_UI_PIC *pPic=(struct AK_2D_UI_PIC *)m_PicList.GetValue(pos);

		//��һ��
		m_PicList.Next(&pos);

		delete [] pPic->pData;

		m_PicList.Remove(pos2);
	}
}

void CAK2DUI::RemoveUI(struct AK_2D_UI *pUI)
{
	m_pOnMouseOverUI=NULL;
	m_pOnLBtnDownUI=NULL;
	m_pOnFocusUI=NULL;
	m_uEventCount=0;
	m_uEventListPointer=0;

	//ɾ���Ӽ�UI
	FreeUIList(&pUI->SonList);
	
	if(pUI->uParentID==0)
	{
		AK_POS_PTR pos=m_UIList.GetHeadPos();
		while(pos)
		{
			struct AK_2D_UI *pCurUI=(struct AK_2D_UI *)m_UIList.GetValue(pos);
			if(pCurUI==pUI)
			{
				//ɾ��UI��ͼ�б�
				pUI->EventPicList.ClearAll();
				if(pUI->pStr)delete [] pUI->pStr;

				m_UIList.Remove(pos);
				break;
			}

			//��һ��
			m_UIList.Next(&pos);
		}
	}
	else
	{
		struct AK_2D_UI *pParentUI=GetUI(pUI->uParentID);
		if(pParentUI)
		{
			AK_POS_PTR pos=pParentUI->SonList.GetHeadPos();
			while(pos)
			{
				struct AK_2D_UI *pCurUI=(struct AK_2D_UI *)pParentUI->SonList.GetValue(pos);
				if(pCurUI==pUI)
				{
					//ɾ��UI��ͼ�б�
					pUI->EventPicList.ClearAll();
					if(pUI->pStr)delete [] pUI->pStr;

					pParentUI->SonList.Remove(pos);
					break;
				}

				//��һ��
				pParentUI->SonList.Next(&pos);
			}
		}
	}
}

void CAK2DUI::FreeUIList(CAKList *pList)
{
	if(!pList)pList=&m_UIList;

	AK_POS_PTR pos2;
	AK_POS_PTR pos=pList->GetHeadPos();
	while(pos)
	{
		pos2=pos;

		struct AK_2D_UI *pUI=(struct AK_2D_UI *)pList->GetValue(pos);

		//�ݹ�ɾ���Ӽ�
		FreeUIList(&pUI->SonList);

		//ɾ��UI��ͼ�б�
		pUI->EventPicList.ClearAll();

		//��һ��
		m_UIList.Next(&pos);
		
		if(pUI->pStr)delete [] pUI->pStr;
		pList->Remove(pos2);
	}
}

struct AK_2D_UI * CAK2DUI::TouchNearUI(float x,float y,CAKList *pList,float xx,float yy)
{
	if(!pList)pList=&m_UIList;

	AK_POS_PTR pos=pList->GetHeadPos();
	while(pos)
	{
		struct AK_2D_UI *pUI=(struct AK_2D_UI *)pList->GetValue(pos);

		//�ݹ����Ӽ�UI��û���Ӵ�
		if(pUI->IsCheckTouch&&pUI->IsDisplayMyself)
		{
			struct AK_2D_UI *pCurUI=TouchNearUI(x,y,&pUI->SonList,pUI->x+xx,pUI->y+yy);
			if(pCurUI)return pCurUI;
		}

		float x_min=pUI->x+xx;
		float x_max=x_min+pUI->uWidth;
		float y_min=pUI->y+yy;
		float y_max=y_min+pUI->uHeight;

		if(x>=x_min&&x<=x_max&&y>=y_min&&y<=y_max&&pUI->IsCheckTouch&&pUI->IsDisplayMyself)
		{
			return pUI;
		}

		//��һ��
		pList->Next(&pos);
	}

	return NULL;
}

struct AK_2DUI_EVENT * CAK2DUI::GerFreeEvent()
{
	//���㵱ǰ��Ϣʹ�õ��б��±�
	unsigned long uCurPointer=m_uEventListPointer+m_uEventCount;
	uCurPointer%=AK_2DUI_EVENT_MAX_COUNT;
	
	//��Ϣ��������
	++m_uEventCount;
	if(m_uEventCount>AK_2DUI_EVENT_MAX_COUNT)
	{
		//��Ϣͷָ�����
		++m_uEventListPointer;
		if(m_uEventListPointer>AK_2DUI_EVENT_MAX_COUNT)
		{
			m_uEventListPointer%=AK_2DUI_EVENT_MAX_COUNT;
		}
		
		m_uEventCount=AK_2DUI_EVENT_MAX_COUNT;
	}

	return &m_EventList[uCurPointer];
}

bool CAK2DUI::GetEvent(struct AK_2DUI_EVENT &event)
{
	if(m_uEventCount>0)
	{
		memcpy(&event,&m_EventList[m_uEventListPointer],sizeof(struct AK_2DUI_EVENT));

		--m_uEventCount;
		++m_uEventListPointer;
		m_uEventListPointer%=AK_2DUI_EVENT_MAX_COUNT;

		return true;
	}
	else return false;
}

void CAK2DUI::SetUIFocus(struct AK_2D_UI *pUI)
{
	AK_POS_PTR pos=m_UIList.GetHeadPos();
	while(pos)
	{
		struct AK_2D_UI *pCurUI=(struct AK_2D_UI *)m_UIList.GetValue(pos);

		//�ҵ�pUI��pos��
		if(pCurUI==pUI)break;

		//��һ��
		m_UIList.Next(&pos);
	}

	AK_POS_PTR pos2;

	if(pos)
	{
		m_pOnFocusUI=pUI;

		while(true)
		{
			pos2=pos;
			//��һ��
			m_UIList.Pre(&pos);

			if(pos)m_UIList.Change(pos,pos2);
			else break;
		}
	}
}

void CAK2DUI::SendLBtnDown(float x,float y)
{
	struct AK_2DUI_EVENT *pEvent=GerFreeEvent();

	pEvent->x=x;
	pEvent->y=y;
	pEvent->uEventID=AK_2DUI_EVENT_LBTN_DOWN;

	struct AK_2D_UI *pCurUI=TouchNearUI(x,y);

	//���Ӵ���UI
	if(pCurUI)
	{
		pEvent->uID=pCurUI->uID;

		pCurUI->uEventID=pEvent->uEventID;

		//���ý���(pCurUI�ö�)
		SetUIFocus(pCurUI);
	}
	else pEvent->uID=0;

	if(pCurUI)
	{
		//��ǰ��������µ�UI
		m_pOnLBtnDownUI=pCurUI;

		//��ǰ����
		m_OldX=x;
		m_OldY=y;
	}
}

void CAK2DUI::SendLBtnDClk(float x,float y)
{
	struct AK_2DUI_EVENT *pEvent=GerFreeEvent();

	pEvent->x=x;
	pEvent->y=y;
	pEvent->uEventID=AK_2DUI_EVENT_LBTN_DCLK;

	struct AK_2D_UI *pCurUI=TouchNearUI(x,y);

	//���Ӵ���UI
	if(pCurUI)
	{
		pEvent->uID=pCurUI->uID;

		pCurUI->uEventID=pEvent->uEventID;

		//���ý���(pCurUI�ö�)
		SetUIFocus(pCurUI);
	}
	else pEvent->uID=0;

	if(pCurUI)
	{
		//��ǰ��������µ�UI
		m_pOnLBtnDownUI=pCurUI;

		//��ǰ����
		m_OldX=x;
		m_OldY=y;
	}
}

void CAK2DUI::SendLBtnUp(float x,float y)
{
	struct AK_2DUI_EVENT *pEvent=GerFreeEvent();

	pEvent->x=x;
	pEvent->y=y;
	pEvent->uEventID=AK_2DUI_EVENT_LBTN_UP;

	struct AK_2D_UI *pCurUI=TouchNearUI(x,y);

	//���Ӵ���UI
	if(pCurUI)
	{
		pEvent->uID=pCurUI->uID;

		pCurUI->uEventID=pEvent->uEventID;
	}
	else pEvent->uID=0;

	m_pOnLBtnDownUI=NULL;
}

void CAK2DUI::SendRBtnDown(float x,float y)
{
	struct AK_2DUI_EVENT *pEvent=GerFreeEvent();

	pEvent->x=x;
	pEvent->y=y;
	pEvent->uEventID=AK_2DUI_EVENT_RBTN_DOWN;

	struct AK_2D_UI *pCurUI=TouchNearUI(x,y);

	//���Ӵ���UI
	if(pCurUI)
	{
		pEvent->uID=pCurUI->uID;

		pCurUI->uEventID=pEvent->uEventID;
	}
	else pEvent->uID=0;
}

void CAK2DUI::SendRBtnDClk(float x,float y)
{
	struct AK_2DUI_EVENT *pEvent=GerFreeEvent();

	pEvent->x=x;
	pEvent->y=y;
	pEvent->uEventID=AK_2DUI_EVENT_RBTN_DCLK;

	struct AK_2D_UI *pCurUI=TouchNearUI(x,y);

	//���Ӵ���UI
	if(pCurUI)
	{
		pEvent->uID=pCurUI->uID;

		pCurUI->uEventID=pEvent->uEventID;
	}
	else pEvent->uID=0;
}

void CAK2DUI::SendRBtnUp(float x,float y)
{
	struct AK_2DUI_EVENT *pEvent=GerFreeEvent();

	pEvent->x=x;
	pEvent->y=y;
	pEvent->uEventID=AK_2DUI_EVENT_RBTN_UP;

	struct AK_2D_UI *pCurUI=TouchNearUI(x,y);

	//���Ӵ���UI
	if(pCurUI)
	{
		pEvent->uID=pCurUI->uID;

		pCurUI->uEventID=pEvent->uEventID;
	}
	else pEvent->uID=0;
}

void CAK2DUI::SendMouseMove(float x,float y)
{
	struct AK_2DUI_EVENT *pEvent=GerFreeEvent();

	pEvent->x=x;
	pEvent->y=y;
	pEvent->uEventID=AK_2DUI_EVENT_MOUSE_MOVE;

	struct AK_2D_UI *pCurUI=TouchNearUI(x,y);

	//���Ӵ���UI
	if(pCurUI)
	{
		pEvent->uID=pCurUI->uID;
	}
	else pEvent->uID=0;

	//�������UI
	if(pCurUI&&!m_pOnMouseOverUI)
	{
		struct AK_2DUI_EVENT *pEvent2=GerFreeEvent();

		pEvent2->uID=pEvent->uID;
		pEvent2->x=x;
		pEvent2->y=y;
		pEvent2->uEventID=AK_2DUI_EVENT_MOUSE_OVER;

		pCurUI->uEventID=pEvent2->uEventID;

		//��ǰ���������UI
		m_pOnMouseOverUI=pCurUI;
	}
	else
	{
		//����Ƴ�UI
		if(m_pOnMouseOverUI&&pCurUI!=m_pOnMouseOverUI)
		{
			struct AK_2DUI_EVENT *pEvent2=GerFreeEvent();

			pEvent2->uID=m_pOnMouseOverUI->uID;
			pEvent2->x=x;
			pEvent2->y=y;
			pEvent2->uEventID=AK_2DUI_EVENT_MOUSE_OUT;

			m_pOnMouseOverUI->uEventID=pEvent2->uEventID;

			m_pOnMouseOverUI=NULL;
		}
	}

	//UI���϶�
	if(m_pOnLBtnDownUI&&m_pOnLBtnDownUI->IsAllowMove)
	{
		float dx=x-m_OldX;
		float dy=y-m_OldY;

		m_OldX=x;
		m_OldY=y;

		m_pOnLBtnDownUI->x+=dx;
		m_pOnLBtnDownUI->y+=dy;
	}
}

void CAK2DUI::DisplayUI(unsigned short uPicDrawID,CAKList *pUIList,struct AK_2D_UI *pParentUI,float x,float y)
{
	if(!pUIList)
	{
		pUIList=&m_UIList;
	}

	AK_POS_PTR pos=pUIList->GetTailPos();
	while(pos)
	{
		struct AK_2D_UI *pUI=(struct AK_2D_UI *)pUIList->GetValue(pos);

		if(!pParentUI&&pUI->uParentID!=0)
		{
		}
		else
		{
			//��ʾ����
			if(pUI->IsDisplayMyself)
			{
				if(pUI->IsDisplayBack)
				{
					CAKPicDraw::GetInst(uPicDrawID)->SetAlpha(pUI->uAlpha);
					
					//�Ҷ�Ӧ��ǰ״̬����ͼ��Ϣ
					struct AK_UI_EVENT_UV *pUIEventUV=FindUIEventUV(pUI,pUI->uEventID);
					if(pUIEventUV)
					{
						//Դλͼ
						CAKPicDraw::GetInst(AK_PIC_DRAW_MAX_COUNT-1)->SelectPic(pUIEventUV->pUIPic->pData,pUIEventUV->pUIPic->uWidth,pUIEventUV->pUIPic->uHeight);

						unsigned long uColor;
						unsigned char *pColor=(unsigned char *)&uColor;

						long i,j;
						long i_max=pUIEventUV->v+pUIEventUV->Height;
						long j_max=pUIEventUV->u+pUIEventUV->Width;

						long xx,yy;

						if(pUI->uAlpha==255)
						{
							for(yy=0,i=pUIEventUV->v;i<i_max;++yy,++i)//��
							{
								for(xx=0,j=pUIEventUV->u;j<j_max;++xx,++j)//��
								{
									//����ͼȡ����
									uColor=CAKPicDraw::GetInst(AK_PIC_DRAW_MAX_COUNT-1)->GetPixel(j,i);

									//�������͸��ɫ
									if(pColor[2]!=pUIEventUV->r||pColor[1]!=pUIEventUV->g||pColor[0]!=pUIEventUV->b)
									{
										CAKPicDraw::GetInst(uPicDrawID)->SetPenColor(pColor[2],pColor[1],pColor[0]);

										//��������
										CAKPicDraw::GetInst(uPicDrawID)->SetPixel(pUI->x+xx+x+m_ScrX,pUI->y+yy+y+m_ScrY);
									}
								}
							}
						}
						else
						{
							for(yy=0,i=pUIEventUV->v;i<i_max;++yy,++i)//��
							{
								for(xx=0,j=pUIEventUV->u;j<j_max;++xx,++j)//��
								{
									//����ͼȡ����
									uColor=CAKPicDraw::GetInst(AK_PIC_DRAW_MAX_COUNT-1)->GetPixel(j,i);

									//�������͸��ɫ
									if(pColor[2]!=pUIEventUV->r||pColor[1]!=pUIEventUV->g||pColor[0]!=pUIEventUV->b)
									{
										CAKPicDraw::GetInst(uPicDrawID)->SetPenColor(pColor[2],pColor[1],pColor[0]);

										//��������
										CAKPicDraw::GetInst(uPicDrawID)->SetPixelEX(pUI->x+xx+x+m_ScrX,pUI->y+yy+y+m_ScrY);
									}
								}
							}
						}

					}
					else
					{
						//��ʾUI����
						CAKPicDraw::GetInst(uPicDrawID)->SetPenColor(pUI->r,pUI->g,pUI->b);
						CAKPicDraw::GetInst(uPicDrawID)->FillRectEX(
							pUI->x+x+m_ScrX,pUI->y+y+m_ScrY,
							pUI->x+x+pUI->uWidth+m_ScrX,pUI->y+y+pUI->uHeight+m_ScrY
							);
					}
				}

				//��ʾUI�ı�
				if(pUI->pStr)
				{
					CAKPicDraw::GetInst(uPicDrawID)->SetAlpha(pUI->uAlpha);
					CAKPicDraw::GetInst(uPicDrawID)->SetPenColor(pUI->r_txt,pUI->g_txt,pUI->b_txt);
					CAKPicDraw::GetInst(uPicDrawID)->SetFontHeight(pUI->FontHeight,pUI->RowSpace,pUI->WordSpace);
					CAKPicDraw::GetInst(uPicDrawID)->TextOut(pUI->x+x+m_ScrX,pUI->y+y+m_ScrY,pUI->pStr,pUI->uWidth);
				}

				//��ʾ�ӿؼ��б�
				if(pUI->IsDisplaySonList)
				{
					DisplayUI(uPicDrawID,&pUI->SonList,pUI,x+pUI->x,y+pUI->y);
				}
			}
		}

		//��һ��
		pUIList->Pre(&pos);
	}
}

bool CAK2DUI::Join(struct AK_2D_UI *pParentUI,struct AK_2D_UI *pSonUI)
{
	if(pParentUI==pSonUI)return false;

	//�����ԭ���ĸ��ؼ�������
	if(pSonUI->uParentID!=0)
	{
		struct AK_2D_UI *pOldParentUI=GetUI(pSonUI->uParentID);
		if(pOldParentUI)
		{
			//�µĸ�����ԭ���ĸ�����һ����
			if(pOldParentUI==pParentUI)return true;

			AK_POS_PTR pos=pOldParentUI->SonList.GetHeadPos();
			while(pos)
			{
				struct AK_2D_UI *pUI=(struct AK_2D_UI *)pOldParentUI->SonList.GetValue(pos);
				if(pUI==pSonUI)
				{
					pOldParentUI->SonList.SetAutoFreeValue(false);
					pOldParentUI->SonList.Remove(pos);
					pOldParentUI->SonList.SetAutoFreeValue(true);
					break;
				}

				//��һ��
				pOldParentUI->SonList.Next(&pos);
			}
		}
	}
	else
	{
		AK_POS_PTR pos=m_UIList.GetHeadPos();
		while(pos)
		{
			struct AK_2D_UI *pUI=(struct AK_2D_UI *)m_UIList.GetValue(pos);
			if(pUI==pSonUI)
			{
				m_UIList.SetAutoFreeValue(false);
				m_UIList.Remove(pos);
				m_UIList.SetAutoFreeValue(true);
				break;
			}

			//��һ��
			m_UIList.Next(&pos);
		}
	}

	if(pParentUI)
	{
		pSonUI->uParentID=pParentUI->uID;
		return pParentUI->SonList.AddTail(pSonUI);
	}
	else
	{
		pSonUI->uParentID=0;
		return m_UIList.AddTail(pSonUI);
	}

}

struct AK_2D_UI * CAK2DUI::GetUI(unsigned long uID,CAKList *pList)
{
	if(!pList)pList=&m_UIList;

	//�ҵ�ǰ��
	AK_POS_PTR pos=pList->GetHeadPos();
	while(pos)
	{
		struct AK_2D_UI *pUI=(struct AK_2D_UI *)pList->GetValue(pos);
		if(pUI->uID==uID)return pUI;

		//��һ��
		pList->Next(&pos);
	}

	//���Ӽ�
	pos=pList->GetHeadPos();
	while(pos)
	{
		struct AK_2D_UI *pUI=(struct AK_2D_UI *)pList->GetValue(pos);

		//�ݹ���
		struct AK_2D_UI *pRtUI=GetUI(uID,&pUI->SonList);
		if(pRtUI)return pRtUI;

		//��һ��
		pList->Next(&pos);
	}

	return NULL;
}

void CAK2DUI::SetTextColor(struct AK_2D_UI *pUI,unsigned char r,unsigned char g,unsigned char b)
{
	pUI->r_txt=r;
	pUI->g_txt=g;
	pUI->b_txt=b;
}

void CAK2DUI::SetUIColor(struct AK_2D_UI *pUI,unsigned char r,unsigned char g,unsigned char b)
{
	pUI->r=r;
	pUI->g=g;
	pUI->b=b;
}

bool CAK2DUI::SetUIText(struct AK_2D_UI *pUI,char *pStr)
{
	if(!pUI->pStr)
		return false;

	unsigned long uLength=strlen(pStr);
	if(uLength>pUI->uStrLength)
		return false;

	strcpy(pUI->pStr,pStr);
	return true;
}

bool CAK2DUI::SetUITextLength(struct AK_2D_UI *pUI,unsigned long uLength)
{
	if(pUI->pStr)delete [] pUI->pStr;

	pUI->pStr=new char[uLength+1];
	if(!pUI->pStr)
	{
		pUI->uStrLength=0;
		return false;
	}

	pUI->uStrLength=uLength;
	pUI->pStr[0] = '\0';

	return true;
}

struct AK_2D_UI * CAK2DUI::CreateUI(unsigned long uID,float x,float y,unsigned long uWidth,unsigned long uHeight,unsigned long uStatus)
{
	if(uID==0)return NULL;

	if(GetUI(uID))return NULL;

	struct AK_2D_UI *pNew=new struct AK_2D_UI;
	
	pNew->uID=uID;
	
	pNew->x=x;
	pNew->y=y;
	
	pNew->uWidth=uWidth;
	pNew->uHeight=uHeight;
	
	pNew->IsActivation=true;
	pNew->IsDisplayMyself=true;
	pNew->IsDisplaySonList=true;
	pNew->IsDisplayBack=true;
	pNew->IsAllowMove=false;
	pNew->IsCheckTouch=true;
	
	pNew->pStr=NULL;
	pNew->uStrLength=0;
	pNew->FontHeight=16;
	pNew->RowSpace=2;
	pNew->WordSpace=2;

	pNew->uParentID=0;
	pNew->uEventID=0;

	pNew->r=255;
	pNew->g=255;
	pNew->b=255;
	pNew->uAlpha=255;

	pNew->pAttrib=NULL;

	bool rt=m_UIList.AddTail(pNew);
	if(rt)return pNew;
	else
	{
		delete [] pNew;
		return NULL;
	}
}

struct AK_2D_UI_PIC * CAK2DUI::FindUIPic(unsigned long uID)
{
	AK_POS_PTR pos=m_PicList.GetHeadPos();
	while(pos)
	{
		struct AK_2D_UI_PIC *pUIPic=(struct AK_2D_UI_PIC *)m_PicList.GetValue(pos);
		if(pUIPic->uID==uID)return pUIPic;

		//��һ��
		m_PicList.Next(&pos);
	}

	return NULL;
}

struct AK_2D_UI_PIC * CAK2DUI::CreateUIPic(unsigned long uID,unsigned long uWidth,unsigned long uHeight)
{
	struct AK_2D_UI_PIC *pUIPic=FindUIPic(uID);
	if(pUIPic)return NULL;//��ͼID�ظ�

	struct AK_2D_UI_PIC *pNew=new struct AK_2D_UI_PIC;
	if(!pNew)return NULL;

	unsigned long uLength=uWidth*uHeight*4;

	pNew->pData=new unsigned char[uLength];
	if(!pNew->pData)
	{
		delete pNew;
		return NULL;
	}
	memset(pNew->pData,0,uLength);

	pNew->uWidth=uWidth;
	pNew->uHeight=uHeight;

	pNew->uID=uID;

	bool rt=m_PicList.AddTail(pNew);
	if(rt)return pNew;
	else
	{
		delete [] pNew->pData;
		delete pNew;
		return NULL;
	}
}

struct AK_UI_EVENT_UV * CAK2DUI::FindUIEventUV(struct AK_2D_UI *pUI,unsigned long uEventID)
{
	AK_POS_PTR pos=pUI->EventPicList.GetHeadPos();
	while(pos)
	{
		struct AK_UI_EVENT_UV *pUIEventUV=(struct AK_UI_EVENT_UV *)pUI->EventPicList.GetValue(pos);
		if(pUIEventUV->uEventID==uEventID)return pUIEventUV;

		//��һ��
		pUI->EventPicList.Next(&pos);
	}

	return NULL;
}

struct AK_UI_EVENT_UV * CAK2DUI::SetUIEventUV(struct AK_2D_UI *pUI,unsigned long uEventID,unsigned long uPicID,long u,long v,long Width,long Height,
	unsigned char r,unsigned char g,unsigned char b)
{
	//����������¼���ͼ,���Զ����������¼���ͼ
	if(uEventID==AK_2DUI_EVENT_NONE)
	{
		CAK2DUI::GetSingle().SetUIEventUV(pUI,AK_2DUI_EVENT_MOUSE_OVER,uPicID,u,v,Width,Height);
		CAK2DUI::GetSingle().SetUIEventUV(pUI,AK_2DUI_EVENT_MOUSE_OUT,uPicID,u,v,Width,Height);

		CAK2DUI::GetSingle().SetUIEventUV(pUI,AK_2DUI_EVENT_LBTN_DOWN,uPicID,u,v,Width,Height);
		CAK2DUI::GetSingle().SetUIEventUV(pUI,AK_2DUI_EVENT_LBTN_DCLK,uPicID,u,v,Width,Height);
		CAK2DUI::GetSingle().SetUIEventUV(pUI,AK_2DUI_EVENT_LBTN_UP,uPicID,u,v,Width,Height);

		CAK2DUI::GetSingle().SetUIEventUV(pUI,AK_2DUI_EVENT_RBTN_DOWN,uPicID,u,v,Width,Height);
		CAK2DUI::GetSingle().SetUIEventUV(pUI,AK_2DUI_EVENT_RBTN_DCLK,uPicID,u,v,Width,Height);
		CAK2DUI::GetSingle().SetUIEventUV(pUI,AK_2DUI_EVENT_RBTN_UP,uPicID,u,v,Width,Height);
	}

	//����ͼ
	struct AK_2D_UI_PIC *pUIPic=FindUIPic(uPicID);
	if(!pUIPic)return NULL;
	
	//����ͼUV��Ϣ
	struct AK_UI_EVENT_UV *pUIEventUV=FindUIEventUV(pUI,uEventID);

	if(!pUIEventUV)
	{
		pUIEventUV=new struct AK_UI_EVENT_UV;
		if(!pUIEventUV)return NULL;
		
		bool rt=pUI->EventPicList.AddTail(pUIEventUV);
		if(!rt)
		{
			delete pUIEventUV;
			return NULL;
		}
	}
	
	pUIEventUV->uPicID=uPicID;
	pUIEventUV->pUIPic=pUIPic;
	pUIEventUV->u=u;
	pUIEventUV->v=v;
	pUIEventUV->Width=Width;
	pUIEventUV->Height=Height;
	pUIEventUV->uEventID=uEventID;
	pUIEventUV->r=r;
	pUIEventUV->g=g;
	pUIEventUV->b=b;

	return pUIEventUV;
}

