
#include "UiMethod.h"

ULONG_PTR CUiMethod::gdiplusToken = NULL;

// ��ʼ��GDI+
void CUiMethod::InitGdiPlus()
{
	if (gdiplusToken == NULL)
	{
		GdiplusStartupInput gdiplusStartupInput;
		// ��ʼ��GDI+.
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	}
}

// ж��GDI+
void CUiMethod::UnInitGdiPlus()
{
	if (gdiplusToken != NULL)
	{
		GdiplusShutdown(gdiplusToken);
		gdiplusToken = NULL;
	}
}

Rect CUiMethod::CRect2Rect(CRect &InRect)
{
	Rect RetRect;
	RetRect.X = InRect.left;
	RetRect.Y = InRect.top;
	RetRect.Width = InRect.Width();
	RetRect.Height = InRect.Height();

	return RetRect;
}

RectF CUiMethod::CRect2RectF(CRect &InRect)
{
	RectF RetRect;
	RetRect.X = (REAL)InRect.left;
	RetRect.Y = (REAL)InRect.top;
	RetRect.Width = (REAL)InRect.Width();
	RetRect.Height = (REAL)InRect.Height();

	return RetRect;
}

CRect CUiMethod::RectF2CRect(RectF &Rf)
{
	CRect RetRect(0, 0, 0, 0);
	RetRect.left = (LONG)Rf.X;
	RetRect.top = (LONG)Rf.Y;
	RetRect.right = RetRect.left + (LONG)Rf.Width;
	RetRect.bottom = RetRect.top + (LONG)Rf.Height;

	return RetRect;
}

PointF CUiMethod::CPoint2PointF(CPoint &point)
{
	PointF ptF((REAL)point.x, (REAL)point.y);
	return ptF;
}

void CUiMethod::SafeColor(int &nColor)
{
	if (nColor > 255)
		nColor = 255;
	
	if (nColor < 0)
		nColor = 0;
}

HBITMAP CUiMethod::GetScreenBitmap(CRect &GetRect) 
{ 
	HDC hDC = NULL, hMemDC = NULL;
	HBITMAP hNewBitmap = NULL;

	if ((hDC = ::GetDC(NULL)) != NULL)
	{ 
		if ((hMemDC = ::CreateCompatibleDC(hDC)) != NULL)
		{ 
			if ((hNewBitmap = ::CreateCompatibleBitmap(hDC, GetRect.Width(), GetRect.Height())) != NULL)
			{
				HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hMemDC, hNewBitmap);
				::BitBlt(hMemDC, 0, 0, GetRect.Width(), GetRect.Height(),
					hDC, GetRect.left, GetRect.top, SRCCOPY);

				::SelectObject(hMemDC, (HGDIOBJ)hOldBitmap);
			}
			::DeleteDC(hMemDC);
		}
		::ReleaseDC(NULL, hDC);
	}
	return hNewBitmap;
}

bool CUiMethod::GetScreenBitmap(HDC hMemDC, CRect &GetRect) 
{
	bool bRet = false;
	HDC hDC = NULL;
	if (hMemDC != NULL && (hDC = ::GetDC(NULL)) != NULL)
	{
		::BitBlt(hMemDC, 0, 0, GetRect.Width(), GetRect.Height(),
			hDC, GetRect.left, GetRect.top, SRCCOPY);

		::ReleaseDC(NULL, hDC);
		bRet = true;
	}

	return bRet;
}

void CUiMethod::ClientToScreen(HWND hWnd, CRect &ClientRect)
{
	POINT Pt;
	int nW = 0, nH = 0;

	Pt.x = ClientRect.left;
	Pt.y = ClientRect.top;
	nW = ClientRect.Width();
	nH = ClientRect.Height();

	::ClientToScreen(hWnd, &Pt);
	ClientRect.left = Pt.x;
	ClientRect.top = Pt.y;
	ClientRect.right = ClientRect.left + nW;
	ClientRect.bottom = ClientRect.top + nH;
}

void CUiMethod::ScreenToClient(HWND hWnd, CRect &ScreenRect)
{
	POINT Pt;
	int nW = 0, nH = 0;

	Pt.x = ScreenRect.left;
	Pt.y = ScreenRect.top;
	nW = ScreenRect.Width();
	nH = ScreenRect.Height();

	::ScreenToClient(hWnd, &Pt);
	ScreenRect.left = Pt.x;
	ScreenRect.top = Pt.y;
	ScreenRect.right = ScreenRect.left + nW;
	ScreenRect.bottom = ScreenRect.top + nH;
}

// ����Բ�Ǿ�������
// �������ӣ�
//	TextureBrush brush(pDrawImage);
//	GraphicsPath * pPath = MakeRoundRect(Point(DstRect1.X, DstRect1.Y),
//		Point(DstRect.X + DstRect.Width, DstRect.Y + DstRect.Height), 30);
//	pDoGrap->FillPath(&brush, pPath);
//	delete pPath;
GraphicsPath* CUiMethod::MakeRoundRect(Point topLeft, Point bottomRight, INT percentageRounded)
{
	assert(percentageRounded >= 1 && percentageRounded <= 100);

	INT left  = min(topLeft.X, bottomRight.X);
	INT right = max(topLeft.X, bottomRight.X);

	INT top    = min(topLeft.Y, bottomRight.Y);
	INT bottom = max(topLeft.Y, bottomRight.Y);

	INT offsetX = (right-left)*percentageRounded/100;
	INT offsetY = (bottom-top)*percentageRounded/100;

	GraphicsPath pt;
	GraphicsPath * path = pt.Clone();

	path->AddArc(right-offsetX, top, offsetX, offsetY, 270, 90);
	path->AddArc(right-offsetX, bottom-offsetY, offsetX, offsetY, 0, 90);
	path->AddArc(left, bottom - offsetY, offsetX, offsetY, 90, 90);
	path->AddArc(left, top, offsetX, offsetY, 180, 90);
	path->AddLine(left + offsetX, top, right - offsetX/2, top);

	return path;
}   

// ��ͼƬ���浽����
bool CUiMethod::SaveToBitmap(HBITMAP hBitmap, CString strPath)
{
	// λͼ��ÿ��������ռ�ֽ����� 
	WORD wbitsCount;
	// ��ɫ���С 
	DWORD dwpalettelsize=0;
	DWORD dwbmdibitsize,dwdibsize,dwwritten; 
	// ������λͼ�ĸ��ֵ���Ϣ�� 
	BITMAP bitmap;
	// �����˴�С�����͵�BMP�ļ�����Ϣ�� 
	BITMAPFILEHEADER bmfhdr;
	BITMAPINFOHEADER bi; 
	LPBITMAPINFOHEADER lpbi; 
	HANDLE fh,fdib;

	// �õ�BITMAP�ṹ��
	GetObject(hBitmap,sizeof(BITMAP),(void *)&bitmap);

	// ���´�������BITMAP����Ϣ���BITMAPINFOHEADER�ṹ 
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

	// ���´����ǻ�ȡ��ɫ��ĳ��ȣ���ɫ�����ڵ��ô����٣���Ϊ256ɫ��λͼ�Ѿ������ˡ� 
	if(wbitsCount <= 8)
		dwpalettelsize = (1 << wbitsCount)*sizeof(RGBQUAD);

	// ����λͼ�Ĵ�С����������Ӧ���ڴ�ռ䣬ע�����û�з���BITMAPFILEHEADER�� 
	dwbmdibitsize=((bitmap.bmWidth*wbitsCount+31)/8)*bitmap.bmHeight; 
	fdib = GlobalAlloc(GHND,dwbmdibitsize+dwpalettelsize+sizeof(BITMAPINFOHEADER)); 
	lpbi = (LPBITMAPINFOHEADER)::GlobalLock(fdib); 
	// ��bi�е�����д�������ڴ��С� 
	*lpbi=bi;
	HDC hdc=::GetDC(NULL); 
	GetDIBits(hdc,hBitmap,0,(UINT)bitmap.bmHeight,(LPSTR)lpbi+sizeof(BITMAPINFOHEADER)+dwpalettelsize,(BITMAPINFO *)lpbi,DIB_RGB_COLORS); 
	// GetDIBits������Ҫ�ĺ������������λͼ���ݵĹ�����������ɣ�����һ������ΪHDC,�ڶ�������Ϊλͼ�����
	// ����������Ϊɨ���еĿ�ʼ�У�һ��Ϊ0�����ĸ�Ϊ�����У�һ����Ǹ߶ȣ����ĸ���������Ҫ������ʾ�������ݵ���ʼ��ַ��
	// �����ַһ�����ڵ�ɫ��֮�󡣵��������ָ���ǽ���BITMAPINFO�ṹ�ĵ�ַ������ṹ����û��д������ʵ����BITMAPINFO�ṹ���ϵ�ɫ����Ϣ��
	// ���һ�������Ǹ�ʽ��һ����DIB_RGB_COLORS

	// �����ļ��Լ��ļ���Ϣͷ 
	fh=CreateFile(strPath.LockBuffer(),GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL|FILE_FLAG_SEQUENTIAL_SCAN,NULL);
	strPath.UnlockBuffer();
	if(fh==INVALID_HANDLE_VALUE) 
		return FALSE;

	// BMP���ͣ�һ��Ҫ����д 
	bmfhdr.bfType=0x4d42;
	// �ļ��ܳ����ɼ����������
	dwdibsize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+dwbmdibitsize+dwpalettelsize;
	bmfhdr.bfSize=dwdibsize;
	bmfhdr.bfReserved1=0;
	bmfhdr.bfReserved2=0;
	// λͼ����������ļ�ͷ��ƫ����
	bmfhdr.bfOffBits=(DWORD)sizeof(BITMAPFILEHEADER)+(DWORD)sizeof(BITMAPINFOHEADER)+dwpalettelsize;

	// ���ļ���Ϣͷд���ļ�
	WriteFile(fh,(LPSTR)&bmfhdr,sizeof(BITMAPFILEHEADER),&dwwritten,NULL);
	// ������д���ļ�������BITMAPINFO�ṹ����ɫ�塢����
	WriteFile(fh,(LPSTR)lpbi,dwdibsize,&dwwritten,NULL);
	// �ر���ؾ��
	::GlobalUnlock(fdib);
	::GlobalFree(fdib);
	::CloseHandle(fh);

	return TRUE; 
}

int CUiMethod::GetImageEncoderClsid(const WCHAR* format, CLSID* pClsid)
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
void CUiMethod::SaveHdcToFile(HDC hdc, CString strPath)
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
}
*/

// ȡ��ͼƬ����
IMAGE_TYPE CUiMethod::GetImageTypeFromLocal(CString strPath)
{
	IMAGE_TYPE ImgType = IT_NON;


	return ImgType;
}
