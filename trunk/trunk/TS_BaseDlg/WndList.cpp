
#include "stdafx.h"
#include "WndList.h"

CWndList::CWndList(void)
{

}

CWndList::~CWndList(void)
{
	ClearAll();
}

WndObj *CWndList::TopObj(void)
{
	return (WndObj *)CTList::TopObj();
}

WndObj *CWndList::NextObj(WndObj *pReqObj)
{
	return (WndObj *)CTList::NextObj(pReqObj);
}

WndObj *CWndList::NewWndObj(void *pWnd)
{
	WndObj *pNewObj = new WndObj;
	if (pNewObj != NULL)
	{
		memset(pNewObj, 0, sizeof(WndObj));
		pNewObj->pWnd = pWnd;
		this->AddObj(pNewObj);
	}

	return pNewObj;
}

void CWndList::DeleteSpWndObj(void *pWnd)
{
	for (WndObj *pWndObj = this->TopObj(); pWndObj != NULL; pWndObj = this->NextObj(pWndObj))
	{
		if (pWnd == pWndObj->pWnd)
		{
			DelWndObj(pWndObj);
			break;
		}
	}
}

void CWndList::ClearAll()
{
	while (!this->IsEmpty())
	{
		WndObj *pWndObj = this->TopObj();
		DelWndObj(pWndObj);
	}
}

void CWndList::DelWndObj(WndObj *pReqObj)
{
	if (pReqObj != NULL)
	{
		this->DelObj(pReqObj);
		delete pReqObj;
	}
}
