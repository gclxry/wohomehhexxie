
#include "StdAfx.h"
#include "RgnDlg.h"
#include "shellapi.h"
#include "math.h"

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

	m_pBmpData = NULL;
}

CRgnDlg::~CRgnDlg(void)
{
	m_PointList.clear();

	if (m_pBmpData != NULL)
	{
		delete [] m_pBmpData;
		m_pBmpData = NULL;
	}
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

	// 设置默认大小
	this->CenterWindow(500, 400);
}

LRESULT CRgnDlg::OnSize(HDWP hWinPoslnfo, WPARAM wParam, LPARAM lParam)
{
	int cx = LOWORD(lParam);
	int cy = HIWORD(lParam);


	if (m_pBmpData != NULL)
	{
		delete [] m_pBmpData;
		m_pBmpData = NULL;
	}

	CRect WndRect = this->GetClientRect();
	long lSize = WndRect.Width() * WndRect.Height() * 4 * sizeof(unsigned char);
	m_pBmpData = new unsigned char[lSize];

	if (m_pBmpData != NULL)
	{
		CAKPicDraw::GetInst()->SelectPic(m_pBmpData, WndRect.Width(), WndRect.Height());
		CAK3DRender::GetInst()->SelectPicDraw(CAKPicDraw::GetInst());
	}

	CRect GifStatic(100, 20, 229, 170);
	if (m_pGifStatic != NULL)
	{
		m_pGifStatic->MoveWindow(GifStatic, hWinPoslnfo);
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

void CRgnDlg::DrawGdiPlus(HDC hMemoryDC, HBITMAP hMemoryBitmap)
{
	CRect rc = this->GetClientRect();

	//清屏
	CAKPicDraw::GetInst()->SelectPic(m_pBmpData, rc.Width(), rc.Height());
	memset(m_pBmpData, 0, rc.Width() * rc.Height()*4);

	//重置深度缓冲
	CAK3DRender::GetInst()->ResetZBuffer(-10000);

	//选择使用的贴图
	AK_2D_UI_PIC *pUIPic=CAK2DUI::GetSingle().FindUIPic(1);
	CAKPicDraw::GetInst(AK_PIC_DRAW_MAX_COUNT-1)->SelectPic(pUIPic->pData, pUIPic->uWidth, pUIPic->uHeight);

	//定义顶点和uv
	//	DEF_VERTEX(v1,200,100,0);
	//	DEF_VERTEX(v2,400,100,0);
	//	DEF_VERTEX(v3,600,500,0);
	//	DEF_VERTEX(v4,50,500,0);

	// v1 左下，v2 右下，v3 右上，v4 左上
	DEF_VERTEX(v1,200,100,0);
	DEF_VERTEX(v2,400,50,0);
	DEF_VERTEX(v3,400,500,0);
	DEF_VERTEX(v4,200,450,0);

	DEF_UV(uv1,0,0);
	DEF_UV(uv2,1023,0);
	DEF_UV(uv3,1023,767);
	DEF_UV(uv4,0,767);

	//渲染
	CAK3DRender::GetInst()->DrawRect2(&v1,&v2,&v3,&v4,uv1,uv2,uv3,uv4,true);

	//把位图显示出来
	DisplayBmpData(hMemoryDC,hMemoryBitmap,0,0,m_pBmpData, rc.Width(), rc.Height());
}

void CRgnDlg::DisplayBmpData(HDC hMemoryDC, HBITMAP hMemoryBitmap, long x, long y, unsigned char *pBmp, long rows, long cols)
{
	//获取当前DC的像素显示位数(16/24/32)
	int BitCount=::GetDeviceCaps(hMemoryDC, BITSPIXEL);
	switch(BitCount)
	{
	case 16://16位色
		{
			long i,index1,index2;
			long total=rows*cols;
			unsigned short r,g,b;
			unsigned short *pValue;

			for(i=0,index1=0,index2=0;i<total;++i)
			{
				index1+=4;
				index2+=2;

				b=pBmp[index1];
				g=pBmp[index1+1];
				r=pBmp[index1+2];

				pValue=(unsigned short *)&pBmp[index2];

				*pValue=(r/8<<11)|(g/4<<5)|(b/8);
			}

			::SetBitmapBits(hMemoryBitmap, cols*rows*2*sizeof(unsigned char), pBmp);
			break;
		}

	case 24://24位色
		{
			long i,index1,index2;
			long total=rows*cols;

			for(i=0,index1=0,index2=0;i<total;++i)
			{
				index1+=4;
				index2+=3;

				memcpy(&pBmp[index2],&pBmp[index1],sizeof(unsigned char)*3);
			}

			::SetBitmapBits(hMemoryBitmap, cols*rows*3*sizeof(unsigned char),pBmp);
			break;
		}

	case 32://32位色
		{
			::SetBitmapBits(hMemoryBitmap, cols*rows*4*sizeof(unsigned char),pBmp);
			break;
		}

	default://其它位色
		{
			::TextOut(hMemoryDC, (cols-7*16)/2, rows/2, _T("显示模式不支持"), 7);
			break;
		}
	}
}

void CRgnDlg::OnPaint(HDC hPaintDc)
{
	// 设置窗体的透明特性
	DWORD dwExStyle = GetWindowLong(m_hWnd, GWL_EXSTYLE);
	if ((dwExStyle & WS_EX_LAYERED) != WS_EX_LAYERED)
		SetWindowLong(m_hWnd, GWL_EXSTYLE, dwExStyle^WS_EX_LAYERED);

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
			m_UiManager.OnPaintRgn(WndRect, &MemDcGrap);

			struct AK_2D_UI_PIC *pUIPic = CAK2DUI::GetSingle().CreateUIPic(1, WndRect.Width(), WndRect.Height());
			if(pUIPic)
			{
				memcpy(pUIPic->pData, BmpDc.GetBits(), WndRect.Width() * WndRect.Height() * 4);

				// 设置alpha值
				//unsigned char *pDataA = NULL;
				//for(int i=0;i<(WndRect.Width() * WndRect.Height());++i)
				//{
				//	pDataA = &pUIPic->pData[i*4];
				//	pDataA[3] = 255;
				//}
			}

			DrawGdiPlus(hMemoryDC, hMemoryBitmap);





			::UpdateLayeredWindow(m_hWnd, hPaintDc, &ptWinPos, &sizeWindow, hMemoryDC, &ptSrc, 0, &m_Blend, ULW_ALPHA);
			CAK2DUI::GetSingle().FreePicList();

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

					// 方式1：椭圆旋转
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

					// 方式2：梯形旋转


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
		CAKTrajectory::EllipseMidPoint(CPoint(WndRect.left + WndRect.Width() / 2, WndRect.top ), WndRect.Width() / 2, WndRect.Width() / 20, EGT_TOP, m_PointList);

		m_dbFactor = 0.0;
		m_nTimerId = this->SetTimer(10);
	}

	__base_super::DUI_OnLButtonUp(wParam, lParam);
}
