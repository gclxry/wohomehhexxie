
#include "StdAfx.h"
#include "..\..\Inc\ICtrlBasePanel.h"
#include "..\..\Inc\IControlManager.h"

ICtrlBasePanel::ICtrlBasePanel(void)
{
	// ��ӿؼ�������3�����ں�ϵͳע��ؼ�
	SetObjectType(CTRL_NAME_BASE_PANEL);

	m_pPropImage = NULL;
}

ICtrlBasePanel::~ICtrlBasePanel(void)
{
}

// �����ؼ����ڴ��������Լ��Ŀؼ�����
bool ICtrlBasePanel::CreateControlPropetry(bool bNeedSetDftProp)
{
	m_pPropImage = (IPropertyImage*)CreatePropetry(NULL, OTID_IMAGE, "Image", "����ͼƬ");
	IPropertyGroup* pPropGroup = (IPropertyGroup*)CreatePropetry(NULL, OTID_GROUP, "BkGroup", "����Group");
	CreatePropetry(pPropGroup, OTID_CURSOR, "BkCursor", "����Cursor");
//	CreatePropetry(pPropGroup, OTID_FONT, "BkFont", "����font");
//	CreatePropetry(pPropGroup, OTID_FONT, "BkFont1", "����font1");
	return true;
}

// ��ʼ���ؼ�
void ICtrlBasePanel::OnCreate()
{
}

// �ؼ���ʼ�����
void ICtrlBasePanel::OnFinalCreate()
{
}

// ���ٿؼ�
void ICtrlBasePanel::OnDestroy()
{
}

// ���ƿؼ�
void ICtrlBasePanel::OnPaint(CDrawingBoard &DrawBoard)
{
	if (m_pPropImage != NULL)
		m_pPropImage->DrawImage(DrawBoard, this->GetClientRect());
}
