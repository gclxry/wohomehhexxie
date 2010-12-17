
#pragma once
#include "FetionSFDefs.h"

class CUiMethod
{
public:
	CUiMethod();
	virtual ~CUiMethod();

	// 初始化GDI+
	static void InitGdiPlus();
	// 卸载GDI+
	static void UnInitGdiPlus();

	// GDI+ 的坐标类型和windows常用坐标类型转换
	static Rect CRect2Rect(CRect &InRect);
	static RectF CRect2RectF(CRect &InRect);
	static CRect RectF2CRect(RectF &Rf);
	static PointF CPoint2PointF(CPoint &point);

	// 设置安全颜色值 0 <= nColor <= 255
	static void SafeColor(int &nColor);

	// 屏幕坐标转换
	static void ClientToScreen(HWND hWnd, CRect &ClientRect);
	static void ScreenToClient(HWND hWnd, CRect &ScreenRect);

	// 创建圆角矩形区域
	static GraphicsPath* MakeRoundRect(Point topLeft, Point bottomRight, INT percentageRounded);

	// 屏幕指定区域截图
	static HBITMAP GetScreenBitmap(CRect &GetRect);
	static bool GetScreenBitmap(HDC hMemDC, CRect &GetRect);

	// 取得图片类型
	static IMAGE_TYPE GetImageTypeFromLocal(CString strPath);

	// 将图片保存到本地
	static bool SaveToBitmap(HBITMAP hBitmap, CString strPath);

	// 通过GDI+取得保存图片的clsid
	static int GetImageEncoderClsid(const WCHAR* format, CLSID* pClsid);

	// 保存DC到图片文件
	static void SaveHdcToFile(HDC hdc, CString strPath);
private:
	//初始化gdiplus的环境
	static ULONG_PTR gdiplusToken;
};
