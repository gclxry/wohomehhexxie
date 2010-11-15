//////////////////////////////////////////////////////////////////////////
// ����MFC CStatic����̬�ı�����

#pragma once
#include "BaseCtrlDefs.h"

typedef vector<COMBO_DATA> COMBO_DATA_LIST;


class CBfComboBox : public CDirectUiWindow, public CDirectUiWindowMsgCtrl
{
	friend class CBfComboBoxSelectDlg;
public:
	CBfComboBox(void);
	virtual ~CBfComboBox(void);

	virtual bool OnDirectUiWndMsgProc(int nMsgId, DWM_INFO &MsgInfo);

	// ��������
	virtual bool CreateWnd(CDirectUiDlg *pParentDlg, CDirectUiManager *pUiManager, CDirectUiWindowMsgCtrl *pMsgCtrl,
		CRect WndRect, int nWndId, WND_TYPE WndType, int nImageId = 0, CString strImagePath = _T(""), IMAGE_TYPE nImageType = IT_BMP);
	
	// �ƶ�����
	virtual void MoveWindow(CRect ToRect, HDWP hWinPoslnfo);

	COMBO_DATA &GetSelectData() { return m_CurComData; };
	void AddComboItem(COMBO_DATA &ComboData);
	void SetCloseButtonImage(BTN_STA_CTNS nStas, CString strImagePath, IMAGE_TYPE nImageType);
	
protected:
	virtual void OnPaint();

	// DirectUi������Ϣ
	// ������������Ϣ
	virtual void DUI_OnLButtonDown(WPARAM wParam, LPARAM lParam);
	// �����봰��
	virtual void DUI_OnMouseHover(WPARAM wParam, LPARAM lParam);
	// ����뿪����
	virtual void DUI_OnMouseLeave(WPARAM wParam, LPARAM lParam);

	virtual void OnMouseHover(CPoint point);
	virtual void OnMouseLeave(CPoint point);

	CRect GetSelectDlgPos() { return m_SelDlgPos; };
	void SetCurrentComboData(COMBO_DATA &ComboData);
	COMBO_DATA_LIST *GetComboDataList() { return &m_ComboDataList; };
	void ClearData();

private:
	CBfEdit *m_pEdit;
	CBfMouseMoveStatic *m_pLogoStatic;
	CBfDropDownButton *m_pDropDownBtn;
	CBfComboBoxSelectDlg *m_pSelectDlg;

	CRect m_SelDlgPos;
	COMBO_DATA_LIST m_ComboDataList;
	COMBO_DATA m_CurComData;
};
