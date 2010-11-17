
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

/*
AlphaBlend是Window自带的GDI函数,在作GUI的时候为了达到更漂亮的效果我们常常用它.
BLENDFUNCTION是AlphaBlend用控制透明效果的重要参数.

定义如下:
typedef struct _BLENDFUNCTION {
BYTE     BlendOp;
BYTE     BlendFlags;
BYTE     SourceConstantAlpha;
BYTE     AlphaFormat;
}BLENDFUNCTION, *PBLENDFUNCTION, *LPBLENDFUNCTION;

BlendOp: 这个参数必须也只能为AC_SRC_OVER(0x00),意思就是把源图片覆盖到目标之上.
BlendFlags: 必须为0
SourceConstantAlpha: 简写为SCA,指定源图片的透明度,这个值是会和源图片的Alpha通道值合并计算的.
AlphaFormat: 可以填两种,一种是0x00,一种是AC_SRC_ALPHA(0x01).填0的话,AlphaBlend据说就和BitBlt一样了,
我没有试验过~填1的话,源DC必须是32位的DC不然的话,AlphaBlend会返回参数错误.

计算公式(当SCA不是0xFF时):
输出像素(R,G,B,A) = 源像素(R,G,B,A) * SCA / 0xFF + 目标像素(R,G,B,A) * (1.0 - SCA / 0xFF)

当SCA是0xFF时，计算公式
输出像素(R,G,B,A) = 源像素(R,G,B,A) + 目标像素(R,G,B,A) * (1.0 - 源像素(A) / 0xFF)

混合计算公式
输出像素(R,G,B) = 源像素(R,G,B) * SCA / 0xFF + 目标像素(R,G,B) * (1.0 - 源像素(A) / 0xFF * SCA / 0xFF)
*/

bool SaveHBITMAP(HBITMAP hBitmap)
{
	WORD wbitsCount;//位图中每个像素所占字节数。 
	DWORD dwpalettelsize=0;//调色板大小 
	DWORD dwbmdibitsize,dwdibsize,dwwritten; 
	BITMAP bitmap;//定义了位图的各种的信息。 
	BITMAPFILEHEADER bmfhdr;//定义了大小、类型等BMP文件的信息。 
	BITMAPINFOHEADER bi; 
	LPBITMAPINFOHEADER lpbi; 
	HANDLE fh,fdib;

	GetObject(hBitmap,sizeof(BITMAP),(void *)&bitmap);//得到BITMAP结构。

	//以下代码是用BITMAP的信息填充BITMAPINFOHEADER结构 
	wbitsCount=bitmap.bmBitsPixel; 
	bi.biSize=sizeof(BITMAPINFOHEADER); 
	bi.biWidth=bitmap.bmWidth; 
	bi.biHeight=bitmap.bmHeight; 
	bi.biPlanes=1; 
	bi.biBitCount= bitmap.bmBitsPixel ; 
	bi.biClrImportant=0; 
	bi.biClrUsed=0; 
	bi.biCompression=BI_RGB; 
	bi.biSizeImage=0; 
	bi.biYPelsPerMeter=0; 
	bi.biXPelsPerMeter=0; 

	//以下代码是获取调色板的长度，调色板现在的用处很少，因为256色的位图已经不多了。 
	if(wbitsCount <= 8)
		dwpalettelsize = (1 << wbitsCount)*sizeof(RGBQUAD);

	//计算位图的大小，并分配相应的内存空间，注意的是没有分配BITMAPFILEHEADER。 
	dwbmdibitsize=((bitmap.bmWidth*wbitsCount+31)/8)*bitmap.bmHeight; 
	fdib = GlobalAlloc(GHND,dwbmdibitsize+dwpalettelsize+sizeof(BITMAPINFOHEADER)); 
	lpbi = (LPBITMAPINFOHEADER)::GlobalLock(fdib); 
	*lpbi=bi;//将bi中的数据写入分配的内存中。 
	HDC hdc=::GetDC(NULL); 
	GetDIBits(hdc,hBitmap,0,(UINT)bitmap.bmHeight,(LPSTR)lpbi+sizeof(BITMAPINFOHEADER)+dwpalettelsize,(BITMAPINFO *)lpbi,DIB_RGB_COLORS); 
	/*GetDIBits是最重要的函数，真正获得位图数据的工作就由它完成，它第一个参数为HDC,第二个参数为位图句柄，第三个参数为扫描行的开始行，一般为0，第四个为结束行，一般就是高度，第四个参数最重要，它表示接收数据的起始地址，这个地址一般是在调色板之后。第五个参数指的是接收BITMAPINFO结构的地址，这个结构上面没有写，它其实就是BITMAPINFO结构加上调色板信息。最后一个参数是格式。一般是DIB_RGB_COLORS*/ 
	//创建文件以及文件信息头 
	fh=CreateFile(_T("C:\\a.bmp"),GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL|FILE_FLAG_SEQUENTIAL_SCAN,NULL); 
	if(fh==INVALID_HANDLE_VALUE) 
		return FALSE;

	bmfhdr.bfType=0x4d42;//BMP类型，一定要这样写 
	dwdibsize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+dwbmdibitsize+dwpalettelsize;//文件总长，由几个部分组成
	bmfhdr.bfSize=dwdibsize;
	bmfhdr.bfReserved1=0;
	bmfhdr.bfReserved2=0;
	bmfhdr.bfOffBits=(DWORD)sizeof(BITMAPFILEHEADER)+(DWORD)sizeof(BITMAPINFOHEADER)+dwpalettelsize;//位图数据相对于文件头的偏移量

	//将文件信息头写入文件
	WriteFile(fh,(LPSTR)&bmfhdr,sizeof(BITMAPFILEHEADER),&dwwritten,NULL);
	//将数据写入文件，包含BITMAPINFO结构、调色板、数据
	WriteFile(fh,(LPSTR)lpbi,dwdibsize,&dwwritten,NULL);
	//关闭相关句柄
	::GlobalUnlock(fdib);
	::GlobalFree(fdib);
	::CloseHandle(fh);

	return TRUE; 
}

int GetImageEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT num = 0; // number of image encoders
	UINT size = 0; // size of the image encoder array in bytes

	ImageCodecInfo* pImageCodecInfo = NULL;

	GetImageEncodersSize(&num, &size);
	if(size == 0)
		return -1; // Failure

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if(pImageCodecInfo == NULL)
		return -1; // Failure

	GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j; // Success
		}   
	}

	free(pImageCodecInfo);
	return -1; // Failure
}

/*
VOID Example_SaveFile(HDC hdc)
{
Graphics graphics(hdc);

// Create an Image object based on a PNG file.
Image  image(L"Mosaic.png");

// Draw the image.
graphics.DrawImage(&image, 10, 10);

// Construct a Graphics object based on the image.
Graphics imageGraphics(&image);

// Alter the image.
SolidBrush brush(Color(255, 0, 0, 255));
imageGraphics.FillEllipse(&brush, 20, 30, 80, 50);

// Draw the altered image.
graphics.DrawImage(&image, 200, 10);

// Save the altered image.
CLSID pngClsid;
GetImageEncoderClsid(L"image/png", &pngClsid);
image.Save(L"Mosaic2.png", &pngClsid, NULL);
*/

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
	//设置窗体的透明特性
	DWORD dwExStyle = GetWindowLong(m_hWnd, GWL_EXSTYLE);
	if ((dwExStyle & WS_EX_LAYERED) != WS_EX_LAYERED)
		SetWindowLong(m_hWnd, GWL_EXSTYLE, dwExStyle^WS_EX_LAYERED);

	CRect WndRect = this->GetClientRect();

	CBitmapDC BmpDc;
	BmpDc.Create(WndRect.Width(), WndRect.Height());

	//HDC hMemoryDC = ::CreateCompatibleDC(hPaintDc);
	HDC hMemoryDC = BmpDc.GetSafeHdc();
	if (hMemoryDC != NULL)
	{
		//HBITMAP hMemoryBitmap = ::CreateCompatibleBitmap(hPaintDc, WndRect.Width(), WndRect.Height());
		HBITMAP hMemoryBitmap = BmpDc.GetBmpHandle();
		if (hMemoryBitmap != NULL)
		{
			::SelectObject(hMemoryDC, hMemoryBitmap);
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
			::DeleteObject(hMemoryBitmap);
		}
		::DeleteDC(hMemoryDC);
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
		RedrawWindow();

	}

	return __base_super::OnTimer(wParam, lParam);
}

// 鼠标左键抬起消息
void CRgnDlg::DUI_OnLButtonUp(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 100)
	{
		CRect WndRect = this->GetClientRect();




/*
		CString strSkinDir = GetAppPath();
		CString strPicPath = strSkinDir + _T("FetionData\\UseFace\\T255.png");
		Image image1(strPicPath.LockBuffer());
		strPicPath.UnlockBuffer();

		Image *pDrawImg = image1.GetThumbnailImage(WndRect.Width(), WndRect.Height());

		CLSID pngClsid;
		GetImageEncoderClsid(L"image/png", &pngClsid);
		strPicPath = strSkinDir + _T("FetionData\\UseFace\\Temp.png");
		pDrawImg->Save(strPicPath.LockBuffer(), &pngClsid, NULL);
		strPicPath.UnlockBuffer();
*/


		CAKTrajectory::EllipseMidPoint(CPoint(WndRect.left + WndRect.Width() / 2, WndRect.top ), WndRect.Width() / 2, WndRect.Width() / 20, EGT_TOP, m_PointList);

		m_dbFactor = 0.0;
		m_nTimerId = this->SetTimer(10);
	}

	__base_super::DUI_OnLButtonUp(wParam, lParam);
}



/*
GDI+在内存中绘制，并保存为BMP、PNG、JPEG格式的图片关键代码(2010-9-11 12:02:00)【收藏】 【评论】 【打印】 【关闭】 


// 获取指定图片格式CLSID

int GetImageEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
UINT num= 0;
UINT size= 0;

ImageCodecInfo* pImageCodecInfo= NULL;

GetImageEncodersSize(&num, &size);
if(size== 0)
{
return -1;
}
pImageCodecInfo= (ImageCodecInfo*)(malloc(size));
if(pImageCodecInfo== NULL)
{
return -1;
}

GetImageEncoders(num, size, pImageCodecInfo);

for(UINT j=0; j< num; ++j)
{
if(wcscmp(pImageCodecInfo[j].MimeType, format)== 0)
{
*pClsid= pImageCodecInfo[j].Clsid;
free(pImageCodecInfo);
pImageCodecInfo= NULL;
return j;
}
}

free(pImageCodecInfo);
pImageCodecInfo= NULL;

return -1;
}



// 在内存中绘制

Bitmap* pBitmap = new Bitmap(200, 400);

if (!pBitmap)
{
return;
}

Graphics* imageGraphics = Graphics::FromImage(pBitmap);



// do some draw on imageGraphics

imageGraphics->FillRectangle(.....);

.... and so on..



// save as image 

CLSID pngClsid;


if (!pBitmap)
{
return FALSE;
}



// save as bmp image
GetImageEncoderClsid(L"image/bmp", &pngClsid);
m_pBitmap->Save("C:\\test.bmp", &pngClsid, NULL);



// save as png image
GetImageEncoderClsid(L"image/png", &pngClsid);
m_pBitmap->Save("C:\\test.png", &pngClsid, NULL);



// save as jpeg image
GetImageEncoderClsid(L"image/jpeg", &pngClsid);
m_pBitmap->Save("C:\\test.jpeg", &pngClsid, NULL);

*/