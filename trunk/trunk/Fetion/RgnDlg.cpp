
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
		::MessageBox(m_hParent, _T("��ʼ�� m_pCloseButton ʧ�ܣ������޷�������"), MSG_TITLE, MB_OK | MB_ICONSTOP);
		::PostMessage(m_hParent, WM_CLOSE, NULL, NULL);
	}

	strPicPath = strSkinDir + _T("FetionData\\UseFace\\tbmin.png");
	m_pMinButton = m_UiManager.CreateBfPictureButton(this, CRect(0, 0, 0, 0), DWM_SYS_CMD_MIN, BSC_THREE, 0, strPicPath, IT_PNG);
	if (m_pMinButton == NULL)
	{
		::MessageBox(m_hParent, _T("��ʼ�� m_pMinButton ʧ�ܣ������޷�������"), MSG_TITLE, MB_OK | MB_ICONSTOP);
		::PostMessage(m_hParent, WM_CLOSE, NULL, NULL);
	}

	strPicPath = strSkinDir + _T("FetionData\\UseFace\\ת.png");
	m_pZhuanBtn = m_UiManager.CreateBfNormalGraduatedButton(this, CRect(0, 0, 0, 0), 100, 0, strPicPath, IT_PNG);
	if (m_pZhuanBtn == NULL)
	{
		::MessageBox(m_hParent, _T("��ʼ�� m_pZhuanBtn ʧ�ܣ������޷�������"), MSG_TITLE, MB_OK | MB_ICONSTOP);
		::PostMessage(m_hParent, WM_CLOSE, NULL, NULL);
	}

	strPicPath = strSkinDir + _T("FetionData\\UseFace\\Test1.gif");
	m_pGifStatic = m_UiManager.CreateBfGifStatic(this, CRect(0, 0, 0, 0), 0, 0, strPicPath);
	if (m_pGifStatic == NULL)
	{
		::MessageBox(m_hParent, _T("��ʼ�� m_pGifStatic ʧ�ܣ������޷�������"), MSG_TITLE, MB_OK | MB_ICONSTOP);
		::PostMessage(m_hParent, WM_CLOSE, NULL, NULL);
		return;
	}
	m_pGifStatic->SetMouseActive(false);

	strPicPath = strSkinDir + _T("FetionData\\UseFace\\T255_50.png");
	m_TImage.LoadImageFromFile(strPicPath, IT_PNG);

	//m_Blend�ǽṹ��BLENDFUNCTION�Ķ�������ָ������DC(��ͼ�豸)���ںϷ�ʽ��
	m_Blend.BlendOp = AC_SRC_OVER;
	m_Blend.BlendFlags = 0;
	m_Blend.AlphaFormat = AC_SRC_ALPHA;
	m_Blend.SourceConstantAlpha = 255;

	// ����Ĭ�ϴ�С
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
AlphaBlend��Window�Դ���GDI����,����GUI��ʱ��Ϊ�˴ﵽ��Ư����Ч�����ǳ�������.
BLENDFUNCTION��AlphaBlend�ÿ���͸��Ч������Ҫ����.

��������:
typedef struct _BLENDFUNCTION {
BYTE     BlendOp;
BYTE     BlendFlags;
BYTE     SourceConstantAlpha;
BYTE     AlphaFormat;
}BLENDFUNCTION, *PBLENDFUNCTION, *LPBLENDFUNCTION;

BlendOp: �����������Ҳֻ��ΪAC_SRC_OVER(0x00),��˼���ǰ�ԴͼƬ���ǵ�Ŀ��֮��.
BlendFlags: ����Ϊ0
SourceConstantAlpha: ��дΪSCA,ָ��ԴͼƬ��͸����,���ֵ�ǻ��ԴͼƬ��Alphaͨ��ֵ�ϲ������.
AlphaFormat: ����������,һ����0x00,һ����AC_SRC_ALPHA(0x01).��0�Ļ�,AlphaBlend��˵�ͺ�BitBltһ����,
��û�������~��1�Ļ�,ԴDC������32λ��DC��Ȼ�Ļ�,AlphaBlend�᷵�ز�������.

���㹫ʽ(��SCA����0xFFʱ):
�������(R,G,B,A) = Դ����(R,G,B,A) * SCA / 0xFF + Ŀ������(R,G,B,A) * (1.0 - SCA / 0xFF)

��SCA��0xFFʱ�����㹫ʽ
�������(R,G,B,A) = Դ����(R,G,B,A) + Ŀ������(R,G,B,A) * (1.0 - Դ����(A) / 0xFF)

��ϼ��㹫ʽ
�������(R,G,B) = Դ����(R,G,B) * SCA / 0xFF + Ŀ������(R,G,B) * (1.0 - Դ����(A) / 0xFF * SCA / 0xFF)
*/

bool SaveHBITMAP(HBITMAP hBitmap)
{
	WORD wbitsCount;//λͼ��ÿ��������ռ�ֽ����� 
	DWORD dwpalettelsize=0;//��ɫ���С 
	DWORD dwbmdibitsize,dwdibsize,dwwritten; 
	BITMAP bitmap;//������λͼ�ĸ��ֵ���Ϣ�� 
	BITMAPFILEHEADER bmfhdr;//�����˴�С�����͵�BMP�ļ�����Ϣ�� 
	BITMAPINFOHEADER bi; 
	LPBITMAPINFOHEADER lpbi; 
	HANDLE fh,fdib;

	GetObject(hBitmap,sizeof(BITMAP),(void *)&bitmap);//�õ�BITMAP�ṹ��

	//���´�������BITMAP����Ϣ���BITMAPINFOHEADER�ṹ 
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

	//���´����ǻ�ȡ��ɫ��ĳ��ȣ���ɫ�����ڵ��ô����٣���Ϊ256ɫ��λͼ�Ѿ������ˡ� 
	if(wbitsCount <= 8)
		dwpalettelsize = (1 << wbitsCount)*sizeof(RGBQUAD);

	//����λͼ�Ĵ�С����������Ӧ���ڴ�ռ䣬ע�����û�з���BITMAPFILEHEADER�� 
	dwbmdibitsize=((bitmap.bmWidth*wbitsCount+31)/8)*bitmap.bmHeight; 
	fdib = GlobalAlloc(GHND,dwbmdibitsize+dwpalettelsize+sizeof(BITMAPINFOHEADER)); 
	lpbi = (LPBITMAPINFOHEADER)::GlobalLock(fdib); 
	*lpbi=bi;//��bi�е�����д�������ڴ��С� 
	HDC hdc=::GetDC(NULL); 
	GetDIBits(hdc,hBitmap,0,(UINT)bitmap.bmHeight,(LPSTR)lpbi+sizeof(BITMAPINFOHEADER)+dwpalettelsize,(BITMAPINFO *)lpbi,DIB_RGB_COLORS); 
	/*GetDIBits������Ҫ�ĺ������������λͼ���ݵĹ�����������ɣ�����һ������ΪHDC,�ڶ�������Ϊλͼ���������������Ϊɨ���еĿ�ʼ�У�һ��Ϊ0�����ĸ�Ϊ�����У�һ����Ǹ߶ȣ����ĸ���������Ҫ������ʾ�������ݵ���ʼ��ַ�������ַһ�����ڵ�ɫ��֮�󡣵��������ָ���ǽ���BITMAPINFO�ṹ�ĵ�ַ������ṹ����û��д������ʵ����BITMAPINFO�ṹ���ϵ�ɫ����Ϣ�����һ�������Ǹ�ʽ��һ����DIB_RGB_COLORS*/ 
	//�����ļ��Լ��ļ���Ϣͷ 
	fh=CreateFile(_T("C:\\a.bmp"),GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL|FILE_FLAG_SEQUENTIAL_SCAN,NULL); 
	if(fh==INVALID_HANDLE_VALUE) 
		return FALSE;

	bmfhdr.bfType=0x4d42;//BMP���ͣ�һ��Ҫ����д 
	dwdibsize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+dwbmdibitsize+dwpalettelsize;//�ļ��ܳ����ɼ����������
	bmfhdr.bfSize=dwdibsize;
	bmfhdr.bfReserved1=0;
	bmfhdr.bfReserved2=0;
	bmfhdr.bfOffBits=(DWORD)sizeof(BITMAPFILEHEADER)+(DWORD)sizeof(BITMAPINFOHEADER)+dwpalettelsize;//λͼ����������ļ�ͷ��ƫ����

	//���ļ���Ϣͷд���ļ�
	WriteFile(fh,(LPSTR)&bmfhdr,sizeof(BITMAPFILEHEADER),&dwwritten,NULL);
	//������д���ļ�������BITMAPINFO�ṹ����ɫ�塢����
	WriteFile(fh,(LPSTR)lpbi,dwdibsize,&dwwritten,NULL);
	//�ر���ؾ��
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

	//����
	CAKPicDraw::GetInst()->SelectPic(m_pBmpData, rc.Width(), rc.Height());
	memset(m_pBmpData, 0, rc.Width() * rc.Height()*4);

	//������Ȼ���
	CAK3DRender::GetInst()->ResetZBuffer(-10000);

	//ѡ��ʹ�õ���ͼ
	AK_2D_UI_PIC *pUIPic=CAK2DUI::GetSingle().FindUIPic(1);
	CAKPicDraw::GetInst(AK_PIC_DRAW_MAX_COUNT-1)->SelectPic(pUIPic->pData, pUIPic->uWidth, pUIPic->uHeight);

	//���嶥���uv
	//	DEF_VERTEX(v1,200,100,0);
	//	DEF_VERTEX(v2,400,100,0);
	//	DEF_VERTEX(v3,600,500,0);
	//	DEF_VERTEX(v4,50,500,0);

	// v1 ���£�v2 ���£�v3 ���ϣ�v4 ����
	DEF_VERTEX(v1,200,100,0);
	DEF_VERTEX(v2,400,50,0);
	DEF_VERTEX(v3,400,500,0);
	DEF_VERTEX(v4,200,450,0);

	DEF_UV(uv1,0,0);
	DEF_UV(uv2,1023,0);
	DEF_UV(uv3,1023,767);
	DEF_UV(uv4,0,767);

	//��Ⱦ
	CAK3DRender::GetInst()->DrawRect2(&v1,&v2,&v3,&v4,uv1,uv2,uv3,uv4,true);

	//��λͼ��ʾ����
	DisplayBmpData(hMemoryDC,hMemoryBitmap,0,0,m_pBmpData, rc.Width(), rc.Height());
}

void CRgnDlg::DisplayBmpData(HDC hMemoryDC, HBITMAP hMemoryBitmap, long x, long y, unsigned char *pBmp, long rows, long cols)
{
	//��ȡ��ǰDC��������ʾλ��(16/24/32)
	int BitCount=::GetDeviceCaps(hMemoryDC, BITSPIXEL);
	switch(BitCount)
	{
	case 16://16λɫ
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

	case 24://24λɫ
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

	case 32://32λɫ
		{
			::SetBitmapBits(hMemoryBitmap, cols*rows*4*sizeof(unsigned char),pBmp);
			break;
		}

	default://����λɫ
		{
			::TextOut(hMemoryDC, (cols-7*16)/2, rows/2, _T("��ʾģʽ��֧��"), 7);
			break;
		}
	}
}

void CRgnDlg::OnPaint(HDC hPaintDc)
{
	//���ô����͸������
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
				// ��ʼ��ͼ
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

					// ����alphaֵ
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
					// ���뱳��ͼƬ
					Image *pDrawImg = m_TImage.GetImage()->GetThumbnailImage(WndRect.Width(), WndRect.Height());
					if (pDrawImg != NULL)
					{
						Graphics ImageGrap(pDrawImg);

						// ��ʼ��ͼ
						m_UiManager.OnPaintRgn(WndRect, &ImageGrap);

						// ����Ť��λ��
						int nSize = (int)m_PointList.size();
						double dbNum = m_dbFactor * (double)nSize;
						nSize = (int)dbNum;

						if (nSize < 0)
							nSize = 0;

						if (nSize >= (int)m_PointList.size())
							nSize = (int)m_PointList.size() - 1;

						WndRect = this->GetClientRect();

						// ��ʽ1����Բ��ת
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

						// ��ʽ2��������ת


						// ����͸����ͼ
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

// ������̧����Ϣ
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
GDI+���ڴ��л��ƣ�������ΪBMP��PNG��JPEG��ʽ��ͼƬ�ؼ�����(2010-9-11 12:02:00)���ղء� �����ۡ� ����ӡ�� ���رա� 


// ��ȡָ��ͼƬ��ʽCLSID

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



// ���ڴ��л���

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