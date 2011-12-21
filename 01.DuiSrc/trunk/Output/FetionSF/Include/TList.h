
#pragma once

#include <Windows.h>

struct ListObj
{
	ListObj *pPrior;
	ListObj *pNext;
};

class CTList
{
protected:
	ListObj ListHeader;

public:
	CTList(void);
	~CTList(void);

	void Init(void);
	BOOL IsEmpty(void);
	void AddObj(ListObj *pListObj);
	void DelObj(ListObj *pListObj);
	ListObj *TopObj(void);
	ListObj *NextObj(ListObj *pListObj);
	void MoveList(CTList *pFromList);
};
