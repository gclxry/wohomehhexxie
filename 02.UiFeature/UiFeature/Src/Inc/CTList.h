
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
	// ��ӵ����е�ĩβ�������б�
	void PushBackObj(ListObj *pListObj);
	// ��ӵ����е�ͷ�������б�
	void PushFrontObj(ListObj *pListObj);
	// ֻ��ɾ���ڵ㣬���ͷſռ�
	void DelObj(ListObj *pListObj);
	ListObj *TopObj();
	ListObj *LastObj();
	ListObj *NextObj(ListObj *pListObj);
	ListObj *PriorObj(ListObj *pListObj);
	// ������б�Ų����ǰ�б�Ŀ�ͷ��ͬʱ���ԭ���б�
	void MoveList(CTList *pFromList);
	// ����б�
	void Clear();
	// ����Objectλ��
	bool ChangeObjPos(ListObj *pFromObj, ListObj *pToObj);

protected:
	ListObj ListHeader;
	int m_nCtns;
};
