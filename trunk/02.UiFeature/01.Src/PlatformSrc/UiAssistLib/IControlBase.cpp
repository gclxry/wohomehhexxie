
#include "StdAfx.h"
#include "..\..\Inc\IControlBase.h"
#include "..\..\Inc\IWindowBase.h"
#include "..\..\Inc\UiFeatureDefs.h"

IControlBase::IControlBase()
{
	SetObjectType("ControlBase");
	m_pUiEngine = NULL;
	m_pParentWindowBase = NULL;
	m_ChildCtrlsVec.clear();
	m_bNeedRedraw = true;
	m_bMouseHover = false;

	InitControlPropetry();
}

IControlBase::~IControlBase()
{
}

// ���ÿؼ����´λ��Ƶ�ʱ���Ƿ���Ҫ�����ػ�
void IControlBase::SetNeedRedraw(bool bNeedRedraw)
{	
	if (!IsVisible())
	{
		m_bNeedRedraw = false;
		return;
	}

	m_bNeedRedraw = bNeedRedraw;
}

// �ػ�ؼ�������ػ涯����ʱ���е���
void IControlBase::RedrawControlInAnimationTimer()
{

}

// �ػ�ؼ�
void IControlBase::RedrawControl(bool bDrawImmediately)
{
	if (m_pParentWindowBase != NULL)
	{
		IControlBase *pCtrl = dynamic_cast<IControlBase*>(this);
		m_pParentWindowBase->RedrawControl(pCtrl);
	}

	m_bNeedRedraw = true;
	SetChildCtrlToRedraw();
}

// �����ӿؼ��������Ի�
void IControlBase::SetChildCtrlToRedraw()
{
	m_bNeedRedraw = true;
	for (CHILD_CTRLS_VEC::iterator pCtrlItem = m_ChildCtrlsVec.begin(); pCtrlItem != m_ChildCtrlsVec.end(); pCtrlItem++)
	{
		IControlBase* pCtrl = *pCtrlItem;
		if (pCtrl != NULL)
			pCtrl->SetChildCtrlToRedraw();
	}
}

// ȡ���ӿؼ��б�
CHILD_CTRLS_VEC* IControlBase::GetChildCtrlsVec()
{
	return &m_ChildCtrlsVec;
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

void IControlBase::OnPaint()
{

}

// ����Ƿ�Hover
void IControlBase::SetMouseHover(bool bHover)
{
	m_bMouseHover = bHover;
}

bool IControlBase::IsMousehover()
{
	return m_bMouseHover;
}
