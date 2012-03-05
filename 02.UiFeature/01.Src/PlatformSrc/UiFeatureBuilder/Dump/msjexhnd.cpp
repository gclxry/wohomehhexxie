//	msjexhnd.cpp 

//==========================================
// Matt Pietrek
// Microsoft Systems Journal, April 1997
// FILE: MSJEXHND.CPP
//==========================================
#include "stdafx.h"
#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include "msjexhnd.h"
#include <time.h>

#include "detours.h"

#pragma warning (disable : 4311)
#pragma warning (disable : 4312)

void ShowMyErrorDialog(EXCEPTION_POINTERS* pep);

DETOUR_TRAMPOLINE(LONG WINAPI org_UnhandledExceptionFilter(struct _EXCEPTION_POINTERS *ExceptionInfo), UnhandledExceptionFilter);
static LONG WINAPI IG_UnhandledExceptionFilter(struct _EXCEPTION_POINTERS *ExceptionInfo)
{
	ShowMyErrorDialog(ExceptionInfo);
	return EXCEPTION_EXECUTE_HANDLER;
}

//============================== Global Variables =============================
//
// Declare the static variables of the MSJExceptionHandler class
//
TCHAR MSJExceptionHandler::m_szLogFileName[MAX_PATH] = { 0 };
LPTOP_LEVEL_EXCEPTION_FILTER MSJExceptionHandler::m_previousFilter;
HANDLE MSJExceptionHandler::m_hReportFile = NULL;

#ifndef _DEBUG
MSJExceptionHandler g_MSJExceptionHandler;  // Declare global instance of class
#endif

//============================== Class Methods =============================
//=============
// Constructor 
//=============
MSJExceptionHandler::MSJExceptionHandler( )
{
	DetourFunctionWithTrampoline((PBYTE)org_UnhandledExceptionFilter, (PBYTE)IG_UnhandledExceptionFilter);

	// Install the unhandled exception filter function
	m_previousFilter = SetUnhandledExceptionFilter(MSJUnhandledExceptionFilter);
	
}
//============
// Destructor 
//============
MSJExceptionHandler::~MSJExceptionHandler( )
{
	SetUnhandledExceptionFilter( m_previousFilter );

	DetourRemove((PBYTE)org_UnhandledExceptionFilter, (PBYTE)IG_UnhandledExceptionFilter);
}
//==============================================================
// Lets user change the name of the report file to be generated 
//==============================================================
void MSJExceptionHandler::SetLogFileName( TCHAR* pszLogFileName )
{
	_tcscpy_s(m_szLogFileName, sizeof(m_szLogFileName), pszLogFileName);
}
//===========================================================
// Entry point where control comes on an unhandled exception 
//===========================================================
LONG WINAPI MSJExceptionHandler::MSJUnhandledExceptionFilter(
															 PEXCEPTION_POINTERS pExceptionInfo )
{
	ShowMyErrorDialog(pExceptionInfo);	
	
	return EXCEPTION_EXECUTE_HANDLER;//EXCEPTION_CONTINUE_SEARCH;
}
//===========================================================================
// Open the report file, and write the desired information to it.  Called by 
// MSJUnhandledExceptionFilter                                               
//===========================================================================
void MSJExceptionHandler::GenerateExceptionReport(
												  PEXCEPTION_POINTERS pExceptionInfo )
{
	// Start out with a banner
	_tprintf( _T("//=====================================================\r\n" ));

	//	最后一次编译msjexhnd.obj的时间。
	_tprintf(_T("最后一次编译msjexhnd.obj的时间（可参照此时间去对应map文件）：\r\n"));
	USES_CONVERSION;
	_tprintf(_T("Date： %s\r\n"), A2T(__DATE__));
	_tprintf(_T("Time： %s\r\n"), A2T(__TIME__));
	_tprintf(_T("\r\n"));


	//	write occur time
	TCHAR tmpbuf[128]={0};
	
	_tstrdate_s( tmpbuf, sizeof(tmpbuf) );
	_tprintf(_T("//==%s "), tmpbuf );
	
	_tstrtime_s( tmpbuf, sizeof(tmpbuf) );
	_tprintf(_T("%s\r\n"), tmpbuf );

	PEXCEPTION_RECORD pExceptionRecord = pExceptionInfo->ExceptionRecord;

	// First print information about the type of fault
	_tprintf(_T("Exception code: %08X %s\r\n"), pExceptionRecord->ExceptionCode,
		GetExceptionString(pExceptionRecord->ExceptionCode) );
	
	// Now print information about where the fault occured
	TCHAR szFaultingModule[MAX_PATH];
	DWORD section, offset;
	GetLogicalAddress(  pExceptionRecord->ExceptionAddress,
		szFaultingModule,
		sizeof( szFaultingModule ),
		section, offset );

//	{	//	added by HaoYongJian 2005-11-25
//		TCHAR fname[_MAX_FNAME] = {0};
//		TCHAR ext[_MAX_EXT] = {0};
//		_tsplitpath(szFaultingModule, 0, 0, fname, ext);
//		_tcscat(fname, ext);
//		for (int i = 0; i < sizeof(g_FatalError)/sizeof(g_FatalError[0]); i++)
//		{
//			if (_tcscmp(g_FatalError[i].m_szModuleName, fname) == 0)
//			{
//				g_FatalError[i].m_bError = 1;
//				break;
//			}
//		}
//	}
	
	_tprintf( _T("Fault address:  %08X %02X:%08X %s\r\n"),
		pExceptionRecord->ExceptionAddress,
		section, offset, szFaultingModule );
	
	PCONTEXT pCtx = pExceptionInfo->ContextRecord;
	
	// Show the registers
#ifdef _M_IX86  // Intel Only!
	_tprintf( _T("\r\nRegisters:\r\n") );
	
	_tprintf(_T("EAX:%08X\r\nEBX:%08X\r\nECX:%08X\r\nEDX:%08X\r\nESI:%08X\r\nEDI:%08X\r\n"),
		pCtx->Eax, pCtx->Ebx, pCtx->Ecx, pCtx->Edx, pCtx->Esi, pCtx->Edi );
	
	_tprintf( _T("CS:EIP:%04X:%08X\r\n"), pCtx->SegCs, pCtx->Eip );
	_tprintf( _T("SS:ESP:%04X:%08X  EBP:%08X\r\n"),
		pCtx->SegSs, pCtx->Esp, pCtx->Ebp );
	_tprintf( _T("DS:%04X  ES:%04X  FS:%04X  GS:%04X\r\n"),
		pCtx->SegDs, pCtx->SegEs, pCtx->SegFs, pCtx->SegGs );
	_tprintf( _T("Flags:%08X\r\n"), pCtx->EFlags );
	
	// Walk the stack using x86 specific code
	IntelStackWalk( pCtx );
	
#endif
	
	_tprintf( _T("\r\n") );
}
//======================================================================
// Given an exception code, returns a pointer to a static string with a 
// description of the exception                                         
//======================================================================
LPTSTR MSJExceptionHandler::GetExceptionString( DWORD dwCode )
{
#define EXCEPTION( x ) case EXCEPTION_##x: return _T(#x);
	
	switch ( dwCode )
	{   
		EXCEPTION( ACCESS_VIOLATION )
		EXCEPTION( DATATYPE_MISALIGNMENT )
		EXCEPTION( BREAKPOINT )
		EXCEPTION( SINGLE_STEP )
		EXCEPTION( ARRAY_BOUNDS_EXCEEDED )
		EXCEPTION( FLT_DENORMAL_OPERAND )
		EXCEPTION( FLT_DIVIDE_BY_ZERO )
		EXCEPTION( FLT_INEXACT_RESULT )
		EXCEPTION( FLT_INVALID_OPERATION )
		EXCEPTION( FLT_OVERFLOW )
		EXCEPTION( FLT_STACK_CHECK )
		EXCEPTION( FLT_UNDERFLOW )
		EXCEPTION( INT_DIVIDE_BY_ZERO )
		EXCEPTION( INT_OVERFLOW )
		EXCEPTION( PRIV_INSTRUCTION )
		EXCEPTION( IN_PAGE_ERROR )
		EXCEPTION( ILLEGAL_INSTRUCTION )
		EXCEPTION( NONCONTINUABLE_EXCEPTION )
		EXCEPTION( STACK_OVERFLOW )
		EXCEPTION( INVALID_DISPOSITION )
		EXCEPTION( GUARD_PAGE )
		EXCEPTION( INVALID_HANDLE )
	}
	
	// If not one of the "known" exceptions, try to get the string
	// from NTDLL.DLL's message table.
	static TCHAR szBuffer[512] = { 0 };
	
	FormatMessage(  FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_HMODULE,
		GetModuleHandle(_T("NTDLL.DLL")),
		dwCode, 0, szBuffer, sizeof( szBuffer ), 0 );
	
	return szBuffer;
}
//==============================================================================
// Given a linear address, locates the module, section, and offset containing  
// that address.                                                               
//                                                                             
// Note: the szModule paramater buffer is an output buffer of length specified 
// by the len parameter (in characters!)                                       
//==============================================================================
BOOL MSJExceptionHandler::GetLogicalAddress(
											PVOID addr, TCHAR* szModule, DWORD len, DWORD& section, DWORD& offset )
{
	MEMORY_BASIC_INFORMATION mbi;
	
	if ( !VirtualQuery( addr, &mbi, sizeof(mbi) ) )
		return FALSE;
	
	DWORD hMod = (DWORD)mbi.AllocationBase;
		
	// Point to the DOS header in memory
	PIMAGE_DOS_HEADER pDosHdr = (PIMAGE_DOS_HEADER)hMod;
	
	// From the DOS header, find the NT (PE) header
	PIMAGE_NT_HEADERS pNtHdr = (PIMAGE_NT_HEADERS)(hMod + pDosHdr->e_lfanew);
	
	PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION( pNtHdr );
	
	DWORD rva = (DWORD)addr - hMod; // RVA is offset from module load address
	
	// Iterate through the section table, looking for the one that encompasses
	// the linear address.
	for (   unsigned i = 0;
	i < pNtHdr->FileHeader.NumberOfSections;
	i++, pSection++ )
	{
		DWORD sectionStart = pSection->VirtualAddress;
		DWORD sectionEnd = sectionStart
			+ max(pSection->SizeOfRawData, pSection->Misc.VirtualSize);
		
		// Is the address in this section???
		if ( (rva >= sectionStart) && (rva <= sectionEnd) )
		{
			// Yes, address is in the section.  Calculate section and offset,
			// and store in the "section" & "offset" params, which were
			// passed by reference.
			section = i+1;
			offset = rva - sectionStart;
			return TRUE;
		}
	}
	
	return FALSE;   // Should never get here!
}
//============================================================
// Walks the stack, and writes the results to the report file 
//============================================================
void MSJExceptionHandler::IntelStackWalk( PCONTEXT pContext )
{
	_tprintf(_T("\r\nCall stack:\r\n"));
	
	_tprintf(_T("Address   Frame     Logical addr  Module\r\n"));
	
	DWORD pc = pContext->Eip;
	PDWORD pFrame, pPrevFrame;
	
	pFrame = (PDWORD)pContext->Ebp;
	
	do
	{
		TCHAR szModule[MAX_PATH] = {0};
		DWORD section = 0, offset = 0;
		
		GetLogicalAddress((PVOID)pc, szModule,sizeof(szModule),section,offset );
		

		_tprintf(_T("%08X  %08X  %04X:%08X %s\r\n"),
			pc, pFrame, section, offset, szModule);
		
		pc = pFrame[1];
		
		pPrevFrame = pFrame;
		
		pFrame = (PDWORD)pFrame[0]; // precede to next higher frame on stack
		
		if ( (DWORD)pFrame & 3 )    // Frame pointer must be aligned on a
			break;                  // DWORD boundary.  Bail if not so.
		
		if ( pFrame <= pPrevFrame )
			break;
		
		// Can two DWORDs be read from the supposed frame address?          
		if ( IsBadWritePtr(pFrame, sizeof(PVOID)*2) )
			break;
		
	} while ( 1 );
}
//============================================================================
// Helper function that writes to the report file, and allows the user to use 
// printf style formating                                                     
//============================================================================
int __cdecl MSJExceptionHandler::_tprintf(const TCHAR * format, ...)
{
	TCHAR szBuff[1024]={0};
	int retValue;
	DWORD cbWritten;
	va_list argptr;
	
	va_start( argptr, format );
	retValue = _vstprintf_s( szBuff, sizeof(szBuff), format, argptr );
	va_end( argptr );
    
	USES_CONVERSION;
    LPCSTR lpStr = T2CA(szBuff);
	WriteFile(m_hReportFile, lpStr, lstrlenA(lpStr), &cbWritten, 0 );
	return retValue;
}

typedef struct tagLogInfoItem
{
	char szInfo[512];
}LOGINFOITEM, *PLOGINFOITEM;
void CreateMiniDumpA( EXCEPTION_POINTERS* pep, LPCSTR pszFileName, LOGINFOITEM * pHead, int nLogCount );

void ShowMyErrorDialog(EXCEPTION_POINTERS* pep)
{
//#ifndef _DEBUG
	{
		char szPath[MAX_PATH] = { 0 };
		GetModuleFileNameA(NULL, szPath, sizeof(szPath));
		char *pEnd = szPath + lstrlenA(szPath) - 1;
		while (*pEnd != '.' && pEnd > szPath) pEnd--;
		*pEnd = 0;
		while (*pEnd != '\\' && pEnd > szPath) pEnd--;
		char szFileName[80] = { 0 };
		strcpy_s(szFileName, sizeof(szFileName), pEnd+1);
		*pEnd = 0;
		SYSTEMTIME tm = { 0 };
		GetLocalTime(&tm);
		char str[MAX_PATH] = { 0 };
		sprintf_s(str, sizeof(str), "%s\\UiFeatureBuilder_%s%04d%02d%02d%02d%02d%02d%03d.dmp", szPath, szFileName, tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond, tm.wMilliseconds);
		LOGINFOITEM li = { 0 };
		strcpy_s(li.szInfo, sizeof(li.szInfo),  "杯具了！还好有Dump！");
		CreateMiniDumpA(pep, str, &li, 1);
	}
	
	TerminateProcess(GetCurrentProcess(), 0);

//#endif	
}

// 生成发布版本的时候，请把下面的代码注释掉
#include "dbghelp.h"
#pragma comment(lib, "dbghelp.lib")
void CreateMiniDumpA( EXCEPTION_POINTERS* pep, LPCSTR pszFileName, LOGINFOITEM * pHead, int nLogCount ) 
{
	HANDLE hFile = CreateFileA( pszFileName, GENERIC_READ | GENERIC_WRITE, 
		0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL ); 
	if( ( hFile != NULL ) && ( hFile != INVALID_HANDLE_VALUE ) ) 
	{
		MINIDUMP_EXCEPTION_INFORMATION mdei; 
		mdei.ThreadId           = GetCurrentThreadId(); 
		mdei.ExceptionPointers  = pep; 
		mdei.ClientPointers     = FALSE; 
		
		MINIDUMP_TYPE mdt       = MiniDumpNormal; 
		
		const int nMax = 100;
		int nItemSz = sizeof(((LOGINFOITEM*)0)->szInfo);
		MINIDUMP_USER_STREAM logs = { 0 };
		logs.Type       = CommentStreamA;
		logs.BufferSize = nMax*512;
		logs.Buffer     = new char[nMax*512];
		char *pEnd      = (char*)logs.Buffer;
		int nc = min(nMax, nLogCount);
		for (int i = 0; i < nc; i++)
		{
			char *pLog = pHead[(nLogCount-1+i)%nMax].szInfo;
			if (pLog && *pLog)
			{
				lstrcpyA(pEnd, pLog);
				pEnd += lstrlenA(pLog);
			}
		}
		MINIDUMP_USER_STREAM_INFORMATION loginfo = {1, &logs};
		
		BOOL rv = MiniDumpWriteDump( GetCurrentProcess(), GetCurrentProcessId(), 
			hFile, mdt, (pep != 0) ? &mdei : 0, &loginfo, 0 ); 
		
		CloseHandle( hFile ); 
		
		delete[] logs.Buffer;
		
		if( !rv ) 
		{
		}
		else 
		{
		}		
	}
}
