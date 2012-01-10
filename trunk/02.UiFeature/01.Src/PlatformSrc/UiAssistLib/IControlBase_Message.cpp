
#include "StdAfx.h"
#include "..\..\Inc\IControlBase.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IControlBase.h"

// 绘制当前控件，参数为父窗口/父控件的内存DC
void IControlBase::OnPaintControl(CDrawingBoard &WndMemDc, RECT ActiveDrawRct)
{
	if (WndMemDc.GetSafeHdc() == NULL || m_pUiEngine == NULL || GetOwnerWindow() == NULL || RECT_WIDTH(ActiveDrawRct) <= 0 || RECT_HEIGHT(ActiveDrawRct) <= 0)
		return;

	RECT RectInWnd = GetWindowRect();

	// 超出父窗口不再绘制
	if ((RectInWnd.right <= ActiveDrawRct.left)
	|| (RectInWnd.bottom <= ActiveDrawRct.top)
	|| (RectInWnd.left >= ActiveDrawRct.right)
	|| (RectInWnd.top >= ActiveDrawRct.bottom))
		return;

	m_CtrlMemDc.Create(RECT_WIDTH(RectInWnd), RECT_HEIGHT(RectInWnd), 0, false, m_bNeedRedraw);
	if (m_CtrlMemDc.GetBits() == NULL)
		return;

	// 重绘控件自身
	if (m_bNeedRedraw)
		OnPaint();

	// 计算有效绘制区域
	RECT DrawRct;
	INIT_RECT(DrawRct);
	DrawRct.left = (RectInWnd.left >= ActiveDrawRct.left) ? RectInWnd.left : ActiveDrawRct.left;
	DrawRct.right = (RectInWnd.right >= ActiveDrawRct.right) ? ActiveDrawRct.right : ActiveDrawRct.left;
	DrawRct.top = (RectInWnd.top >= ActiveDrawRct.top) ? RectInWnd.top : ActiveDrawRct.top;
	DrawRct.bottom = (RectInWnd.bottom >= ActiveDrawRct.bottom) ? ActiveDrawRct.bottom : ActiveDrawRct.bottom;

	// 绘制到窗口的DC上
	int nWidth = RECT_WIDTH(DrawRct);
	int nHeight = RECT_HEIGHT(DrawRct);
	m_pUiEngine->AlphaBlend(WndMemDc, DrawRct.left, DrawRct.top, nWidth, nHeight,
		m_CtrlMemDc, DrawRct.left - RectInWnd.left, DrawRct.top - RectInWnd.top, nWidth, nHeight);

	// 绘制子控件
	for (CHILD_CTRLS_VEC::iterator pCtrlItem = m_ChildCtrlsVec.begin(); pCtrlItem != m_ChildCtrlsVec.end(); pCtrlItem++)
	{
		IControlBase* pCtrl = *pCtrlItem;
		if (pCtrl != NULL)
			pCtrl->OnPaintControl(WndMemDc, DrawRct);
	}
}

// 设置有效的绘制区域
void IControlBase::SetActiveDrawRect(RECT ActiveDrawRect)
{

}
