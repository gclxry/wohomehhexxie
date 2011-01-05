
#include "StdAfx.h"
#include "CPUID.h"

#pragma warning(disable:4800)

CPUID::CPUID()
{
	m_eax = 0;
	m_ebx = 0;
	m_ecx = 0;
	m_edx = 0;
}

CPUID::~CPUID()
{
}

void CPUID::Executecpuid(DWORD veax)
{
	// ��ΪǶ��ʽ�Ļ����벻��ʶ�� ���Ա���� ���Զ����ĸ���ʱ������Ϊ����
	DWORD deax = 0;
	DWORD debx = 0;
	DWORD decx = 0;
	DWORD dedx = 0;

	__asm
	{
		mov eax, veax
		cpuid			// ִ��cpuid
		mov deax, eax
		mov debx, ebx
		mov decx, ecx
		mov dedx, edx
	}

	m_eax = deax;
	m_ebx = debx;
	m_ecx = decx;
	m_edx = dedx;
}

// ��������Ϣ
CString CPUID::GetVID()
{
	// �ַ����������洢��������Ϣ
	char cVID[13];
	memset(cVID, 0, 13);

	// ִ��cpuidָ�ʹ��������� eax = 0
	Executecpuid(0);

	memcpy(cVID, &m_ebx, 4);
	memcpy(cVID+4, &m_edx, 4);
	memcpy(cVID+8, &m_ecx, 4);

	return CString(cVID);
}

// �̱�
CString CPUID::GetBrand()
{
	// ��0x80000002��ʼ����0x80000004����
	const DWORD BRANDID = 0x80000002;

	// �����洢�̱��ַ�����48���ַ�
	char cBrand[49];
	memset(cBrand, 0, 49);

	// ����ִ��3��ָ��
	for (DWORD i = 0; i < 3; i++)
	{
		Executecpuid(BRANDID + i);
		
		// ÿ��ִ�н����󣬱����ĸ��Ĵ������asc�뵽����
		// ���ڴ��У�m_eax, m_ebx, m_ecx, m_edx����������
		memcpy(cBrand + i*16, &m_eax, 16);
	}

	return CString(cBrand);
}

// �ж��Ƿ�֧�ֳ��߳�
bool CPUID::IsHyperThreading() 
{
	// ִ��cpuidָ�ʹ��������� eax = 1
	Executecpuid(1);
	// ����edx��bit 28
	return (m_edx & (1<<28));
}

// �ж��Ƿ�֧��speed step
bool CPUID::IsEST()
{
	Executecpuid(1);
	// ����ecx��bit 7
	return (m_ecx & (1<<7)); 
}

// �ж��Ƿ�֧��MMX
bool CPUID::IsMMX()
{
	Executecpuid(1);
	// ����edx��bit 23
	return (m_edx & (1<<23));
}

// �ж��Ƿ�֧��SSE
bool CPUID::IsSSE()
{
	Executecpuid(1);
	return (m_edx & (1<<25));
}

// �ж��Ƿ�֧��SSE2
bool CPUID::IsSSE2()
{
	Executecpuid(1);
	return (m_edx & (1<<26));
}

// �ж��Ƿ�֧��SSE3
bool CPUID::IsSSE3()
{
	Executecpuid(1);
	return m_ecx;
}

// �ж��Ƿ�֧��SSE4.1
bool CPUID::IsSSE4_1()
{
	Executecpuid(1);
	return (m_ecx & (1<<19));
}

// �ж��Ƿ�֧��SSE4.2
bool CPUID::IsSSE4_2()
{
	Executecpuid(1);
	return (m_ecx & (1<<20));
}
