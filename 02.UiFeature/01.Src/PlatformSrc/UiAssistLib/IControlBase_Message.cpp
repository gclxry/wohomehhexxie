
#include "StdAfx.h"
#include "..\..\Inc\IControlBase.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IControlBase.h"

void IControlBase::OnCtrlMessage(int nMsgId, WPARAM wParam, LPARAM lParam)
{
	switch (nMsgId)
	{
		// 初始化控件
	case CM_Create:
		OnCreate();
		break;

		// 控件初始化完毕
	case CM_FinalCreate:
		OnFinalCreate();
		break;

		// Builder刷新属性
	case CM_BuilderRefreshProp:
		OnBuilderRefreshProp();
		break;

		// 鼠标进入
	case CM_MouseEnter:
		break;

		// 鼠标移出
	case CM_MouseLeave:
		OnMouseLeave();
		break;

		// 鼠标移动
	case CM_MouseMove:
		break;

		// 鼠标左键点击
	case CM_LButtonDown:
		break;

		// 鼠标左键抬起
	case CM_LButtonUp:
		break;

		// 鼠标左键双击
	case CM_LButtonDbClick:
		break;

		// 鼠标右键点击
	case CM_RButtonDown:
		break;

		// 移动、设置控件位置
	case CM_Size:
		OnSize();
		break;

		// 绘制控件
	case CM_Paint:
		break;

		// 移动窗口开始
	case CM_EnterSizeMove:
		OnEnterSizeMove();
		break;

		// 移动窗口结束
	case CM_ExitSizeMove:
		OnExitSizeMove();
		break;

		// 销毁控件
	case CM_Destroy:
		OnDestroy();
		break;

		// 控件取得焦点，通过Tab键跳转，激活控件
	case CM_SetFocus:
		OnSetFocus();
		break;

		// 控件失去焦点
	case CM_KillFocus:
		OnKillFocus();
		break;

		// 控件取得键盘输入消息
	case CM_Char:
		OnChar(wParam, lParam);
		break;

		// 接受到默认回车键信息
	case CM_DefaultEnterCtrl:
		OnDefaultEnterCtrl();
		break;

	default:
		OnNotification(nMsgId, wParam, lParam);
		break;
	}
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
