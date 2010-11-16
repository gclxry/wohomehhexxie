#pragma once

#include "BaseCtrlDefs.h"

#include "BfDrawButton.h"
#include "BfPictureButton.h"
#include "BfStatic.h"
#include "BfMouseMoveStatic.h"
#include "BfLinkStatic.h"
#include "BfEdit.h"
#include "BfCheckBox.h"
#include "BfComboBox.h"
#include "BfDropDownButton.h"
#include "BfGifStatic.h"
#include "BfFlash.h"
//#include "BfNormalGraduatedButton.h"
#include "BfComboSelBtnBar.h"


class CBaseCtrlManager : public CDirectUiManager
{
public:
	CBaseCtrlManager(void);
	~CBaseCtrlManager(void);

	CBfComboSelBtnBar* CreateBfComboSelBtnBar(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId);

	CBfFlash* CreateBfFlash(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, CString strFlashPath = _T(""));

//	CBfGraduatedDropDownButton* CreateBfGraduatedDropDownButton(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId, int nImageId = 0, CString strImagePath = _T(""), IMAGE_TYPE nImageType = IT_BMP);
//	CBfNormalGraduatedButton* CreateBfNormalGraduatedButton(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId, int nImageId = 0, CString strImagePath = _T(""), IMAGE_TYPE nImageType = IT_BMP);
	CBfPictureButton* CreateBfPictureButton(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId, BTN_STA_CTNS nPicStas, int nImageId = 0, CString strImagePath = _T(""), IMAGE_TYPE nImageType = IT_BMP);
	CBfDropDownButton* CreateBfDropDownButton(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId, int nImageId = 0, CString strImagePath = _T(""), IMAGE_TYPE nImageType = IT_BMP);
	CBfDrawButton* CreateBfDrawButton(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId, int nImageId = 0, CString strImagePath = _T(""), IMAGE_TYPE nImageType = IT_BMP);

	CBfEdit* CreateBfEdit(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId, int nImageId = 0, CString strImagePath = _T(""), IMAGE_TYPE nImageType = IT_BMP);
	CBfCheckBox* CreateBfCheckBox(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId, int nImageId = 0, CString strImagePath = _T(""), IMAGE_TYPE nImageType = IT_BMP);
	CBfComboBox* CreateBfComboBox(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId, int nImageId = 0, CString strImagePath = _T(""), IMAGE_TYPE nImageType = IT_BMP);

	CBfGifStatic* CreateBfGifStatic(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId, int nImageId = 0, CString strImagePath = _T(""));
	CBfMouseMoveStatic* CreateBfMouseMoveStatic(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId, int nImageId = 0, CString strImagePath = _T(""), IMAGE_TYPE nImageType = IT_BMP);
	CBfStatic* CreateBfStatic(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nImageId = 0, CString strImagePath = _T(""), IMAGE_TYPE nImageType = IT_BMP);
	CBfLinkStatic* CreateBfLinkStatic(CDirectUiWindowMsgCtrl *pMsgCtrl, CRect WndRect, int nWndId, int nImageId = 0, CString strImagePath = _T(""), IMAGE_TYPE nImageType = IT_BMP);
};
