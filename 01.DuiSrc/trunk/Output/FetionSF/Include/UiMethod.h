
#pragma once
#include "FetionSFDefs.h"

class CUiMethod
{
public:
	CUiMethod();
	virtual ~CUiMethod();

	// ��ʼ��GDI+
	static void InitGdiPlus();
	// ж��GDI+
	static void UnInitGdiPlus();

	// GDI+ ���������ͺ�windows������������ת��
	static Rect CRect2Rect(CRect &InRect);
	static RectF CRect2RectF(CRect &InRect);
	static CRect RectF2CRect(RectF &Rf);
	static PointF CPoint2PointF(CPoint &point);

	// ���ð�ȫ��ɫֵ 0 <= nColor <= 255
	static void SafeColor(int &nColor);

	// ��Ļ����ת��
	static void ClientToScreen(HWND hWnd, CRect &ClientRect);
	static void ScreenToClient(HWND hWnd, CRect &ScreenRect);

	// ����Բ�Ǿ�������
	static GraphicsPath* MakeRoundRect(Point topLeft, Point bottomRight, INT percentageRounded);

	// ��Ļָ�������ͼ
	static HBITMAP GetScreenBitmap(CRect &GetRect);
	static bool GetScreenBitmap(HDC hMemDC, CRect &GetRect);

	// ȡ��ͼƬ����
	static IMAGE_TYPE GetImageTypeFromLocal(CString strPath);

	// ��ͼƬ���浽����
	static bool SaveToBitmap(HBITMAP hBitmap, CString strPath);

	// ͨ��GDI+ȡ�ñ���ͼƬ��clsid
	static int GetImageEncoderClsid(const WCHAR* format, CLSID* pClsid);

	// ����DC��ͼƬ�ļ�
	static void SaveHdcToFile(HDC hdc, CString strPath);
private:
	//��ʼ��gdiplus�Ļ���
	static ULONG_PTR gdiplusToken;
};
