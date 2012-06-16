
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

	// ��ӵ����е�ĩβ�������б�
	virtual void PushBackObj(ListObj *pListObj) {};
	// ��ӵ����е�ͷ�������б�
	virtual void PushFrontObj(ListObj *pListObj) {};
	// ֻ��ɾ���ڵ㣬���ͷſռ�
	virtual void DelObj(ListObj *pListObj) {};
	// ������б�Ų����ǰ�б�Ŀ�ͷ��ͬʱ���ԭ���б�
	virtual void MoveList(CTList *pFromList) {};
};
