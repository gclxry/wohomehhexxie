
#pragma once

#include "BfButton.h"

// 绘制正常状态的渐变
#define GRADUATE_STA_NORMAL					(1)
// 绘制按钮按下的渐变
#define GRADUATE_STA_LBUTTONDOWN			(2)

class CBfGraduatedButton : public CBfButton
{
public:
	CBfGraduatedButton(void);
	virtual ~CBfGraduatedButton(void);

	virtual void OnPaint();
	virtual bool CreateWnd(CDirectUiDlg *pParentDlg, CDirectUiManager *pUiManager, CDirectUiWindowMsgCtrl *pMsgCtrl,
		CRect WndRect, int nWndId, WND_TYPE WndType, int nImageId = 0, CString strImagePath = _T(""), IMAGE_TYPE nImageType = IT_BMP);

protected:
	static UINT WINAPI DrawGraduatedButtonThread(LPVOID lpParameter);

	virtual void OnMouseHover(CPoint point);
	virtual void OnMouseLeave(CPoint point);
	virtual void OnLButtonUp(CPoint point);

	virtual void SetDrawButtonParam();
	virtual void DrawGraduatedButton(int nDrawSta) = 0;
	virtual void NormalDraw() = 0;

protected:
	HANDLE m_hThread;
	Color m_UpGraduateColor;
	Color m_DownGraduateColor;

	// 绘画用的上下渐变颜色
	Color m_UpColor;
	Color m_DownColor;

	bool m_bIsCanDrawGraduate;
	int m_nDrawCtns;
};
