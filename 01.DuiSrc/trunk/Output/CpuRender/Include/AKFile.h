#ifndef _AKFILE_H_
#define _AKFILE_H_

#include "stdio.h"

//AK 文件类
class CAKFile
{
public:

	//文件定位
	bool Seek(unsigned long uSize,int method);

	//写数据到文件
	bool Write(void *pBuf,unsigned long uSize);

	//从文件读数据
	bool Read(void *pBuf,unsigned long uSize);

	//打开文件
	bool Open(char *pFilePathName,char *pMethod);

	//关闭文件
	void Close();

	CAKFile();

	~CAKFile();

protected:

	FILE *m_pFile;
};

#endif