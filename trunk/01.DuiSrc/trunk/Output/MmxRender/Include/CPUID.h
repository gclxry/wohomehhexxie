
#pragma once

#include <atlstr.h>

class CPUID
{
public:
	CPUID();
	~CPUID();
	// 制造商信息
	CString GetVID();
	// 商标
	CString GetBrand();
	// 判断是否支持超线程
	bool IsHyperThreading();
	// 判断是否支持speed step
	bool IsEST();
	// 判断是否支持MMX
	bool IsMMX();
	// 判断是否支持SSE
	bool IsSSE();
	// 判断是否支持SSE2
	bool IsSSE2();
	// 判断是否支持SSE3
	bool IsSSE3();
	// 判断是否支持SSE4.1
	bool IsSSE4_1();
	// 判断是否支持SSE4.2
	bool IsSSE4_2();

private:
	// 用来实现cpuid
	void Executecpuid(DWORD eax);
	// 存储返回的eax
	DWORD m_eax;
	// 存储返回的ebx
	DWORD m_ebx;
	// 存储返回的ecx
	DWORD m_ecx;
	// 存储返回的edx
	DWORD m_edx;
};
