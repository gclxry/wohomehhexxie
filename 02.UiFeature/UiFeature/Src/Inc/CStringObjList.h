
#pragma once
#include "CTList.h"

class STRING_OBJ : public ListObj
{
public:
	STRING_OBJ();
	~STRING_OBJ();

	int nFlag;
	char * pString;
};

class CStringObjList : public CTList
{
public:
	CStringObjList();
	~CStringObjList();

	virtual void Clear();
	bool PushBackString(const char * pszString, int nFlag = -1);
	bool PushBackString(char * pszString, int nFlag = -1);
	bool ResetStringByFlag(const char * pszString, int nFlag);

	void clear();
	int size();
	bool push_back(const char * pszString, int nFlag = -1);
	bool push_back(char * pszString, int nFlag = -1);
	const char* find(int nFlag);

	const char * operator[](int nNum);

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
