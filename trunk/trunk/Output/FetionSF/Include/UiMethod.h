
#pragma once
#include "GlobalDef.h"

class CUiMethod
{
public:
	CUiMethod();
	virtual ~CUiMethod();

	// ȡ�õ�ǰexe��Ŀ¼·�������'\'����
	static CString GetAppPath();

	// �õ�ָ�����ھ��Σ�[0,0]����ϵ
	static CRect GetWndRect(HWND hWnd);

	// GDI+ ���������ͺ�windows������������ת��
	static Rect CRect2Rect(CRect &InRect);
	static RectF CRect2RectF(CRect &InRect);
	static CRect RectF2CRect(RectF &Rf);
	static PointF CPoint2PointF(CPoint &point);

	// ���ݴ��ڵĳ��ȺͿ�ȣ��õ���Ļ���д��ڵ�����
	static CRect CenterWnd(int cx, int cy);

	// ���ð�ȫ��ɫֵ 0 <= nColor <= 255
	static void SafeColor(int &nColor);

	// ��Ļ����ת��
	static void ClientToScreen(HWND hWnd, CRect &ClientRect);
	static void ScreenToClient(HWND hWnd, CRect &ScreenRect);

	// ����Բ�Ǿ�������
	static GraphicsPath* MakeRoundRect(Point topLeft, Point bottomRight, INT percentageRounded);

	// ��Ļָ�������ͼ
	static HBITMAP WINAPI GetScreenBitmap(CRect &GetRect);

private:

};

