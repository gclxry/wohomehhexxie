#include "StdAfx.h"
#include <process.h>
#include "BfGifStatic.h"
#include "DirectUiManager.h"


UINT WINAPI CBfGifStatic::DrawGifThread(LPVOID lpParameter)
{
	CBfGifStatic* pGif = (CBfGifStatic*)lpParameter;

	if (pGif != NULL)
		pGif->DrawGif();

	return 0;
}

CBfGifStatic::CBfGifStatic(void)
{
	m_pGifImg = NULL;
	m_hThread = NULL;
}

CBfGifStatic::~CBfGifStatic(void)
{
	if (m_hThread != NULL)
	{
		::CloseHandle(m_hThread);
		m_hThread = NULL;
	}
}

// ��������
bool CBfGifStatic::CreateWnd(CWin32BaseDlg *pParentDlg, CDirectUiManager *pUiManager, CDirectUiWndMsgCtrl *pMsgCtrl,
					   CRect WndRect, int nWndId, WND_TYPE WndType, int nImageId, CString strImagePath, IMAGE_TYPE nImageType)
{
	bool bRet = CBfLinkStatic::CreateWnd(pParentDlg, pUiManager, pMsgCtrl, WndRect, nWndId, WndType, nImageId, strImagePath, nImageType);

	if (bRet)
	{
		m_pGifImg = m_BkgndImage.GetGifImage();

		if (m_pGifImg != NULL && m_pGifImg->IsAnimatedGIF())
		{
			if (m_hThread == NULL)
			{
				UINT nThreadID = 0;
				m_hThread = (HANDLE)_beginthreadex(NULL, 0, DrawGifThread, this, 0, &nThreadID);
			}
		}

		OnPaint();
	}

	return bRet;
}

CRect CBfGifStatic::GetGifRect()
{
	CRect GifRect(0, 0, 0, 0);
	if (m_pGifImg != NULL && m_pGifImg->IsAnimatedGIF())
	{
		GifRect.right = m_pGifImg->GetImage()->GetWidth();
		GifRect.bottom = m_pGifImg->GetImage()->GetHeight();
	}

	return GifRect;
}

void CBfGifStatic::OnPaint()
{
	if (m_hThread == NULL && m_pGifImg != NULL && m_pGifImg->IsAnimatedGIF())
	{
		UINT nThreadID = 0;
		m_hThread = (HANDLE)_beginthreadex(NULL, 0, DrawGifThread, this, 0, &nThreadID);
	}

	if (m_hThread != NULL && m_pGifImg != NULL)
		m_pUiManager->DrawCenterImage(m_pDoGrap, m_pGifImg->GetImage(), m_WndRect);
}

void CBfGifStatic::DrawGif()
{
	int nFrame = 0;
	// Guid��ֵ����ʾGIFΪ FrameDimensionTime����ʾTIFʱΪ FrameDimensionPage
	GUID Guid = FrameDimensionTime;
	while (!IsDestroy())
	{
		if (IsVisable() && !m_WndRect.IsRectEmpty() && m_pGifImg != NULL && m_pGifImg->IsAnimatedGIF())
		{
			// �������õ�ǰ�Ļ����֡
			m_pGifImg->GetImage()->SelectActiveFrame(&Guid, nFrame);
			this->RedrawWindow();

			long lPause = 0;
			if (nFrame >= m_pGifImg->GetFrameCounts())
				lPause = (((long*)(m_pGifImg->GetFrameParam()->value))[0]) * 10;
			else
				lPause = (((long*)(m_pGifImg->GetFrameParam()->value))[nFrame]) * 10;

			Sleep(lPause);

			// ����������һ֡���������¿�ʼ
			nFrame++;
			if (nFrame >= m_pGifImg->GetFrameCounts())
				nFrame = 0;
		}
		else
		{
			Sleep(200);
		}
	}
}
