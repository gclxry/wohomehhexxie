
#pragma once

#include <atlstr.h>

class CPUID
{
public:
	CPUID();
	~CPUID();
	// ��������Ϣ
	CString GetVID();
	// �̱�
	CString GetBrand();
	// �ж��Ƿ�֧�ֳ��߳�
	bool IsHyperThreading();
	// �ж��Ƿ�֧��speed step
	bool IsEST();
	// �ж��Ƿ�֧��MMX
	bool IsMMX();
	// �ж��Ƿ�֧��SSE
	bool IsSSE();
	// �ж��Ƿ�֧��SSE2
	bool IsSSE2();
	// �ж��Ƿ�֧��SSE3
	bool IsSSE3();
	// �ж��Ƿ�֧��SSE4.1
	bool IsSSE4_1();
	// �ж��Ƿ�֧��SSE4.2
	bool IsSSE4_2();

private:
	// ����ʵ��cpuid
	void Executecpuid(DWORD eax);
	// �洢���ص�eax
	DWORD m_eax;
	// �洢���ص�ebx
	DWORD m_ebx;
	// �洢���ص�ecx
	DWORD m_ecx;
	// �洢���ص�edx
	DWORD m_edx;
};
