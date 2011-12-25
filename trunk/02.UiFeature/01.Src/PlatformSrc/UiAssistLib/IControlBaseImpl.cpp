
#include "StdAfx.h"
#include "IControlBaseImpl.h"
#include "..\..\Inc\UiFeatureDefs.h"

IControlBaseImpl::IControlBaseImpl(void)
{
	SetObjectType("ControlBase");
	m_pUiEngine = NULL;
	m_pParentWindowBase = NULL;
	m_ChildCtrlsVec.clear();
	m_bNeedRedraw = true;
	m_bMouseHover = false;
	m_pCtrlProp = NULL;
}

IControlBaseImpl::~IControlBaseImpl(void)
{
}

// ���ÿؼ����´λ��Ƶ�ʱ���Ƿ���Ҫ�����ػ�
void IControlBaseImpl::SetNeedRedraw(bool bNeedRedraw)
{
	if (m_pCtrlProp == NULL)
		return;
	
	if (!m_pCtrlProp->IsVisible())
	{
		m_bNeedRedraw = false;
		return;
	}

	m_bNeedRedraw = bNeedRedraw;
}

// �ػ�ؼ�������ػ涯����ʱ���е���
void IControlBaseImpl::RedrawControlInAnimationTimer()
{

}

// �ػ�ؼ�
void IControlBaseImpl::RedrawControl(bool bDrawImmediately)
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
void IControlBaseImpl::SetChildCtrlToRedraw()
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
CHILD_CTRLS_VEC* IControlBaseImpl::GetChildCtrlsVec()
{
	return &m_ChildCtrlsVec;
}

// ȡ������
IPropertyControlManager* IControlBaseImpl::GetControlBaseProp()
{
	return m_pCtrlProp;
}

// ���Ƶ�ǰ�ؼ�������Ϊ������/���ؼ����ڴ�DC
void IControlBaseImpl::OnPaintControl(CMemoryDC &WndMemDc)
{
	if (m_pCtrlProp == NULL || WndMemDc.GetSafeHdc() == NULL && m_pUiEngine != NULL)
		return;

	RECT RectInWnd = m_pCtrlProp->GetCtrlInWindowRect();
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

void IControlBaseImpl::OnPaint()
{

}

// ����Ƿ�Hover
void IControlBaseImpl::SetMouseHover(bool bHover)
{
	m_bMouseHover = bHover;
}

bool IControlBaseImpl::IsMousehover()
{
	return m_bMouseHover;
}
