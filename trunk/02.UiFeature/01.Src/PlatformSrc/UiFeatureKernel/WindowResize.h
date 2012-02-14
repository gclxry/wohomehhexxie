
#pragma once

class IWindowBaseImpl;
class CWindowResize
{
public:
	CWindowResize();
	~CWindowResize();

	VOID InitResizeInfo(IWindowBaseImpl *pWndBase, UINT uNcHitTest, int nMaxWidth, int nMaxHeight, int nMinWidth, int nMinHeight);
	VOID UnInit();
	bool MoveWindowToRect(RECT &MoveRect);
	bool IsInResize();
	UINT GetHitType();

private:
	// 上一次拉伸后的窗口的大小和位置
	RECT m_OldRect;
	// 鼠标拉伸操作
	UINT m_uNcHitTest;
	// 被拉伸的窗口
	IWindowBaseImpl *m_pWindowBase;
	// 窗口最大值和最小值
	int m_nMaxWidth;
	int m_nMaxHeight;
	int m_nMinWidth;
	int m_nMinHeight;
};
