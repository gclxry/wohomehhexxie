
#pragma once
#include "CTList.h"

class STRING_MAP_OBJ : public ListObj
{
public:
	STRING_MAP_OBJ();
	~STRING_MAP_OBJ();

	char* pKeyString;
	VOID* pData;
};

class CStringMap : public CTList
{
public:
	CStringMap();
	~CStringMap();

	virtual void Clear();
	void clear();
	int size();
	VOID* find(const char *pKeyString, STRING_MAP_OBJ** ppOutObj = NULL);

	bool insert(const char * pszString, VOID* pData);

	VOID* operator[](int nNum);

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
