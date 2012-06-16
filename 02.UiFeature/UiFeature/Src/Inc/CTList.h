
#pragma once

#include <Windows.h>

class ListObj
{
public:
	ListObj();
	~ListObj();

	ListObj *pPrior;
	ListObj *pNext;
};

class CTList
{
public:
	CTList();
	~CTList();

	int Size();
	void Init();
	BOOL IsEmpty();
	// 添加到队列的末尾，环形列表
	void PushBackObj(ListObj *pListObj);
	// 添加到队列的头，环形列表
	void PushFrontObj(ListObj *pListObj);
	// 只是删除节点，不释放空间
	void DelObj(ListObj *pListObj);
	ListObj *TopObj();
	ListObj *LastObj();
	ListObj *NextObj(ListObj *pListObj);
	ListObj *PriorObj(ListObj *pListObj);
	// 将这个列表挪到当前列表的开头，同时清空原有列表
	void MoveList(CTList *pFromList);
	// 清空列表
	void Clear();
	// 交换Object位置
	bool ChangeObjPos(ListObj *pFromObj, ListObj *pToObj);

protected:
	ListObj ListHeader;
	int m_nCtns;
};
