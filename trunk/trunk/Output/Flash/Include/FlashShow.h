
#pragma once
#include "windows.h"

struct UI_WND 
{
	void* pFlashWnd;
	HWND hWnd;
};

bool InitPlayWnd(void *pUiWnd, HWND hWnd);
void UnInit(void *pUiWnd);
void PlayFlash(void *pUiWnd, char *strFlashPath);
void MovePlayWindow(void *pUiWnd, RECT &PlayRect);
void OnTimerPlay(void *pUiWnd, HWND hWnd, int nTimeId);
void OnPaint(void *pUiWnd, HDC hDc, RECT &WndRect);
void OnActivateApp(void *pUiWnd, HWND hWnd);

typedef bool (*pInitPlayWnd)(void *pUiWnd, HWND hWnd);
typedef void (*pUnInit)(void *pUiWnd);
typedef void (*pPlayFlash)(void *pUiWnd, char *strFlashPath);
typedef void (*pMovePlayWindow)(void *pUiWnd, RECT &PlayRect);
typedef void (*pOnTimerPlay)(void *pUiWnd, HWND hWnd, int nTimeId);
typedef void (*pOnPaint)(void *pUiWnd, HDC hDc, RECT &WndRect);
typedef void (*pOnActivateApp)(void *pUiWnd, HWND hWnd);
