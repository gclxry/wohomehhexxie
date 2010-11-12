//��д�ڴ�

#ifndef _AKMEM_H_
#define _AKMEM_H_

#include "../AKListCommon/AKList.h"

/*
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
*/

//�ڴ��д��
class CAKMem
{

public:

	//�����������������ݵ�����,���ػ����ַ�ͳ���(ʹ�ú���Ҫ�Լ�����delete[]������)
	unsigned char *GetBuffer(unsigned long *pSize);

	//�����ڴ�ռ�õ����ֽ���
	unsigned long GetTotalByte();
	
	//д��������
	bool WriteData(unsigned char *pData,//��������ַ
		unsigned long uSize//�������ߴ�
		);
	
	//д��һ���ֽ����ݵ��ڴ浱ǰλ��
	bool WriteByte(unsigned char ch);

	//д��һ��λ����(0����1)���ڴ浱ǰλ��
	bool WriteBit(unsigned char bit);

	//�������ڴ��(ҳ),����оɵ��ڴ��(ҳ),�򱣴浽[�ڴ���б�]��β��
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

	//����
	void FreeAll();
	
	//��ʼ��
	bool Init(unsigned long MemBlockSize=512);
	
	CAKMem();

	~CAKMem();

protected:
	
	//�ڴ���б�
	CAKList m_MemBlockList;

	//�ڴ��(1ҳ)���ߴ�(�ֽ�)
	unsigned long m_MemBlockSize;

	//��ǰʹ�õ��ڴ��
	unsigned char *m_pCurMemBlockData;

	//��ǰ�ֽ�
	unsigned long m_uCurByte;

	//��ǰλ
	unsigned short m_uCurBit;
	
};

#endif
