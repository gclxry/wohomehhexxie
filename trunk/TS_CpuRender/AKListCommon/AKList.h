//AK双向链表

#ifndef _AKLIST_H_
#define _AKLIST_H_

/*#ifdef _DEBUG
#define new DEBUG_NEW
#endif*/

//AK元素位置
struct AK_POS
{
	//元素内容
	void *pValue;

	//上一个元素
	struct AK_POS *pPre;

	//下一个元素
	struct AK_POS *pNext;
};

typedef struct AK_POS * AK_POS_PTR;

//AK双向链表类
class CAKList
{

public:

	//设置是否自动清理元素捆绑的内存块(默认是自动清除的)
	void SetAutoFreeValue(bool t=true);

	//获取头部位置
	AK_POS_PTR GetHeadPos();

	//获取尾部位置
	AK_POS_PTR GetTailPos();

	//获取元素内容的地址
	void *GetValue(AK_POS_PTR pPos);

	//位置调整到下一个元素位置
	void Next(AK_POS_PTR *ppPos);


	//位置调整到上一个元素位置
	void Pre(AK_POS_PTR *ppPos);

	//添加元素到头部
	bool AddHead(void *pValue);

	//添加元素到尾部
	bool AddTail(void *pValue);

	//删除元素
	void Remove(AK_POS_PTR pPos);

	//交换两个元素的内容(交换地址)
	void Change(AK_POS_PTR pPos1,AK_POS_PTR pPos2);

	//释放整个链表
	void ClearAll();

	//返回元素数量
	unsigned long GetCount();

	//构造函数
	CAKList();

	//释构函数
	~CAKList();

protected:

	//链表头
	AK_POS_PTR m_pHead;

	//链表尾
	AK_POS_PTR m_pTail;

	//元素数量
	unsigned long m_Count;

	//是否自动清理元素捆绑的内存块
	bool m_IsAutoFreeValue;


};

#endif