
#pragma once
#include "GlobalDef.h"


// ȡ�õ�ǰexe��Ŀ¼·�������'\'����
CString GetAppPath();

// �õ�ָ�����ھ��Σ�[0,0]����ϵ
CRect GetWndRect(HWND hWnd);

// GDI+ ���������ͺ�windows������������ת��
Rect CRect2Rect(CRect &InRect);
RectF CRect2RectF(CRect &InRect);
CRect RectF2CRect(RectF &Rf);
PointF CPoint2PointF(CPoint &point);

// ���ݴ��ڵĳ��ȺͿ�ȣ��õ���Ļ���д��ڵ�����
CRect CenterWnd(int cx, int cy);

// ���ð�ȫ��ɫֵ 0 <= nColor <= 255
void SafeColor(int &nColor);

// ��Ļ����ת��
void ClientToScreen(HWND hWnd, CRect &ClientRect);
void ScreenToClient(HWND hWnd, CRect &ScreenRect);

// ����Բ�Ǿ�������
GraphicsPath* MakeRoundRect(Point topLeft, Point bottomRight, INT percentageRounded);

// ��Ļָ�������ͼ
HBITMAP WINAPI GetScreenBitmap(CRect &GetRect);

// ȡ����Բ�켣����
void EllipseMidPoint(CPoint &MidPoint, double dbRx, double dbRy, ELLIPSE_GET_TYPE egtType, POINT_VET &PointList);
