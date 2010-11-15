#pragma once
#include "BfBaseBar.h"
#include "BfStatic.h"
#include "BfPictureButton.h"
#include "DirectUiWndMsgCtrl.h"

struct COMBO_DATA 
{
	CString strImagePath;
	IMAGE_TYPE nImageType;
	CString strTextId;
	CString strTextName;

	COMBO_DATA()
	{
		nImageType = IT_BMP;
		strImagePath = _T("");
		strTextId = _T("");
		strTextName = _T("");
	};
};

// ComboBox ѡ��ťID��־
#define COMBO_SEL_BTN_ID_SIGN					(0x00FA0000)
// ComboBox �رհ�ťID��־
#define COMBO_COLSE_BTN_ID_SIGN					(0x0FA00000)

class CBfComboSelBtnBar : public CBfBaseBar, public CDirectUiWindowMsgCtrl
{
public:
	CBfComboSelBtnBar(void);
	~CBfComboSelBtnBar(void);

	// ��������
	virtual bool CreateWnd(CDirectUiDlg *pParentDlg, CDirectUiManager *pUiManager, CDirectUiWindowMsgCtrl *pMsgCtrl,
		CRect WndRect, int nWndId, WND_TYPE WndType, int nImageId = 0, CString strImagePath = _T(""), IMAGE_TYPE nImageType = IT_BMP);

	virtual bool InitBar();
	virtual void SetComboItem(COMBO_DATA &ComboData);
	virtual void MoveWindow(CRect ToRect, HDWP hWinPoslnfo);

	void SetSelect(bool bIsSelect) { m_bIsSelect = bIsSelect; };
	void SetCloseButtonImage(BTN_STA_CTNS nStas, CString strImagePath, IMAGE_TYPE nImageType);

	void ReleaseWindow();

protected:
	virtual bool IsReady();

	bool OnDirectUiWndMsgProc(int nMsgId, DWM_INFO &MsgInfo);

	virtual void OnMouseHover(CPoint point);
	virtual void OnMouseLeave(CPoint point);
	
	// DirectUi������Ϣ
	virtual void DUI_OnMouseHover(WPARAM wParam, LPARAM lParam);

private:
	bool m_bIsSelect;
	CBfStatic *m_pBkgndStatic;
	CBfStatic *m_pLogoStatic;
	CBfStatic *m_pIdStatic;
	CBfStatic *m_pNameStatic;
	CBfPictureButton *m_pCloseButton;

	COMBO_DATA m_ComboData;
};
