#include "stdafx.h"

#include "AKFile.h"

CAKFile::CAKFile()
{
	m_pFile=NULL;
}

CAKFile::~CAKFile()
{
	Close();
}

void CAKFile::Close()
{
	if(m_pFile)
	{
		fclose(m_pFile);
		m_pFile=NULL;
	}
}

bool CAKFile::Open(char *pFilePathName,char *pMethod)
{
	Close();

	fopen_s(&m_pFile,pFilePathName,pMethod);

	return (m_pFile != NULL);
}

bool CAKFile::Read(void *pBuf,unsigned long uSize)
{
	if(!m_pFile)return false;

	if(fread(pBuf,uSize,1,m_pFile))return true;
	else return false;
}

bool CAKFile::Write(void *pBuf,unsigned long uSize)
{
	if(!m_pFile)return false;

	if(fwrite(pBuf,uSize,1,m_pFile))return true;
	else return false;
}

bool CAKFile::Seek(unsigned long uSize,int method)
{
	if(!m_pFile)return false;

	fseek(m_pFile,uSize,method);

	return true;
}

