//////////////////////////////////////////////////////////////////////////
// 类似MFC CStatic，静态文本窗口

#pragma once
#include "DirectUiWnd.h"

class CBfStatic : public CDirectUiWnd
{
public:
	CBfStatic(void);
	virtual ~CBfStatic(void);

	virtual void OnPaint();

	// 是否绘制背景色，默认不绘制
	void SetDrawBkgndColor(bool bIsDraw) { m_bIsDrawBkgndColor = bIsDraw; };
	// 绘制图片为圆角的参数
	void SetDrawImageWane(int nWaneEllipse = 10)  { m_nWaneEllipse = nWaneEllipse; };
	// 拉伸全屏绘制图片
	void SetFullDrawImage(bool bIsFull) { m_bIsFullDraw = bIsFull; };

protected:
	bool m_bIsDrawBkgndColor;
	bool m_bIsFullDraw;
	int m_nWaneEllipse;
};
