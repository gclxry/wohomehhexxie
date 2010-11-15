#include "StdAfx.h"
#include <assert.h>
#include "BfComboBoxSelectDlg.h"
#include "BfComboBox.h"
#include "DirectUiManager.h"

// ��ѡ��İ�ť�Ĵ�С
#define CBSB_SELECT_BTN_H						(45)
// ��ѡ��İ�ť�ĸ����İ�ť��С
#define CBSB_AFTER_SELECT_BTN_H					(30)
// ��ͨ��ť
#define CBSB_NORMAL_BTN_H						(20)
// ��ť���
#define CBSB_BTN_JG_H							(1)
// �߿�
#define CBSB_DLG_FRAME							(3)
// �������Ž����С
#define CBSB_SOUFANG							(3)

UINT WINAPI CBfComboBoxSelectDlg::DrawGraduatedSelBtnThread(LPVOID lpParameter)
{
	CBfComboBoxSelectDlg* pButton = (CBfComboBoxSelectDlg*)lpParameter;

	if (pButton != NULL)
		pButton->DrawGraduatedSelBtn();

	return 0;
}

CBfComboBoxSelectDlg::CBfComboBoxSelectDlg(HINSTANCE hInstance, HWND hParentWnd, CBfComboBox *pComboBox) :
CDirectUiDlg(hInstance, hParentWnd, 0)
{
	m_nSelectBtnId = 1;
	m_pComboBox = pComboBox;
	m_pUiManager = NULL;
	m_hThread = NULL;
	m_SelBtnList.clear();
	m_bIsDestroy = false;

	m_nCloseBtnImageStas = BSC_THREE;
	m_strCloseBtnImagePath = _T("");
	m_nCloseBtnImageType = IT_BMP;

	DeleteBfStyle(BFS_CAN_DRAW);
	AddBfStyle(BFS_MODAL_DLG);
	DeleteBfStyle(BFS_HAVE_MIN_BTN);
	DeleteBfStyle(BFS_HAVE_MAX_BTN);
}

CBfComboBoxSelectDlg::~CBfComboBoxSelectDlg(void)
{
	if (m_pUiManager != NULL)
	{
		delete m_pUiManager;
		m_pUiManager = NULL;
	}

	ReleaseBtnList();
}

void CBfComboBoxSelectDlg::ReleaseBtnList()
{
	if (m_pUiManager != NULL)
		m_pUiManager->ClearAllDirectUiWnd();

	m_SelBtnList.clear();
}

// �����Ƿ��ʼ��
bool CBfComboBoxSelectDlg::IsReady()
{
	return (m_pUiManager != NULL && m_hWnd != NULL && ::IsWindow(m_hWnd) && m_pComboBox != NULL);
}

void CBfComboBoxSelectDlg::SetCloseButtonImage(BTN_STA_CTNS nStas, CString strImagePath, IMAGE_TYPE nImageType)
{
	m_nCloseBtnImageStas = nStas;
	m_strCloseBtnImagePath = strImagePath;
	m_nCloseBtnImageType = nImageType;

	for (COMBO_SEL_BTN_LIST::iterator pItem = m_SelBtnList.begin(); pItem != m_SelBtnList.end(); pItem++)
	{
		CBfComboSelBtnBar* pBtn = *pItem;
		if (pBtn != NULL)
			pBtn->SetCloseButtonImage(nStas, strImagePath, nImageType);
	}
}

LRESULT CBfComboBoxSelectDlg::OnKillFocus(WPARAM wParam, LPARAM lParam)
{
	EndThisDialog();
	return 0;
}

void CBfComboBoxSelectDlg::OnDestroy()
{
	m_bIsDestroy = true;

	if (m_hThread != NULL)
	{
		::CloseHandle(m_hThread);
		m_hThread = NULL;
	}

	if (IsReady())
		m_pUiManager->OnDestroy();
}

LRESULT CBfComboBoxSelectDlg::OnNcActive(UINT message, WPARAM wParam, LPARAM lParam)
{
	return WM_PAINT;
}

LRESULT CBfComboBoxSelectDlg::OnNcCalcSize(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

LRESULT CBfComboBoxSelectDlg::OnEraseBkgnd(WPARAM wParam, LPARAM lParam)
{
	return 1;
}

LRESULT CBfComboBoxSelectDlg::OnNcPaint(WPARAM wParam, LPARAM lParam)
{
	return 1;
}

void CBfComboBoxSelectDlg::OnCreate()
{
	m_bIsDestroy = false;

	if (m_hThread == NULL)
	{
		UINT nThreadID = 0;
		m_hThread = (HANDLE)_beginthreadex(NULL, 0, DrawGraduatedSelBtnThread, this, 0, &nThreadID);
	}

	if (m_pComboBox != NULL)
	{
		if (m_pUiManager == NULL)
		{
			m_pUiManager = new CDirectUiManager;
			if (m_pUiManager != NULL)
			{
				// ��ʼ������
				m_pUiManager->InitManager(this);
				m_pUiManager->SetBkgndColor(Color(255, 255, 255));
			}
		}

		if (m_pUiManager != NULL)
		{
			// 1. ����ѡ��ť
			ReleaseBtnList();
			int nId = 1;
			COMBO_DATA_LIST *pComList = m_pComboBox->GetComboDataList();
			for (COMBO_DATA_LIST::iterator pItem = pComList->begin(); pItem != pComList->end(); pItem++)
			{
				COMBO_DATA ComData = *pItem;
				CBfComboSelBtnBar* pBtn = m_pUiManager->CreateBfComboSelBtnBar(this, CRect(0, 0, 0, 0), nId);
				if (pBtn != NULL)
				{
					if (nId == m_nSelectBtnId)
						pBtn->SetSelect(true);

					pBtn->SetComboItem(ComData);
					pBtn->SetCloseButtonImage(m_nCloseBtnImageStas, m_strCloseBtnImagePath, m_nCloseBtnImageType);

					m_SelBtnList.push_back(pBtn);
					nId++;
				}
			}

			// 2. ���ô���Ĭ�ϴ�С
			CRect DlgRect = m_pComboBox->GetSelectDlgPos();
			ClientToScreen(m_hParent, DlgRect);
			int nWndH = (CBSB_DLG_FRAME * 2);
			if (pComList->size() <= 1)
			{
				nWndH += CBSB_SELECT_BTN_H;
			}
			else if (pComList->size() == 2)
			{
				nWndH += (CBSB_SELECT_BTN_H + CBSB_AFTER_SELECT_BTN_H + CBSB_BTN_JG_H);
			}
			else
			{
				nWndH += (CBSB_SELECT_BTN_H + 
					CBSB_AFTER_SELECT_BTN_H * 2 + 
					CBSB_NORMAL_BTN_H * ((int)pComList->size() - 3) +
					CBSB_BTN_JG_H * ((int)pComList->size() - 1));
			}
			::MoveWindow(this->GetSafeHandle(), DlgRect.left, DlgRect.top, DlgRect.Width(), nWndH, TRUE);

			HRGN hRgn = ::CreateRectRgn(0, 0, DlgRect.Width(), nWndH);
			::SetWindowRgn(m_hWnd, hRgn, TRUE);
			::DeleteObject(hRgn);

			SetSelectButtonPos(m_nSelectBtnId);
		}
	}
}

void CBfComboBoxSelectDlg::OnPaint(HDC hPaintDc)
{
	CRect WndRect = GetWndRect(m_hWnd);
	HDC hMemoryDC = ::CreateCompatibleDC(hPaintDc);
	if (hMemoryDC != NULL && IsReady())
	{
		HBITMAP hMemoryBitmap = ::CreateCompatibleBitmap(hPaintDc, WndRect.Width(), WndRect.Height());
		if (hMemoryDC != NULL)
		{
			::SelectObject(hMemoryDC, hMemoryBitmap);

			// ��ʼ��ͼ
			m_pUiManager->OnPaint(hMemoryDC, WndRect, UBT_NORMAL);

			::BitBlt(hPaintDc, 0, 0, WndRect.Width(), WndRect.Height(),
				hMemoryDC, 0, 0, SRCCOPY);

			::DeleteObject(hMemoryBitmap);
		}
		::DeleteDC(hMemoryDC);
	}
}

LRESULT CBfComboBoxSelectDlg::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	if (IsReady())
	{
		AddBfStyle(BFS_FIRST_IN_WND);
	}

	return 0;
}

LRESULT CBfComboBoxSelectDlg::OnMouseMove(WPARAM wParam, LPARAM lParam)
{
	if (IsReady())
	{
		// ����ȡ������뿪���ڵ���Ϣ
		if (IsSetBfStyle(BFS_FIRST_IN_WND))
		{
			DeleteBfStyle(BFS_FIRST_IN_WND);
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(tme);
			tme.hwndTrack = m_hWnd;
			tme.dwFlags = TME_LEAVE;
			::TrackMouseEvent(&tme);
		}

		int nFlags = (int)wParam;
		CPoint point(LOWORD(lParam), HIWORD(lParam));
		m_pUiManager->OnMouseMove(nFlags, point);
	}

	return 0;
}

LRESULT CBfComboBoxSelectDlg::OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	if (IsReady())
	{
		int nFlags = (int)wParam;
		CPoint point(LOWORD(lParam), HIWORD(lParam));
		m_pUiManager->OnLButtonDown(nFlags, point);
	}

	EndThisDialog();
	return 0;
}

// ����뿪����
void CBfComboBoxSelectDlg::DUI_OnMouseLeave(WPARAM wParam, LPARAM lParam)
{

}

bool CBfComboBoxSelectDlg::OnDirectUiWindowMsgProc(int nMsgId, DWM_INFO &MsgInfo)
{
	bool bRet = false;
	if (IsReady())
	{
		bRet = true;
		if (nMsgId == DWM_LBUTTONDOWN)
		{
			DUI_OnLButtonDown(MsgInfo.wParam, MsgInfo.lParam);
		}
		else if (nMsgId == DWM_MOUSEHOVER)
		{
			DUI_OnMouseHover(MsgInfo.wParam, MsgInfo.lParam);
		}
		else if (nMsgId == DWM_MOUSELEAVE)
		{
			DUI_OnMouseLeave(MsgInfo.wParam, MsgInfo.lParam);
		}
	}
	return bRet;
}

// ������������Ϣ
void CBfComboBoxSelectDlg::DUI_OnLButtonDown(WPARAM wParam, LPARAM lParam)
{
	bool bIsClickClose = (((int)wParam & COMBO_COLSE_BTN_ID_SIGN) == COMBO_COLSE_BTN_ID_SIGN);
	int nBtnId = (int)(0x0000FFFF & (int)wParam);

	if (m_pComboBox != NULL)
	{
		if (bIsClickClose)
		{
			// ɾ��һ��ѡ��
			if (nBtnId <= (int)m_SelBtnList.size() && nBtnId <= (int)m_pComboBox->GetComboDataList()->size())
			{
				// ɾ������
				int nComId = 1;
				COMBO_DATA_LIST *pList = m_pComboBox->GetComboDataList();
				for (COMBO_DATA_LIST::iterator pDataItem = pList->begin(); pDataItem != pList->end(); pDataItem++)
				{
					if (nComId == nBtnId)
					{
						pList->erase(pDataItem);
						break;
					}
					nComId++;
				}
			
				// ɾ����ť
				for (COMBO_SEL_BTN_LIST::iterator pBtnItem = m_SelBtnList.begin(); pBtnItem != m_SelBtnList.end(); pBtnItem++)
				{
					CBfComboSelBtnBar* pBtn = *pBtnItem;
					if (pBtn != NULL && pBtn->GetWindowId() == (int)wParam)
					{
						pBtn->ReleaseWindow();
						m_SelBtnList.erase(pBtnItem);
						break;
					}
				}

				// ˢ��combobox������
				if (m_pComboBox->GetComboDataList()->size() > 0)
				{
					COMBO_DATA_LIST *pList = m_pComboBox->GetComboDataList();
					m_pComboBox->SetCurrentComboData((*pList)[0]);
				}
				else
				{
					m_pComboBox->ClearData();
				}
			}
		}
		else
		{
			// ѡ��һ���µ�ѡ��
			if (nBtnId <= (int)m_pComboBox->GetComboDataList()->size())
			{
				COMBO_DATA_LIST *pList = m_pComboBox->GetComboDataList();
				m_pComboBox->SetCurrentComboData((*pList)[nBtnId - 1]);
			}
		}
	}
}

// �����봰��
void CBfComboBoxSelectDlg::DUI_OnMouseHover(WPARAM wParam, LPARAM lParam)
{
	int nBtnId = (int)(0x0000FFFF & (int)wParam);
	m_nSelectBtnId = nBtnId;
	
	for (COMBO_SEL_BTN_LIST::iterator pBtnItem = m_SelBtnList.begin();
		pBtnItem != m_SelBtnList.end(); pBtnItem++)
	{
		CBfComboSelBtnBar *pBtn = *pBtnItem;
		if (pBtn != NULL && pBtn->IsVisable())
		{
			if (pBtn->GetWindowId() == (int)wParam)
				pBtn->SetSelect(true);
			else
				pBtn->SetSelect(false);
		}
		nBtnId++;
	}
}

void CBfComboBoxSelectDlg::SetSelectButtonPos(int nSelBtnId)
{
	m_nSelectBtnId = nSelBtnId;

	int nBtnNum = 1, nBtnTop = CBSB_DLG_FRAME;
	CRect WndRect = GetWndRect(m_hWnd);

	for (COMBO_SEL_BTN_LIST::iterator pBtnItem = m_SelBtnList.begin();
		pBtnItem != m_SelBtnList.end(); pBtnItem++)
	{
		CBfComboSelBtnBar *pBtn = *pBtnItem;
		if (pBtn != NULL)
		{
			int nBtnH = CBSB_NORMAL_BTN_H;
			if (nBtnNum == (nSelBtnId - 1) || nBtnNum == (nSelBtnId + 1))
			{
				nBtnH = CBSB_AFTER_SELECT_BTN_H;
			}
			else if (nBtnNum == nSelBtnId)
			{
				nBtnH = CBSB_SELECT_BTN_H;
			}

			CRect BtnRect(WndRect.left + CBSB_DLG_FRAME, WndRect.top + nBtnTop, WndRect.right - CBSB_DLG_FRAME, nBtnTop + nBtnH);
			pBtn->MoveWindow(BtnRect, NULL);

			nBtnNum++;
			nBtnTop += (nBtnH + CBSB_BTN_JG_H);
		}
	}
}

void CBfComboBoxSelectDlg::DrawGraduatedSelBtn()
{
	int nOldSelId = m_nSelectBtnId;
	while (!m_bIsDestroy)
	{
		if (nOldSelId != m_nSelectBtnId)
		{
			nOldSelId = m_nSelectBtnId;

			while (!m_bIsDestroy && nOldSelId == m_nSelectBtnId)
			{
				int nBtnNum = 1, nBtnTop = CBSB_DLG_FRAME;
				CRect WndRect = GetWndRect(m_hWnd);
				bool bHaveMove = false;

				for (COMBO_SEL_BTN_LIST::iterator pBtnItem = m_SelBtnList.begin();
					pBtnItem != m_SelBtnList.end(); pBtnItem++)
				{
					CBfComboSelBtnBar *pBtn = *pBtnItem;
					if (pBtn != NULL)
					{
						int nBtnDstH = CBSB_NORMAL_BTN_H;
						if (nBtnNum == (m_nSelectBtnId - 1) || nBtnNum == (m_nSelectBtnId + 1))
						{
							nBtnDstH = CBSB_AFTER_SELECT_BTN_H;
						}
						else if (nBtnNum == m_nSelectBtnId)
						{
							nBtnDstH = CBSB_SELECT_BTN_H;
						}

						CRect CurBtnRect = pBtn->GetWindowRect();
						int nBtnMoveH = CurBtnRect.Height();
						if (CurBtnRect.Height() > nBtnDstH)
						{
							bHaveMove = true;
							nBtnMoveH -= CBSB_SOUFANG;
							if (nBtnMoveH < nBtnDstH)
								nBtnMoveH = nBtnDstH;
						}
						else if (CurBtnRect.Height() < nBtnDstH)
						{
							bHaveMove = true;
							nBtnMoveH += CBSB_SOUFANG;
							if (nBtnMoveH > nBtnDstH)
								nBtnMoveH = nBtnDstH;
						}

						CRect BtnRect(WndRect.left + CBSB_DLG_FRAME, WndRect.top + nBtnTop, WndRect.right - CBSB_DLG_FRAME, nBtnTop + nBtnMoveH);
						pBtn->MoveWindow(BtnRect, NULL);

						nBtnNum++;
						nBtnTop += (nBtnMoveH + CBSB_BTN_JG_H);
					}
				}
				::RedrawWindow(m_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);

				if (!bHaveMove)
					break;
			}
		}
		else
		{
			Sleep(50);
		}
	}
}
