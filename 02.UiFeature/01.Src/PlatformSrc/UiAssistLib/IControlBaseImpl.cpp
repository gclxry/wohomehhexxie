
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

// 设置控件在下次绘制的时候是否需要进行重绘
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

// 重绘控件，这个重绘动画定时器中调用
void IControlBaseImpl::RedrawControlInAnimationTimer()
{

}

// 重绘控件
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

// 设置子控件都必须自绘
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

// 取得子控件列表
CHILD_CTRLS_VEC* IControlBaseImpl::GetChildCtrlsVec()
{
	return &m_ChildCtrlsVec;
}

// 取得属性
IPropertyControlManager* IControlBaseImpl::GetControlBaseProp()
{
	return m_pCtrlProp;
}

// 绘制当前控件，参数为父窗口/父控件的内存DC
void IControlBaseImpl::OnPaintControl(CMemoryDC &WndMemDc)
{
	if (m_pCtrlProp == NULL || WndMemDc.GetSafeHdc() == NULL && m_pUiEngine != NULL)
		return;

	RECT RectInWnd = m_pCtrlProp->GetCtrlInWindowRect();
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

void IControlBaseImpl::OnPaint()
{

}

// 鼠标是否Hover
void IControlBaseImpl::SetMouseHover(bool bHover)
{
	m_bMouseHover = bHover;
}

bool IControlBaseImpl::IsMousehover()
{
	return m_bMouseHover;
}
