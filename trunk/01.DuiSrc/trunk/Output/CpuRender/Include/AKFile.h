#ifndef _AKFILE_H_
#define _AKFILE_H_

#include "stdio.h"

//AK �ļ���
class CAKFile
{
public:

	//�ļ���λ
	bool Seek(unsigned long uSize,int method);

	//д���ݵ��ļ�
	bool Write(void *pBuf,unsigned long uSize);

	//���ļ�������
	bool Read(void *pBuf,unsigned long uSize);

	//���ļ�
	bool Open(char *pFilePathName,char *pMethod);

	//�ر��ļ�
	void Close();

	CAKFile();

	~CAKFile();

protected:

	FILE *m_pFile;
};

#endif