
#include "StdAfx.h"
#include "RgnDlg.h"
#include "AggRender.h"

#define __base_super					CHighEfficiencyDlg


CRgnDlg::CRgnDlg(HINSTANCE hInstance, HWND hParentWnd, int nIconId)
: __base_super(hInstance, hParentWnd, nIconId)
{
//	DeleteBfStyle(BFS_CAN_DRAW);
	AddBfStyle(BFS_MODAL_DLG);
//	DeleteBfStyle(BFS_HAVE_MIN_BTN);
	DeleteBfStyle(BFS_HAVE_MAX_BTN);

	m_pGifStatic = NULL;
	m_pMinButton = NULL;
	m_pCloseButton = NULL;
	m_pZhuanBtn = NULL;

	m_dbFactor = 0.0;

	m_PointList.clear();

	m_pUiManager = &m_UiManager;
}

CRgnDlg::~CRgnDlg(void)
{
	m_PointList.clear();
}

void CRgnDlg::OnCreate()
{
	__base_super::OnCreate();

	m_UiManager.InitManager(this);

	CString strSkinDir = CSysUnit::GetAppPath();

	CString strPicPath = strSkinDir + _T("FetionData\\UseFace\\tbclose.png");
	m_pCloseButton = m_UiManager.CreateBfPictureButton(this, CRect(0, 0, 0, 0), DWM_SYS_CMD_CLOSE, BSC_THREE, 0, strPicPath, IT_PNG);
	if (m_pCloseButton == NULL)
	{
		::MessageBox(m_hParent, _T("初始化 m_pCloseButton 失败，程序无法启动！"), MSG_TITLE, MB_OK | MB_ICONSTOP);
		::PostMessage(m_hParent, WM_CLOSE, NULL, NULL);
	}

	strPicPath = strSkinDir + _T("FetionData\\UseFace\\tbmin.png");
	m_pMinButton = m_UiManager.CreateBfPictureButton(this, CRect(0, 0, 0, 0), DWM_SYS_CMD_MIN, BSC_THREE, 0, strPicPath, IT_PNG);
	if (m_pMinButton == NULL)
	{
		::MessageBox(m_hParent, _T("初始化 m_pMinButton 失败，程序无法启动！"), MSG_TITLE, MB_OK | MB_ICONSTOP);
		::PostMessage(m_hParent, WM_CLOSE, NULL, NULL);
	}

	strPicPath = strSkinDir + _T("FetionData\\UseFace\\转.png");
	m_pZhuanBtn = m_UiManager.CreateBfNormalGraduatedButton(this, CRect(0, 0, 0, 0), 100, 0, strPicPath, IT_PNG);
	if (m_pZhuanBtn == NULL)
	{
		::MessageBox(m_hParent, _T("初始化 m_pZhuanBtn 失败，程序无法启动！"), MSG_TITLE, MB_OK | MB_ICONSTOP);
		::PostMessage(m_hParent, WM_CLOSE, NULL, NULL);
	}

	strPicPath = strSkinDir + _T("FetionData\\UseFace\\Test1.gif");
	m_pGifStatic = m_UiManager.CreateBfGifStatic(this, CRect(0, 0, 0, 0), 0, 0, strPicPath);
	if (m_pGifStatic == NULL)
	{
		::MessageBox(m_hParent, _T("初始化 m_pGifStatic 失败，程序无法启动！"), MSG_TITLE, MB_OK | MB_ICONSTOP);
		::PostMessage(m_hParent, WM_CLOSE, NULL, NULL);
		return;
	}
	m_pGifStatic->SetMouseActive(false);

	strPicPath = strSkinDir + _T("FetionData\\UseFace\\T255_50.png");
	m_TImage.LoadImageFromFile(strPicPath, IT_PNG);

	//m_Blend是结构体BLENDFUNCTION的对象，用于指定两个DC(画图设备)的融合方式。
	m_Blend.BlendOp = AC_SRC_OVER;
	m_Blend.BlendFlags = 0;
	m_Blend.AlphaFormat = AC_SRC_ALPHA;
	m_Blend.SourceConstantAlpha = 255;

	// 设置窗体的透明特性
	CSysUnit::SetWindowToTransparence(m_hWnd, true);

	// 设置默认大小
	this->CenterWindow(500, 400);
}

LRESULT CRgnDlg::OnSize(HDWP hWinPoslnfo, WPARAM wParam, LPARAM lParam)
{
	int cx = LOWORD(lParam);
	int cy = HIWORD(lParam);

	CRect WndRect = this->GetClientRect();

	CRect GifStatic(100, 20, 229, 170);
	if (m_pGifStatic != NULL)
	{
//		m_pGifStatic->MoveWindow(GifStatic, hWinPoslnfo);
	}

	CRect CloseRect(0, 0, 0, 0);
	CloseRect.left = GifStatic.right + 100;
	CloseRect.right = CloseRect.left + 30;
	CloseRect.top = GifStatic.bottom;
	CloseRect.bottom = CloseRect.top + 30;

	if (m_pCloseButton != NULL)
	{
		m_pCloseButton->MoveWindow(CloseRect, hWinPoslnfo);
	}

	CRect MinRect(0, 0, 0, 0);
	MinRect.right = GifStatic.right;
	MinRect.left = MinRect.right - 30;
	MinRect.bottom = GifStatic.bottom - 30;
	MinRect.top = MinRect.bottom - 30;
	if (m_pMinButton != NULL)
	{
		m_pMinButton->MoveWindow(MinRect, hWinPoslnfo);
	}

	CRect ZhuanRect(MinRect);
	ZhuanRect.left = MinRect.right + 100;
	ZhuanRect.right = ZhuanRect.left + 40;
	if (m_pZhuanBtn != NULL)
	{
		m_pZhuanBtn->MoveWindow(ZhuanRect, hWinPoslnfo);
	}

	RedrawWindow();
	return __base_super::OnSize(hWinPoslnfo, wParam, lParam);
}

void CRgnDlg::OnPaint(HDC hPaintDc)
{
	// 设置窗体的透明特性
	CSysUnit::SetWindowToTransparence(m_hWnd, true);

	CRect WndRect = this->GetClientRect();
	CBitmapDC BmpDc;
	BmpDc.Create(WndRect.Width(), WndRect.Height());

	HDC hMemoryDC = BmpDc.GetSafeHdc();
	HBITMAP hMemoryBitmap = BmpDc.GetBmpHandle();
	if (hMemoryDC != NULL && hMemoryBitmap != NULL)
	{
		Graphics MemDcGrap(hMemoryDC);

		WndRect = this->GetWindowRect();
		POINT ptWinPos = {WndRect.left, WndRect.top};
		POINT ptSrc = {0, 0};
		SIZE sizeWindow = {WndRect.Width(), WndRect.Height()};

		if (m_PointList.size() <= 0)
		{
			// 开始画图
			m_UiManager.OnPaintRgn(WndRect, &MemDcGrap);
			::UpdateLayeredWindow(m_hWnd, hPaintDc, &ptWinPos, &sizeWindow, hMemoryDC, &ptSrc, 0, &m_Blend, ULW_ALPHA);
		}
		else
		{
			// 绘图
			m_UiManager.OnPaintRgn(WndRect, &MemDcGrap);

			// 计算扭曲位置
			int nSize = (int)m_PointList.size();
			double dbNum = m_dbFactor * (double)nSize;
			nSize = (int)dbNum;

			if (nSize < 0)
				nSize = 0;

			if (nSize >= (int)m_PointList.size())
				nSize = (int)m_PointList.size() - 1;

			WndRect = this->GetClientRect();

			// 方式：梯形旋转
			// 轨迹点
			CPoint ptTraj = m_PointList[nSize];
			CPoint ptLeftUp(ptTraj.x, WndRect.top + ptTraj.y);
			CPoint ptLeftDown(ptLeftUp.x, WndRect.bottom - ptTraj.y);
			CPoint ptRightUp(WndRect.right - ptTraj.x, WndRect.top - ptTraj.y);
			CPoint ptRightDown(ptRightUp.x, WndRect.bottom + ptTraj.y);


			CPoint vP[4];
			vP[0] = ptLeftDown;
			vP[1] = ptRightDown;
			vP[2] = ptRightUp;
			vP[3] = ptLeftUp;

			pixel_map SrcMapImg;
			rendering_buffer SrcImgBuf;
			pixel_map DstMapImg;
			rendering_buffer DstImgBuf;

			HANDLE g_hMem = CAggInterface::CreatePixelMap(hMemoryBitmap, SrcMapImg, SrcImgBuf);
			CAggInterface::CreatePixelMap(DstMapImg, DstImgBuf, WndRect.Width(), WndRect.Height());

			// 绘制3D图案
			CAggDraw2DTo3D::Draw2DTo3D(DstImgBuf, SrcImgBuf, vP);

			::UpdateLayeredWindow(m_hWnd, hPaintDc, &ptWinPos, &sizeWindow, hMemoryDC, &ptSrc, 0, &m_Blend, ULW_ALPHA);

			CAggInterface::ClosePixelMap(g_hMem);
			CAggInterface::ClosePixelMap(DstMapImg);

			if (m_dbFactor >= 1.0)
			{
				m_PointList.clear();
				this->RedrawWindow();
			}

			/*
			if (m_TImage.IsReady())
			{
				// 导入背景图片
				Image *pDrawImg = m_TImage.GetImage()->GetThumbnailImage(WndRect.Width(), WndRect.Height());
				if (pDrawImg != NULL)
				{
					Graphics ImageGrap(pDrawImg);

					// 开始画图
					m_UiManager.OnPaintRgn(WndRect, &ImageGrap);

					// 计算扭曲位置
					int nSize = (int)m_PointList.size();
					double dbNum = m_dbFactor * (double)nSize;
					nSize = (int)dbNum;

					if (nSize < 0)
						nSize = 0;

					if (nSize >= (int)m_PointList.size())
						nSize = (int)m_PointList.size() - 1;

					WndRect = this->GetClientRect();

					// 方式1：平行四边形旋转
					CPoint PtUpTop = m_PointList[nSize];
					CPoint PtUpBottom(PtUpTop.x + ((WndRect.left + (WndRect.Width() / 2)) - PtUpTop.x) * 2,
						PtUpTop.y + (WndRect.top - PtUpTop.y) * 2);
					CPoint PtDownTop(PtUpTop.x, PtUpTop.y + WndRect.Height());

					Point destinationPoints[] =
					{
						Point(PtUpTop.x, PtUpTop.y),
						Point(PtUpBottom.x, PtUpBottom.y),
						Point(PtDownTop.x, PtDownTop.y)
					};
					MemDcGrap.DrawImage(pDrawImg, destinationPoints, 3);

					// 窗口透明贴图
					::UpdateLayeredWindow(m_hWnd, hPaintDc, &ptWinPos, &sizeWindow, hMemoryDC, &ptSrc, 0, &m_Blend, ULW_ALPHA);

					if (m_dbFactor >= 1.0)
						m_PointList.clear();

					delete pDrawImg;
				}
			}
			*/
		}
	}
}

LRESULT CRgnDlg::OnTimer(WPARAM wParam, LPARAM lParam)
{
	int nTimerId = (int)wParam;

	if (nTimerId == m_nTimerId)
	{
		m_dbFactor += 0.05;

		if (m_dbFactor >= 1.0)
		{
			this->KillTimer(m_nTimerId);
		}
		this->RedrawWindow();
	}

	return __base_super::OnTimer(wParam, lParam);
}

// 鼠标左键抬起消息
void CRgnDlg::DUI_OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 100)
	{
		CRect WndRect = this->GetClientRect();
		CAKTrajectory::EllipseMidPoint(CPoint(WndRect.Width() / 2, 0), WndRect.Width() / 2, WndRect.Width() / 20, EGT_TOP, m_PointList);

		m_dbFactor = 0.0;
		m_nTimerId = this->SetTimer(10);
	}

	__base_super::DUI_OnLButtonUp(wParam, lParam);
}
