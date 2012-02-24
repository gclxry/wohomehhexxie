
#include "stdafx.h"
#include "..\..\Inc\CHighAccuracyTimer.h"

static int gs_nTimerId = 1;

void CALLBACK HighTimerCallBack(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
	if (dwUser == NULL)
		return;

	HIGH_TIMER_INFO *pTimerInfo = (HIGH_TIMER_INFO *)dwUser;

	if(::IsWindow(pTimerInfo->hWnd))
		::SendMessage(pTimerInfo->hWnd, WM_TIMER, pTimerInfo->nTimerId, 0);
}

CHighAccuracyTimer::CHighAccuracyTimer()
{
	// 取得最小时间周期
	m_TimeCaps.wPeriodMax = m_TimeCaps.wPeriodMin = 0;
	m_BeginPeriodRst = timeGetDevCaps(&m_TimeCaps, sizeof(m_TimeCaps));
	memset(&m_TimerInfo, 0, sizeof(HIGH_TIMER_INFO));
	m_dwTimeID = 0;
}

CHighAccuracyTimer::~CHighAccuracyTimer()
{
}

void CHighAccuracyTimer::KillTimer()
{
	if (m_dwTimeID == 0)
		return;

	timeKillEvent(m_dwTimeID);
	m_dwTimeID = 0;

	if (m_BeginPeriodRst != MMSYSERR_ERROR)
		m_BeginPeriodRst = timeEndPeriod(m_TimeCaps.wPeriodMin);
}

int CHighAccuracyTimer::SetTimer(IWindowBase *pWnd, DWORD uElapse)
{
	if (pWnd == NULL || pWnd->GetUiKernel() == NULL || !::IsWindow(pWnd->GetSafeHandle()) || uElapse <= 0 || m_dwTimeID != 0)
		return 0;

	m_TimerInfo.hWnd = pWnd->GetSafeHandle();
	m_TimerInfo.nTimerId = pWnd->GetUiKernel()->GetTimerId();
	m_TimerInfo.uElapse = uElapse;

	m_dwTimeID = timeSetEvent(uElapse, 0, (LPTIMECALLBACK)HighTimerCallBack, (DWORD_PTR)&m_TimerInfo, TIME_PERIODIC | TIME_CALLBACK_FUNCTION);
	if (m_dwTimeID == 0)
		return 0;

	if (m_BeginPeriodRst != MMSYSERR_ERROR)
		m_BeginPeriodRst = timeBeginPeriod(m_TimeCaps.wPeriodMin);

	return m_TimerInfo.nTimerId;
}
