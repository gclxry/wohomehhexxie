
#include "StdAfx.h"
#include "..\..\Inc\IControlBase.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IControlBase.h"

// ���Ƶ�ǰ�ؼ�������Ϊ������/���ؼ����ڴ�DC
void IControlBase::OnPaintControl(CDrawingBoard &WndMemDc)
{
	if (WndMemDc.GetSafeHdc() == NULL && m_pUiEngine != NULL)
		return;

	RECT RectInWnd = GetCtrlInWindowRect();
	m_CtrlMemDc.Create(RECT_WIDTH(RectInWnd), RECT_HEIGHT(RectInWnd), 0, false, m_bNeedRedraw);
	if (m_CtrlMemDc.GetBits() == NULL)
		return;

	// �ػ�ؼ�����
	if (m_bNeedRedraw)
		OnPaint();

	// ���Ƶ����ؼ���DC��
	int nWidth = RECT_WIDTH(RectInWnd);
	int nHeight = RECT_HEIGHT(RectInWnd);
	m_pUiEngine->AlphaBlend(WndMemDc, RectInWnd.left, RectInWnd.top, nWidth, nHeight,
		m_CtrlMemDc, 0, 0, nWidth, nHeight);

	// �����ӿؼ�
	for (CHILD_CTRLS_VEC::iterator pCtrlItem = m_ChildCtrlsVec.begin(); pCtrlItem != m_ChildCtrlsVec.end(); pCtrlItem++)
	{
		IControlBase* pCtrl = *pCtrlItem;
		if (pCtrl != NULL)
			pCtrl->OnPaintControl(WndMemDc);
	}
}
