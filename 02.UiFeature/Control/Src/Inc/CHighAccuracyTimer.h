// 注意，一个 CHighAccuracyTimer 对象只能处理一个定时器，需要多个定时器请定义多个对象
#pragma once
#include <Windows.h>
#include <Mmsystem.h>
#include "..\..\Inc\IUiFeatureKernel.h"

struct HIGH_TIMER_INFO
{
	HWND hWnd;
	int nTimerId;
	DWORD uElapse;
};

class CHighAccuracyTimer
{
public:
	CHighAccuracyTimer();
	virtual ~CHighAccuracyTimer();

	int SetTimer(IWindowBase *pWnd, DWORD uElapse);
	void KillTimer();

private:
	TIMECAPS m_TimeCaps;
	MMRESULT m_BeginPeriodRst;
	HIGH_TIMER_INFO m_TimerInfo;
	DWORD m_dwTimeID;
};
