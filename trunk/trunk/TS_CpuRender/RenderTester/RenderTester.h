#pragma once

#include "resource.h"

#include "atltypes.h"
#include "GdiPlus.h"
using namespace Gdiplus;

#include "Fetionsf.h"

#include "CpuRender.h"
#include "AkLoadPic.h"

void OnCreate();
void OnTimer(WPARAM wParam, LPARAM lParam);
void OnSize(WPARAM wParam, LPARAM lParam);

void Draw(HWND hWnd, HDC hdc);
void DrawGdiPlus(HWND hWnd, HDC hMemoryDC, HBITMAP hMemoryBitmap);


bool SetBmpData(long w,long h);
void DisplayBmpData(HDC hMemoryDC, HBITMAP hMemoryBitmap, long x, long y, unsigned char *pBmp, long rows, long cols);