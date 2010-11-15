//////////////////////////////////////////////////////////////////////////
// 

#pragma once
#include "BfGraduatedButton.h"
#include "BfPopupMenu.h"

class CBfGraduatedDropDownButton : public CBfGraduatedButton
{
public:
	CBfGraduatedDropDownButton(void);
	virtual ~CBfGraduatedDropDownButton(void);

	virtual bool CreateWnd(CDirectUiDlg *pParentDlg, CDirectUiManager *pUiManager, CDirectUiWndMsgCtrl *pMsgCtrl,
		CRect WndRect, int nWndId, WND_TYPE WndType, int nImageId = 0, CString strImagePath = _T(""), IMAGE_TYPE nImageType = IT_BMP);

protected:
	virtual void OnMouseMove(CPoint point);
	virtual void OnMouseLeave(CPoint point);
	virtual void OnLButtonDown(CPoint point);
	virtual void OnLButtonUp(CPoint point);
	virtual void OnDestroy();

	virtual void DrawGraduatedButton(int nDrawSta);
	virtual void NormalDraw();

	bool m_bIsDownInDropWnd;
	bool m_bIsMoveInDropWnd;
	CBfPopupMenu m_PopupMenu;
};
