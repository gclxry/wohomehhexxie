
#include "StdAfx.h"
#include "ICtrlPanelImpl.h"
#include "..\..\Inc\IControlManager.h"

ICtrlPanelImpl::ICtrlPanelImpl(void)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_BASE_PANEL);

	m_pPropImage = NULL;
}

ICtrlPanelImpl::~ICtrlPanelImpl(void)
{
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlPanelImpl::CreateControlPropetry(bool bNeedSetDftProp)
{
	m_pPropImage = (IPropertyImage*)CreatePropetry(NULL, OTID_IMAGE, "Image", "����ͼƬ");
	IPropertyGroup* pPropGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "BkGroup", "����Group");
	CreatePropetry(pPropGroup, OTID_CURSOR, "BkCursor", "����Cursor");
	CreatePropetry(pPropGroup, OTID_FONT, "BkFont", "����font");
//	CreatePropetry(pPropGroup, OTID_FONT, "BkFont1", "����font1");
	return true;
}

// ��ʼ���ؼ�
void ICtrlPanelImpl::OnCreate()
{
}

// �ؼ���ʼ�����
void ICtrlPanelImpl::OnFinalCreate()
{
}

// ���ٿؼ�
void ICtrlPanelImpl::OnDestroy()
{
}

// ���ƿؼ�
void ICtrlPanelImpl::OnPaint(CDrawingBoard &DrawBoard)
{
	if (m_pPropImage != NULL)
		m_pPropImage->DrawImage(DrawBoard, this->GetClientRect());
}
