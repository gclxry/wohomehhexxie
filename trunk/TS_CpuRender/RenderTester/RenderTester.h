#pragma once

#include "resource.h"

#include "atltypes.h"
#include "GdiPlus.h"
using namespace Gdiplus;

void Draw(HWND hWnd, HDC hdc);
void DrawGdiPlus(HWND hWnd, HDC hMemoryDC, HBITMAP hMemoryBitmap);
