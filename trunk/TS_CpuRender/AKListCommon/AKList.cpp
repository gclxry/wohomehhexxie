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
	//释放链表元素
	ClearAll();
}

bool CAKList::AddHead(void *pValue)
{
	struct AK_POS *pNew=new struct AK_POS;
	
	if(!pNew)return false;

	pNew->pPre=pNew->pNext=NULL;

	pNew->pValue=pValue;
	
	if(m_Count<=0)//链表是空的
	{
		m_pHead=m_pTail=pNew;
	}
	else//链表不为空
	{
		//新元素捆绑原头部元素
		pNew->pNext=m_pHead;
		
		//原头部元素捆绑新元素
		m_pHead->pPre=pNew;
		
		//链表头指向新元素
		m_pHead=pNew;
	}
	
	//元素数量加1
	++m_Count;

	return true;
}

bool CAKList::AddTail(void *pValue)
{
	struct AK_POS *pNew=new struct AK_POS;
	
	if(!pNew)return false;

	pNew->pPre=pNew->pNext=NULL;

	pNew->pValue=pValue;
	
	if(m_Count<=0)//链表是空的
	{
		m_pHead=m_pTail=pNew;
	}
	else//链表不为空
	{
		//新元素捆绑原尾部元素
		pNew->pPre=m_pTail;
		
		//原尾部元素捆绑新元素
		m_pTail->pNext=pNew;
		
		//链表尾指向新元素
		m_pTail=pNew;
	}
	
	//元素数量加1
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

	//只有一个元素(pPos同时为链表头部也是尾部)
	if((!pNext)&&(!pPre))
	{
		if(m_IsAutoFreeValue)
			delete[] pPos->pValue;

		delete pPos;

		m_pHead=m_pTail=NULL;

		m_Count=0;

		return;
	}

	//如果pPos之前和之后都有元素
	if(pPre&&pNext)
	{
		//pPos之前元素链接pPos之后元素
		pPre->pNext=pNext;

		//pPos之后元素链接pPos之前元素
		pNext->pPre=pPre;

		if(m_IsAutoFreeValue)
			delete[] pPos->pValue;

		delete pPos;

		--m_Count;

		return;
	}

	//pPos是链表尾部,只有pPos之前有元素(前面已经说明pPre和pNext不会同时存在)
	if(pPre)
	{
		//标志pPos之前元素指向下一个元素为NULL
		pPre->pNext=NULL;

		//链表尾部指向pPos之前元素
		m_pTail=pPre;

		if(m_IsAutoFreeValue)
			delete[] pPos->pValue;
		
		delete pPos;

		--m_Count;

		return;
	}

	//pPos是链表头部,只有pPos之后有元素(前面已经说明pPre和pNext不会同时存在)
	if(pNext)
	{
		//标志pPos之后元素指向上一个元素为NULL
		pNext->pPre=NULL;

		//链表头部指向pPos之后元素
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


