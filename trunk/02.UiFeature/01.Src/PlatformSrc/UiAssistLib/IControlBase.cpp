
#include "StdAfx.h"
#include "..\..\Inc\IControlBase.h"
#include "..\..\Inc\IWindowBase.h"
#include "..\..\Inc\UiFeatureDefs.h"

IControlBase::IControlBase()
{
	SetObjectType("ControlBase");
	m_pUiEngine = NULL;
	m_pOwnerWindowBase = NULL;
	m_pParentCtrl = NULL;
	m_ChildCtrlsVec.clear();

	m_pXmlPropCtrl = NULL;
	m_pSkinPropMgr = NULL;

	m_bNeedRedraw = true;
	m_bMouseHover = false;

	memset(&m_BD_FangKuai8, 0, sizeof(FANGKUAI_8));
	// Ƥ����������
	m_pSkinPropMgr = NULL;
	// ��¼��xml�е�����
	m_pXmlPropCtrl = NULL;
	// Group:base
	m_pPropGroupBase = NULL;
	// base-��������
	m_pPropBase_TypeName = NULL;
	// base-objectid
	m_pPropBase_ObjectId = NULL;
	// base-name
	m_pPropBase_Name = NULL;
	// base-lock
	m_pPropBase_Lock = NULL;
	// base-visible
	m_pPropBase_Visible = NULL;
	// base-ReceiveMouseMessage
	m_pPropBase_RcvMouseMsg = NULL;
	// base-enable
	m_pPropBase_Enable = NULL;
	// base-dragInCtrl
	m_pPropBase_DragInCtrl = NULL;
	// base-taborder
	m_pPropBase_TabOrder = NULL;
	// base-defaultenterctrl
	m_pPropBase_DefaultEnterCtrl = NULL;
	// base-layout
	m_pPropBase_LayoutGroup = NULL;
	// layout-width
	m_pPropBase_Layout_Width = NULL;
	// layout-height
	m_pPropBase_Layout_Height = NULL;

	// layout-leftspace
	m_pPropBase_Layout_Layout = NULL;
	// layout-leftspace
	m_pPropBase_Layout_LeftSpace = NULL;
	// layout-rightspace
	m_pPropBase_Layout_RightSpace = NULL;
	// layout-topspace
	m_pPropBase_Layout_TopSpace = NULL;
	// layout-bottomspace
	m_pPropBase_Layout_BottomSpace = NULL;

	// Group:CtrlDefs
	m_pPropGroupCtrlDefs = NULL;

	INIT_RECT(m_RectInWindow);
}


void IControlBase::SetUiEngine(IUiEngine *pUiEngine)
{
	if (pUiEngine != NULL)
		m_pUiEngine = pUiEngine;
}

// �õ���Builder����ʾ������8�������λ��
FANGKUAI_8* IControlBase::BD_GetFangKuai8Rect()
{
	return &m_BD_FangKuai8;
}

IControlBase::~IControlBase()
{
}

// �����δ����һ���ؼ�
void IControlBase::AppendChildContrl(IControlBase *pCtrl)
{
	if (pCtrl != NULL)
		m_ChildCtrlsVec.push_back(pCtrl);
}

void IControlBase::SetOwnerWindow(IWindowBase* pWindowsBase)
{
	m_pOwnerWindowBase = pWindowsBase;
}

IWindowBase* IControlBase::GetOwnerWindow()
{
	return m_pOwnerWindowBase;
}

// ���ø��ؼ�
void IControlBase::SetParentControl(IControlBase* pParentCtrl)
{
	m_pParentCtrl = pParentCtrl;
}

// ���ø��ؼ�
IControlBase* IControlBase::GetParentControl()
{
	return m_pParentCtrl;
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
	//if (m_pOwnerWindowBase != NULL)
	//{
	//	IControlBase *pCtrl = dynamic_cast<IControlBase*>(this);
	//	m_pOwnerWindowBase->RedrawControl(pCtrl);
	//}

	m_bNeedRedraw = true;
//	SetChildCtrlToRedraw();
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
CHILD_CTRLS_VEC* IControlBase::GetChildControlsVec()
{
	return &m_ChildCtrlsVec;
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