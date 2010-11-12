#include "stdafx.h"

#include "AKMem.h"

CAKMem::CAKMem()
{
	m_pCurMemBlockData=NULL;
	
	m_uCurByte=0;

	m_uCurBit=0;
}

bool CAKMem::Init(unsigned long MemBlockSize)
{
	FreeAll();

	if(MemBlockSize<512)MemBlockSize=512;
	
	m_MemBlockSize=MemBlockSize;

	return NewMemBlock();
}

CAKMem::~CAKMem()
{
	FreeAll();
}

bool CAKMem::WriteData(unsigned char *pData,
					   unsigned long uSize
					   )
{
	bool rt;
	unsigned long i;

	for(i=0;i<uSize;++i)
	{
		rt=WriteByte(pData[i]);

		if(!rt)return false;
	}

	return true;
}

bool CAKMem::WriteByte(unsigned char ch)
{
	if(m_uCurBit==0)
	{
		m_pCurMemBlockData[m_uCurByte]=ch;
		
		++m_uCurByte;

		if(m_uCurByte>=m_MemBlockSize)
		{
			return NewMemBlock();
		}
	}
	else
	{
		unsigned short i;
		bool rt;

		for(i=0;i<8;++i)
		{
			rt=WriteBit((ch>>i)&0x1);

			if(!rt)return false;
		}
	}

	return true;
}

bool CAKMem::WriteBit(unsigned char bit)
{
	m_pCurMemBlockData[m_uCurByte]|=bit<<m_uCurBit;

	++m_uCurBit;

	if(m_uCurBit>=8)
	{
		m_uCurBit=0;
		
		++m_uCurByte;
	}

	if(m_uCurByte>=m_MemBlockSize)
	{
		return NewMemBlock();
	}

	return true;
}

void CAKMem::FreeAll()
{
	m_MemBlockList.ClearAll();

	if(m_pCurMemBlockData)delete[] m_pCurMemBlockData;
	
	m_pCurMemBlockData=NULL;

	m_uCurByte=0;

	m_uCurBit=0;
}

unsigned long CAKMem::GetTotalByte()
{
	unsigned long uLen=m_MemBlockList.GetCount()*m_MemBlockSize+m_uCurByte;

	if(m_uCurBit>0)uLen+=1;

	return uLen;
}

unsigned char *CAKMem::GetBuffer(unsigned long *pSize)
{
	unsigned long len=GetTotalByte();
	if(len==0)return NULL;

	unsigned char *pBuf=new unsigned char[len];
	if(!pBuf)return NULL;

	AK_POS_PTR pos=m_MemBlockList.GetHeadPos();
	
	unsigned char *pCurMemBlock;

	unsigned long i=0;

	//复制内存块列表中的数据
	while(pos)
	{
		//当前内存块(页)
		pCurMemBlock=(unsigned char *)m_MemBlockList.GetValue(pos);

		memcpy(&pBuf[i],pCurMemBlock,m_MemBlockSize);

		i+=m_MemBlockSize;
		
		m_MemBlockList.Next(&pos);
	}

	//复制剩余数据
	memcpy(&pBuf[i],m_pCurMemBlockData,len-i);

	*pSize=len;

	return pBuf;
}