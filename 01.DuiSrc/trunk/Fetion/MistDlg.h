
#pragma once
#include "Fetion.h"
#include "MoveMistDlg.h"
#include "SizeMistDlg.h"

#define WND_ID_LOGON_USER_LOGO					(65535)
#define WND_ID_LOGON_LINK_1						(65536)
#define WND_ID_LOGON_LINK_2						(65537)
#define WND_ID_LOGON_LINK_3						(65538)
#define WND_ID_LOGON_LINK_4						(65539)
#define WND_ID_LOGON_PSW_EDIT					(65540)
#define WND_ID_LOGON_USER_COMBO_BOX				(65541)
#define WND_ID_LOGON_BTN						(65542)

class CMistDlg : public CHighEfficiencyDlg
{
public:
	CMistDlg(HINSTANCE hInstance, HWND hParentWnd, int nIconId);
	~CMistDlg(void);

protected:
	virtual LRESULT OnMoving(WPARAM wParam, LPARAM lParam);
	virtual void OnPaint(HDC hPaintDc);
	virtual void OnCreate();
	virtual LRESULT OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnSizing(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnSize(HDWP hWinPoslnfo, WPARAM wParam, LPARAM lParam);

	// 鼠标左键按下消息
	virtual void DUI_OnLButtonDown(WPARAM wParam, LPARAM lParam);
	// 鼠标左键抬起消息
	virtual void DUI_OnLButtonUp(WPARAM wParam, LPARAM lParam);
	// 鼠标左键双击消息
	virtual void DUI_OnLButtonDblClk(WPARAM wParam, LPARAM lParam);
	// 鼠标进入窗口
	virtual void DUI_OnMouseHover(WPARAM wParam, LPARAM lParam);
	// 鼠标离开窗口
	virtual void DUI_OnMouseLeave(WPARAM wParam, LPARAM lParam);

	virtual void MoveMistBegin();
	virtual void MoveMistEnd();

	virtual void SizeMistBegin();
	virtual void SizeMistEnd();

private:
	CBfMouseMoveStatic *m_pUserLogo;
	CBfLinkStatic *m_pLink1;
	CBfLinkStatic *m_pLink2;
	CBfLinkStatic *m_pLink3;
	CBfLinkStatic *m_pLink4;
	CBfStatic *m_pStatic;

	CBfStatic *m_pL1;
	CBfStatic *m_pL2;
	CBfStatic *m_pYdLogo;

	CBfComboBox *m_pUserComboBox;
	CBfEdit *m_pPassWordEdit;
	CBfCheckBox *m_pCheckBox1;
	CBfCheckBox *m_pCheckBox2;

	CBfDrawButton *m_pLogonBtn;

	CBaseCtrlManager m_UiManager;


	CBitmapDC m_BmpDc;
	BLENDFUNCTION m_Blend;


	CMoveMistDlg m_MoveMistDlg;
	bool m_bInMoveMist;
	CRect m_MistDlgShowRect;

////////////////////////////////////////////
	CSizeMistDlg m_SizeMistDlg;
	bool m_bInSizeMist;
};
