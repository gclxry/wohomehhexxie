
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
	// 因为嵌入式的汇编代码不能识别 类成员变量 所以定义四个临时变量作为过渡
	DWORD deax = 0;
	DWORD debx = 0;
	DWORD decx = 0;
	DWORD dedx = 0;

	__asm
	{
		mov eax, veax
		cpuid			// 执行cpuid
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

// 制造商信息
CString CPUID::GetVID()
{
	// 字符串，用来存储制造商信息
	char cVID[13];
	memset(cVID, 0, 13);

	// 执行cpuid指令，使用输入参数 eax = 0
	Executecpuid(0);

	memcpy(cVID, &m_ebx, 4);
	memcpy(cVID+4, &m_edx, 4);
	memcpy(cVID+8, &m_ecx, 4);

	return CString(cVID);
}

// 商标
CString CPUID::GetBrand()
{
	// 从0x80000002开始，到0x80000004结束
	const DWORD BRANDID = 0x80000002;

	// 用来存储商标字符串，48个字符
	char cBrand[49];
	memset(cBrand, 0, 49);

	// 依次执行3个指令
	for (DWORD i = 0; i < 3; i++)
	{
		Executecpuid(BRANDID + i);
		
		// 每次执行结束后，保存四个寄存器里的asc码到数组
		// 在内存中，m_eax, m_ebx, m_ecx, m_edx是连续排列
		memcpy(cBrand + i*16, &m_eax, 16);
	}

	return CString(cBrand);
}

// 判断是否支持超线程
bool CPUID::IsHyperThreading() 
{
	// 执行cpuid指令，使用输入参数 eax = 1
	Executecpuid(1);
	// 返回edx的bit 28
	return (m_edx & (1<<28));
}

// 判断是否支持speed step
bool CPUID::IsEST()
{
	Executecpuid(1);
	// 返回ecx的bit 7
	return (m_ecx & (1<<7)); 
}

// 判断是否支持MMX
bool CPUID::IsMMX()
{
	Executecpuid(1);
	// 返回edx的bit 23
	return (m_edx & (1<<23));
}

// 判断是否支持SSE
bool CPUID::IsSSE()
{
	Executecpuid(1);
	return (m_edx & (1<<25));
}

// 判断是否支持SSE2
bool CPUID::IsSSE2()
{
	Executecpuid(1);
	return (m_edx & (1<<26));
}

// 判断是否支持SSE3
bool CPUID::IsSSE3()
{
	Executecpuid(1);
	return m_ecx;
}

// 判断是否支持SSE4.1
bool CPUID::IsSSE4_1()
{
	Executecpuid(1);
	return (m_ecx & (1<<19));
}

// 判断是否支持SSE4.2
bool CPUID::IsSSE4_2()
{
	Executecpuid(1);
	return (m_ecx & (1<<20));
}
