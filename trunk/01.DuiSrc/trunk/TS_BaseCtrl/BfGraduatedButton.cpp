
#include "BfGraduatedButton.h"


UINT WINAPI CBfGraduatedButton::DrawGraduatedButtonThread(LPVOID lpParameter)
{
	CBfGraduatedButton* pButton = (CBfGraduatedButton*)lpParameter;

	if (pButton != NULL)
		pButton->SetDrawButtonParam();

	return 0;
}

CBfGraduatedButton::CBfGraduatedButton(void)
{
	m_hThread = NULL;

	m_bIsCanDrawGraduate = false;
	m_nDrawCtns = 1;

	m_UpGraduateColor = Color(150, 255, 255);
	m_DownGraduateColor = Color(0, 255, 255, 255);

	m_UpColor = Color(0, 255, 255, 255);
	m_DownColor = Color(0, 255, 255, 255);
}

CBfGraduatedButton::~CBfGraduatedButton(void)
{
	if (m_hThread != NULL)
	{
		::CloseHandle(m_hThread);
		m_hThread = NULL;
	}
}

// 创建窗口
bool CBfGraduatedButton::CreateWnd(CDirectUiDlg *pParentDlg, CDirectUiManager *pUiManager, CDirectUiWindowMsgCtrl *pMsgCtrl,
					   CRect WndRect, int nWndId, WND_TYPE WndType, int nImageId, CString strImagePath, IMAGE_TYPE nImageType)
{
	bool bRet = CBfButton::CreateWnd(pParentDlg, pUiManager, pMsgCtrl, WndRect, nWndId, WndType, nImageId, strImagePath, nImageType);

	if (bRet)
	{
		if (m_hThread == NULL)
		{
			UINT nThreadID = 0;
			m_hThread = (HANDLE)_beginthreadex(NULL, 0, DrawGraduatedButtonThread, this, 0, &nThreadID);
		}

		bRet = (m_hThread != NULL);
	}

	return bRet;
}

void CBfGraduatedButton::OnPaint()
{
	if (m_hThread == NULL)
	{
		UINT nThreadID = 0;
		m_hThread = (HANDLE)_beginthreadex(NULL, 0, DrawGraduatedButtonThread, this, 0, &nThreadID);
	}

	if (m_hThread != NULL && m_bIsCanDrawGraduate)
	{
		DrawGraduatedButton(GRADUATE_STA_NORMAL);
		//m_bIsCanDrawGraduate = false;
	}

	if (IsMouseDown())
	{
		DrawGraduatedButton(GRADUATE_STA_LBUTTONDOWN);
	}

	NormalDraw();
	CBfButton::OnPaint();
}

void CBfGraduatedButton::OnMouseHover(CPoint point)
{
}

void CBfGraduatedButton::OnMouseLeave(CPoint point)
{
}

void CBfGraduatedButton::OnLButtonUp(CPoint point)
{
	m_nDrawCtns = 1;
	CBfButton::OnLButtonUp(point);
}

void CBfGraduatedButton::SetDrawButtonParam()
{
	int nShowCtns = 3;
	int nSleepTime = 20;
	bool bIsMouseHoveSta = false;

	m_nDrawCtns = 1;
	while (!IsDestroy())
	{
		if (IsVisable())
		{
			int nAUp = m_UpGraduateColor.GetA() / nShowCtns;
			int nADown = m_DownGraduateColor.GetA() / nShowCtns;

			// 鼠标进入
			while (IsMouseHover() && m_nDrawCtns <= nShowCtns)
			{
				bIsMouseHoveSta = true;
				int nUpAlpha = nAUp * m_nDrawCtns, nDownAlpha = nADown * m_nDrawCtns;
				CUiMethod::SafeColor(nUpAlpha);
				CUiMethod::SafeColor(nDownAlpha);

				m_UpColor = Color(nUpAlpha, m_UpGraduateColor.GetR(), m_UpGraduateColor.GetG(), m_UpGraduateColor.GetB());
				m_DownColor = Color(nDownAlpha, m_DownGraduateColor.GetR(), m_DownGraduateColor.GetG(), m_DownGraduateColor.GetB());

				m_bIsCanDrawGraduate = true;
				this->RedrawWindow();

				m_nDrawCtns++;
				Sleep(nSleepTime);
			}

			// 鼠标移出
			bool bIsMouseHover_New = IsMouseHover();
			if (bIsMouseHoveSta && !bIsMouseHover_New)
			{
				bIsMouseHoveSta = false;
				while (m_nDrawCtns >= 1)
				{
					int nUpAlpha = nAUp * m_nDrawCtns, nDownAlpha = nADown * m_nDrawCtns;
					CUiMethod::SafeColor(nUpAlpha);
					CUiMethod::SafeColor(nDownAlpha);

					m_UpColor = Color(nUpAlpha, m_UpGraduateColor.GetR(), m_UpGraduateColor.GetG(), m_UpGraduateColor.GetB());
					m_DownColor = Color(nDownAlpha, m_DownGraduateColor.GetR(), m_DownGraduateColor.GetG(), m_DownGraduateColor.GetB());

					m_bIsCanDrawGraduate = true;
					this->RedrawWindow();

					m_nDrawCtns--;
					Sleep(nSleepTime);
				}

				m_bIsCanDrawGraduate = false;
				this->RedrawWindow();
			}

			Sleep(nSleepTime);
		}
		else
		{
			Sleep(100);
		}
	}
}
