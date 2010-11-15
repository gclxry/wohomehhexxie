
#pragma once
#include "Win32BaseDlg.h"
#include "DirectUiWndMsgCtrl.h"
#include "BfComboSelBtnBar.h"

class CDirectUiManager;
class CBfComboBox;

#include <vector>
using namespace std;
typedef vector<CBfComboSelBtnBar*> COMBO_SEL_BTN_LIST;

class CBfComboBoxSelectDlg : public CDirectUiDlg, public CDirectUiWindowMsgCtrl
{
public:
	CBfComboBoxSelectDlg(HINSTANCE hInstance, HWND hParentWnd, CBfComboBox *pComboBox);
	~CBfComboBoxSelectDlg(void);

	bool OnDirectUiWndMsgProc(int nMsgId, DWM_INFO &MsgInfo);
	void SetComboBox(CBfComboBox *pComboBox) { m_pComboBox = pComboBox; };
	void SetCloseButtonImage(BTN_STA_CTNS nStas, CString strImagePath, IMAGE_TYPE nImageType);

protected:
	static UINT WINAPI DrawGraduatedSelBtnThread(LPVOID lpParameter);
	void DrawGraduatedSelBtn();

	virtual void OnCreate();
	virtual void OnPaint(HDC hPaintDc);
	virtual void OnDestroy();
	virtual LRESULT OnNcActive(UINT message, WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnNcCalcSize(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnEraseBkgnd(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnNcPaint(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnMouseMove(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnLButtonDown(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnKillFocus(WPARAM wParam, LPARAM lParam);

	virtual bool IsReady();

	// DirectUi窗口消息
	// 鼠标左键按下消息
	virtual void DUI_OnLButtonDown(WPARAM wParam, LPARAM lParam);
	// 鼠标进入窗口
	virtual void DUI_OnMouseHover(WPARAM wParam, LPARAM lParam);
	// 鼠标离开窗口
	virtual void DUI_OnMouseLeave(WPARAM wParam, LPARAM lParam);

private:
	void ReleaseBtnList();
	void SetSelectButtonPos(int nSelBtnId);

protected:
	CDirectUiManager *m_pUiManager;
	CBfComboBox *m_pComboBox;
	COMBO_SEL_BTN_LIST m_SelBtnList;
	int m_nSelectBtnId;

	bool m_bIsDestroy;
	HANDLE m_hThread;
	BTN_STA_CTNS m_nCloseBtnImageStas;
	CString m_strCloseBtnImagePath;
	IMAGE_TYPE m_nCloseBtnImageType;
};
