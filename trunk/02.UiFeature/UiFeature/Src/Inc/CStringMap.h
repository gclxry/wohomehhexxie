
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

	// ��ӵ����е�ĩβ�������б�
	virtual void PushBackObj(ListObj *pListObj) {};
	// ��ӵ����е�ͷ�������б�
	virtual void PushFrontObj(ListObj *pListObj) {};
	// ֻ��ɾ���ڵ㣬���ͷſռ�
	virtual void DelObj(ListObj *pListObj) {};
	// ������б�Ų����ǰ�б�Ŀ�ͷ��ͬʱ���ԭ���б�
	virtual void MoveList(CTList *pFromList) {};
};
