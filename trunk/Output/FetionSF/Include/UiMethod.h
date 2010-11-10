
#pragma once
#include "GlobalDef.h"


// 取得当前exe的目录路径，最后'\'结束
CString GetAppPath();

// 得到指定窗口矩形，[0,0]坐标系
CRect GetWndRect(HWND hWnd);

// GDI+ 的坐标类型和windows常用坐标类型转换
Rect CRect2Rect(CRect &InRect);
RectF CRect2RectF(CRect &InRect);
CRect RectF2CRect(RectF &Rf);
PointF CPoint2PointF(CPoint &point);

// 根据窗口的长度和宽度，得到屏幕居中窗口的坐标
CRect CenterWnd(int cx, int cy);

// 设置安全颜色值 0 <= nColor <= 255
void SafeColor(int &nColor);

// 屏幕坐标转换
void ClientToScreen(HWND hWnd, CRect &ClientRect);
void ScreenToClient(HWND hWnd, CRect &ScreenRect);

// 创建圆角矩形区域
GraphicsPath* MakeRoundRect(Point topLeft, Point bottomRight, INT percentageRounded);

// 屏幕指定区域截图
HBITMAP WINAPI GetScreenBitmap(CRect &GetRect);

// 取得椭圆轨迹数据
void EllipseMidPoint(CPoint &MidPoint, double dbRx, double dbRy, ELLIPSE_GET_TYPE egtType, POINT_VET &PointList);
