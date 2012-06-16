
#pragma once
#include "CTList.h"

class DWORD_MAP_OBJ : public ListObj
{
public:
	DWORD_MAP_OBJ();
	~DWORD_MAP_OBJ();

	DWORD dwKeyDword;
	VOID* pData;
};

class CDWORDMap : public CTList
{
public:
	CDWORDMap();
	~CDWORDMap();

	virtual void Clear();
	VOID* find(const DWORD dwKey, DWORD_MAP_OBJ** ppOutObj = NULL);
	bool insert(const DWORD dwKey, VOID* pData);
	VOID* operator[](int nNum);
	VOID* erase(const DWORD dwKey);

//////////////////////////////////////////////////////////////////////////

	// 添加到队列的末尾，环形列表
	virtual void PushBackObj(ListObj *pListObj) {};
	// 添加到队列的头，环形列表
	virtual void PushFrontObj(ListObj *pListObj) {};
	// 只是删除节点，不释放空间
	virtual void DelObj(ListObj *pListObj) {};
	// 将这个列表挪到当前列表的开头，同时清空原有列表
	virtual void MoveList(CTList *pFromList) {};
};
