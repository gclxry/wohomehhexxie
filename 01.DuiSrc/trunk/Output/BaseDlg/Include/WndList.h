
#pragma once

#include "TList.h"

struct WndObj : public ListObj
{
	void *pWnd;
};

class CWndList : public CTList
{
public:
	CWndList(void);
	~CWndList(void);

	WndObj *TopObj(void);
	WndObj *NextObj(WndObj *pReqObj);
	WndObj *NewWndObj(void *pWnd);
	void DeleteSpWndObj(void *pWnd);
	void ClearAll();

private:
	void DelWndObj(WndObj *pReqObj);
};
