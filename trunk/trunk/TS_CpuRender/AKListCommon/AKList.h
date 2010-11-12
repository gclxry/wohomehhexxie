//AK˫������

#ifndef _AKLIST_H_
#define _AKLIST_H_

/*#ifdef _DEBUG
#define new DEBUG_NEW
#endif*/

//AKԪ��λ��
struct AK_POS
{
	//Ԫ������
	void *pValue;

	//��һ��Ԫ��
	struct AK_POS *pPre;

	//��һ��Ԫ��
	struct AK_POS *pNext;
};

typedef struct AK_POS * AK_POS_PTR;

//AK˫��������
class CAKList
{

public:

	//�����Ƿ��Զ�����Ԫ��������ڴ��(Ĭ�����Զ������)
	void SetAutoFreeValue(bool t=true);

	//��ȡͷ��λ��
	AK_POS_PTR GetHeadPos();

	//��ȡβ��λ��
	AK_POS_PTR GetTailPos();

	//��ȡԪ�����ݵĵ�ַ
	void *GetValue(AK_POS_PTR pPos);

	//λ�õ�������һ��Ԫ��λ��
	void Next(AK_POS_PTR *ppPos);


	//λ�õ�������һ��Ԫ��λ��
	void Pre(AK_POS_PTR *ppPos);

	//���Ԫ�ص�ͷ��
	bool AddHead(void *pValue);

	//���Ԫ�ص�β��
	bool AddTail(void *pValue);

	//ɾ��Ԫ��
	void Remove(AK_POS_PTR pPos);

	//��������Ԫ�ص�����(������ַ)
	void Change(AK_POS_PTR pPos1,AK_POS_PTR pPos2);

	//�ͷ���������
	void ClearAll();

	//����Ԫ������
	unsigned long GetCount();

	//���캯��
	CAKList();

	//�͹�����
	~CAKList();

protected:

	//����ͷ
	AK_POS_PTR m_pHead;

	//����β
	AK_POS_PTR m_pTail;

	//Ԫ������
	unsigned long m_Count;

	//�Ƿ��Զ�����Ԫ��������ڴ��
	bool m_IsAutoFreeValue;


};

#endif