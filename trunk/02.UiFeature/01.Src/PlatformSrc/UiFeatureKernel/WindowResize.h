
#pragma once
#include "..\..\Inc\IPropertyBool.h"
#include "..\..\Inc\IPropertyInt.h"

class IWindowBaseImpl;
class CWindowResize
{
public:
	CWindowResize();
	~CWindowResize();

	void InitResizeInfo(IWindowBaseImpl *pWndBase, IPropertyBool *pPropBase_Layered,
		IPropertyBool *pPropSize_Enable,
		IPropertyInt *pPropSize_MaxWidth, IPropertyInt *pPropSize_MaxHeight,
		IPropertyInt *pPropSize_MinWidth, IPropertyInt *pPropSize_MinHeight,
		IPropertyBool *pPropStretching_Enable,
		IPropertyInt *pPropStretching_LeftSpace, IPropertyInt *pPropStretching_RightSpace,
		IPropertyInt *pPropStretching_TopSpace, IPropertyInt *pPropStretching_BottomSpace);

	// 鼠标是否移动到了窗口可以进行拉伸操作的边缘
	int MouseMoveInWindowFrame(POINT pt);

	bool IsInResize();

	// 分层窗口模式下，拉伸窗口操作
	bool BeginResizeInLayeredWindow();
	bool ResizeInLayeredWindow(RECT &OutOldRect, RECT &OutNewRect);
	void EndResizeInLayeredWindow();

private:
	// 上一次拉伸后的窗口的大小和位置
	RECT m_OldRect;
	// 鼠标拉伸操作
	int m_nNcHitTest;
	// 被拉伸的窗口
	IWindowBaseImpl *m_pWindowBase;
	// 是否支持分层窗口
	bool m_bSupLayered;

	// stretching-enable
	bool m_bStretching;
	// stretching-leftspace
	int m_nLeftSpace;
	// stretching-rightspace
	int m_nRightSpace;
	// stretching-topspace
	int m_nTopSpace;
	// stretching-bottomspace
	int m_nBottomSpace;

	bool m_bUseSize;
	int m_nMaxWidth;
	int m_nMaxHeight;
	int m_nMinWidth;
	int m_nMinHeight;
};
