
#pragma once
#include "FetionSFDefs.h"

class CGdiPlusDraw
{
public:
	CGdiPlusDraw();
	virtual ~CGdiPlusDraw();

	// ��������
	static void DrawRectLine(Graphics *pDoGrap, Color nLineColor, CRect DstRect);
	// ������ɫ
	static void DrawColor(Graphics *pDoGrap, Color nBkgndColor, CRect DstRect);
	// ��ͼ�����������
	static void DrawImage(Graphics *pDoGrap, Image *pDrawImage, CRect &DstRect, CRect &SrcRect);
	// ��ͼ���ھ����м�[nWaneEllipse��Բ�Ǿ��β�����һ��Ϊ10�Ϻ�]
	static void DrawCenterImage(Graphics *pDoGrap, Image *pDrawImage, CRect &DstRect, int nWaneEllipse = 0);
	// ������
	static void DrawWndText(Graphics *pDoGrap, WND_TEXT &WndText);
	static void DrawText(Graphics *pDoGrap, CString strText, CRect TextRect, CString strFontName, int nFontHeight, FontStyle FStyle, Color nTextColor, StringFormat &OutFormat);

private:

};

