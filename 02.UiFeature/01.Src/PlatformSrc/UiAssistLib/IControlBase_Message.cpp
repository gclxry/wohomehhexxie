
#include "StdAfx.h"
#include "..\..\Inc\IControlBase.h"
#include "..\..\Inc\UiFeatureDefs.h"
#include "..\..\Inc\IControlBase.h"

void IControlBase::OnCtrlMessage(int nMsgId, WPARAM wParam, LPARAM lParam)
{
	switch (nMsgId)
	{
		// ��ʼ���ؼ�
	case CM_Create:
		OnCreate();
		break;

		// �ؼ���ʼ�����
	case CM_FinalCreate:
		OnFinalCreate();
		break;

		// Builderˢ������
	case CM_BuilderRefreshProp:
		OnBuilderRefreshProp();
		break;

		// ������
	case CM_MouseEnter:
		break;

		// ����Ƴ�
	case CM_MouseLeave:
		OnMouseLeave();
		break;

		// ����ƶ�
	case CM_MouseMove:
		break;

		// ���������
	case CM_LButtonDown:
		break;

		// ������̧��
	case CM_LButtonUp:
		break;

		// ������˫��
	case CM_LButtonDbClick:
		break;

		// ����Ҽ����
	case CM_RButtonDown:
		break;

		// �ƶ������ÿؼ�λ��
	case CM_Size:
		OnSize();
		break;

		// ���ƿؼ�
	case CM_Paint:
		break;

		// �ƶ����ڿ�ʼ
	case CM_EnterSizeMove:
		OnEnterSizeMove();
		break;

		// �ƶ����ڽ���
	case CM_ExitSizeMove:
		OnExitSizeMove();
		break;

		// ���ٿؼ�
	case CM_Destroy:
		OnDestroy();
		break;

		// �ؼ�ȡ�ý��㣬ͨ��Tab����ת������ؼ�
	case CM_SetFocus:
		OnSetFocus();
		break;

		// �ؼ�ʧȥ����
	case CM_KillFocus:
		OnKillFocus();
		break;

		// �ؼ�ȡ�ü���������Ϣ
	case CM_Char:
		OnChar(wParam, lParam);
		break;

		// ���ܵ�Ĭ�ϻس�����Ϣ
	case CM_DefaultEnterCtrl:
		OnDefaultEnterCtrl();
		break;

	default:
		OnNotification(nMsgId, wParam, lParam);
		break;
	}
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
