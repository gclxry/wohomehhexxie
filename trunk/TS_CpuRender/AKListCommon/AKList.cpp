#include "stdafx.h"

#include "AKList.h"

CAKList::CAKList()
{
	m_pHead=m_pTail=NULL;

	m_Count=0;

	m_IsAutoFreeValue=true;
}

CAKList::~CAKList()
{
	//�ͷ�����Ԫ��
	ClearAll();
}

bool CAKList::AddHead(void *pValue)
{
	struct AK_POS *pNew=new struct AK_POS;
	
	if(!pNew)return false;

	pNew->pPre=pNew->pNext=NULL;

	pNew->pValue=pValue;
	
	if(m_Count<=0)//�����ǿյ�
	{
		m_pHead=m_pTail=pNew;
	}
	else//����Ϊ��
	{
		//��Ԫ������ԭͷ��Ԫ��
		pNew->pNext=m_pHead;
		
		//ԭͷ��Ԫ��������Ԫ��
		m_pHead->pPre=pNew;
		
		//����ͷָ����Ԫ��
		m_pHead=pNew;
	}
	
	//Ԫ��������1
	++m_Count;

	return true;
}

bool CAKList::AddTail(void *pValue)
{
	struct AK_POS *pNew=new struct AK_POS;
	
	if(!pNew)return false;

	pNew->pPre=pNew->pNext=NULL;

	pNew->pValue=pValue;
	
	if(m_Count<=0)//�����ǿյ�
	{
		m_pHead=m_pTail=pNew;
	}
	else//����Ϊ��
	{
		//��Ԫ������ԭβ��Ԫ��
		pNew->pPre=m_pTail;
		
		//ԭβ��Ԫ��������Ԫ��
		m_pTail->pNext=pNew;
		
		//����βָ����Ԫ��
		m_pTail=pNew;
	}
	
	//Ԫ��������1
	++m_Count;

	return true;
}

AK_POS_PTR CAKList::GetHeadPos()
{
	return m_pHead;
}

AK_POS_PTR CAKList::GetTailPos()
{
	return m_pTail;
}

void *CAKList::GetValue(AK_POS_PTR pPos)
{
	return pPos->pValue;
}

void CAKList::Next(AK_POS_PTR *ppPos)
{
	*ppPos=(*ppPos)->pNext;
}

void CAKList::Pre(AK_POS_PTR *ppPos)
{
	*ppPos=(*ppPos)->pPre;
}

void CAKList::ClearAll()
{
	AK_POS_PTR pPos=m_pHead,pPos2;

	while(pPos)
	{
		pPos2=pPos;
		
		pPos=pPos->pNext;

		if(m_IsAutoFreeValue)
			delete[] pPos2->pValue;
		
		delete pPos2;
	}

	m_pHead=m_pTail=NULL;

	m_Count=0;

}

void CAKList::Remove(AK_POS_PTR pPos)
{
	AK_POS_PTR pPre=pPos->pPre;
	AK_POS_PTR pNext=pPos->pNext;

	//ֻ��һ��Ԫ��(pPosͬʱΪ����ͷ��Ҳ��β��)
	if((!pNext)&&(!pPre))
	{
		if(m_IsAutoFreeValue)
			delete[] pPos->pValue;

		delete pPos;

		m_pHead=m_pTail=NULL;

		m_Count=0;

		return;
	}

	//���pPos֮ǰ��֮����Ԫ��
	if(pPre&&pNext)
	{
		//pPos֮ǰԪ������pPos֮��Ԫ��
		pPre->pNext=pNext;

		//pPos֮��Ԫ������pPos֮ǰԪ��
		pNext->pPre=pPre;

		if(m_IsAutoFreeValue)
			delete[] pPos->pValue;

		delete pPos;

		--m_Count;

		return;
	}

	//pPos������β��,ֻ��pPos֮ǰ��Ԫ��(ǰ���Ѿ�˵��pPre��pNext����ͬʱ����)
	if(pPre)
	{
		//��־pPos֮ǰԪ��ָ����һ��Ԫ��ΪNULL
		pPre->pNext=NULL;

		//����β��ָ��pPos֮ǰԪ��
		m_pTail=pPre;

		if(m_IsAutoFreeValue)
			delete[] pPos->pValue;
		
		delete pPos;

		--m_Count;

		return;
	}

	//pPos������ͷ��,ֻ��pPos֮����Ԫ��(ǰ���Ѿ�˵��pPre��pNext����ͬʱ����)
	if(pNext)
	{
		//��־pPos֮��Ԫ��ָ����һ��Ԫ��ΪNULL
		pNext->pPre=NULL;

		//����ͷ��ָ��pPos֮��Ԫ��
		m_pHead=pNext;

		if(m_IsAutoFreeValue)
			delete[] pPos->pValue;
		
		delete pPos;

		--m_Count;

		return;
	}

	
	
}

void CAKList::Change(AK_POS_PTR pPos1,AK_POS_PTR pPos2)
{
	void *pTmp=pPos1->pValue;

	pPos1->pValue=pPos2->pValue;

	pPos2->pValue=pTmp;
}

unsigned long CAKList::GetCount()
{
	return m_Count;
}

void CAKList::SetAutoFreeValue(bool t)
{
	m_IsAutoFreeValue=t;
}


