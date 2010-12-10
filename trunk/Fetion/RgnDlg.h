
#pragma once
#include "Fetion.h"
#include "TestDx9.h"

typedef std::vector<CResImage*> RES_IMAGE_LIST;


class CRgnDlg : public CHighEfficiencyDlg
{
public:
	CRgnDlg(HINSTANCE hInstance, HWND hParentWnd, int nIconId);
	~CRgnDlg(void);

protected:
	virtual void OnCreate();
	virtual LRESULT OnTimer(WPARAM wParam, LPARAM lParam);

	BLENDFUNCTION m_Blend;//结构体BLENDFUNCTION用于指定两个DC(画图设备)的融合方式。

	virtual void OnPaint(HDC hPaintDc);
	virtual LRESULT OnSize(HDWP hWinPoslnfo, WPARAM wParam, LPARAM lParam);

	// 鼠标左键抬起消息
	virtual void DUI_OnLButtonUp(WPARAM wParam, LPARAM lParam);


	void CRgnDlg::DrawGdiPlus(HDC hMemoryDC, HBITMAP hMemoryBitmap);

	void CRgnDlg::DisplayBmpData(HDC hMemoryDC, HBITMAP hMemoryBitmap, long x, long y, unsigned char *pBmp, long rows, long cols);

protected:
	double m_dbFactor;
	int m_nTimerId;

	POINT_VET m_PointList;

	CResImage m_TImage;

	CDxD3DRender m_DxD3d;

private:
	CBfNormalGraduatedButton *m_pZhuanBtn;
	CBfGifStatic *m_pGifStatic;
	CBfPictureButton *m_pMinButton;
	CBfPictureButton *m_pCloseButton;
	CBaseCtrlManager m_UiManager;
};
