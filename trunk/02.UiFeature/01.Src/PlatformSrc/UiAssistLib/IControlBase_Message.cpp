
#include "StdAfx.h"
#include "..\..\Inc\IControlBase.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IControlBase.h"

// ���Ƶ�ǰ�ؼ�������Ϊ������/���ؼ����ڴ�DC
void IControlBase::OnPaintControl(CDrawingBoard &WndMemDc, RECT ActiveDrawRct)
{
	if (WndMemDc.GetSafeHdc() == NULL || !IsVisible() || m_pUiEngine == NULL || GetOwnerWindow() == NULL || RECT_WIDTH(ActiveDrawRct) <= 0 || RECT_HEIGHT(ActiveDrawRct) <= 0)
		return;

	// ���������ڲ��ٻ���
	if ((m_RectInWindow.right <= ActiveDrawRct.left)
	|| (m_RectInWindow.bottom <= ActiveDrawRct.top)
	|| (m_RectInWindow.left >= ActiveDrawRct.right)
	|| (m_RectInWindow.top >= ActiveDrawRct.bottom))
		return;

	bool bIsCreateNew = m_CtrlMemDc.Create(RECT_WIDTH(m_RectInWindow), RECT_HEIGHT(m_RectInWindow), 0, false, m_bNeedRedraw);
	if (m_CtrlMemDc.GetBits() == NULL)
		return;

	if (bIsCreateNew)
		m_bNeedRedraw = true;

	// �ػ�ؼ�����
	if (m_bNeedRedraw)
	{
		OnPaint(m_CtrlMemDc);
		m_bNeedRedraw = false;
	}

	// ������Ч��������
	RECT DrawRct;
	INIT_RECT(DrawRct);
	DrawRct.left = (m_RectInWindow.left >= ActiveDrawRct.left) ? m_RectInWindow.left : ActiveDrawRct.left;
	DrawRct.right = (m_RectInWindow.right >= ActiveDrawRct.right) ? ActiveDrawRct.right : m_RectInWindow.right;
	DrawRct.top = (m_RectInWindow.top >= ActiveDrawRct.top) ? m_RectInWindow.top : ActiveDrawRct.top;
	DrawRct.bottom = (m_RectInWindow.bottom >= ActiveDrawRct.bottom) ? ActiveDrawRct.bottom : m_RectInWindow.bottom;

	// ���Ƶ����ڵ�DC��
	int nWidth = RECT_WIDTH(DrawRct);
	int nHeight = RECT_HEIGHT(DrawRct);
	if (GetControlAlpha() == 255)
	{
		m_pUiEngine->AlphaBlend(WndMemDc, DrawRct.left, DrawRct.top, nWidth, nHeight,
			m_CtrlMemDc, DrawRct.left - m_RectInWindow.left, DrawRct.top - m_RectInWindow.top, nWidth, nHeight);
	}
	else
	{
		// ��Ҫ��͸����ʾ�ؼ� TBD
	}

	// �����ӿؼ�
	for (CHILD_CTRLS_VEC::iterator pCtrlItem = m_ChildCtrlsVec.begin(); pCtrlItem != m_ChildCtrlsVec.end(); pCtrlItem++)
	{
		IControlBase* pCtrl = *pCtrlItem;
		if (pCtrl != NULL)
			pCtrl->OnPaintControl(WndMemDc, DrawRct);
	}
}

// ������Ч�Ļ�������
void IControlBase::SetActiveDrawRect(RECT ActiveDrawRect)
{

}
