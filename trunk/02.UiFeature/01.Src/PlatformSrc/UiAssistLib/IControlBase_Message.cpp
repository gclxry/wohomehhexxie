
#include "StdAfx.h"
#include "..\..\Inc\IControlBase.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IControlBase.h"

// ��ʼ���ؼ�
void IControlBase::OnCreate()
{

}

// �ؼ���ʼ�����
void IControlBase::OnFinalCreate()
{

}

// Builderˢ������
void IControlBase::OnRefreshProp()
{

}

// ������
void IControlBase::OnMouseEnter(POINT pt)
{

}

// ����Ƴ�
void IControlBase::OnMouseLeave()
{

}

// ����ƶ�
void IControlBase::OnMouseMove(POINT pt)
{

}

// ���������
void IControlBase::OnLButtonDown(POINT pt)
{

}

// ������̧��
void IControlBase::OnLButtonUp(POINT pt)
{

}

// ������˫��
void IControlBase::OnLButtonDbClick(POINT pt)
{

}

// ����϶��ؼ�
void IControlBase::OnMouseDrag(POINT pt)
{

}

// ����Ҽ����
void IControlBase::OnRButtonDown(POINT pt)
{

}

// �ƶ������ÿؼ�λ��
void IControlBase::OnSize()
{

}

// ���ƿؼ�
void IControlBase::OnPaint()
{

}

// �ƶ����ڿ�ʼ
void IControlBase::OnEnterSizeMove()
{

}

// �ƶ����ڽ���
void IControlBase::OnExitSizeMove()
{

}

// ���ٿؼ�
void IControlBase::OnDestroy()
{

}

// �ؼ�ȡ�ý��㣬ͨ��Tab����ת������ؼ�
void IControlBase::OnSetFocus()
{

}

// �ؼ�ʧȥ����
void IControlBase::OnKillFocus()
{

}

// �ؼ�ȡ�ü���������Ϣ
void IControlBase::OnChar(WPARAM wParam, LPARAM lParam)
{

}

// ���ܵ�Ĭ�ϻس�����ִ�пؼ�����
void IControlBase::OnEnterRun()
{

}

// ���Ƶ�ǰ�ؼ�������Ϊ������/���ؼ����ڴ�DC
void IControlBase::OnPaintControl(CMemoryDC &WndMemDc)
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
