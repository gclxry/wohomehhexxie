#pragma once

#include "resource.h"
#include "AggRender.h"

void OnTimer(HWND hWnd, WPARAM wParam, LPARAM lParam);
void OnSize(WPARAM wParam, LPARAM lParam);
void OnCreate();
void Draw(HWND hWnd, HDC hdc);
void AggDraw(HWND hWnd, HDC hMemoryDC, HBITMAP hMemoryBitmap);
