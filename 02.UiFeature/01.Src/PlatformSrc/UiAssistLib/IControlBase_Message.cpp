
#include "StdAfx.h"
#include "..\..\Inc\IControlBase.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IControlBase.h"

// 初始化控件
void IControlBase::OnCreate()
{

}

// 控件初始化完毕
void IControlBase::OnFinalCreate()
{

}

// Builder刷新属性
void IControlBase::OnRefreshProp()
{

}

// 鼠标进入
void IControlBase::OnMouseEnter(POINT pt)
{

}

// 鼠标移出
void IControlBase::OnMouseLeave()
{

}

// 鼠标移动
void IControlBase::OnMouseMove(POINT pt)
{

}

// 鼠标左键点击
void IControlBase::OnLButtonDown(POINT pt)
{

}

// 鼠标左键抬起
void IControlBase::OnLButtonUp(POINT pt)
{

}

// 鼠标左键双击
void IControlBase::OnLButtonDbClick(POINT pt)
{

}

// 鼠标拖动控件
void IControlBase::OnMouseDrag(POINT pt)
{

}

// 鼠标右键点击
void IControlBase::OnRButtonDown(POINT pt)
{

}

// 移动、设置控件位置
void IControlBase::OnSize()
{

}

// 绘制控件
void IControlBase::OnPaint()
{

}

// 移动窗口开始
void IControlBase::OnEnterSizeMove()
{

}

// 移动窗口结束
void IControlBase::OnExitSizeMove()
{

}

// 销毁控件
void IControlBase::OnDestroy()
{

}

// 控件取得焦点，通过Tab键跳转，激活控件
void IControlBase::OnSetFocus()
{

}

// 控件失去焦点
void IControlBase::OnKillFocus()
{

}

// 控件取得键盘输入消息
void IControlBase::OnChar(WPARAM wParam, LPARAM lParam)
{

}

// 接受到默认回车键，执行控件操作
void IControlBase::OnEnterRun()
{

}

// 绘制当前控件，参数为父窗口/父控件的内存DC
void IControlBase::OnPaintControl(CMemoryDC &WndMemDc)
{
	if (WndMemDc.GetSafeHdc() == NULL && m_pUiEngine != NULL)
		return;

	RECT RectInWnd = GetCtrlInWindowRect();
	m_CtrlMemDc.Create(RECT_WIDTH(RectInWnd), RECT_HEIGHT(RectInWnd), 0, false, m_bNeedRedraw);
	if (m_CtrlMemDc.GetBits() == NULL)
		return;

	// 重绘控件自身
	if (m_bNeedRedraw)
		OnPaint();

	// 绘制到父控件的DC上
	int nWidth = RECT_WIDTH(RectInWnd);
	int nHeight = RECT_HEIGHT(RectInWnd);
	m_pUiEngine->AlphaBlend(WndMemDc, RectInWnd.left, RectInWnd.top, nWidth, nHeight,
		m_CtrlMemDc, 0, 0, nWidth, nHeight);

	// 绘制子控件
	for (CHILD_CTRLS_VEC::iterator pCtrlItem = m_ChildCtrlsVec.begin(); pCtrlItem != m_ChildCtrlsVec.end(); pCtrlItem++)
	{
		IControlBase* pCtrl = *pCtrlItem;
		if (pCtrl != NULL)
			pCtrl->OnPaintControl(WndMemDc);
	}
}
