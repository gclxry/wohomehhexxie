
#include "stdafx.h"
#include "TList.h"

CTList::CTList(void)
{
	Init();
}

CTList::~CTList(void)
{

}

void CTList::Init(void)
{
	ListHeader.pPrior = ListHeader.pNext = &ListHeader;
}

BOOL CTList::IsEmpty(void)
{
	return (ListHeader.pNext == &ListHeader);
}

// 添加到队列的末尾，环形列表
void CTList::AddObj(ListObj *pListObj)
{
	if (pListObj != NULL)
	{
		pListObj->pPrior = ListHeader.pPrior;
		pListObj->pNext = &ListHeader;
		ListHeader.pPrior->pNext = pListObj;
		ListHeader.pPrior = pListObj;
	}
}

void CTList::DelObj(ListObj *pListObj)
{
	if (pListObj != NULL)
	{
		if (pListObj->pNext != NULL)
		{
			pListObj->pNext->pPrior = pListObj->pPrior;
		}

		if (pListObj->pPrior != NULL)
		{
			pListObj->pPrior->pNext = pListObj->pNext;
		}

		pListObj->pNext = pListObj->pPrior = NULL;
	}
}

ListObj* CTList::TopObj(void)
{
	return ((ListHeader.pNext == &ListHeader) ? NULL : ListHeader.pNext);
}

ListObj* CTList::NextObj(ListObj *pListObj)
{
	ListObj* pRetObj = NULL;

	if (pListObj != NULL)
		pRetObj = ((pListObj->pNext == &ListHeader) ? NULL : pListObj->pNext);

	return pRetObj;
}

void CTList::MoveList(CTList *pFromList)
{
	if (pFromList != NULL)
	{
		if (pFromList->ListHeader.pNext != &pFromList->ListHeader)
		{
			if (ListHeader.pNext == &ListHeader)
			{
				ListHeader = pFromList->ListHeader;
				ListHeader.pNext->pPrior = ListHeader.pPrior->pNext = &ListHeader;
			}
			else
			{
				ListHeader.pPrior->pNext = pFromList->ListHeader.pNext;
				pFromList->ListHeader.pNext->pPrior = ListHeader.pPrior;
				pFromList->ListHeader.pPrior->pNext = &ListHeader;
				ListHeader.pPrior = pFromList->ListHeader.pPrior;
			}
			pFromList->Init();
		}
	}
}
