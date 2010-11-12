#include "stdafx.h"

#include "AKLoadPic.h"

#include <AFXPRIV2.H>

#include "sys/types.h"
#include "sys/stat.h"

unsigned long get_file_len(char *path_name)
{
	struct stat buf;
    if(stat(path_name,&buf)==0)
    {
        return buf.st_size;
    }
    else
    {
        return 0;
    }
}

bool AKLoadPic(char *pFilePath,unsigned char **ppData,long *pWidth,long *pHeight)
{
	unsigned char *pic_data;
	long pic_width,pic_height;

	unsigned long file_len;

	if((file_len=get_file_len(pFilePath))<=0)
		return FALSE;
	
	//��ʱ�ռ�
	HGLOBAL hGlobal=GlobalAlloc(GMEM_MOVEABLE,file_len);
	if(!hGlobal)
		return FALSE;

	char *pData_Tmp=(char *)GlobalLock(hGlobal);

	if (g_spIPicture)
		g_spIPicture.Release();

	//��JPG�ļ�
	BOOL rt;
	CFile file;
	rt=file.Open(pFilePath,CFile::modeRead|CFile::shareDenyWrite);
	if(!rt)
		return FALSE;

	//����JPG�ļ�����
	file.Read(pData_Tmp,file_len);

	IStream* pstm=NULL;

	GlobalUnlock(hGlobal);
	CreateStreamOnHGlobal(hGlobal,TRUE,&pstm);

	//����JPG�ļ��е�λͼ��������
	HRESULT hr = OleLoadPicture(pstm, 0, FALSE,
		IID_IPicture, (void**)&g_spIPicture);

	if(hr!=0)
	{
		GlobalFree(hGlobal);
		return false;
	}

	//ȡλͼ���
	OLE_HANDLE pHandle;
	g_spIPicture->get_Handle(&pHandle);

	//���ӵ�CBitmap����
	CBitmap bmp;
	bmp.Attach((HBITMAP)pHandle);

	//ȡJPGλͼ�ߴ�
	BITMAP bitmap;
	bmp.GetBitmap(&bitmap);

	//����λͼ����
	unsigned long w,h;
	w=bitmap.bmWidth;
	h=bitmap.bmHeight;
	//
	unsigned long l=w*h*4*sizeof(unsigned char);
	
	unsigned char *pData=new unsigned char[l];
	if(!pData)
	{
		return FALSE;
	}
	unsigned char *pData2=new unsigned char[l];
	if(!pData2)
	{
		return FALSE;
	}

	BITMAPINFOHEADER bih;
	bih.biBitCount=32;//bitmap.bmBitsPixel;
	bih.biClrImportant=0;
	bih.biClrUsed=0;
	bih.biCompression=0;
	bih.biHeight=h;
	bih.biPlanes=1;
	bih.biSize=sizeof(BITMAPINFOHEADER);
	bih.biSizeImage=l;
	bih.biWidth=w;
	bih.biXPelsPerMeter=0;
	bih.biYPelsPerMeter=0;

	//
	HDC hDC=CreateDC("DISPLAY",NULL,NULL,NULL);

	GetDIBits(hDC,(HBITMAP)pHandle,0,bih.biHeight,pData,(BITMAPINFO*)&bih,DIB_RGB_COLORS);

	//bmp.GetBitmapBits(l,pData);

	//��GetDIBitsȡλͼ���ݺ�,ͼ���ǵ��õ�,��Ҫ��һ�´���
	long i;
	for(i=h-1;i>=0;--i)
	{
		memcpy(&pData2[(h-i-1)*w*4],&pData[i*w*4],l/h);
	}

	pic_data=pData2;
	pic_width=w;
	pic_height=h;

	delete[] pData;

	//�ر��ļ�
	file.Close();

	GlobalFree(hGlobal);

	*ppData=pic_data;
	*pWidth=pic_width;
	*pHeight=pic_height;
	
	return TRUE;
}
