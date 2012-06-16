
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

	// ��ӵ����е�ĩβ�������б�
	virtual void PushBackObj(ListObj *pListObj) {};
	// ��ӵ����е�ͷ�������б�
	virtual void PushFrontObj(ListObj *pListObj) {};
	// ֻ��ɾ���ڵ㣬���ͷſռ�
	virtual void DelObj(ListObj *pListObj) {};
	// ������б�Ų����ǰ�б�Ŀ�ͷ��ͬʱ���ԭ���б�
	virtual void MoveList(CTList *pFromList) {};
};
