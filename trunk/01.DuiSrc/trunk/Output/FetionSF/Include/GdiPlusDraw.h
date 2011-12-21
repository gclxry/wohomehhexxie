
#pragma once
#include "FetionSFDefs.h"

class CGdiPlusDraw
{
public:
	CGdiPlusDraw();
	virtual ~CGdiPlusDraw();

	// 画矩形线
	static void DrawRectLine(Graphics *pDoGrap, Color nLineColor, CRect DstRect);
	// 画背景色
	static void DrawColor(Graphics *pDoGrap, Color nBkgndColor, CRect DstRect);
	// 画图拉伸充满窗口
	static void DrawImage(Graphics *pDoGrap, Image *pDrawImage, CRect &DstRect, CRect &SrcRect);
	// 画图画在矩形中间[nWaneEllipse：圆角矩形参数，一般为10较好]
	static void DrawCenterImage(Graphics *pDoGrap, Image *pDrawImage, CRect &DstRect, int nWaneEllipse = 0);
	// 画文字
	static void DrawWndText(Graphics *pDoGrap, WND_TEXT &WndText);
	static void DrawText(Graphics *pDoGrap, CString strText, CRect TextRect, CString strFontName, int nFontHeight, FontStyle FStyle, Color nTextColor, StringFormat &OutFormat);

private:

};

