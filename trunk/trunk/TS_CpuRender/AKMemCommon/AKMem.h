//读写内存

#ifndef _AKMEM_H_
#define _AKMEM_H_

#include "../AKListCommon/AKList.h"

/*
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
*/

//内存读写类
class CAKMem
{

public:

	//创建并复制所有数据到缓冲,返回缓冲地址和长度(使用后需要自己调用delete[]来销毁)
	unsigned char *GetBuffer(unsigned long *pSize);

	//返回内存占用的总字节数
	unsigned long GetTotalByte();
	
	//写入数据流
	bool WriteData(unsigned char *pData,//数据流地址
		unsigned long uSize//数据流尺寸
		);
	
	//写入一个字节数据到内存当前位置
	bool WriteByte(unsigned char ch);

	//写入一个位数据(0或者1)到内存当前位置
	bool WriteBit(unsigned char bit);

	//创建新内存块(页),如果有旧的内存块(页),则保存到[内存块列表]的尾部
	bool NewMemBlock()
	{
		if(m_pCurMemBlockData)
		{
			m_MemBlockList.AddTail(m_pCurMemBlockData);
		}
		
		m_pCurMemBlockData=new unsigned char[m_MemBlockSize];
		
		m_uCurByte=0;
		
		m_uCurBit=0;
		
		if(m_pCurMemBlockData)
		{
			memset(m_pCurMemBlockData,0,m_MemBlockSize*sizeof(unsigned char));
			return true;
		}
		else return false;
	}

	//销毁
	void FreeAll();
	
	//初始化
	bool Init(unsigned long MemBlockSize=512);
	
	CAKMem();

	~CAKMem();

protected:
	
	//内存块列表
	CAKList m_MemBlockList;

	//内存块(1页)最大尺寸(字节)
	unsigned long m_MemBlockSize;

	//当前使用的内存块
	unsigned char *m_pCurMemBlockData;

	//当前字节
	unsigned long m_uCurByte;

	//当前位
	unsigned short m_uCurBit;
	
};

#endif
